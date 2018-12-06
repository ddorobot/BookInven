#pragma once

#include <vector>
#include <string>

#include "BookInfo.h"
#include "sqlite3.h"

#pragma comment(lib, "Sqlite_static.lib")

#define DB_PATH		"modo.db"

//table name
#define TABLE_NAME_BOOK_INFO		"TBookInfo"

typedef struct DB_BookInfo {
	int idx;
	std::string reg_date;
	BookInfo book_info;
} DB_BookInfo;


class CDataBase
{
public:
	CDataBase();
	~CDataBase();

	//Book Info
	int GetBookInfo(const std::string isbn, BookInfo *bookinfo);

private:
	static int sql_callback_get_bookinfo(void *NotUsed, int argc, char **argv, char **azColName);
};

