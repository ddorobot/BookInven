#include "CGetGoodsCount.h"



CGetGoodsCount::CGetGoodsCount()
{
}


CGetGoodsCount::~CGetGoodsCount()
{
}

int CGetGoodsCount::GetCount(const std::string code)
{

	CDataBaseBookInHistory cls_db_book_in_history;
	int book_in_count = 0; // cls_db_book_in_history.GetBookCount(code);

	int book_out_count = 0;

	int count = book_in_count - book_out_count;

	return count;
}