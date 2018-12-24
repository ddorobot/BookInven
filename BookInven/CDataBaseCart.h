#pragma once

#include <string>

#include "CDataBase.h"

//table name
#define TABLE_NAME_CART		"TCart"
#define TABLE_DATA_CART		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
							'bookin_idx' INTEGER, \
							'reg_date' TEXT"

typedef struct DB_Cart {
	int idx=-1;
	int bookin_idx = -1;
	std::string reg_date = "";
} DB_Cart;

class CDataBaseCart : CDataBase
{
public:
	CDataBaseCart();
	~CDataBaseCart();

	int AddCart(const int index);
	int PopCart(const int index);
	std::vector<int> GetInfo(const int index=-1);
	std::vector<DB_Cart> GetDBInfo(void);
	int GetCount(const int index=-1);
private:

	static int sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName);
	static int sql_callback_get_count(void *count, int argc, char **argv, char **azColName);
};

