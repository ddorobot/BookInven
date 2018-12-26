#include "CDataBase.h"



CDataBase::CDataBase()
{
}


CDataBase::~CDataBase()
{
}

int CDataBase::DeleteItem(const std::string str_table_name, const int index)
{
	int ret = 1;

	sqlite3* pDB = NULL;

	char* pErr=NULL, *pDBFile = DB_PATH;
	int nResult = sqlite3_open(pDBFile, &pDB);

	//Tablek Book
	//Tablek Book
	std::string sql_command = "DELETE FROM " + str_table_name + " WHERE idx=" + std::to_string(index);

	nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

	if (nResult)
	{
		printf("[%s] 테이블 (%d) 삭제 실패!\n", str_table_name.c_str(), index);

		if (pErr != NULL)
		{
			printf(" - pErr : %s\n", pErr);
			 
			sqlite3_free(&pErr);
		}

		ret = 0;
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}

int CDataBase::CheckExistAndCreate(const std::string str_table_name, const std::string str_table_data)
{
	int ret = 1;

	sqlite3* pDB = NULL;

	char* pErr, *pDBFile = DB_PATH;
	int nResult = sqlite3_open(pDBFile, &pDB);

	//Tablek Book
	//Tablek Book
	std::string sql_command = "CREATE TABLE IF NOT EXISTS [" + str_table_name + "] (" + str_table_data + ")";

	nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

	if (nResult)
	{
		printf("[%s] 테이블 만들기 실패!\n", str_table_name.c_str());
		sqlite3_free(&pErr);

		ret = 0;
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;

}

int CDataBase::AddNewColumn(const std::string str_table_name, const std::string str_column_name, const std::string str_column_option)
{
	sqlite3* pDB = NULL;

	char* pErr = NULL, *pDBFile = DB_PATH;
	int nResult = sqlite3_open(pDBFile, &pDB);

	//같은 정보가 있는지 확인
	std::string sql_command = "ALTER TABLE " + str_table_name + " ADD '" + str_column_name + "' " + str_column_option;		//

	nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

	if (nResult)
	{
		if (pErr)
		{
			printf("%s Error : %s\n", __func__, pErr);

			sqlite3_free(&pErr);
		}
	}


	//db close
	if (pDB != NULL) sqlite3_close(pDB);
}