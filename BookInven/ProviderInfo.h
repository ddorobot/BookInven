#pragma once

#include <string>

enum ProvideType
{
	cash=0,
	credit,
	provide_type_size
};

const std::string str_provide_type[provide_type_size] =
{
	"Çö¸Å",
	"À§Å¹"
};

enum ReceiptAngle
{
	receipt_no = 0,
	receipt_yes
};

#define PROVIDE_BASE_RATE		70.0
#define PROVIDE_BASE_TYPE		cash
#define PROVIDE_BASE_CALC_DAY	1

typedef struct ProviderInfo {
	std::string name = "";
	std::string tel = "";
	std::string email = "";
	std::string address = "";
	float provide_rate = PROVIDE_BASE_RATE;
	int provide_type = PROVIDE_BASE_TYPE;
	int calc_day = PROVIDE_BASE_CALC_DAY;
	bool receipt_able = false;
	std::string bank_name = "";
	std::string bank_num = "";
	std::string bank_author = "";
} ProviderInfo;
