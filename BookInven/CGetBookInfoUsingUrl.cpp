#include "CGetBookInfoUsingUrl.h"

CGetBookInfoUsingUrl* g_p_me = NULL;

CGetBookInfoUsingUrl::CGetBookInfoUsingUrl()
{
	g_p_me = this;
}


CGetBookInfoUsingUrl::~CGetBookInfoUsingUrl()
{
}

void CGetBookInfoUsingUrl::startElement(void *userData, const XML_Char *name,
	const XML_Char **atts)
{
	struct ParserStruct *state = (struct ParserStruct *) userData;
	state->tags++;
	state->depth++;

	/* Get a clean slate for reading in character data. */
	free(state->characters.memory);
	state->characters.memory = NULL;
	state->characters.size = 0;
}

void CGetBookInfoUsingUrl::characterDataHandler(void *userData, const XML_Char *s, int len)
{
	struct ParserStruct *state = (struct ParserStruct *) userData;
	struct MemoryStruct *mem = &state->characters;

	mem->memory = (char *)realloc(mem->memory, mem->size + len + 1);
	if (mem->memory == NULL) {
		/* Out of memory. */
		fprintf(stderr, "Not enough memory (realloc returned NULL).\n");
		state->ok = 0;
		return;
	}

	memcpy(&(mem->memory[mem->size]), s, len);
	mem->size += len;
	mem->memory[mem->size] = 0;
}

void CGetBookInfoUsingUrl::endElement(void *userData, const XML_Char *name)
{
	struct ParserStruct *state = (struct ParserStruct *) userData;
	state->depth--;

	//printf("%5lu   %10lu   %s\n", state->depth, state->characters.size, name);

	std::string tag_name = name;

	if (g_p_me != NULL)
	{
		if (tag_name == "TITLE")
		{
			//printf("title : %s\n", g_p_me->UTF8toANSI(state->characters.memory));

			char * data = NULL;
			data = g_p_me->UTF8toANSI(state->characters.memory);

			if (data != NULL)
			{
				g_p_me->m_book_title = data;

				delete[] data;

				data = NULL;
			}
		}
		else if (tag_name == "AUTHOR")
		{
			//printf("author : %s\n", g_p_me->UTF8toANSI(state->characters.memory));
			char * data = NULL;
			data = g_p_me->UTF8toANSI(state->characters.memory);

			if (data != NULL)
			{
				g_p_me->m_book_author = data;

				delete[] data;

				data = NULL;
			}
		}
		else if (tag_name == "PUBLISHER")
		{
			//printf("publisher : %s\n", g_p_me->UTF8toANSI(state->characters.memory));
			char * data = NULL;
			data = g_p_me->UTF8toANSI(state->characters.memory);

			if (data != NULL)
			{
				g_p_me->m_book_publisher = data;

				delete[] data;

				data = NULL;
			}
		}
		else if (tag_name == "PRE_PRICE")
		{
			//printf("price : %s\n", state->characters.memory);
			char * data = NULL;
			data = g_p_me->UTF8toANSI(g_p_me->UTF8toANSI(state->characters.memory));

			if (data != NULL)
			{
				g_p_me->m_book_price = data;

				delete[] data;

				data = NULL;
			}
		}
		else if (tag_name == "PUBLISH_PREDATE")
		{
			char * data = NULL;
			data = g_p_me->UTF8toANSI(g_p_me->UTF8toANSI(state->characters.memory));

			if (data != NULL)
			{
				g_p_me->m_book_publish_date = data;

				delete[] data;

				data = NULL;
			}
		}
		else if (tag_name == "TITLE_URL")
		{
			char * data = NULL;

			printf("TITLE_URL = %s\n", state->characters.memory);

			data = g_p_me->UTF8toANSI(g_p_me->UTF8toANSI(state->characters.memory));

			if (data != NULL)
			{
				g_p_me->m_book_title_url = data;

				delete[] data;

				data = NULL;
			}
		}
	}
}

size_t CGetBookInfoUsingUrl::parseStreamCallback(void *contents, size_t length, size_t nmemb, void *userp)
{
	XML_Parser parser = (XML_Parser)userp;
	size_t real_size = length * nmemb;
	struct ParserStruct *state = (struct ParserStruct *) XML_GetUserData(parser);

	/* Only parse if we're not already in a failure state. */
	if (state->ok && XML_Parse(parser, (const char*)contents, real_size, 0) == 0) {
		int error_code = XML_GetErrorCode(parser);
		fprintf(stderr, "Parsing response buffer of length %lu failed"
			" with error code %d (%s).\n",
			real_size, error_code, XML_ErrorString((XML_Error)error_code));
		state->ok = 0;
	}

	return real_size;
}

