#pragma once

#include "BookInfo.h"
#include "ProviderInfo.h"

typedef struct BookIn_Info {
	BookInfo book_info;
	ProviderInfo provider_info;
	std::string provide_date;
	int count = 0;
	float sale_rate = 0.0;
	int sale_cost = 0;
} BookIn_Info;