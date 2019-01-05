#include "CDataBaseBookReturnHistory.h"



CDataBaseBookReturnHistory::CDataBaseBookReturnHistory()
{
}


CDataBaseBookReturnHistory::~CDataBaseBookReturnHistory()
{
}

BookReturnHistory CDataBaseBookReturnHistory::GetInfo(const int idx)
{
	BookReturnHistory book_return_info;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_RETURN_HISTORY), std::string(TABLE_DATA_BOOK_RETURN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_RETURN_HISTORY) + " WHERE idx='" + std::to_string(idx) + "' ORDER BY idx DESC LIMIT 1";		//가장 최근의 정보를 얻어옴.

		std::vector<DB_BookReturnHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_info, &vec_history, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int history_size = vec_history.size();

			if (history_size > 0)
			{
				DB_BookReturnHistory db_history = vec_history[0];

				BookReturnHistory return_info;
				return_info = db_history.return_info;

				book_return_info = return_info;
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return book_return_info;
}

BookReturnHistory CDataBaseBookReturnHistory::GetInfo(const std::string code)
{
	BookReturnHistory book_return_info;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_RETURN_HISTORY), std::string(TABLE_DATA_BOOK_RETURN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_RETURN_HISTORY) + " WHERE code='" + code + "' ORDER BY idx DESC LIMIT 1";		//가장 최근의 정보를 얻어옴.

		std::vector<DB_BookReturnHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_info, &vec_history, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int history_size = vec_history.size();

			if ( history_size > 0 )
			{
				DB_BookReturnHistory db_history = vec_history[0];

				BookReturnHistory return_info;
				return_info = db_history.return_info;

				book_return_info = return_info;
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return book_return_info;
}

std::vector<BookReturnHistory> CDataBaseBookReturnHistory::GetInfo(const std::string str_date_start, const std::string str_date_end)
{
	std::vector<BookReturnHistory> rer_vec_book_return_info;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_RETURN_HISTORY), std::string(TABLE_DATA_BOOK_RETURN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		std::string date_where_option = "";
		if (!str_date_start.empty() && !str_date_end.empty())
		{
			date_where_option = "WHERE DATE(reg_date) BETWEEN DATE('" + str_date_start + "') AND DATE('" + str_date_end + "') ";		//가장 최근의 정보를 얻어옴.
		}

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_RETURN_HISTORY) + " " + date_where_option + "ORDER BY idx DESC";		//가장 최근의 정보를 얻어옴.

		std::vector<DB_BookReturnHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_info, &vec_history, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int history_size = vec_history.size();

			for (int i = 0; i < history_size; i++)
			{
				DB_BookReturnHistory db_history = vec_history[i];

				BookReturnHistory return_info;
				return_info = db_history.return_info;

				rer_vec_book_return_info.push_back(return_info);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return rer_vec_book_return_info;
}

//DB
/*
#define TABLE_NAME_BOOK_RETURN_HISTORY		"TBookReturnHistory"
#define TABLE_DATA_BOOK_RETURN_HISTORY		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
											'bookin_idx' INTEGER, \
											'code' TEXT, \
											'memo' TEXT, \
											'reg_date' TEXT"
*/
int CDataBaseBookReturnHistory::sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_BookReturnHistory return_info;
	for (i = 0; i < argc; i++)
	{
		if (NotUsed != NULL)
		{
			std::string name = azColName[i];

			if (name == "idx")
			{
				return_info.idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "bookin_idx")
			{
				return_info.return_info.bookin_idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "code")
			{
				return_info.return_info.code = argv[i] ? argv[i] : "";
			}
			else if (name == "memo")
			{
				return_info.return_info.memo = argv[i] ? argv[i] : "";
			}
			else if (name == "reg_date")
			{
				return_info.return_info.reg_date = argv[i] ? argv[i] : "";
			}
		}
	}

	if (NotUsed != NULL)
	{
		(*(std::vector<DB_BookReturnHistory> *)(NotUsed)).push_back(return_info);
	}

	return 0;
}

std::string CDataBaseBookReturnHistory::MakeCode(void)
{
	//날짜와 시간, 랜덤숫자을 조합
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

	//boost::format f = boost::format("%s-%02d-%02d %02d:%02d:%02d")
	boost::format f = boost::format("%s%02d%02d%02d%02d%02d_RET_")
		% now.date().year_month_day().year
		% now.date().year_month_day().month.as_number()
		% now.date().year_month_day().day.as_number()
		% now.time_of_day().hours()
		% now.time_of_day().minutes()
		% now.time_of_day().seconds();

	std::string code = f.str() ;

	//random char
	srand(time(NULL));

	const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	const int random_str_size = 4;
	for (int i = 0; i < random_str_size; ++i) {
		code += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return code;
}

//Set
std::string CDataBaseBookReturnHistory::AddBookReturnInfo(const BookReturnHistory return_bookinfo)
{
	std::string ret_code = "";

	//check
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_RETURN_HISTORY), std::string(TABLE_DATA_BOOK_RETURN_HISTORY));

	//check data
	if (check_db )
	{
		printf("BookReturnInfo Insert\n");

		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
/*
#define TABLE_NAME_BOOK_RETURN_HISTORY		"TBookReturnHistory"
#define TABLE_DATA_BOOK_RETURN_HISTORY		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
											'bookin_idx' INTEGER, \
											'code' TEXT, \
											'memo' TEXT, \
											'reg_date' TEXT"
*/

		std::string return_code = MakeCode();

		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_BOOK_RETURN_HISTORY) + " (bookin_idx, code, memo, reg_date) VALUES (";
		sql_command += "'" + std::to_string(return_bookinfo.bookin_idx) + "', ";
		sql_command += "'" + return_code + "', ";
		sql_command += "'" + return_bookinfo.memo + "', ";
		sql_command += "datetime('now','localtime')";
		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 저장 실패!\n", TABLE_NAME_BOOK_RETURN_HISTORY);
			sqlite3_free(pErr);
		}
		else
		{
			ret_code = return_code;

			//BookIn Detail정보에 결제 정보를 전송!
			int bookin_db_index = return_bookinfo.bookin_idx;

			//Detail정보에 판매 되었음을 입력
			CDataBaseBookInHistoryDetail cls_db_book_in_detail;
			if (cls_db_book_in_detail.AddDetail(bookin_db_index, -1, trade_return, ret_code))
			{
			}
			else
			{
				ret_code = "";
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret_code;
}
