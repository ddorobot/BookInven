#pragma once

#include <string>

#define ISBN_CODE_SIZE		13 

typedef struct BookInfo {
	std::string isbn;
	std::string name;
	std::string author;
	std::string publisher;
	unsigned int price;
	std::string publish_date;
	std::string title_url;
} BookInfo;
