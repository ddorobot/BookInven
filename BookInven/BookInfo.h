#pragma once

#include <string>

typedef struct BookInfo {
	std::string isbn;
	std::string name;
	std::string author;
	std::string publisher;
	unsigned int price;
	std::string publish_date;
} BookInfo;
