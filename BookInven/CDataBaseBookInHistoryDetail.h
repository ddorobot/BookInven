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

const std::string str_book_trade_type[trade_size]
{
	"입고",
	"판매",
	"환불",
	"반품"
};

//table name
#define TABLE_NAME_BOOK_IN_HISTORY_DETAIL		"TBookInHistoryDetail"
#define TABLE_DATA_BOOK_IN_HISTORY_DETAIL		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
												'base_idx' INTEGER, \
												'book_count' INTEGER, \
												'type' INTEGER, \
												'type_code' TEXT, \
												'reg_date' TEXT"

typedef struct BookInHistoryDetail {
	int book_count = 0;
	int type = -1;
	std::string type_code = "";
} BookInHistoryDetail;

typedef struct DB_BookInHistoryDetail {
	int idx=-1;
	int base_idx = -1;
	BookInHistoryDetail detail;
	std::string reg_date = "";

} DB_BookInHistoryDetail;

class CDataBaseBookInHistoryDetail : CDataBase
{
public:
	CDataBaseBookInHistoryDetail();
	~CDataBaseBookInHistoryDetail();

	int AddDetail(const int base_idx, const int count, const int type, const std::string type_code="");
	std::vector<BookInHistoryDetail> GetDetail(const int base_idx=-1, const int type = trade_in);
	std::vector<BookInHistoryDetail> GetDetail(const std::string code);
	std::vector<DB_BookInHistoryDetail> GetDetail_DB(const std::string code);


private:
	static int sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName);
};

