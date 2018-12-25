#include "CDataBaseBookInHistoryDetail.h"



CDataBaseBookInHistoryDetail::CDataBaseBookInHistoryDetail()
{
}


CDataBaseBookInHistoryDetail::~CDataBaseBookInHistoryDetail()
{
}

//DB
/*
#define TABLE_NAME_BOOK_IN_HISTORY_DETAIL		"TBookInHistoryDetail"
#define TABLE_DATA_BOOK_IN_HISTORY_DETAIL		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
												'base_idx' INTEGER, \
												'book_count' INTEGER, \
												'type' INTEGER, \
												'type_code' TEXT, \
												'reg_date' TEXT"
*/
int CDataBaseBookInHistoryDetail::sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_BookInHistoryDetail bookinfo;
	for (i = 0; i < argc; i++)
	{
		if (NotUsed != NULL)
		{
			std::string name = azColName[i];

			if (name == "idx")
			{
				bookinfo.idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "base_idx")
			{
				bookinfo.base_idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "book_count")
			{
				bookinfo.detail.book_count = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "type")
			{
				bookinfo.detail.type = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "type_code")
			{
				bookinfo.detail.type_code = argv[i] ? argv[i] : "";
			}
			else if (name == "reg_date")
			{
				bookinfo.reg_date = argv[i] ? argv[i] : "";
			}
		}
	}

	if (NotUsed != NULL)
	{
		(*(std::vector<DB_BookInHistoryDetail> *)(NotUsed)).push_back(bookinfo);
	}

	return 0;
}

int CDataBaseBookInHistoryDetail::AddDetail(const int base_idx, const int count, const int type, const std::string type_code)
{
	int ret = 0;

	//check
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY_DETAIL), std::string(TABLE_DATA_BOOK_IN_HISTORY_DETAIL));

	//check data
	if (check_db)
	{
		printf("%s Insert\n", TABLE_NAME_BOOK_IN_HISTORY_DETAIL);

		char* pErr=NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
/*
#define TABLE_NAME_BOOK_IN_HISTORY_DETAIL		"TBookInHistoryDetail"
#define TABLE_DATA_BOOK_IN_HISTORY_DETAIL		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
												'base_idx' INTEGER, \
												'book_count' INTEGER, \
												'type' INTEGER, \
												'type_code' TEXT, \
												'reg_date' TEXT"
*/
		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_BOOK_IN_HISTORY_DETAIL) + " (base_idx, book_count, type, type_code, reg_date) VALUES (";
		sql_command += "'" + std::to_string(base_idx) + "', ";
		sql_command += "'" + std::to_string(count) + "', ";
		sql_command += "'" + std::to_string(type) + "', ";
		sql_command += "'" + type_code + "', ";
		sql_command += "datetime('now','localtime')";
		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 저장 실패!\n", TABLE_NAME_BOOK_IN_HISTORY_DETAIL);

			if (pErr)
			{
				printf("%s Error : %s\n", __func__, pErr);

				sqlite3_free(pErr);
			}
		}
		else
		{
			ret = 1;
		}

	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}

std::vector<DB_BookInHistoryDetail> CDataBaseBookInHistoryDetail::GetDetail_DB(const std::string code)
{
	std::vector<DB_BookInHistoryDetail> retDetail;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY_DETAIL), std::string(TABLE_DATA_BOOK_IN_HISTORY_DETAIL));

	if (check_db)
	{
		char* pErr = NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY_DETAIL) + " WHERE type_code='" + code + "' ORDER BY idx DESC";		//가장 최근의 정보를 얻어옴.

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_info, &retDetail, &pErr);

		if (nResult)
		{
			if (pErr)
			{
				printf("%s Error : %s\n", __func__, pErr);

				sqlite3_free(&pErr);
			}
		}
		else
		{
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retDetail;
}

std::vector<BookInHistoryDetail> CDataBaseBookInHistoryDetail::GetDetail(const std::string code)
{
	std::vector<BookInHistoryDetail> retDetail;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY_DETAIL), std::string(TABLE_DATA_BOOK_IN_HISTORY_DETAIL));

	if (check_db)
	{
		char* pErr = NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY_DETAIL) + " WHERE type_code=" + code + " ORDER BY idx DESC";		//가장 최근의 정보를 얻어옴.

		std::vector<DB_BookInHistoryDetail> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_info, &vec_history, &pErr);

		if (nResult)
		{
			if (pErr)
			{
				printf("%s Error : %s\n", __func__, pErr);

				sqlite3_free(&pErr);
			}
		}
		else
		{
			int history_size = vec_history.size();

			for (int i = 0; i < history_size; i++)
			{
				BookInHistoryDetail detail;
				detail = vec_history[i].detail;

				retDetail.push_back(detail);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retDetail;
}

std::vector<BookInHistoryDetail> CDataBaseBookInHistoryDetail::GetDetail(const int base_idx, const int type)
{
	std::vector<BookInHistoryDetail> retDetail;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY_DETAIL), std::string(TABLE_DATA_BOOK_IN_HISTORY_DETAIL));

	if (check_db)
	{
		char* pErr=NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY_DETAIL) + " WHERE base_idx=" + std::to_string(base_idx) + " AND type=" + std::to_string(type) + " ORDER BY idx DESC";		//가장 최근의 정보를 얻어옴.

		std::vector<DB_BookInHistoryDetail> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_info, &vec_history, &pErr);

		if (nResult)
		{
			if (pErr)
			{
				printf("%s Error : %s\n", __func__, pErr);

				sqlite3_free(&pErr);
			}
		}
		else
		{
			int history_size = vec_history.size();

			for (int i = 0; i < history_size; i++)
			{
				BookInHistoryDetail detail;
				detail = vec_history[i].detail;

				retDetail.push_back(detail);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retDetail;
}