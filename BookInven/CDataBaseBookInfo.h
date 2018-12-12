#pragma once

#include "CDataBase.h"

//table name
#define TABLE_NAME_BOOK_INFO		"TBookInfo"
#define TABLE_DATA_BOOK_INFO		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
									'isbn' TEXT, \
									'name' TEXT, \
									'author' TEXT, \
									'publisher' TEXT, \
									'price' TEXT, \
									'title_url' TEXT, \
									'publish_date' TEXT, \
									'reg_date' TEXT"

typedef struct DB_BookInfo {
	int idx;
	std::string reg_date;
	BookInfo book_info;
} DB_BookInfo;


class CDataBaseBookInfo : CDataBase
{
public:
	CDataBaseBookInfo();
	~CDataBaseBookInfo();

	//Book Info
	int GetBookInfo(const std::string isbn, BookInfo *bookinfo);
	void AddBookInfo(const BookInfo bookinfo);
	DB_BookInfo GetLastInfo(void);
	void Print(void);

private:
	static int sql_callback_get_bookinfo(void *NotUsed, int argc, char **argv, char **azColName);

	bool CheckData(const BookInfo bookinfo);
	bool CheckDataSameValue(const BookInfo bookinfo);
};

