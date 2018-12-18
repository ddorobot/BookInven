#pragma once

#include <string>

#define ISBN_CODE_SIZE		13 

#define BOOK_COVER_WIDTH	150
#define BOOK_COVER_HEIGHT	200

typedef struct BookInfo {
	int idx = -1;
	std::string isbn;
	std::string name;
	std::string author;
	std::string publisher;
	unsigned int price=0;
	std::string publish_date;
	std::string title_url;
} BookInfo;
