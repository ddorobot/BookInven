#pragma once

#include "BookInfo.h"

#include <string>

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

class GetBookInfo
{
public:
	GetBookInfo();
	~GetBookInfo();

	BookInfo GetInfo(const std::string str);
};

