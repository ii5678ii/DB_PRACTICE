// LOGIN.cpp: 구현 파일
//

#include "pch.h"
#include "DB_PRACTICE.h"
#include "afxdialogex.h"
#include "LOGIN.h"
#include <afxdb.h>
#include "DatabaseDB.h"
#include "DB_PRACTICEDlg.h"
#include "ADMIN.h"
#include "USER.h"

// CLOGIN 대화 상자

IMPLEMENT_DYNAMIC(CLOGIN, CDialogEx)

CLOGIN::CLOGIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

CLOGIN::~CLOGIN()
{
}

void CLOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLOGIN, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLOGIN::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLOGIN 메시지 처리기


void CLOGIN::OnBnClickedButton1()
{
	CDBPRACTICEDlg* pdatabase = (CDBPRACTICEDlg*)AfxGetMainWnd();
	
	CString table_n = _T("select * from abcd");
	CString temp,str_format;
	vector<CString>data_values;
	//pdatabase->database_record();
	
	GetDlgItemText(IDC_EDIT1, ID);
	GetDlgItemText(IDC_EDIT2, PW);
	
	int flag = 0;

	if (ID == "admin" && PW == "root") {
		
		flag = 1;
		CADMIN* padmin = new CADMIN;

		padmin->Create(IDD_ADMIN);
		padmin->ShowWindow(SW_SHOW);
		//this->ShowWindow(SW_HIDE);
		CDialog::OnOK();
	}
	else {
		//pdatabase->database_open();
		flag = 2;
		pdatabase->main_recode->Open(CRecordset::dynaset, "select a,b from abcd where book is null");

		int a = 1;
		for (pdatabase->main_recode->MoveFirst(); !pdatabase->main_recode->IsEOF(); pdatabase->main_recode->MoveNext()) {

			int cnt = pdatabase->main_recode->GetODBCFieldCount();

			for (int i = 0; i < cnt; i++) {
				pdatabase->main_recode->SetAbsolutePosition(a);
				pdatabase->main_recode->GetFieldValue(i, temp);
				data_values.push_back(temp);
			}
			a++;

		}


		for (int b = 0; b < data_values.size() - 1; b++) {
			if (ID == data_values[b] && PW == data_values[b + 1]) {

				CUSER* pUSer = new CUSER;
				pUSer->Create(IDD_USER);
				pUSer->ShowWindow(SW_SHOW);

				pUSer->USER_ID = ID;
				pUSer->USER_PW = PW;

				pdatabase->main_recode->Close();
				str_format.Format("%s 로그인 되었습니다.", ID);
				pdatabase->m_main_list.AddString(str_format);
				pdatabase->m_id_list.AddString(ID);
				CDialog::OnOK();

			}
		}
	}
	
	if (!(flag == 1 || flag == 2)) {
		str_format.Format("%s는 없는 ID 입니다.", ID);
		AfxMessageBox(str_format);
	}
	
	pdatabase->main_recode->Close();
	

}
