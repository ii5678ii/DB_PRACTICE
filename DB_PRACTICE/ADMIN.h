#pragma once
#include "afxdialogex.h"


// CADMIN 대화 상자

class CADMIN : public CDialogEx
{
	DECLARE_DYNAMIC(CADMIN)

public:
	CADMIN(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CADMIN();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	CListCtrl m_edit_admin;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
