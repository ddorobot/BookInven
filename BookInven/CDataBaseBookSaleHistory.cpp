#include "CDataBaseBookSaleHistory.h"



CDataBaseBookSaleHistory::CDataBaseBookSaleHistory()
{
}


CDataBaseBookSaleHistory::~CDataBaseBookSaleHistory()
{
}

//DB
int CDataBaseBookSaleHistory::sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_BookSaleHistory sale_info;
	for (i = 0; i < argc; i++)
	{
		if (NotUsed != NULL)
		{
			std::string name = azColName[i];

			if (name == "idx")
			{
				sale_info.idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "code")
			{
				sale_info.code = argv[i] ? argv[i] : "";
			}
			else if (name == "discount")
			{
				sale_info.sale_cost = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "total_count")
			{
				sale_info.sale_cost = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "sale_cost")
			{
				sale_info.sale_cost = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "reg_date")
			{
				sale_info.reg_date = argv[i] ? argv[i] : "NULL";
			}
		}
	}

	if (NotUsed != NULL)
	{
		(*(std::vector<DB_BookSaleHistory> *)(NotUsed)).push_back(sale_info);
	}

	return 0;
}

//Set
int CDataBaseBookSaleHistory::AddBookSaleInfo(const BookSaleInfo sale_bookinfo)
{
	int ret = 0;

	//check
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_SALE_HISTORY), std::string(TABLE_DATA_BOOK_SALE_HISTORY));

	//check data
	if (check_db )
	{
		printf("BookInHistory Insert\n");

		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
/*
#define TABLE_NAME_BOOK_SALE_HISTORY		"TBookSaleHistory"
#define TABLE_DATA_BOOK_SALE_HISTORY		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
											'code' TEXT, \
											'total_count' INTEGER, \
											'discount' INTEGER, \
											'sale_cost' INTEGER, \
											'reg_date' TEXT"
*/

		std::string sale_code = "codedfdfsdfsadfsadf";
		int sale_cost = 100;
		int total_count = 100;

		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_BOOK_SALE_HISTORY) + " (code, total_count, discount, sale_cost, reg_date) VALUES (";
		sql_command += "'" + sale_code + "', ";
		sql_command += "'" + std::to_string(total_count) + "', ";
		sql_command += "'" + std::to_string(sale_bookinfo.discount) + "', ";
		sql_command += "'" + std::to_string(sale_cost) + "', ";
		sql_command += "datetime('now','localtime')";
		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 저장 실패!\n", TABLE_NAME_BOOK_SALE_HISTORY);
			sqlite3_free(pErr);
		}
		else
		{
			//Detail 저장
			int sale_book_count = sale_bookinfo.vec_sale_books_info.size();

			for (int i = 0; i < sale_book_count; i++)
			{
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}
