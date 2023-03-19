// ADMIN.cpp: 구현 파일
//

#include "pch.h"
#include "DB_PRACTICE.h"
#include "afxdialogex.h"
#include "ADMIN.h"
#include "DB_PRACTICEDlg.h"
#include <iostream>
#include <vector>
#include<afxdb.h>

using namespace std;

// CADMIN 대화 상자

IMPLEMENT_DYNAMIC(CADMIN, CDialogEx)

CADMIN::CADMIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMIN, pParent)
{

}

CADMIN::~CADMIN()
{
}

void CADMIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_edit_admin);
}


BEGIN_MESSAGE_MAP(CADMIN, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CADMIN::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CADMIN::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CADMIN::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CADMIN::OnBnClickedButton4)
END_MESSAGE_MAP()


// CADMIN 메시지 처리기


BOOL CADMIN::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_edit_admin.InsertColumn(0, "ID",LVCFMT_LEFT, 90);
	m_edit_admin.InsertColumn(1, "PW", LVCFMT_LEFT, 90);
	m_edit_admin.InsertColumn(2, "NAME", LVCFMT_LEFT, 90);
	m_edit_admin.InsertColumn(3, "PHONE", LVCFMT_LEFT, 120);
	m_edit_admin.InsertColumn(4, "HOME", LVCFMT_LEFT, 90);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CADMIN::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CADMIN::OnBnClickedButton1()
{
	CDBPRACTICEDlg* pdbpractice = (CDBPRACTICEDlg*)AfxGetMainWnd();
	CString temp;

	int a = 0;

	//pdbpractice->database_open();
	pdbpractice->main_recode->Open(CRecordset::dynaset, "select a,b,c,d,e from abcd where book is null");
	pdbpractice->main_recode->MoveFirst();
	int check = m_edit_admin.GetHeaderCtrl()->GetItemCount();
	if (check == 2) {
		m_edit_admin.DeleteColumn(0);
		m_edit_admin.DeleteColumn(0);
		m_edit_admin.InsertColumn(0, "ID", LVCFMT_LEFT, 90);
		m_edit_admin.InsertColumn(1, "PW", LVCFMT_LEFT, 90);
		m_edit_admin.InsertColumn(2, "NAME", LVCFMT_LEFT, 90);
		m_edit_admin.InsertColumn(3, "PHONE", LVCFMT_LEFT, 120);
		m_edit_admin.InsertColumn(4, "HOME", LVCFMT_LEFT, 90);
	}

	m_edit_admin.DeleteAllItems();

	while (!pdbpractice->main_recode->IsEOF()) {
		pdbpractice->main_recode->GetFieldValue(short(0), temp);
		m_edit_admin.InsertItem(a, temp);

		pdbpractice->main_recode->GetFieldValue(short(1), temp);
		m_edit_admin.SetItemText(a, 1, temp);

		pdbpractice->main_recode->GetFieldValue(short(2), temp);
		m_edit_admin.SetItemText(a, 2, temp);

		pdbpractice->main_recode->GetFieldValue(short(3), temp);
		m_edit_admin.SetItemText(a, 3, temp);

		pdbpractice->main_recode->GetFieldValue(short(4), temp);
		m_edit_admin.SetItemText(a, 4, temp);

		pdbpractice->main_recode->MoveNext();
		a++;
	}
	
	pdbpractice->main_recode->Close();
	//pdbpractice->main_db.Close();
	

}

