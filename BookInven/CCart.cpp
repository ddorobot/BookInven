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

	//DB �԰� ����Ʈ�� ������ Ȯ��
	CDataBaseBookInHistory cls_db_bookin;
	int bookin_count = cls_db_bookin.GetAbleInCartIndex(isbn);

	//DB�� ����

	return ret;
}

