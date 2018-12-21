#include "CDataBaseBookInHistory.h"



CDataBaseBookInHistory::CDataBaseBookInHistory()
{
}


CDataBaseBookInHistory::~CDataBaseBookInHistory()
{
}

//DB
int CDataBaseBookInHistory::sql_callback_get_count(void *count, int argc, char **argv, char **azColName)
{
	if (count != NULL)
	{
		int *c = (int *)count;
		*c = argv[0] ? atoi(argv[0]) : 0;  //atoi(argv[0]);
	}
	return 0;
}

//DB
int CDataBaseBookInHistory::sql_callback_get_bookinfo(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_BookInHistory bookinfo;
	for (i = 0; i < argc; i++)
	{
		if (NotUsed != NULL)
		{
			std::string name = azColName[i];

			if (name == "idx")
			{
				bookinfo.idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "book_info_isbn")
			{
				bookinfo.book_info_isbn = argv[i] ? argv[i] : "";
			}
			else if (name == "book_cost")
			{
				bookinfo.book_cost = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "book_count")
			{
				bookinfo.book_count = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "provider_base_info_idx")
			{
				bookinfo.provider_base_info_idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "provie_type")
			{
				bookinfo.provie_type = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "provie_rate")
			{
				bookinfo.provie_rate = argv[i] ? std::stof(argv[i]) : 0;
			}
			else if (name == "provie_cost")
			{
				bookinfo.provie_cost = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "sale_cost")
			{
				bookinfo.sale_cost = argv[i] ? std::stoi(argv[i]) : 0;
			}
			else if (name == "reg_date")
			{
				bookinfo.reg_date = argv[i] ? argv[i] : "NULL";
			}
		}
	}

	if (NotUsed != NULL)
	{
		(*(std::vector<DB_BookInHistory> *)(NotUsed)).push_back(bookinfo);
	}

	return 0;
}

void CDataBaseBookInHistory::Delete(const int index)
{
	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		DeleteItem(std::string(TABLE_NAME_BOOK_IN_HISTORY), index);
	}
}

