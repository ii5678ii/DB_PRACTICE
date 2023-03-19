#pragma once
#include "afxdialogex.h"
#include <iostream>

using namespace std;

// CUSER 대화 상자

class CUSER : public CDialogEx
{
	DECLARE_DYNAMIC(CUSER)

public:
	CUSER(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUSER();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString USER_ID;
	CString USER_PW;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

};
