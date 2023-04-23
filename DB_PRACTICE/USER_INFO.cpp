// USER_INFO.cpp: 구현 파일
//

#include "pch.h"
#include "DB_PRACTICE.h"
#include "afxdialogex.h"
#include "USER_INFO.h"
#include "DB_PRACTICEDlg.h"
#include "USER.h"
#include <iostream>
#include <vector>

using namespace std;

// CUSER_INFO 대화 상자

IMPLEMENT_DYNAMIC(CUSER_INFO, CDialogEx)

CUSER_INFO::CUSER_INFO(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER_INFO, pParent)
{

}

CUSER_INFO::~CUSER_INFO()
{
}

void CUSER_INFO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUSER_INFO, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUSER_INFO::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CUSER_INFO::OnBnClickedButton5)
END_MESSAGE_MAP()


// CUSER_INFO 메시지 처리기
BOOL CUSER_INFO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT1, update_id);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CUSER_INFO::OnBnClickedButton1()
{
	
	CDBPRACTICEDlg* pmaindlg = (CDBPRACTICEDlg*)AfxGetMainWnd();
	vector<CString> data;
	CString temp,str_format;

	GetDlgItemText(IDC_EDIT1, update_id_re);
	GetDlgItemText(IDC_EDIT2, update_pw);
	GetDlgItemText(IDC_EDIT3, update_name);
	GetDlgItemText(IDC_EDIT4, update_phone);
	GetDlgItemText(IDC_EDIT5, update_home);
	
	pmaindlg->main_recode->Open(CRecordset::dynaset, "select a,b,c,d,e from abcd");

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
	str_format.Format("UPDATE abcd SET a='%s',b='%s',c='%s',d='%s',e='%s' WHERE a = '%s'", update_id, update_pw, update_name, update_phone, update_home, update_id_re);
	pmaindlg->main_db.ExecuteSQL(str_format);

	pmaindlg->main_recode->Close();

	CDialog::OnOK();
	
}

void CUSER_INFO::OnBnClickedButton5()
{
	
	CDBPRACTICEDlg* pmaindlg = (CDBPRACTICEDlg*)AfxGetMainWnd();
	CUSER* pUserDlg = (CUSER*)AfxGetMainWnd();
	CString str_format;
	GetDlgItemText(IDC_EDIT1, update_id_re);
	str_format.Format("delete from abcd where book is null and a ='%s'", update_id_re);
	pmaindlg->main_db.ExecuteSQL(str_format);
	pmaindlg->m_id_list.ResetContent();
	CDialog::OnOK();
}
