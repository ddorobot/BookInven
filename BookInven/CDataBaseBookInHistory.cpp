#include "CDataBaseBookInHistory.h"



CDataBaseBookInHistory::CDataBaseBookInHistory()
{
	//AddNewColumn(TABLE_NAME_BOOK_IN_HISTORY, "provide_date", "TEXT");
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
			else if (name == "provide_date")
			{
				bookinfo.provide_date = argv[i] ? argv[i] : "";
			}
			else if (name == "book_info_isbn")
			{
				bookinfo.book_info_isbn = argv[i] ? argv[i] : "";
			}
			else if (name == "book_info_copy_from_detail_idx")
			{
				bookinfo.book_info_copy_from_detail_idx = argv[i] ? std::stoi(argv[i]) : -1;
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

		//같은 정보가 있는지 확인
		std::string sql_command;

#if 0
		if (str_date_start == str_date_end)
		{
			sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE DATE(reg_date)=DATE('" + str_date_start + "') ORDER BY idx DESC";
		}
		else
#endif
		{
			sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE reg_date BETWEEN DATE('" + str_date_start + "') AND DATE('" + str_date_end + "') ORDER BY idx DESC";		//가장 최근의 정보를 얻어옴.
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

std::vector<BookInHistory> CDataBaseBookInHistory::GetInHistory(const std::string str_date_start, const std::string str_date_end)
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
			date_where_option = "WHERE DATE(reg_date) BETWEEN DATE('" + str_date_start + "') AND DATE('" + str_date_end + "') ";		//가장 최근의 정보를 얻어옴.
		}

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " " + date_where_option + "ORDER BY idx DESC";		//가장 최근의 정보를 얻어옴.

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

				//입고 정보를 얻는다.
				CDataBaseBookInHistoryDetail cls_db_bookin_history_detail;
				std::vector<BookInHistoryDetail> vec_history_detail = cls_db_bookin_history_detail.GetDetail(vec_history[i].idx);
				int detail_size = vec_history_detail.size();

				for (int j = 0; j < detail_size; j++)
				{
					//입고 정보로 수량을 업데이트
					bookin_history.bookin_info.count = vec_history_detail[j].book_count;
					//입고 정보로 저장일을 업데이트
					retProviderInfo.push_back(bookin_history);
				}
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retProviderInfo;
}

int CDataBaseBookInHistory::PushPopCount(const int index, const int count, const int type)
{
	int ret = 0;

	//check
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	//check data
	if (check_db)
	{
		printf("BookInHistory Update\n");

		char* pErr=NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);
		
		//Update
		//Tablek Book
		std::string sql_command = "UPDATE " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " SET book_count=book_count+(" + std::to_string(count) + ") WHERE idx=" + std::to_string(index);

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 업데이트 실패!\n", TABLE_NAME_BOOK_IN_HISTORY);

			if (pErr)
			{
				printf("%s Error : %s\n", __func__, pErr);

				sqlite3_free(pErr);
			}
		}
		else
		{
			//Detail에 저장
			//기존의 데이타 Detail엔 환불 정보 입력
			// Detail정보에 환불를 입력 한다.
			CDataBaseBookInHistoryDetail cls_db_book_in_detail;
			if (cls_db_book_in_detail.AddDetail(index, count, type, ""))
			{
				//검증
				ret = 1;
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}

int CDataBaseBookInHistory::GetAbleInCartIndex(const std::string isbn)
{
	//가장 과거에 추가 가능한 index번호를 확인하여 리턴
	int retIndex = -1 ;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		char* pErr=NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE book_info_isbn='" + isbn + "' AND book_count>0 ORDER BY idx DESC LIMIT 1";		//가장 과거의 정보 부터

		std::vector<DB_BookInHistory> vec_history;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_history, &pErr);

		if (nResult)
		{
			if (pErr)
			{
				printf("Error(%s) = %s\n", __func__, pErr);

				sqlite3_free(&pErr);
			}
		}
		else
		{
			int history_size = vec_history.size();

			if (history_size > 0)
			{
				DB_BookInHistory db_history = vec_history[0];

				retIndex = db_history.idx;
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

		//같은 정보가 있는지 확인
		//SELECT SUM(COL_VALUES) FROM myTable
		std::string sql_command = "SELECT SUM(book_count) FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE book_info_isbn='" + isbn + "'";		//가장 최근의 정보를 얻어옴.

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
	data.bookin_info.count = db_data.book_count;
	data.copy_from_detail_idx = db_data.book_info_copy_from_detail_idx;
	data.bookin_info.provide_date = db_data.provide_date;

	return data;
}

DB_BookInHistory CDataBaseBookInHistory::GetInfoBookInfoHistory(const int idx)
{
	DB_BookInHistory retBookHistory;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_IN_HISTORY), std::string(TABLE_DATA_BOOK_IN_HISTORY));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE idx='" + std::to_string(idx) + "' ORDER BY idx DESC LIMIT 1";		//가장 최근의 정보를 얻어옴.

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
				retBookHistory = vec_history[0];
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retBookHistory;
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

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " WHERE idx='" + std::to_string(idx) + "' ORDER BY idx DESC LIMIT 1";		//가장 최근의 정보를 얻어옴.

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

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " ORDER BY idx DESC LIMIT 1";		//가장 최근의 정보를 얻어옴.

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

int CDataBaseBookInHistory::Refund(std::vector<int> vec_copy_from_detail_index)
{
	int ret = 0;

	int refund_cost = 0;
	int refund_size = vec_copy_from_detail_index.size();

	std::vector<int> vec_refund_index;
	for (int i = 0; i < refund_size; i++)
	{
		int copy_from_detail_index = vec_copy_from_detail_index[i];

		//Detail 정보를 읽어 온다. 
		CDataBaseBookInHistoryDetail cls_db_bookin_history_detail;
		DB_BookInHistoryDetail bookin_history_detail = cls_db_bookin_history_detail.GetDetail_DB(copy_from_detail_index);

		//기존의 데이타 Detail엔 환불 정보 입력
		// Detail정보에 환불를 입력 한다.
		CDataBaseBookInHistoryDetail cls_db_book_in_detail;
		if (cls_db_book_in_detail.AddDetail(bookin_history_detail.base_idx, 0/*환불로인한 수량변화는 0*/, trade_refund, bookin_history_detail.detail.type_code))
		{
			//기존 데이타에 환불처리가 완료 되면 재입고 처리.
			//History 정보를 읽어 온다.
			DB_BookInHistory bookin_history = GetInfoBookInfoHistory(bookin_history_detail.base_idx);

			//어디서 복사 되었는지 데이타를 넣어 준다.
			bookin_history.book_info_copy_from_detail_idx = bookin_history_detail.idx;
			bookin_history.book_count = 1;		//환불로 인한 수량은 1
			bookin_history.reg_date = "";		//비워두어야 현재 시간으로 업데이트가 됨.

			if (AddBookInInfo(bookin_history))			//입고(환불) 정보에 저장
			{
				refund_cost -= bookin_history.sale_cost;
				vec_refund_index.push_back(i);
			}
		}
	}
	//Copy(Add)
	
	//
	//-------
	//-----------------------------------------------------------------
	//판매 정보에 환불로 (-가격) 정보 저장
	refund_size = vec_refund_index.size();

	BookSaleHistory book_sale_info;

	book_sale_info.count = refund_size;
	book_sale_info.discount = 0;
	book_sale_info.cash = cash;
	book_sale_info.sale_cost = refund_cost;
	book_sale_info.memo = "관리자 환불 처리";

	CDataBaseBookSaleHistory cls_db_book_sale_history;
	std::string code = cls_db_book_sale_history.AddBookSaleInfo(book_sale_info);

	int refunc_run_count = 0;
	for (int i = 0; i < refund_size; i++)
	{
		int copy_from_detail_index = vec_copy_from_detail_index[vec_refund_index[i]];

		//Detail 정보를 읽어 온다. 
		CDataBaseBookInHistoryDetail cls_db_bookin_history_detail;
		DB_BookInHistoryDetail bookin_history_detail = cls_db_bookin_history_detail.GetDetail_DB(copy_from_detail_index);

		//기존의 데이타 Detail엔 환불 정보 입력
		// Detail정보에 환불를 입력 한다.
		CDataBaseBookInHistoryDetail cls_db_book_in_detail;
		//기존 데이타에 환불처리가 완료 되면 재입고 처리.
		//History 정보를 읽어 온다.
		DB_BookInHistory bookin_history = GetInfoBookInfoHistory(bookin_history_detail.base_idx);

		if (!code.empty())		//판매(환불)코드로 Detail 리스트 저장
		{
			//BookIn Detail정보에 결제 정보를 전송!
			int bookin_db_index = bookin_history_detail.base_idx;
			//Detail정보에 환불을 입력 한다.
			if (cls_db_book_in_detail.AddDetail(bookin_db_index, -1, trade_refund, code))
			{
				refunc_run_count++;
			}
		}
	}
	//판매 정보에 환불로 (-가격) 정보 저장
	//-----------------------------------------------------------------
	//-------

	if (refunc_run_count == vec_copy_from_detail_index.size())
	{
		ret = 1;
	}

	return ret;
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
		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_BOOK_IN_HISTORY) + " (provide_date, book_info_isbn, book_info_copy_from_detail_idx, book_cost, book_count, provider_base_info_idx, provie_type, provie_rate, provie_cost, sale_cost, reg_date) VALUES (";
		sql_command += "'" + bookinfo.provide_date + "', ";
		sql_command += "'" + bookinfo.book_info_isbn + "', ";
		sql_command += "'" + std::to_string(bookinfo.book_info_copy_from_detail_idx) + "', ";
		sql_command += "'" + std::to_string(bookinfo.book_cost) + "', ";
		sql_command += "'" + std::to_string(bookinfo.book_count) + "', ";
		sql_command += "'" + std::to_string(bookinfo.provider_base_info_idx) + "', ";
		sql_command += "'" + std::to_string(bookinfo.provie_type) + "', ";
		sql_command += "'" + std::to_string(bookinfo.provie_rate) + "', ";
		sql_command += "'" + std::to_string(bookinfo.provie_cost) + "', ";
		sql_command += "'" + std::to_string(bookinfo.sale_cost) + "', ";

		if (bookinfo.reg_date.empty())
		{
			sql_command += "datetime('now','localtime')";
		}
		else
		{
			sql_command += "'" + bookinfo.reg_date + "'";
		}

		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 저장 실패!\n", TABLE_NAME_BOOK_IN_HISTORY);
			sqlite3_free(pErr);
		}
		else
		{
			//가격이 기존의 정보와 다르다면 책정보를 업데이트 한다.
			CDataBaseBookInfo cls_db_book_info;

			BookInfo book;
			if (cls_db_book_info.GetBookInfo(bookinfo.book_info_isbn, &book))
			{
				//기존의 price와 같은지 확인
				if (book.price != bookinfo.book_cost)
				{
					book.price = bookinfo.book_cost;
					//DB 업데이트
					cls_db_book_info.AddBookInfo(book);
				}
			}

			//Detail정보에 입고를 입력 한다.
			BookInHistory save_data = GetLastInfo();
			CDataBaseBookInHistoryDetail cls_db_book_in_detail;

			int trade_type = trade_in;
			if (bookinfo.book_info_copy_from_detail_idx > 0)
			{
				trade_type = trade_refund;
			}

			if (cls_db_book_in_detail.AddDetail(save_data.db_idx, save_data.bookin_info.count, trade_type))
			{
				ret = 1;
			}
		}

	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}
