
#include <afxdb.h>
#include <iostream>
#include <vector>

using namespace std;

#pragma once

class CDatabaseDB
{
public:
	CDatabase main_db;
	CRecordset* main_recode;
	vector<CString> data_values;

	void database_open();
	//void database_record(CString table_name);
	void database_record();

};

