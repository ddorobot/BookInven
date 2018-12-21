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
	int bookin_count = cls_db_bookin.GetBookCount(isbn);
	int bookin_candidate_index = cls_db_bookin.GetAbleInCartIndex(isbn);

	//DB�� ����
	if (bookin_count > 0 && bookin_candidate_index >= 0 )
	{
		//īƮ DB�� �߰��ϰ� �԰���������� �ӽ������� 1�� ���� �Ѵ�. 
		CDataBaseCart cls_db_cart;
		if (cls_db_cart.AddCart(bookin_candidate_index))
		{
			//DB�� �߰� �Ǿ����� �԰�������� 1�� �����Ѵ�.
			if (cls_db_bookin.PopCount(bookin_candidate_index))
			{
				ret = 1;
			}
		}
	}

	return ret;
}

