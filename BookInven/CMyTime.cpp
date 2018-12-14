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

std::string CMyTime::GetNowDate(void)
{
	//현재 시간
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

	//boost::format f = boost::format("%s-%02d-%02d %02d:%02d:%02d")
	boost::format f = boost::format("%s-%02d-%02d")
		% now.date().year_month_day().year
		% now.date().year_month_day().month.as_number()
		% now.date().year_month_day().day.as_number();

	std::string cur_day_time = f.str();

	return cur_day_time;
}

std::string CMyTime::GetPeriodDate(const int pre_days)
{
	boost::posix_time::ptime cur_time = boost::posix_time::second_clock::local_time();
	boost::posix_time::ptime pre_time;

	//pre_time = cur_time - boost::posix_time::minutes(1);
	//pre_time = cur_time - boost::gregorian::pre_days(40);
	pre_time = cur_time - boost::gregorian::days(pre_days);

	boost::format f = boost::format("%s-%02d-%02d")
		% pre_time.date().year_month_day().year
		% pre_time.date().year_month_day().month.as_number()
		% pre_time.date().year_month_day().day.as_number();

	std::string pre_day_time = f.str();

	return pre_day_time;
}