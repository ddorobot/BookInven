#pragma once

#include <string>

#include "CDataBase.h"
#include "CDataBaseBookInfo.h"
#include "CDataBaseProvider.h"
#include "CDataBaseProviderDetail.h"
#include "CDataBaseBookInHistoryDetail.h"
#include "CDataBaseBookSaleHistory.h"

#include "BookInInfo.h"

//table name
#define TABLE_NAME_BOOK_IN_HISTORY		"TBookInHistory"
#define TABLE_DATA_BOOK_IN_HISTORY		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
										'book_info_isbn' TEXT, \
										'book_info_copy_from_detail_idx' INTEGER DEFAULT -1, \
										'book_cost' INTEGER, \
										'book_count' INTEGER, \
										'provider_base_info_idx' INTEGER, \
										'provie_type' INTEGER, \
										'provie_rate' FLOAT, \
										'provie_cost' INTEGER, \
										'sale_cost' INTEGER, \
										'reg_date' TEXT"

typedef struct DB_BookInHistory {
	int idx=-1;
	std::string book_info_isbn = "";
	int book_info_copy_from_detail_idx = -1;
	int book_cost = 0;
	int book_count = 0;
	int provider_base_info_idx = -1;
	int provie_type = -1; 
	float provie_rate = 0.0;
	int provie_cost = 0;
	int sale_cost = 0;
	std::string reg_date = "";

} DB_BookInHistory;

typedef struct BookInHistory {
	int db_idx = -1;
	int copy_from_detail_idx = -1;
	BookIn_Info bookin_info;
	std::string reg_date = "";
} BookInHistory;

class CDataBaseBookInHistory : CDataBase
{
public:
	CDataBaseBookInHistory();
	~CDataBaseBookInHistory();

	//Book Info
	int GetBookCount(const std::string isbn);
	int AddBookInInfo(const DB_BookInHistory bookinfo);
	int Refund(std::vector<int> vec_copy_from_detail_index);
	BookInHistory GetLastInfo(void);
	BookInHistory GetInfo(const int idx);
	
	std::vector<BookInHistory> GetInHistory(const std::string str_date_start="", const std::string str_date_end="");
	void Delete(const int index);
	int GetAbleInCartIndex(const std::string isbn);
	int PushPopCount(const int index, const int count, const int type);

private:
	static int sql_callback_get_bookinfo(void *NotUsed, int argc, char **argv, char **azColName);
	static int sql_callback_get_count(void *count, int argc, char **argv, char **azColName);

	DB_BookInHistory GetInfoBookInfoHistory(const int idx);
	BookInHistory CvtDB_BookInHistoryToBookInHistory(const DB_BookInHistory db_data);
};

