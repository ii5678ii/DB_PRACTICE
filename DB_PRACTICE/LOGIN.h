#pragma once
#include "afxdialogex.h"
#include <iostream>
#include <vector>
#include <afxdb.h>

using namespace std;

// CLOGIN 대화 상자

class CLOGIN : public CDialogEx
{
	DECLARE_DYNAMIC(CLOGIN)

public:
	CLOGIN(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLOGIN();

	CString ID;
	CString PW;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();


};
