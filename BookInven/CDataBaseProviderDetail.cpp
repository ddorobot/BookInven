#include "CDataBaseProviderDetail.h"



CDataBaseProviderDetail::CDataBaseProviderDetail()
{
}


CDataBaseProviderDetail::~CDataBaseProviderDetail()
{
}

//Set
int CDataBaseProviderDetail::AddProviderDetailInfo(const int base_idx, const ProviderInfoDetail provider)
{
	int ret = -1;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER_DETAIL), std::string(TABLE_DATA_PROVIDER_DETAIL));
	//bool check_data = CheckData(provider);

	//check same data from DB
	//bool check_same_data = CheckDataSameValue(provider);

	//printf("check_db=%d, check_data=%d, check_same_data=%d\n", check_db, check_data, check_same_data);

	//check data
	//if (check_db && check_data && check_same_data)
	if (check_db )
	{
		printf("provider Insert\n");

		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_PROVIDER_DETAIL) + " (base_idx, tel, email, address, base_provide_rate, base_provide_type, base_calc_day, receipt_able, bank_name, bank_num, bank_author, memo, reg_date) VALUES (";
		sql_command += "" + std::to_string(base_idx) + ", ";
		sql_command += "'" + provider.tel + "', ";
		sql_command += "'" + provider.email + "', ";
		sql_command += "'" + provider.address + "', ";
		sql_command += "" + std::to_string(provider.provide_rate) + ", ";
		sql_command += "" + std::to_string(provider.provide_type) + ", ";
		sql_command += "" + std::to_string(provider.calc_day) + ", ";
		sql_command += "" + std::to_string(provider.receipt_able) + ", ";
		sql_command += "'" + provider.bank_name + "', ";
		sql_command += "'" + provider.bank_num + "', ";
		sql_command += "'" + provider.bank_author + "', ";
		sql_command += "'" + provider.memo + "', ";
		sql_command += "datetime('now','localtime')";
		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 저장 실패!\n", TABLE_NAME_PROVIDER_DETAIL);
			sqlite3_free(pErr);
		}
		else
		{
			DB_ProviderDetailInfo db_provider_detail_info = GetLastInfo();
			ret = db_provider_detail_info.idx;
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}

ProviderInfoDetail CDataBaseProviderDetail::GetProviderDetailInfo(const int idx, int* out_base_idx)
{
	ProviderInfoDetail provider_detail;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER_DETAIL), std::string(TABLE_DATA_PROVIDER_DETAIL));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER_DETAIL) + " WHERE idx=" + std::to_string(idx) + "";		//idx에 해당되는 데이타를 얻어 옴

		std::vector<DB_ProviderDetailInfo> vec_provider;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_provider, &vec_provider, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			if (vec_provider.size() > 0)
			{
				provider_detail = vec_provider[0].detail;

				if (out_base_idx != NULL)
				{
					(*out_base_idx) = vec_provider[0].base_idx;
				}
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return provider_detail;
}

bool CDataBaseProviderDetail::CheckDataSameValue(const ProviderInfoDetail provider)
{
	bool ret = false;

	//가장 최신의 데이타와 현재 입력 데이타가 같은 데이타 인지 체크
	DB_ProviderDetailInfo provider_detail_db = GetLastInfo();

#if 0
	if (bookinfo.isbn == bookinfo_db.book_info.isbn &&
		bookinfo.name == bookinfo_db.book_info.name &&
		bookinfo.author == bookinfo_db.book_info.author &&
		bookinfo.publisher == bookinfo_db.book_info.publisher &&
		bookinfo.price == bookinfo_db.book_info.price &&
		bookinfo.publish_date == bookinfo_db.book_info.publish_date &&
		bookinfo.title_url == bookinfo_db.book_info.title_url)
	{
		return false;
	}
	else
	{
		return true;
	}
#endif

	return ret;
}

DB_ProviderDetailInfo CDataBaseProviderDetail::GetLastInfo(void)
{
	DB_ProviderDetailInfo retProviderInfo;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER_DETAIL), std::string(TABLE_DATA_PROVIDER_DETAIL));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER_DETAIL) + " ORDER BY idx DESC LIMIT 1";		//가장 최근의 정보를 얻어옴.

		std::vector<DB_ProviderDetailInfo> vec_provider;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_provider, &vec_provider, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			if (vec_provider.size() > 0)
			{
				retProviderInfo = vec_provider[0];
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retProviderInfo;
}

//DB
int CDataBaseProviderDetail::sql_callback_get_provider(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_ProviderDetailInfo provider;
	for (i = 0; i < argc; i++)
	{
		if (NotUsed != NULL)
		{
			std::string name = azColName[i];

			if (name == "idx")
			{
				provider.idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "base_idx")
			{
				provider.base_idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "tel")
			{
				provider.detail.tel = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "email")
			{
				provider.detail.email = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "address")
			{
				provider.detail.address = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "base_provide_rate")
			{
				provider.detail.provide_rate = argv[i] ? std::stof(argv[i]) : PROVIDE_BASE_RATE;
			}
			else if (name == "base_provide_type")
			{
				provider.detail.provide_type = argv[i] ? std::stoi(argv[i]) : PROVIDE_BASE_TYPE;
			}
			else if (name == "base_calc_day")
			{
				provider.detail.calc_day = argv[i] ? std::stoi(argv[i]) : PROVIDE_BASE_CALC_DAY;
			}
			else if (name == "receipt_able")
			{
				provider.detail.receipt_able = argv[i] ? std::stoi(argv[i]) : PROVIDE_BASE_RECEIPT_ABLE;
			}
			else if (name == "bank_name")
			{
				provider.detail.bank_name = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "bank_num")
			{
				provider.detail.bank_num = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "bank_author")
			{
				provider.detail.bank_author = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "memo")
			{
				provider.detail.memo = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "reg_date")
			{
				provider.reg_date = argv[i] ? argv[i] : "NULL";
			}

		}

		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	//printf("\n");

	if (NotUsed != NULL)
	{
		(*(std::vector<DB_ProviderDetailInfo> *)(NotUsed)).push_back(provider);
	}

	return 0;
}
