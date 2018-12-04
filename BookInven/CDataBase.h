#pragma once

#include <string>

#include "BookInfo.h"
#include "sqlite3.h"

#define DB_PATH		"modo.db"

//table name
#define TABLE_NAME_BOOK_INFO		"TBookInfo"

class CDataBase
{
public:
	CDataBase();
	~CDataBase();

	//Book Info
	BookInfo GetBookInfo(const std::string isbn);
};

