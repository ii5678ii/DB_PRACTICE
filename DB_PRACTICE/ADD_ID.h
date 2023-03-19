#pragma once
#include "afxdialogex.h"
#include <iostream>
#include<vector>

using namespace std;

// CADD_ID 대화 상자

class CADD_ID : public CDialogEx
{
	DECLARE_DYNAMIC(CADD_ID)

public:
	CADD_ID(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CADD_ID();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_ID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString ID;
	CString PW;
	CString PW_CHECK;
	CString NAME;
	CString PHONE;
	CString HOME;
};
