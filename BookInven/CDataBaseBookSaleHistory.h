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
											'reg_date' TEXT"


typedef struct DB_BookSaleHistory {
	int idx=-1;
	std::string code = "";
	int discount = 0;
	int sale_cost = 0;
	bool cash = false;
	std::string reg_date = "";

} DB_BookSaleHistory;

typedef struct SaleBooksInfo2 {
	BookInfo book_info;
	int count = 0;
} SaleBooksInfo2;


typedef struct BookSaleInfo {
	int idx = -1;
	std::vector<SaleBooksInfo2> vec_sale_books_info;
	int discount = 0;
	bool cash = false;
} BookSaleInfo;


class CDataBaseBookSaleHistory : CDataBase
{
public:
	CDataBaseBookSaleHistory();
	~CDataBaseBookSaleHistory();

	//Book Info
	int AddBookSaleInfo(const BookSaleInfo sale_bookinfo);

private:
	static int sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName);
	std::string MakeCode(void);
};

