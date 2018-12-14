#pragma once

#include <string>

#include "CDataBase.h"
#include "CDataBaseBookInfo.h"
#include "CDataBaseProvider.h"
#include "CDataBaseProviderDetail.h"

#include "BookInInfo.h"

//table name
#define TABLE_NAME_BOOK_IN_HISTORY		"TBookInHistory"
#define TABLE_DATA_BOOK_IN_HISTORY		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
										'book_info_isbn' TEXT, \
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
	int book_cost = 0;
	int book_count = 0;
	int provider_base_info_idx = -1;
	int provie_type = -1;
	int provie_rate = 0.0;
	int provie_cost = 0.0;
	int sale_cost = 0.0;
	std::string reg_date = "";

} DB_BookInHistory;

typedef struct BookInHistory {
	int db_idx = -1;
	BookIn_Info bookin_info;
	std::string reg_date = "";
} BookInHistory;

class CDataBaseBookInHistory : CDataBase
{
public:
	CDataBaseBookInHistory();
	~CDataBaseBookInHistory();

	//Book Info
	int AddBookInInfo(const BookIn_Info bookinfo);
	BookInHistory GetLastInfo(void);
	std::vector<BookInHistory> GetPeriodInfo(const std::string str_date_start, const std::string str_date_end);
	std::vector<BookInHistory> GetAllInfo(void);
	void Delete(const int index);

private:
	static int sql_callback_get_bookinfo(void *NotUsed, int argc, char **argv, char **azColName);
};

