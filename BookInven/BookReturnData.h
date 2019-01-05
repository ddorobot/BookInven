#pragma once

#include <vector>
#include "CDataBaseBookInHistory.h"

typedef struct BookReturnData {
	int provider_index = -1;
	std::vector<BookInHistory> vec_bookin_history;
} BookReturnData;