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

#define PROVIDE_BASE_RATE			70.0
#define PROVIDE_BASE_TYPE			cash
#define PROVIDE_BASE_CALC_DAY		1
#define PROVIDE_BASE_RECEIPT_ABLE	0

typedef struct ProviderInfoBase {
	std::string name = "";
	std::string lic = "";
} ProviderInfoBase;

typedef struct ProviderInfoDetail {
	std::string tel = "";
	std::string email = "";
	std::string address = "";
	float provide_rate = PROVIDE_BASE_RATE;
	int provide_type = PROVIDE_BASE_TYPE;
	int calc_day = PROVIDE_BASE_CALC_DAY;
	bool receipt_able = (bool)PROVIDE_BASE_RECEIPT_ABLE;
	std::string bank_name = "";
	std::string bank_num = "";
	std::string bank_author = "";
	std::string memo;
} ProviderInfoDetail;

typedef struct ProviderInfo {
	ProviderInfoBase base;
	ProviderInfoDetail detail;
} ProviderInfo;