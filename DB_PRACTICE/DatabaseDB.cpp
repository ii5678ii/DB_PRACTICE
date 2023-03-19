#include "pch.h"
#include "DatabaseDB.h"
#include "DB_PRACTICEDlg.h"
#include <afxdb.h>

void CDatabaseDB::database_open() {

	bool check = main_db.OpenEx(_T("DSN=PostgreSQL35W;Server=localhost;PORT=5432;UID=postgres;PWD=root;Database=test"));

	if (check) {
		main_recode = new CRecordset(&main_db);
		CDBPRACTICEDlg* p_main = (CDBPRACTICEDlg*)AfxGetMainWnd();
		p_main->m_main_list.AddString(_T("DatabaseDB 연결 완료"));
	}
	else {

		AfxMessageBox(_T("Database 연결 오류"));
	}
	
}
void CDatabaseDB::database_record() {

	main_recode->Open(CRecordset::dynaset, "select * from abcd");

	for (main_recode->MoveFirst(); !main_recode->IsEOF(); main_recode->MoveNext()) {



	}


}
