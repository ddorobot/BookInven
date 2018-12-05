#pragma once

#include "BookInfo.h"

#include <string>

#include <expat.h>
#include <curl/curl.h>

#include <wininet.h>

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "expat.lib")
#pragma comment(lib, "libcurl.lib")

enum {
	ERROR_ARGS = 1,
	ERROR_CURL_INIT = 2
};

enum {
	OPTION_FALSE = 0,
	OPTION_TRUE = 1
};

enum {
	FLAG_DEFAULT = 0
};

struct MemoryStruct {
	char *memory;
	size_t size;
};

struct ParserStruct {
	int ok;
	size_t tags;
	size_t depth;
	struct MemoryStruct characters;
};

class CGetBookInfoUsingUrl
{
public:
	CGetBookInfoUsingUrl();
	~CGetBookInfoUsingUrl();

	BookInfo Run(const std::string isbn);

private:
	void Clear(void);

	char* UTF8toANSI(char *pszCode);

	static void startElement(void *userData, const XML_Char *name, const XML_Char **atts);
	static void characterDataHandler(void *userData, const XML_Char *s, int len);
	static void endElement(void *userData, const XML_Char *name);
	static size_t parseStreamCallback(void *contents, size_t length, size_t nmemb, void *userp);

	//data
	std::string m_book_title;
	std::string m_book_author;
	std::string m_book_publisher;
	std::string m_book_price;
	std::string m_book_publish_date;
	std::string m_book_title_url;
};

