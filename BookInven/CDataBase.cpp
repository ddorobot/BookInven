#include "CDataBase.h"



CDataBase::CDataBase()
{
}


CDataBase::~CDataBase()
{
}

//DB
int CDataBase::sql_callback_get_bookinfo(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	DB_BookInfo bookinfo;
	for (i = 0; i < argc; i++)
	{
		if (NotUsed != NULL)
		{
			std::string name = azColName[i];

			if (name == "idx")
			{
				bookinfo.idx = argv[i] ? std::stoi(argv[i]) : -1;
			}
			else if (name == "isbn")
			{
				bookinfo.book_info.isbn = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "name")
			{
				bookinfo.book_info.name = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "author")
			{
				bookinfo.book_info.author = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "publisher")
			{
				bookinfo.book_info.publisher = argv[i] ? argv[i] : "NULL";
			}
			else if (name == "price")
			{
				bookinfo.book_info.price = argv[i] ? atoi(argv[i]) : 0;
			}
			else if (name == "reg_date")
			{
				bookinfo.reg_date = argv[i] ? argv[i] : "NULL";
			}
		}

		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	//printf("\n");

	if (NotUsed != NULL)
	{
		(*(std::vector<DB_BookInfo> *)(NotUsed)).push_back(bookinfo);
	}

	return 0;
}

int CDataBase::GetBookInfo(const std::string isbn, BookInfo *bookinfo)
{
	int ret = 1;

	sqlite3* pDB = NULL;

	char* pErr, *pDBFile = DB_PATH;
	int nResult = sqlite3_open(pDBFile, &pDB);

	//-----------------------------------------------------
	//기존에 정보가 있는지 DB에서 검색
	std::vector<DB_BookInfo> vec_info;

	std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_INFO) + " WHERE id='" + isbn + "' ORDER BY idx DESC LIMIT 1";		//Book 테이블에서 Code의 필드값만 불러 옴.

	/* Execute SQL statement */
	nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_info, &pErr);

	if (nResult != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", pErr);
		sqlite3_free(pErr);

		ret = 0;
	}
	else
	{
		//fprintf(stdout, "Operation done successfully\n");

		ret = vec_info.size();

		if (ret > 0)
		{
			if (bookinfo != NULL)
			{
				(*bookinfo) = vec_info[0].book_info;
			}
		}
	}


	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return ret;
}

