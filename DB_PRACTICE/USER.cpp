// USER.cpp: 구현 파일
//

#include "pch.h"
#include "DB_PRACTICE.h"
#include "afxdialogex.h"
#include "USER.h"
#include "USER_BOOK.h"
#include "USER_INFO.h"


// CUSER 대화 상자

IMPLEMENT_DYNAMIC(CUSER, CDialogEx)

CUSER::CUSER(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER, pParent)
{

}

CUSER::~CUSER()
{
}

void CUSER::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUSER, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUSER::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUSER::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUSER 메시지 처리기


void CUSER::OnBnClickedButton1()
{
	CUSER_BOOK* p_userbook = new CUSER_BOOK;
	p_userbook->book_id = USER_ID;
	p_userbook->book_pw = USER_PW;
	p_userbook->Create(IDD_USER_BOOK);
	p_userbook->ShowWindow(SW_SHOW);
	

}


void CUSER::OnBnClickedButton2()
{
	CUSER_INFO* p_user_info = new CUSER_INFO;
	p_user_info->update_id = USER_ID;
	p_user_info->update_pw = USER_PW;
	p_user_info->Create(IDD_USER_INFO);
	p_user_info->ShowWindow(SW_SHOW);

}
