#pragma once

#include "BookInfo.h"

#include <string>
#include <vector>
#include <deque>

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "Utility.h"

#include "CGetBookInfoUsingUrl.h"

typedef struct StreamInfo {
	UINT nChar;
	boost::posix_time::ptime gettime;
} StreamInfo;


class GetBookInfo
{
public:
	GetBookInfo();
	~GetBookInfo();

	std::string GetISBNInfo(const UINT nChar);
	BookInfo GetInfo(const std::string isbn);
private:
	std::deque<StreamInfo> m_strem;

	CGetBookInfoUsingUrl m_cls_get_bookinfo_using_url;
};

