#include "CDataBaseBookInfo.h"



CDataBaseBookInfo::CDataBaseBookInfo()
{
}


CDataBaseBookInfo::~CDataBaseBookInfo()
{
}


//DB
int CDataBaseBookInfo::sql_callback_get_bookinfo(void *NotUsed, int argc, char **argv, char **azColName)
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
			else if (name == "title_url")
			{
				bookinfo.book_info.title_url = argv[i] ? argv[i] : "NULL";
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

int CDataBaseBookInfo::GetBookInfo(const std::string isbn, BookInfo *bookinfo)
{
	int ret = 1;

	sqlite3* pDB = NULL;

	char* pErr, *pDBFile = DB_PATH;
	int nResult = sqlite3_open(pDBFile, &pDB);

	//-----------------------------------------------------
	//기존에 정보가 있는지 DB에서 검색
	std::vector<DB_BookInfo> vec_info;

	std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_INFO) + " WHERE isbn='" + isbn + "' ORDER BY idx DESC LIMIT 1";		//Book 테이블에서 Code의 필드값만 불러 옴.

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

bool CDataBaseBookInfo::CheckData(const BookInfo bookinfo)
{
	bool check_data = false;

	CCheckString cls_check_string;
	//id
	check_data = cls_check_string.CheckString(bookinfo.isbn);
	if (check_data)	goto EXIT_CHECKDATA;

	//name
	check_data = cls_check_string.CheckString(bookinfo.name);
	if (check_data)	goto EXIT_CHECKDATA;

	//author
	check_data = cls_check_string.CheckString(bookinfo.author);
	if (check_data)	goto EXIT_CHECKDATA;

	//publisher
	check_data = cls_check_string.CheckString(bookinfo.publisher);
	if (check_data)	goto EXIT_CHECKDATA;

	//price
	//check_data = cls_check_string.CheckString(bookinfo.price);
	//if (check_data)	goto EXIT_CHECKDATA;

	check_data = cls_check_string.CheckString(bookinfo.title_url);
	if (check_data)	goto EXIT_CHECKDATA;

	//publish_date
	check_data = cls_check_string.CheckString(bookinfo.publish_date);
	if (check_data)	goto EXIT_CHECKDATA;

EXIT_CHECKDATA:
	return check_data;
}

//Set
void CDataBaseBookInfo::AddBookInfo(const BookInfo bookinfo)
{
	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_INFO), std::string(TABLE_DATA_BOOK_INFO));
	bool check_data = CheckData(bookinfo);

	//check same data from DB
	bool check_same_data = CheckDataSameValue(bookinfo);

	printf("check_db=%d, check_data=%d, check_same_data=%d\n", check_db, check_data, check_same_data);

	//check data
	if (check_db && check_data && check_same_data)
	{
		printf("BookInfo Insert\n");

		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		CMyTime cls_mytime;
		std::string str_cur_time = cls_mytime.GetNow();

		//Tablek Book
		std::string sql_command = "INSERT INTO " + std::string(TABLE_NAME_BOOK_INFO) + " (isbn, name, author, publisher, price, publish_date, title_url, reg_date) VALUES (";
		sql_command += "'" + bookinfo.isbn + "', ";
		sql_command += "'" + bookinfo.name + "', ";
		sql_command += "'" + bookinfo.author + "', ";
		sql_command += "'" + bookinfo.publisher + "', ";
		sql_command += "'" + std::to_string(bookinfo.price) + "', ";
		sql_command += "'" + bookinfo.publish_date + "', ";
		sql_command += "'" + bookinfo.title_url + "', ";
		sql_command += "'" + str_cur_time + "'";
		sql_command += "); ";

		//printf("AddBookInfo sql = %s\n", sql_command.c_str());

		nResult = sqlite3_exec(pDB, sql_command.c_str(), NULL, NULL, &pErr);

		if (nResult)
		{
			printf("%s 데이터 저장 실패!\n", TABLE_NAME_BOOK_INFO);
			sqlite3_free(pErr);
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

}

DB_BookInfo CDataBaseBookInfo::GetLastInfo(void)
{
	DB_BookInfo retBookInfo;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_INFO), std::string(TABLE_DATA_BOOK_INFO));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_INFO) + " ORDER BY idx DESC LIMIT 1";		//가장 최근의 정보를 얻어옴.

		std::vector<DB_BookInfo> vec_bookinfo;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_bookinfo, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			if (vec_bookinfo.size() > 0)
			{
				retBookInfo = vec_bookinfo[0];
			}
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);

	return retBookInfo;
}

bool CDataBaseBookInfo::CheckDataSameValue(const BookInfo bookinfo)
{
	//가장 최신의 데이타와 현재 입력 데이타가 같은 데이타 인지 체크
	DB_BookInfo bookinfo_db = GetLastInfo();

	if (bookinfo.isbn == bookinfo_db.book_info.isbn &&
		bookinfo.name == bookinfo_db.book_info.name &&
		bookinfo.author == bookinfo_db.book_info.author &&
		bookinfo.publisher == bookinfo_db.book_info.publisher &&
		bookinfo.price == bookinfo_db.book_info.price &&
		bookinfo.publish_date == bookinfo_db.book_info.publish_date && 
		bookinfo.title_url == bookinfo_db.book_info.title_url )
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CDataBaseBookInfo::Print(void)
{
	printf("%s Table DB print\n", TABLE_NAME_BOOK_INFO);

	DB_BookInfo retBookInfo;

	sqlite3* pDB = NULL;

	int check_db = CheckExistAndCreate(std::string(TABLE_NAME_BOOK_INFO), std::string(TABLE_DATA_BOOK_INFO));

	if (check_db)
	{
		char* pErr, *pDBFile = DB_PATH;
		int nResult = sqlite3_open(pDBFile, &pDB);

		//같은 정보가 있는지 확인
		std::string sql_command = "SELECT * FROM " + std::string(TABLE_NAME_BOOK_INFO) ;

		std::vector<DB_BookInfo> vec_bookinfo;

		nResult = sqlite3_exec(pDB, sql_command.c_str(), sql_callback_get_bookinfo, &vec_bookinfo, &pErr);

		if (nResult)
		{
			sqlite3_free(&pErr);
		}
		else
		{
			int vec_size = vec_bookinfo.size();

			printf("data size = %d\n", vec_size);

			if (vec_size > 0)
			{
				//print
				for (int i = 0; i < vec_size; i++)
				{
					printf(" - [%04d] (%d) %s,%s,%s,%s,%d,%s,%s,%s\n", i, vec_bookinfo[i].idx, vec_bookinfo[i].reg_date.c_str(), vec_bookinfo[i].book_info.isbn.c_str(), vec_bookinfo[i].book_info.name.c_str(), vec_bookinfo[i].book_info.author.c_str(), vec_bookinfo[i].book_info.price, vec_bookinfo[i].book_info.publisher.c_str(), vec_bookinfo[i].book_info.publish_date.c_str(), vec_bookinfo[i].book_info.title_url.c_str());
				}
			}
			printf("end\n");
		}
	}

	//db close
	if (pDB != NULL) sqlite3_close(pDB);
}