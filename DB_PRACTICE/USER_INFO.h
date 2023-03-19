#pragma once
#include "afxdialogex.h"
#include<iostream>

using namespace std;

// CUSER_INFO 대화 상자

class CUSER_INFO : public CDialogEx
{
	DECLARE_DYNAMIC(CUSER_INFO)

public:
	CUSER_INFO(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUSER_INFO();
	CString update_id, update_pw, update_name, update_phone, update_home, update_id_re;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
