#pragma once

#include <string>

#include "CDataBaseBookInHistory.h"
#include "CDataBaseCart.h"

typedef struct CartInfo {
	int db_idx = -1;
	BookIn_Info bookin_info;
	int count = 0;
} CartInfo;

class CCart
{
public:
	CCart();
	~CCart();

	int AddCart(const std::string isbn);		//isbn�� �ش�Ǵ� ��ǰ�� ���� 1�� �߰�
	int PopCart(const std::string isbn);		//isbn�� �ش�Ǵ� ��ǰ�� ���� 1�� ����
	int DelCart(const std::string isbn);		//isbn�� �ش�Ǵ� ��ǰ�� ��� ���� ����
	int GetCartCount(void);
	std::vector<int> GetCartAllIndex(void);
	std::vector<CartInfo> GetCartData(const std::string isbn="");
	int GetCount(const int index);
};

