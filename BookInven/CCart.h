#pragma once

#include <string>

#include "BookInInfo.h"
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

	int AddCart(const std::string isbn);		//isbn에 해당되는 제품의 수량 1개 추가
	int PopCart(const std::string isbn);		//isbn에 해당되는 제품의 수량 1개 제거
	int DelCart(const std::string isbn, const bool bret=true);		//isbn에 해당되는 제품의 모든 수량 제거
	int GetCartCount(void);
	std::vector<int> GetCartAllIndex(void);
	std::vector<CartInfo> GetCartData(const std::string isbn="");
	int GetCount(const int index);
};

