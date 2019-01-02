#pragma once

#include <string>

#include "CDataBase.h"

//table name
#define TABLE_NAME_RETURN	"TReturn"
#define TABLE_DATA_RETURN		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
							'bookin_idx' INTEGER, \
							'reg_date' TEXT"

typedef struct DB_Return {
	int idx=-1;
	int bookin_idx = -1;
	std::string reg_date = "";
} DB_Return;

class CDataBaseReturn : CDataBase
{
public:
	CDataBaseReturn();
	~CDataBaseReturn();

	int AddReturn(const int index);
	int PopReturn(const int index);
	int DelReturn(const int bookin_index=-1);
	std::vector<int> GetInfo(const int index=-1);
	std::vector<DB_Return> GetDBInfo(void);
	int GetCount(const int index=-1);
private:

	static int sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName);
	static int sql_callback_get_count(void *count, int argc, char **argv, char **azColName);
};