void CADMIN::OnBnClickedButton3()
{
	CDBPRACTICEDlg* pdbpractice = (CDBPRACTICEDlg*)AfxGetMainWnd();
	CString str_format,BOOK,temp;
	vector<CString>data;

	GetDlgItemText(IDC_EDIT1, BOOK);
	if (BOOK == "") {
		AfxMessageBox("추가할 도서명을 입력해 주세요");
		return;
	}
	pdbpractice->main_recode->Open(CRecordset::dynaset, "select book from abcd");

	int a = 1;
	for (pdbpractice->main_recode->MoveFirst(); !pdbpractice->main_recode->IsEOF(); pdbpractice->main_recode->MoveNext()) {

		int cnt = pdbpractice->main_recode->GetODBCFieldCount();

		for (int i = 0; i < cnt; i++) {
			pdbpractice->main_recode->SetAbsolutePosition(a);
			pdbpractice->main_recode->GetFieldValue(i, temp);
			data.push_back(temp);
			
			
		}
		a++;
		
	}
	for (int i = 0; i < data.size(); i++) {
		
		if (temp == BOOK) {
			AfxMessageBox("이미 등록된 도서입니다.");
			pdbpractice->main_recode->Close();
			return;
		}
	}

	str_format.Format("insert into abcd (book) values('%s')", BOOK);
	pdbpractice->main_db.ExecuteSQL(str_format);

	pdbpractice->main_recode->Close();
	//pdbpractice->database_open();
	
	int check = m_edit_admin.GetHeaderCtrl()->GetItemCount();
	
	if (check == 5) {
		m_edit_admin.DeleteColumn(0);
		m_edit_admin.DeleteColumn(0);
		m_edit_admin.DeleteColumn(0);
		m_edit_admin.DeleteColumn(0);
		m_edit_admin.DeleteColumn(0);
		m_edit_admin.InsertColumn(0, "book", LVCFMT_LEFT, 90);
		m_edit_admin.InsertColumn(1, "대여상황", LVCFMT_LEFT, 90);
	}


	
	pdbpractice->main_recode->Open(CRecordset::dynaset, "select book,a from abcd where book is not null");
	pdbpractice->main_recode->MoveFirst();
	int c = 0;

	m_edit_admin.DeleteAllItems();

	while (!pdbpractice->main_recode->IsEOF()) {
		pdbpractice->main_recode->GetFieldValue(short(0), temp);
		m_edit_admin.InsertItem(c, temp);

		pdbpractice->main_recode->GetFieldValue(short(1), temp);
		if (temp == "") {
			m_edit_admin.SetItemText(c, 1, "대여 가능");

		}
		else {
			m_edit_admin.SetItemText(c, 1, "대여 중");
		}

		pdbpractice->main_recode->MoveNext();
		c++;
	}


	pdbpractice->main_recode->Close();
	//pdbpractice->main_db.Close();
}

void CADMIN::OnBnClickedButton4()
{
	CDBPRACTICEDlg* pdbpractice = (CDBPRACTICEDlg*)AfxGetMainWnd();
	CString delete_book;
	CString str_format,temp;
	vector<CString> data;
	GetDlgItemText(IDC_EDIT1, delete_book);
	if (delete_book == "") {
		AfxMessageBox("삭제할 도서명을 입력해 주세요");
		return;
	}
	//pdbpractice->database_open();
	
	

	pdbpractice->main_recode->Open(CRecordset::dynaset, "select book from abcd");

	int a = 1;
	for (pdbpractice->main_recode->MoveFirst(); !pdbpractice->main_recode->IsEOF(); pdbpractice->main_recode->MoveNext()) {

		int cnt = pdbpractice->main_recode->GetODBCFieldCount();

		for (int i = 0; i < cnt; i++) {
			
			pdbpractice->main_recode->SetAbsolutePosition(a);
			pdbpractice->main_recode->GetFieldValue(i, temp);
			data.push_back(temp);

		}
		a++;

	}
	
	for (int i = 0; i < data.size(); i++) {

		if (data[i] == delete_book) {
			str_format.Format("delete from abcd where book = '%s'", delete_book);
			pdbpractice->main_db.ExecuteSQL(str_format);
			str_format.Format("%s가 삭제 되었습니다.", delete_book);
			AfxMessageBox(str_format);
		}

	}
	
	pdbpractice->main_recode->Close();


	//view
	pdbpractice->main_recode->Open(CRecordset::dynaset, "select book,a from abcd where book is not null");
	pdbpractice->main_recode->MoveFirst();
	int c = 0;

	m_edit_admin.DeleteAllItems();

	while (!pdbpractice->main_recode->IsEOF()) {
		pdbpractice->main_recode->GetFieldValue(short(0), temp);
		m_edit_admin.InsertItem(c, temp);

		pdbpractice->main_recode->GetFieldValue(short(1), temp);
		if (temp == "") {
			m_edit_admin.SetItemText(c, 1, "대여 가능");

		}
		else {
			m_edit_admin.SetItemText(c, 1, "대여 중");
		}

		pdbpractice->main_recode->MoveNext();
		c++;
	}


	pdbpractice->main_recode->Close();
	//pdbpractice->main_db.Close();

}
