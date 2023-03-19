
// DB_PRACTICEDlg.h: 헤더 파일
//
#include "DatabaseDB.h"
#include <afxdb.h>
#pragma once


// CDBPRACTICEDlg 대화 상자
class CDBPRACTICEDlg : public CDialogEx
{
// 생성입니다.
public:
	CDBPRACTICEDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DB_PRACTICE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListBox m_main_list;
	afx_msg void OnLbnSelchangeList1();
	CDatabase main_db;
	CRecordset* main_recode;
	void database_open();
	//void database_record();
	afx_msg void OnBnClickedButton2();
	
	


	CListBox m_id_list;
};
