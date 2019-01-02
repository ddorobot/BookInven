#include "CDataBaseReturn.h"



CDataBaseReturn::CDataBaseReturn()
{
}


CDataBaseReturn::~CDataBaseReturn()
{
}

std::vector<DB_Return> CDataBaseReturn::GetDBInfo(void)
{
	std::vector<DB_Return> ret_vec;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_RETURN), std::string(TABLE_DATA_RETURN));

	if (check_db)
	{
		char* pErr=NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);


		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_RETURN) + " ORDER BY idx ASC";		//ASC : 가장 과거의 정보를 먼저 얻어옴.

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_info, &ret_vec, &pErr);

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

	return ret_vec;
}

std::vector<int> CDataBaseReturn::GetInfo(const int index)
{
	std::vector<int> ret_index;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_RETURN), std::string(TABLE_DATA_RETURN));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		std::string sql_option = "";
		if (index >= 0)
		{
			sql_option = " WHERE idx=" + std::to_string(index);
		}

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_RETURN) + sql_option + " ORDER BY idx DESC";		//가장 최근의 정보를 먼저 얻어옴.

		std::vector<DB_Return> vec_cart;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_info, &vec_cart, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int info_sizse = vec_cart.size();

			for (int i = 0; i < info_sizse; i++)
			{
				ret_index.push_back(vec_cart[i].bookin_idx);
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret_index;
}

int CDataBaseReturn::DelReturn(const int bookin_index)
{
	int ret = 0;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_RETURN), std::string(TABLE_DATA_RETURN));

	//check data
	if (check_db)
	{
		printf("%s\n", __func__);

		char* pErr = NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		/*
#define TABLE_NAME_RETURN		"TReturn"
#define TABLE_DATA_RETURN		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
							'bookin_idx' INTEGER, \
							'reg_date' TEXT"
		*/
		std::string sql_command = "DELETE FROM " + std::string(TABLE_NAME_RETURN) + " WHERE bookin_idx=" + std::to_string(bookin_index);

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 삭제 실패!\n", TABLE_NAME_RETURN);

			if (pErr)
			{
				printf("%s Error %s\n", __func__, pErr);
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

int CDataBaseReturn::PopReturn(const int index)
{
	int ret = 0;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_RETURN), std::string(TABLE_DATA_RETURN));

	//check data
	if (check_db)
	{
		printf("Return Delete\n");

		char* pErr = NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		/*
#define TABLE_NAME_RETURN		"TReturn"
#define TABLE_DATA_RETURN		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
							'bookin_idx' INTEGER, \
							'reg_date' TEXT"
		*/
		std::string sql_command = "DELETE FROM " + std::string(TABLE_NAME_RETURN) + " WHERE idx=" + std::to_string(index) ;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 삭제 실패!\n", TABLE_NAME_RETURN);

			if (pErr)
			{
				printf("%s Error %s\n", __func__, pErr);
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

int CDataBaseReturn::AddReturn(const int index)
{
	int ret = 0;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_RETURN), std::string(TABLE_DATA_RETURN));

	//check data
	if (check_db)
	{
		printf("Return Insert\n");

		char* pErr=NULL, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		/*
#define TABLE_NAME_RETURN		"TReturn"
#define TABLE_DATA_RETURN		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
							'bookin_idx' INTEGER, \
							'reg_date' TEXT"
		*/
		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_RETURN) + " (bookin_idx, reg_date) VALUES (";
		sql_command += "'" + std::to_string(index) + "', ";
		sql_command += "datetime('now','localtime')";
		sql_command += "); ";

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 저장 실패!\n", TABLE_NAME_RETURN);

			if (pErr)
			{
				printf("%s Error %s\n", __func__, pErr);
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

int CDataBaseReturn::GetCount(const int index)
{
	int ret = 0;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_RETURN), std::string(TABLE_DATA_RETURN));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		std::string sql_option = "";
		if (index >= 0)
		{
			sql_option = " WHERE idx=" + std::to_string(index);
		}

		//같은 정보가 있는지 확인
		//SELECT SUM(COL_VALUES) FROM myTable
		std::string sql_command = "SELECT COUNT(*) FROM " + std::string(TABLE_NAME_RETURN) + sql_option;

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

	return ret;
}

//DB
int CDataBaseReturn::sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_Return cart_info;

	for (i = 0; i < argc; i++)
	{
		if (NotUsed != NULL)
		{
			std::string name = azColName[i];

			if (name == "idx")
			{
				cart_info.idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			if (name == "bookin_idx")
			{
				cart_info.bookin_idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "reg_date")
			{
				cart_info.reg_date = argv[i] ? argv[i] : "NULL";
			}
		}

		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	//printf("\n");

	if (NotUsed != NULL)
	{
		(*(std::vector<DB_Return> *)(NotUsed)).push_back(cart_info);
	}

	return 0;
}

//DB
int CDataBaseReturn::sql_callback_get_count(void *count, int argc, char **argv, char **azColName)
{
	if (count != NULL)
	{
		int *c = (int *)count;
		*c = argv[0] ? atoi(argv[0]) : 0;  //atoi(argv[0]);
	}
	return 0;
}
