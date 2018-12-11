#pragma once

#include "CDataBase.h"

//table name
#define TABLE_NAME_BOOK_IN		"TBookIn"
#define TABLE_DATA_BOOK_IN		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
								'book_info_idx' INTEGER, \
								'provider_info_idx' INTEGER, \
								'count' INTEGER, \
								'provide_rate' FLOAT, \
								'provide_type' TEXT, \
								'sale_rate' FLOAT, \
								'sale_cost' INTEGER, \
								'reg_date' TEXT"

typedef struct DB_BookIn {
	int idx;
	int book_info_idx;
	int provider_info_idx;
	int count = 1;
	float provide_rate = 70.0;
	std::string provide_type = "Çö¸Å";
	float sale_rate = 0.0;
	int sale_cost = 0;
} DB_BookIn;

class CDataBaseIn : CDataBase
{
public:
	CDataBaseIn();
	~CDataBaseIn();
};
