#pragma once
#include "afxdialogex.h"


// CUSER_BOOK 대화 상자

class CUSER_BOOK : public CDialogEx
{
	DECLARE_DYNAMIC(CUSER_BOOK)

public:
	CUSER_BOOK(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUSER_BOOK();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_user_book_list;
	CListCtrl m_user_book_ctn;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CString book_id;
	CString book_pw;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	int clicked_index;
};
