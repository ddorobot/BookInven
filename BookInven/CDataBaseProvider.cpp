#include "CDataBaseProvider.h"



CDataBaseProvider::CDataBaseProvider()
{
}


CDataBaseProvider::~CDataBaseProvider()
{
}

void CDataBaseProvider::Delete(const int base_index)
{
	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		DeleteItem(std::string(TABLE_NAME_PROVIDER), base_index);
	}
}

void CDataBaseProvider::SetDetailIndex(const int base_idx, const int detail_idx)
{
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db )
	{
		printf("provider Detail Index Update\n");

		// 1 : Base ����
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		std::string sql_command = "UPDATE " + std::string(TABLE_NAME_PROVIDER) + " SET detail_idx=" + std::to_string(detail_idx) + " WHERE idx=" + std::to_string(base_idx);

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s ������ ���� ����!\n", TABLE_NAME_PROVIDER);
			sqlite3_free(pErr);
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);
}

//Update
void CDataBaseProvider::UpdateProviderInfo(const int base_index, const ProviderInfo provider)
{
	int ret = -1;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));
	bool check_data = CheckData(provider.base);

	if (check_db && check_data)
	{
		printf("provider Insert\n");

		// 1 : Base ����
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		std::string sql_command = "UPDATE " + std::string(TABLE_NAME_PROVIDER);
		//sql_command += " SET name='" + provider.base.name + "', lic='" + provider.base.lic + "', reg_date='" + str_cur_time + "' WHERE idx=" + std::to_string(base_index) + ";" ;
		sql_command += " SET name='" + provider.base.name + "', lic='" + provider.base.lic + "', reg_date=CURRENT_TIMESTAMP WHERE idx=" + std::to_string(base_index) + ";";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s ������ (%d) UPDATE ����!\n", TABLE_NAME_PROVIDER, base_index);
			sqlite3_free(pErr);
		}
		else
		{
			//Detail Update
			//Detail�� Update�� �ƴ϶� ����Ÿ�� ��� �״°ɷ� �սô�.
			CDataBaseProviderDetail cls_db_provider_detail;
			int detail_index = cls_db_provider_detail.AddProviderDetailInfo(base_index, provider.detail);

			//printf("%s : detail_index=%d\n", __func__, detail_index);

			if (detail_index >= 0)
			{
				//update detail index
				SetDetailIndex(base_index, detail_index);
			}


		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);
}

//Set
void CDataBaseProvider::AddProviderInfo(const ProviderInfo provider)
{
	//Add Base
	int base_index = AddProviderBaseInfo(provider.base);

	printf("%s : base_index=%d\n", __func__, base_index);

	//Add Detail
	if (base_index >= 0)
	{

		CDataBaseProviderDetail cls_db_provider_detail;
		int detail_index = cls_db_provider_detail.AddProviderDetailInfo(base_index, provider.detail);

		printf("%s : detail_index=%d\n", __func__, detail_index);

		if (detail_index >= 0) 
		{
			//update detail index
			SetDetailIndex(base_index, detail_index);
		}
	}
}

int CDataBaseProvider::GetProviderSize(void)
{
	int ret = 0;
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT COUNT(*) " + std::string(TABLE_NAME_PROVIDER);		//count

		int count = 0;
		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_count, &count, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			ret = count;
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret ;
}

int CDataBaseProvider::AddProviderBaseInfo(ProviderInfoBase provider)
{
	int ret = -1;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));
	bool check_data = CheckData(provider);

	if (check_db && check_data)
	{
		printf("provider Insert\n");

		// 1 : Base ����
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_PROVIDER) + " (name, lic, reg_date) VALUES (";
		sql_command += "'" + provider.name + "', ";
		sql_command += "'" + provider.lic + "', ";
		//sql_command += "'" + str_cur_time + "'";
		sql_command += "CURRENT_TIMESTAMP";
		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s ������ ���� ����!\n", TABLE_NAME_PROVIDER);
			sqlite3_free(pErr);
		}
		else
		{
			//ret = 
			DB_ProviderInfo db_provider_base_info = GetLastInfo() ;
			ret = db_provider_base_info.idx;
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}

bool CDataBaseProvider::CheckData(const ProviderInfoBase provider)
{
	//provider ������ �̸��� �ݵ�� �־�� �Ѵ�.
	bool check_data = false;

	CCheckString cls_check_string;
	check_data = cls_check_string.CheckString(provider.name);
	if (check_data)	goto EXIT_CHECKDATA;

EXIT_CHECKDATA:
	return check_data;
}

