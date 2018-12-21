#include "CDataBaseCart.h"



CDataBaseCart::CDataBaseCart()
{
}


CDataBaseCart::~CDataBaseCart()
{
}

std::vector<int> CDataBaseCart::GetAllInfo(void)
{
	std::vector<int> ret_index;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_CART), std::string(TABLE_DATA_CART));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_CART) + " ORDER BY idx DESC";		//가장 최근의 정보를 얻어옴.

		std::vector<DB_Cart> vec_cart;

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

int CDataBaseCart::AddCart(const int index)
{
	int ret = 0;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_CART), std::string(TABLE_DATA_CART));

	//check data
	if (check_db)
	{
		printf("Cart Insert\n");

		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//Tablek Book
		/*
#define TABLE_NAME_CART		"TCart"
#define TABLE_DATA_CART		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
							'bookin_idx' INTEGER, \
							'reg_date' TEXT"
		*/
		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_CART) + " (bookin_idx, reg_date) VALUES (";
		sql_command += "'" + std::to_string(index) + "', ";
		sql_command += "datetime('now','localtime')";
		sql_command += "); ";

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 저장 실패!\n", TABLE_NAME_CART);
			sqlite3_free(pErr);
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}

int CDataBaseCart::GetCount(void)
{
	int ret = 0;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_CART), std::string(TABLE_DATA_CART));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		//SELECT SUM(COL_VALUES) FROM myTable
		std::string sql_command = "SELECT COUNT(*) FROM " + std::string(TABLE_NAME_CART) ;

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
int CDataBaseCart::sql_callback_get_info(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_Cart cart_info;

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
		(*(std::vector<DB_Cart> *)(NotUsed)).push_back(cart_info);
	}

	return 0;
}

//DB
int CDataBaseCart::sql_callback_get_count(void *count, int argc, char **argv, char **azColName)
{
	if (count != NULL)
	{
		int *c = (int *)count;
		*c = argv[0] ? atoi(argv[0]) : 0;  //atoi(argv[0]);
	}
	return 0;
}
