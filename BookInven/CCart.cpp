#include "CCart.h"



CCart::CCart()
{
}


CCart::~CCart()
{
}

int CCart::AddCart(const std::string isbn)
{
	int ret = 0;

	//DB 입고 리스트의 수량을 확인
	CDataBaseBookInHistory cls_db_bookin;
	int bookin_count = cls_db_bookin.GetAbleInCartIndex(isbn);

	//DB에 저장

	return ret;
}

