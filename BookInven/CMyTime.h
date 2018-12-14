#pragma once

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\filesystem\path.hpp"
#include "boost\range\iterator_range.hpp"
#include "boost\system\error_code.hpp"
#include "boost/algorithm/string/replace.hpp"
#include "boost/date_time/local_time/local_date_time.hpp"
#include "boost/format.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/posix_time/posix_time_io.hpp"
#include "boost\date_time\gregorian\gregorian.hpp"
#include "boost\regex.hpp"

class CMyTime
{
public:
	CMyTime();
	~CMyTime();

	std::string GetNow(void);
	std::string GetNowDate(void);
	std::string GetPeriodDate(const int pre_days);
};