#if 0
std::vector<BookInHistory> CDataBaseBookInHistory::GetPeriodInfo(const std::string str_date_start, const std::string str_date_end)
{
	std::vector<BookInHistory> retProviderInfo;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command;

#if 0
		if (str_date_start == str_date_end)
		{
			sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE DATE(reg_date)=DATE('" + str_date_start + "') ORDER BY idx DESC";
		}
		else
#endif
		{
			sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE reg_date BETWEEN DATE('" + str_date_start + "') AND DATE('" + str_date_end + "') ORDER BY idx DESC";		//���� �ֱ��� ������ ����.
		}

		std::vector<DB_BookInHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_history, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int history_size = vec_history.size();

			for (int i = 0; i < history_size; i++)
			{
				DB_BookInHistory db_history = vec_history[i];

				//Get Book Info. from DB
				CDataBaseBookInfo cls_db_book_info;
				BookInfo book;
				cls_db_book_info.GetBookInfo(db_history.book_info_isbn, &book);

				//Get Provider Info. from DB
				CDataBaseProvider cls_db_provider;
				ProviderInfoBase provider_base = cls_db_provider.GetBaseInfo(db_history.provider_base_info_idx);

				int detail_index = cls_db_provider.GetDetailIndex(db_history.provider_base_info_idx);

				CDataBaseProviderDetail cls_db_provider_detail;
				int out_base_index = -1;
				ProviderInfoDetail provider_detail = cls_db_provider_detail.GetProviderDetailInfo(detail_index, &out_base_index);

				ProviderInfo provider_info;
				provider_info.base = provider_base;
				provider_info.detail = provider_detail;

				BookInHistory bookin_history;
				bookin_history.db_idx = db_history.idx;
				bookin_history.bookin_info.book_info = book;
				bookin_history.bookin_info.book_info.price = db_history.book_cost;
				bookin_history.bookin_info.count = db_history.book_count;
				bookin_history.bookin_info.provider_info = provider_info;
				bookin_history.bookin_info.provider_info.detail.provide_cost = db_history.provie_cost;
				bookin_history.bookin_info.provider_info.detail.provide_rate = db_history.provie_rate;
				bookin_history.bookin_info.provider_info.detail.provide_type = db_history.provie_type;
				bookin_history.bookin_info.sale_cost = db_history.sale_cost;
				bookin_history.reg_date = db_history.reg_date;

				retProviderInfo.push_back(bookin_history);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retProviderInfo;
}
#endif

std::vector<BookInHistory> CDataBaseBookInHistory::GetInfo(const std::string str_date_start, const std::string str_date_end)
{
	std::vector<BookInHistory> retProviderInfo;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		std::string date_where_option = "";
		if( !str_date_start.empty() && !str_date_end.empty() )
		{
			date_where_option = "WHERE DATE(reg_date) BETWEEN DATE('" + str_date_start + "') AND DATE('" + str_date_end + "') ";		//���� �ֱ��� ������ ����.
		}

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " " + date_where_option + "ORDER BY idx DESC";		//���� �ֱ��� ������ ����.

		std::vector<DB_BookInHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_history, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int history_size = vec_history.size();

			for (int i = 0; i < history_size; i++)
			{
				BookInHistory bookin_history = CvtDB_BookInHistoryToBookInHistory(vec_history[i]);

				retProviderInfo.push_back(bookin_history);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retProviderInfo;
}

std::vector<int> CDataBaseBookInHistory::GetAbleInCartIndex(const std::string isbn)
{
	std::vector<int> retIndex;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE book_info_isbn='" + isbn + " AND book_count>0 ORDER BY idx DESC";		//���� �ֱ��� ������ ����.

		std::vector<DB_BookInHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_history, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int history_size = vec_history.size();

			for (int i = 0; i < history_size; i++)
			{
				DB_BookInHistory db_history = vec_history[i];

				retIndex.push_back(db_history.idx);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retIndex;
}

#if 1
int CDataBaseBookInHistory::GetBookCount(const std::string isbn)
{
	int ret = 0;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		//SELECT SUM(COL_VALUES) FROM myTable
		std::string sql_command = "SELECT SUM(book_count) FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE book_info_isbn='" + isbn + "' AND sale_code=''";		//���� �ֱ��� ������ ����.

		int book_count = 0;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_count, &book_count, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			ret = book_count;
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}
#endif

BookInHistory CDataBaseBookInHistory::CvtDB_BookInHistoryToBookInHistory(const DB_BookInHistory db_data)
{
	BookInHistory data;

	//Get Book Info. from DB
	CDataBaseBookInfo cls_db_book_info;
	BookInfo book;
	cls_db_book_info.GetBookInfo(db_data.book_info_isbn, &book);

	//Get Provider Info. from DB
	CDataBaseProvider cls_db_provider;
	ProviderInfoBase provider_base = cls_db_provider.GetBaseInfo(db_data.provider_base_info_idx);

	int detail_index = cls_db_provider.GetDetailIndex(db_data.provider_base_info_idx);

	CDataBaseProviderDetail cls_db_provider_detail;
	int out_base_index = -1;
	ProviderInfoDetail provider_detail = cls_db_provider_detail.GetProviderDetailInfo(detail_index, &out_base_index);

	ProviderInfo provider_info;
	provider_info.base = provider_base;
	provider_info.detail = provider_detail;

	data.db_idx = db_data.idx;
	data.bookin_info.book_info = book;
	data.bookin_info.book_info.price = db_data.book_cost;
	data.bookin_info.provider_info = provider_info;
	data.bookin_info.provider_info.detail.provide_cost = db_data.provie_cost;
	data.bookin_info.provider_info.detail.provide_rate = db_data.provie_rate;
	data.bookin_info.provider_info.detail.provide_type = db_data.provie_type;
	data.bookin_info.sale_cost = db_data.sale_cost;
	data.reg_date = db_data.reg_date;

	return data;
}

BookInHistory CDataBaseBookInHistory::GetInfo(const int idx)
{
	BookInHistory retBookHistory;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE idx='" + std::to_string(idx) + "' ORDER BY idx DESC LIMIT 1";		//���� �ֱ��� ������ ����.

		std::vector<DB_BookInHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_history, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			if (vec_history.size() > 0)
			{
				retBookHistory = CvtDB_BookInHistoryToBookInHistory(vec_history[0]);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retBookHistory;
}

BookInHistory CDataBaseBookInHistory::GetLastInfo(void)
{
	BookInHistory retBookHistory;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " ORDER BY idx DESC LIMIT 1";		//���� �ֱ��� ������ ����.

		std::vector<DB_BookInHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_history, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			if (vec_history.size() > 0)
			{
				retBookHistory = CvtDB_BookInHistoryToBookInHistory(vec_history[0]);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retBookHistory;
}

//Set
int CDataBaseBookInHistory::AddBookInInfo(const DB_BookInHistory bookinfo)
{
	int ret = 0;

	//check
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	//check data
	if (check_db )
	{
		printf("BookInHistory Insert\n");

		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " (book_info_isbn, book_cost, book_count, provider_base_info_idx, provie_type, provie_rate, provie_cost, sale_cost, reg_date) VALUES (";
		sql_command += "'" + bookinfo.book_info_isbn + "', ";
		sql_command += "'" + std::to_string(bookinfo.book_cost) + "', ";
		sql_command += "'" + std::to_string(bookinfo.book_count) + "', ";
		sql_command += "'" + std::to_string(bookinfo.provider_base_info_idx) + "', ";
		sql_command += "'" + std::to_string(bookinfo.provie_type) + "', ";
		sql_command += "'" + std::to_string(bookinfo.provie_rate) + "', ";
		sql_command += "'" + std::to_string(bookinfo.provie_cost) + "', ";
		sql_command += "'" + std::to_string(bookinfo.sale_cost) + "', ";
		sql_command += "datetime('now','localtime')";
		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s ������ ���� ����!\n", TABLE_NAME_BOOK_IN_HISTORY);
			sqlite3_free(pErr);
		}
		else
		{
			//������ ������ ������ �ٸ��ٸ� å������ ������Ʈ �Ѵ�.
			CDataBaseBookInfo cls_db_book_info;

			BookInfo book;
			if (cls_db_book_info.GetBookInfo(bookinfo.book_info_isbn, &book))
			{
				//������ price�� ������ Ȯ��
				if (book.price != bookinfo.book_cost)
				{
					book.price = bookinfo.book_cost;
					//DB ������Ʈ
					cls_db_book_info.AddBookInfo(book);
				}
			}

			//Detail������ �԰� �Է� �Ѵ�.
			CDataBaseBookInHistoryDetail cls_db_book_in_detail;

			ret = 1;
		}

	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}
