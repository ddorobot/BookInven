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
	int bookin_count = cls_db_bookin.GetBookCount(isbn);
	int bookin_candidate_index = cls_db_bookin.GetAbleInCartIndex(isbn);

	//DB에 저장
	if (bookin_count > 0 && bookin_candidate_index >= 0 )
	{
		//카트 DB에 추가하고 입고수량에서는 임시적으로 1을 삭제 한다. 
		CDataBaseCart cls_db_cart;
		if (cls_db_cart.AddCart(bookin_candidate_index))
		{
			//DB에 추가 되었으니 입고수량에서 1을 삭제한다.
			if (cls_db_bookin.PopCount(bookin_candidate_index))
			{
				ret = 1;
			}
		}
	}

	return ret;
}

