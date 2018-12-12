#pragma once

#include <vector>
#include <string>

#include "BookInfo.h"
#include "sqlite3.h"
#include "CMyTime.h"
#include "CCheckString.h"

#pragma comment(lib, "Sqlite_static.lib")

#define DB_PATH		"modo.db"

class CDataBase
{
public:
	CDataBase();
	~CDataBase();

	int CheckExistAndCreate(const std::string str_table_name, const std::string str_table_data);
};

