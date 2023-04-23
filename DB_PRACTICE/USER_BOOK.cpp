// USER_BOOK.cpp: 구현 파일
//

#include "pch.h"
#include "DB_PRACTICE.h"
#include "afxdialogex.h"
#include "USER_BOOK.h"
#include "DB_PRACTICEDlg.h"

// CUSER_BOOK 대화 상자

IMPLEMENT_DYNAMIC(CUSER_BOOK, CDialogEx)

CUSER_BOOK::CUSER_BOOK(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER_BOOK, pParent)
{

}

CUSER_BOOK::~CUSER_BOOK()
{
}

void CUSER_BOOK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_user_book_list);
	DDX_Control(pDX, IDC_LIST1, m_user_book_ctn);
}


BEGIN_MESSAGE_MAP(CUSER_BOOK, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUSER_BOOK::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUSER_BOOK::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUSER_BOOK::OnBnClickedButton3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CUSER_BOOK::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CUSER_BOOK 메시지 처리기
BOOL CUSER_BOOK::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_user_book_ctn.InsertColumn(0, "ID", LVCFMT_LEFT, 90);
	m_user_book_ctn.InsertColumn(1, "PW", LVCFMT_LEFT, 90);
	m_user_book_ctn.InsertColumn(2, "NAME", LVCFMT_LEFT, 90);
	m_user_book_ctn.InsertColumn(3, "PHONE", LVCFMT_LEFT, 120);
	m_user_book_ctn.InsertColumn(4, "HOME", LVCFMT_LEFT, 90);
	m_user_book_list.AddString(book_id);
	//OnBnClickedButton3();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CUSER_BOOK::OnBnClickedButton1()
{
	CDBPRACTICEDlg* pmaindlg = (CDBPRACTICEDlg*)AfxGetMainWnd();
	CString str_format, temp,book_name,name,phone,home;
	GetDlgItemText(IDC_EDIT3, book_name);
	vector<CString> data;

	if (book_name == "") {

		AfxMessageBox("도서명을 입력해 주세요");
		return;

	}

	pmaindlg->main_recode->Open(CRecordset::dynaset, "select * from abcd");
	int a = 1;
	for (pmaindlg->main_recode->MoveFirst(); !pmaindlg->main_recode->IsEOF(); pmaindlg->main_recode->MoveNext()) {

		int cnt = pmaindlg->main_recode->GetODBCFieldCount();

		for (int i = 0; i < cnt; i++) {
			pmaindlg->main_recode->SetAbsolutePosition(a);
			pmaindlg->main_recode->GetFieldValue(i, temp);
			data.push_back(temp);
		}
		a++;
	}


	for (int i = 0; i < data.size(); i++) {

		if (data[i] == book_id) {
			
			name = data[i + 2];
			phone = data[i + 3];
			home = data[i + 4];

		}

	}

	/*pmaindlg->main_recode->Close();
	pmaindlg->main_recode->Open(CRecordset::dynaset, "select book,a from abcd");
	for (int i = 0; i < data.size()-1; i++) {
	
		if ((data[i] == book_name)&&(data[i+1]=="")) {
			str_format.Format("UPDATE abcd SET a='%s',b='%s',c='%s',d='%s',e='%s' WHERE book = '%s' ", book_id,book_pw,name,phone,home, book_name);
			pmaindlg->main_db.ExecuteSQL(str_format);
			str_format.Format("'%s'이(가) 대출 되었습니다.",book_name);
			AfxMessageBox(str_format);
			
		}

	}*/
	

	/*for (int i = 0; i < data.size() - 1; i++) {

		if ((data[i] == book_name)) {
			str_format.Format("UPDATE abcd SET a='%s',b='%s',c='%s',d='%s',e='%s' WHERE book = '%s' ", book_id, book_pw, name, phone, home, book_name);
			pmaindlg->main_db.ExecuteSQL(str_format);
			str_format.Format("'%s'이(가) 대출 되었습니다.", book_name);
			AfxMessageBox(str_format);

		}

	}*/

	for (int i = 5; i < data.size() - 5; i++) {

		if ((data[i] == book_name)) {
			if (data[i-4]  == "") {
				str_format.Format("UPDATE abcd SET a='%s',b='%s',c='%s',d='%s',e='%s' WHERE book = '%s' ", book_id, book_pw, name, phone, home, book_name);
				pmaindlg->main_db.ExecuteSQL(str_format);
				str_format.Format("'%s'이(가) 대출 되었습니다.", book_name);
				AfxMessageBox(str_format);
			}
			else{

				str_format.Format("'%s'이(가) 대출 중입니다.", book_name);
				AfxMessageBox(str_format);

			}

		}

	}

	int check = m_user_book_ctn.GetHeaderCtrl()->GetItemCount();

	if (check == 5) {
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.InsertColumn(0, "book", LVCFMT_LEFT, 90);
		m_user_book_ctn.InsertColumn(1, "대여상황", LVCFMT_LEFT, 90);
	}
	int c = 0;
	m_user_book_ctn.DeleteAllItems();
	
	pmaindlg->main_recode->Close();
	pmaindlg->main_recode->Open(CRecordset::dynaset, "select book,a from abcd where book is not null");

	while (!pmaindlg->main_recode->IsEOF()) {
		pmaindlg->main_recode->GetFieldValue(short(0), temp);
		m_user_book_ctn.InsertItem(c, temp);

		pmaindlg->main_recode->GetFieldValue(short(1), temp);
		if (temp == "") {
			m_user_book_ctn.SetItemText(c, 1, "대여 가능");

		}
		else {
			m_user_book_ctn.SetItemText(c, 1, "대여 중");
		}

		pmaindlg->main_recode->MoveNext();
		c++;
	}



	pmaindlg->main_recode->Close();




}


void CUSER_BOOK::OnBnClickedButton2()
{
	CDBPRACTICEDlg* pmaindlg = (CDBPRACTICEDlg*)AfxGetMainWnd();
	CString str_format, temp, book_name, name, phone, home;
	GetDlgItemText(IDC_EDIT3, book_name);
	vector<CString> data;

	if (book_name == "") {

		AfxMessageBox("도서명을 입력해 주세요");
		return;

	}

	//pmaindlg->main_recode->Open(CRecordset::dynaset, "select * from abcd");
	pmaindlg->main_recode->Open(CRecordset::dynaset, "select book,a from abcd");
	int a = 1;
	for (pmaindlg->main_recode->MoveFirst(); !pmaindlg->main_recode->IsEOF(); pmaindlg->main_recode->MoveNext()) {

		int cnt = pmaindlg->main_recode->GetODBCFieldCount();

		for (int i = 0; i < cnt; i++) {
			pmaindlg->main_recode->SetAbsolutePosition(a);
			pmaindlg->main_recode->GetFieldValue(i, temp);
			data.push_back(temp);
		}
		a++;
	}


	
	

	for (int i = 0; i < data.size() - 1; i++) {

		if ((i % 2 == 0) && (data[i] == book_name) && (!(data[i + 1] == ""))) {
			str_format.Format("UPDATE abcd SET a=null,b=null,c=null,d=null,e=null WHERE book = '%s' ", book_name);
			pmaindlg->main_db.ExecuteSQL(str_format);
			str_format.Format("'%s'이(가) 반납 되었습니다.", book_name);
			AfxMessageBox(str_format);

		}

	}


	pmaindlg->main_recode->Close();

	pmaindlg->main_recode->Open(CRecordset::dynaset, "select book,a from abcd");
	int check = m_user_book_ctn.GetHeaderCtrl()->GetItemCount();

	if (check == 5) {
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.InsertColumn(0, "book", LVCFMT_LEFT, 90);
		m_user_book_ctn.InsertColumn(1, "대여상황", LVCFMT_LEFT, 90);
	}
	int c = 0;
	m_user_book_ctn.DeleteAllItems();

	pmaindlg->main_recode->Close();
	pmaindlg->main_recode->Open(CRecordset::dynaset, "select book,a from abcd where book is not null");

	while (!pmaindlg->main_recode->IsEOF()) {
		pmaindlg->main_recode->GetFieldValue(short(0), temp);
		m_user_book_ctn.InsertItem(c, temp);

		pmaindlg->main_recode->GetFieldValue(short(1), temp);
		if (temp == "") {
			m_user_book_ctn.SetItemText(c, 1, "대여 가능");

		}
		else {
			m_user_book_ctn.SetItemText(c, 1, "대여 중");
		}

		pmaindlg->main_recode->MoveNext();
		c++;
	}



	pmaindlg->main_recode->Close();


}


void CUSER_BOOK::OnBnClickedButton3()
{
	CDBPRACTICEDlg* pmaindlg = (CDBPRACTICEDlg*)AfxGetMainWnd();
	CString temp;

	int check = m_user_book_ctn.GetHeaderCtrl()->GetItemCount();

	if (check == 5) {
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.DeleteColumn(0);
		m_user_book_ctn.InsertColumn(0, "book", LVCFMT_LEFT, 90);
		m_user_book_ctn.InsertColumn(1, "대여상황", LVCFMT_LEFT, 90);
	}
	int c = 0;
	m_user_book_ctn.DeleteAllItems();

	
	pmaindlg->main_recode->Open(CRecordset::dynaset, "select book,a from abcd where book is not null");

	while (!pmaindlg->main_recode->IsEOF()) {
		pmaindlg->main_recode->GetFieldValue(short(0), temp);
		m_user_book_ctn.InsertItem(c, temp);

		pmaindlg->main_recode->GetFieldValue(short(1), temp);
		if (temp == "") {
			m_user_book_ctn.SetItemText(c, 1, "대여 가능");

		}
		else {
			m_user_book_ctn.SetItemText(c, 1, "대여 중");
		}

		pmaindlg->main_recode->MoveNext();
		c++;
	}
	pmaindlg->main_recode->Close();
}


void CUSER_BOOK::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	clicked_index = pNMView->iItem;

	m_user_book_ctn.GetSelectionMark();
	CString temp;

	CString idNum = m_user_book_ctn.GetItemText(clicked_index, 0);
	
	SetDlgItemText(IDC_EDIT3, idNum);

	*pResult = 0;
}
