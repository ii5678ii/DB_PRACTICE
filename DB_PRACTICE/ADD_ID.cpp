// ADD_ID.cpp: 구현 파일
//

#include "pch.h"
#include "DB_PRACTICE.h"
#include "afxdialogex.h"
#include "ADD_ID.h"
#include "DB_PRACTICEDlg.h"
#include <regex>
#include<iostream>
#include<vector>

using namespace std;

// CADD_ID 대화 상자

IMPLEMENT_DYNAMIC(CADD_ID, CDialogEx)

CADD_ID::CADD_ID(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_ID, pParent)
{

}

CADD_ID::~CADD_ID()
{
}

void CADD_ID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CADD_ID, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CADD_ID::OnBnClickedButton1)
END_MESSAGE_MAP()


// CADD_ID 메시지 처리기


void CADD_ID::OnBnClickedButton1()
{
	CDBPRACTICEDlg* pdbdata = (CDBPRACTICEDlg*)AfxGetMainWnd();
	CString str_format, temp;
	vector<CString>data_values;

	GetDlgItemText(IDC_EDIT1, ID);
	GetDlgItemText(IDC_EDIT2, PW);
	GetDlgItemText(IDC_EDIT3, PW_CHECK);
	GetDlgItemText(IDC_EDIT4, NAME);
	GetDlgItemText(IDC_EDIT5, PHONE);
	GetDlgItemText(IDC_EDIT6, HOME);

	if (ID == "") {
		AfxMessageBox("ID를 입력해주세요");
		return;
	}
	if (PW == "") {
		AfxMessageBox("PW를 입력해주세요");
		return;
	}
	if (PW_CHECK == "") {
		AfxMessageBox("PW_CHECK를 입력해주세요");
		return;
	}
	if (NAME == "") {
		AfxMessageBox("NAME를 입력해주세요");
		return;
	}
	if (PHONE == "") {
		AfxMessageBox("PHONE를 입력해주세요");
		return;
	}
	if (HOME == "") {
		AfxMessageBox("HOME를 입력해주세요");
		return;
	}
	if (PW != PW_CHECK) {
		AfxMessageBox("PW와 PW_CHECK가 일치하지 않습니다.");
	}
	bool pw_check = 0;
	char ch[10] = { 0, };
	memcpy(ch, (LPSTR)(LPCSTR)ID, ID.GetLength());
	int i = 0;
	while (ch[i] != NULL) {
		if (i == 5) {
			pw_check = true;
		}
		i++;
	}
	pdbdata->main_recode->Open(CRecordset::dynaset, "select a,b from abcd");

	int a = 1;
	for (pdbdata->main_recode->MoveFirst(); !pdbdata->main_recode->IsEOF(); pdbdata->main_recode->MoveNext()) {

		int cnt = pdbdata->main_recode->GetODBCFieldCount();

		for (int i = 0; i < cnt; i++) {
			pdbdata->main_recode->SetAbsolutePosition(a);
			pdbdata->main_recode->GetFieldValue(i, temp);
			data_values.push_back(temp);
		}
		a++;

	}
	for (int i = 0; i < data_values.size(); i++) {
		if (data_values[i] == ID) {
			AfxMessageBox("이미 존재하는 ID입니다.");
			pdbdata->main_recode->Close();
			return;
		}
	}
	
	vector<string> phone_numbers;

	phone_numbers.push_back(string(CT2CA(PHONE)));
	bool phone_check=0;
	std::regex re("[01]{3}-\\d{4}-\\d{4}");
	for (const auto& number : phone_numbers) {
	
		phone_check = regex_match(number, re);
	}
	if (pw_check == false) {
		AfxMessageBox("ID는 6자리이상 입니다.");
		pdbdata->main_recode->Close();
		return;

	}
	if (phone_check == false) {
		AfxMessageBox("휴대전화 형식이 틀렸습니다.");
		pdbdata->main_recode->Close();
		return;
	}
	if ((phone_check==true)&&(pw_check==true)) {

		str_format.Format("insert into abcd (a,b,c,d,e) values ('%s','%s','%s','%s','%s')", ID, PW, NAME, PHONE, HOME);

		pdbdata->main_db.ExecuteSQL(str_format);

		this->ShowWindow(SW_HIDE);
		str_format.Format("%s 회원가입 완료 되었습니다.",ID);
		pdbdata->m_main_list.AddString(str_format);

	}
	
	pdbdata->main_recode->Close();

}
