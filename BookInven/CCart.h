#pragma once

#include <string>

#include "CDataBaseBookInHistory.h"
#include "CDataBaseCart.h"

class CCart
{
public:
	CCart();
	~CCart();

	int AddCart(const std::string isbn);
};