bool CDataBaseProvider::CheckDataSameValue(const ProviderInfo provider)
{
	bool ret = false;

	//���� �ֽ��� ����Ÿ�� ���� �Է� ����Ÿ�� ���� ����Ÿ ���� üũ
	DB_ProviderInfo provider_db = GetLastInfo(provider.base.name, provider.base.lic);

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

int CDataBaseProvider::GetDetailIndex(const int index)
{
	int ret = -1 ;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER) + " WHERE idx=" + std::to_string(index) + " ORDER BY idx DESC";		//

		std::vector<DB_ProviderInfo> vec_provider;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_provider, &vec_provider, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int provider_size = vec_provider.size();

			if (provider_size > 0)
			{
				ret = vec_provider[0].detail_idx;
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret ;
}

ProviderInfoBase CDataBaseProvider::GetBaseInfo(const int index)
{
	ProviderInfoBase ret_provider_info;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER) + " WHERE idx=" + std::to_string(index) + " ORDER BY idx DESC";		//

		std::vector<DB_ProviderInfo> vec_provider;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_provider, &vec_provider, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int provider_size = vec_provider.size();

			if (provider_size > 0)
			{
				ret_provider_info = vec_provider[0].base;
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret_provider_info;
}

std::vector<ProviderInfoBase> CDataBaseProvider::GetBaseInfo(void)
{
	std::vector<ProviderInfoBase> ret_vec_provider_info;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER) + " ORDER BY idx DESC";		//

		std::vector<DB_ProviderInfo> vec_provider;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_provider, &vec_provider, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int provider_size = vec_provider.size();

			if (provider_size > 0)
			{
				for (int i = 0; i < provider_size; i++)
				{
					//push
					ProviderInfoBase provider_base_info;
					provider_base_info = vec_provider[i].base;
					ret_vec_provider_info.push_back(provider_base_info);
				}
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret_vec_provider_info;
}

std::vector<ProviderInfo> CDataBaseProvider::GetInfo(void)
{
	std::vector<ProviderInfo> ret_vec_provider_info;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER) + " ORDER BY idx DESC";		//

		std::vector<DB_ProviderInfo> vec_provider;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_provider, &vec_provider, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int provider_size = vec_provider.size();

			if (provider_size > 0)
			{
				//search detail
				CDataBaseProviderDetail m_cls_db_provider_detail;
				for (int i = 0; i < provider_size; i++)
				{
					int out_my_idx = -1;
					ProviderInfoDetail provider_detail = m_cls_db_provider_detail.GetProviderDetailInfo(vec_provider[i].detail_idx, &out_my_idx);

					if (out_my_idx >= 0 && vec_provider[i].idx == out_my_idx)
					{
						//push
						ProviderInfo provider_info;
						provider_info.base = vec_provider[i].base;
						provider_info.detail = provider_detail;
						provider_info.base.idx = vec_provider[i].idx;
						ret_vec_provider_info.push_back(provider_info);
					}
				}
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret_vec_provider_info;
}

std::vector<ProviderInfo> CDataBaseProvider::GetInfo(const std::string name, const std::string lic)
{
	std::vector<ProviderInfo> ret_vec_provider_info;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER) + " WHERE name = '" + name + "' OR lic = '" + lic + "' ORDER BY idx DESC LIMIT 1";		//���� �ֱ��� ������ ����.

		std::vector<DB_ProviderInfo> vec_provider;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_provider, &vec_provider, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int provider_size = vec_provider.size();

			if (provider_size > 0)
			{
				//search detail
				CDataBaseProviderDetail m_cls_db_provider_detail;
				for (int i = 0; i < provider_size; i++)
				{
					int out_my_idx = -1;
					ProviderInfoDetail provider_detail = m_cls_db_provider_detail.GetProviderDetailInfo(vec_provider[i].detail_idx, &out_my_idx);

					if (out_my_idx >= 0 && vec_provider[i].idx == out_my_idx)
					{
						//push
						ProviderInfo provider_info;
						provider_info.base = vec_provider[i].base;
						provider_info.detail = provider_detail;
						provider_info.base.idx = vec_provider[i].idx;
						ret_vec_provider_info.push_back(provider_info);
					}
				}
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret_vec_provider_info;
}

DB_ProviderInfo CDataBaseProvider::GetLastInfo(const std::string name, const std::string lic)
{
	DB_ProviderInfo retProviderInfo;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER) + " WHERE name = '" + name + "' OR lic = '" + lic + "' ORDER BY idx DESC LIMIT 1";		//���� �ֱ��� ������ ����.

		std::vector<DB_ProviderInfo> vec_provider;

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

DB_ProviderInfo CDataBaseProvider::GetLastInfo(void)
{
	DB_ProviderInfo retProviderInfo;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_PROVIDER), std::string(TABLE_DATA_PROVIDER));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//���� ������ �ִ��� Ȯ��
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_PROVIDER) + " ORDER BY idx DESC LIMIT 1";		//���� �ֱ��� ������ ����.

		std::vector<DB_ProviderInfo> vec_provider;

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
int CDataBaseProvider::sql_callback_get_count(void *count, int argc, char **argv, char **azColName)
{
	if (count != NULL)
	{
		int *c = (int *)count;
		*c = atoi(argv[0]);
	}
	return 0;
}

int CDataBaseProvider::sql_callback_get_provider(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_ProviderInfo provider;
	for (i = 0; i < argc; i++)
	{
		if (NotUsed != NULL)
		{
			std::string name = azColName[i];

			if (name == "idx")
			{
				provider.idx = argv[i] ? std::stoi(argv[i]) : -1;
				provider.base.idx = provider.idx;
			}
			else if (name == "detail_idx")
			{
				provider.detail_idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "name")
			{
				provider.base.name = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "lic")
			{
				provider.base.lic = argv[i] ? argv[i] : "NULL";
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
		(*(std::vector<DB_ProviderInfo> *)(NotUsed)).push_back(provider);
	}

	return 0;
}
