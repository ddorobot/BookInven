#pragma once

#include <string>

#include "CDataBase.h"
#include "CDataBaseBookInfo.h"
#include "CDataBaseProvider.h"

#include "CSaleBooksList.h"

//table name
#define TABLE_NAME_BOOK_RETURN_HISTORY		"TBookReturnHistory"
#define TABLE_DATA_BOOK_RETURN_HISTORY		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
											'bookin_idx' INTEGER, \
											'code' TEXT, \
											'memo' TEXT, \
											'reg_date' TEXT"


typedef struct BookReturnHistory {
	std::string code = "";
	int bookin_idx = -1;
	std::string memo;
	std::string reg_date;
} BookReturnHistory;

typedef struct DB_BookReturnHistory {
	int idx=-1;
	BookReturnHistory return_info;
} DB_BookReturnHistory;

class CDataBaseBookReturnHistory : CDataBase
{
public:
	CDataBaseBookReturnHistory();
	~CDataBaseBookReturnHistory();

	//Book Info
	std::string AddBookReturnInfo(const BookReturnHistory sale_bookinfo);
	std::vector<BookReturnHistory> GetInfo(const std::string str_date_start, const std::string str_date_end);
	BookReturnHistory GetInfo(const std::string code);
	BookReturnHistory GetInfo(const int idx);

private:
	static int sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName);
	std::string MakeCode(void);
};

