#pragma once

#include <string>

#include "CDataBase.h"

enum book_trade_type
{
	trade_in,
	trade_sale,
	trade_refund,
	trade_return,
	trade_size
};

//table name
#define TABLE_NAME_BOOK_IN_HISTORY_DETAIL		"TBookInHistoryDetail"
#define TABLE_DATA_BOOK_IN_HISTORY_DETAIL		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
												'base_idx' INTEGER, \
												'book_count' INTEGER, \
												'type' INTEGER, \
												'type_code' TEXT, \
												'reg_date' TEXT"

typedef struct DB_BookInHistoryDetail {
	int idx=-1;
	int base_idx = -1;
	int book_count = 0;
	int type = -1;
	std::string type_code = "";
	std::string reg_date = "";

} DB_BookInHistoryDetail;

class CDataBaseBookInHistoryDetail : CDataBase
{
public:
	CDataBaseBookInHistoryDetail();
	~CDataBaseBookInHistoryDetail();

private:
};

