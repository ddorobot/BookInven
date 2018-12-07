#include "CMyTime.h"



CMyTime::CMyTime()
{
}


CMyTime::~CMyTime()
{
}

std::string CMyTime::GetNow(void)
{
	//현재 시간
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

	//boost::format f = boost::format("%s-%02d-%02d %02d:%02d:%02d")
	boost::format f = boost::format("%s-%02d-%02d %02d:%02d:%02d")
		% now.date().year_month_day().year
		% now.date().year_month_day().month.as_number()
		% now.date().year_month_day().day.as_number()
		% now.time_of_day().hours()
		% now.time_of_day().minutes()
		% now.time_of_day().seconds();

	std::string cur_day_time = f.str();

	return cur_day_time;
}