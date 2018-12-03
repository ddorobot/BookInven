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
	StreamInfo GetInfo(const std::string isbn);
private:
	std::deque<StreamInfo> m_strem;
};

