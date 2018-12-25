#include "CDataBaseBookSaleHistory.h"



CDataBaseBookSaleHistory::CDataBaseBookSaleHistory()
{
}


CDataBaseBookSaleHistory::~CDataBaseBookSaleHistory()
{
}

std::vector<BookSaleHistory> CDataBaseBookSaleHistory::GetInfo(const std::string str_date_start, const std::string str_date_end)
{
	std::vector<BookSaleHistory> rer_vec_book_sale_info;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_SALE_HISTORY), std::string(TABLE_DATA_BOOK_SALE_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		std::string date_where_option = "";
		if (!str_date_start.empty() && !str_date_end.empty())
		{
			date_where_option = "WHERE DATE(reg_date) BETWEEN DATE('" + str_date_start + "') AND DATE('" + str_date_end + "') ";		//���� �ֱ��� ������ ����.
		}

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_SALE_HISTORY) + " " + date_where_option + "ORDER BY idx DESC";		//���� �ֱ��� ������ ����.

		std::vector<DB_BookSaleHistory> vec_history;

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
				DB_BookSaleHistory db_history = vec_history[i];

				BookSaleHistory sale_info;
				sale_info = db_history.sale_info;

				rer_vec_book_sale_info.push_back(sale_info);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return rer_vec_book_sale_info;
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
				sale_info.sale_info.code = argv[i] ? argv[i] : "";
			}
			else if (name == "discount")
			{
				sale_info.sale_info.discount = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "total_count")
			{
				sale_info.sale_info.count = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "sale_cost")
			{
				sale_info.sale_info.sale_cost = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "cash")
			{
				int cash = argv[i] ? std::stoi(argv[i]) : 0;

				if (cash == 0)
				{
					sale_info.sale_info.cash = false;
				}
				else
				{
					sale_info.sale_info.cash = true;
				}
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

std::string CDataBaseBookSaleHistory::MakeCode(void)
{
	//��¥�� �ð�, ���������� ����
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

	//boost::format f = boost::format("%s-%02d-%02d %02d:%02d:%02d")
	boost::format f = boost::format("%s%02d%02d%02d%02d%02d_")
		% now.date().year_month_day().year
		% now.date().year_month_day().month.as_number()
		% now.date().year_month_day().day.as_number()
		% now.time_of_day().hours()
		% now.time_of_day().minutes()
		% now.time_of_day().seconds();

	std::string code = f.str();

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
std::string CDataBaseBookSaleHistory::AddBookSaleInfo(const BookSaleHistory sale_bookinfo)
{
	std::string ret_code = "";

	//check
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_SALE_HISTORY), std::string(TABLE_DATA_BOOK_SALE_HISTORY));

	//check data
	if (check_db )
	{
		printf("BookSaleInfo Insert\n");

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

		std::string sale_code = MakeCode();

		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_BOOK_SALE_HISTORY) + " (code, total_count, discount, sale_cost, cash, reg_date) VALUES (";
		sql_command += "'" + sale_code + "', ";
		sql_command += "'" + std::to_string(sale_bookinfo.count) + "', ";
		sql_command += "'" + std::to_string(sale_bookinfo.discount) + "', ";
		sql_command += "'" + std::to_string(sale_bookinfo.sale_cost) + "', ";
		sql_command += "'" + std::to_string(sale_bookinfo.cash) + "', ";
		sql_command += "datetime('now','localtime')";
		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s ������ ���� ����!\n", TABLE_NAME_BOOK_SALE_HISTORY);
			sqlite3_free(pErr);
		}
		else
		{
			ret_code = sale_code;
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret_code;
}
