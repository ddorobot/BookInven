#pragma once

#include <string>

#include "CDataBase.h"

//table name
#define TABLE_NAME_CART		"TCart"
#define TABLE_DATA_CART		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
							'bookin_idx' INTEGER, \
							'book_count' INTEGER, \
							'reg_date' TEXT"

typedef struct DB_Cart {
	int idx=-1;
	int bookin_idx = -1;
	int book_count = 0;
	std::string reg_date = "";

} DB_Cart;

class CDataBaseCart : CDataBase
{
public:
	CDataBaseCart();
	~CDataBaseCart();

private:
};

