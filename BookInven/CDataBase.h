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
	int DeleteItem(const std::string str_table_name, const int index);

	int AddNewColumn(const std::string str_table_name, const std::string str_column_name, const std::string str_column_option);
	int	ChangeColumnName(const std::string str_table_name, const std::string str_column_name, const std::string str_column_new_name);

	int DropTable(const std::string str_table_name);
};