char* CGetBookInfoUsingUrl::UTF8toANSI(char *pszCode)
{
	if (pszCode == NULL)	return NULL;

	BSTR    bstrWide;
	char*   pszAnsi;
	int     nLength;

	// Get nLength of the Wide Char buffer   
	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	// Change UTF-8 to Unicode (UTF-16)   
	MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);


	// Get nLength of the multi byte buffer    
	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	// Change from unicode to mult byte   
	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);

	SysFreeString(bstrWide);


	return pszAnsi;
}

void CGetBookInfoUsingUrl::Clear(void)
{
	m_book_title = "";
	m_book_author = "";
	m_book_publisher = "";
	m_book_price = "0";
	m_book_publish_date = "";
	m_book_title_url = "";
}

int CGetBookInfoUsingUrl::GetBookInfo(const std::string isbn, BookInfo* bookinfo)
{
	int ret = 0;

	//Data Clear
	Clear();

	//Check Internet
	DWORD dwFlag;
	TCHAR szName[256];
	BOOL bInternet = ::InternetGetConnectedStateEx(&dwFlag, szName, 256, 0);

	bool b_get_data = false;

	//more information : http://www.nl.go.kr/nl/service/open/api_util_isbn.jsp

	if (bInternet)
	{
#if 0
		const char* targetUrl = "http://www.nl.go.kr/app/nl/search/openApi/search.jsp?key=aa9d5d55aeb939697bc8a8df6b26f23f&category=dan&kwd=%ED%85%8C%EC%8A%A4%ED%8A%B8";
		curl_global_init(CURL_GLOBAL_ALL);

		CURL* ctx = curl_easy_init();

		if (NULL == ctx) {
			std::cerr << "Unable to initialize cURL interface" << std::endl;
			return;
		}

		// Target URL: 
		curl_easy_setopt(ctx, CURLOPT_URL, targetUrl);
		// no progress bar:
		curl_easy_setopt(ctx, CURLOPT_NOPROGRESS, OPTION_TRUE);

		// 응답데이터를 표준출력으로 보낸다. 
		curl_easy_setopt(ctx, CURLOPT_WRITEDATA, stdout);
#endif
		CURL *curl_handle;
		CURLcode res;
		XML_Parser parser;
		struct ParserStruct state;

		/* Initialize the state structure for parsing. */
		memset(&state, 0, sizeof(struct ParserStruct));
		state.ok = 1;

		/* Initialize a namespace-aware parser. */
		parser = XML_ParserCreateNS(NULL, '\0');
		XML_SetUserData(parser, &state);
		XML_SetElementHandler(parser, startElement, endElement);
		XML_SetCharacterDataHandler(parser, characterDataHandler);

		//char url[2048];
		std::string url;
		std::string key = "aa9d5d55aeb939697bc8a8df6b26f23f";
		url = "http://seoji.nl.go.kr/landingPage/SearchApi.do?cert_key=" + key + "&result_style=xml&isbn=" + isbn + "&page_no=1&page_size=1";
		//sprintf(url, "%s8", isbn.c_str());

		/* Initialize a libcurl handle. */
		curl_global_init(CURL_GLOBAL_ALL ^ CURL_GLOBAL_SSL);
		curl_handle = curl_easy_init();
		curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, parseStreamCallback);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)parser);
		curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT_MS, 300L);

		//printf("Depth   Characters   Closing Tag\n");

		/* Perform the request and any follow-up parsing. */
		int iter = 0;
		do
		{
			res = curl_easy_perform(curl_handle);
			if (res != CURLE_OK) {
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
				printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			}
			else if (state.ok) {
				/* Expat requires one final call to finalize parsing. */
				if (XML_Parse(parser, NULL, 0, 1) == 0) {
					int error_code = XML_GetErrorCode(parser);
					fprintf(stderr, "Finalizing parsing failed with error code %d (%s).\n", error_code, XML_ErrorString((XML_Error)error_code));
					printf("Finalizing parsing failed with error code %d (%s).\n", error_code, XML_ErrorString((XML_Error)error_code));
				}
				else {
					//printf("                     --------------\n");
					//printf("                     %lu tags total\n", state.tags);

					b_get_data = true;
					break;

				}
			}

			iter++;

			if (iter > 3)
			{
				break;
			}
		} while (1);

		//state.tags

		/* Clean up. */
		free(state.characters.memory);
		XML_ParserFree(parser);
		curl_easy_cleanup(curl_handle);
		curl_global_cleanup();
	}

	if (bookinfo != NULL)
	{
		if (!isbn.empty() &&
			!m_book_title.empty())
		{
			bookinfo->isbn = isbn;
			bookinfo->name = m_book_title;
			bookinfo->author = m_book_author;
			bookinfo->price = std::stoi(m_book_price);
			bookinfo->publisher = m_book_publisher;
			bookinfo->publish_date = m_book_publish_date;
			bookinfo->title_url = m_book_title_url;

			ret = 1;
		}
	}

	return ret;
		
}