#pragma once

#include <string>

#include "CDataBase.h"
#include "CDataBaseBookInfo.h"
#include "CDataBaseProvider.h"

#include "CSaleBooksList.h"


//table name
#define TABLE_NAME_BOOK_SALE_HISTORY		"TBookSaleHistory"
#define TABLE_DATA_BOOK_SALE_HISTORY		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
											'code' TEXT, \
											'total_count' INTEGER, \
											'discount' INTEGER, \
											'sale_cost' INTEGER, \
											'cash' BOOLEAN, \
											'memo' TEXT, \
											'reg_date' TEXT"


typedef struct BookSaleHistory {
	std::string code = "";
	int count = 0;
	int discount = 0;
	int sale_cost = 0;
	std::string memo;
	bool cash = false;
	std::string reg_date;
} BookSaleHistory;

typedef struct DB_BookSaleHistory {
	int idx=-1;
	BookSaleHistory sale_info;
} DB_BookSaleHistory;

class CDataBaseBookSaleHistory : CDataBase
{
public:
	CDataBaseBookSaleHistory();
	~CDataBaseBookSaleHistory();

	//Book Info
	std::string AddBookSaleInfo(const BookSaleHistory sale_bookinfo);
	std::vector<BookSaleHistory> GetInfo(const std::string str_date_start, const std::string str_date_end);
	BookSaleHistory GetInfo(const std::string code);

private:
	static int sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName);
	std::string MakeCode(void);
};

