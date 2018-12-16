#pragma once

#include "CDataBaseBookInHistory.h"

class CGetGoodsCount
{
public:
	CGetGoodsCount();
	~CGetGoodsCount();

	int GetCount(const std::string code);
};

