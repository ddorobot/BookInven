#pragma once

#include "CDataBase.h"
#include "ProviderInfo.h"

//table name
#define TABLE_NAME_PROVIDER_DETAIL		"TProviderDetail"
#define TABLE_DATA_PROVIDER_DETAIL		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
										'base_idx' INTEGER, \
										'tel' TEXT, \
										'email' TEXT, \
										'address' TEXT, \
										'base_provide_rate' FLOAT, \
										'base_provide_type' INTEGER, \
										'base_calc_day' INTEGER , \
										'receipt_able' BOOLEAN , \
										'bank_name' TEXT , \
										'bank_num' TEXT , \
										'bank_author' TEXT , \
										'memo' TEXT , \
										'reg_date' TEXT"

typedef struct DB_ProviderDetailInfo {
	int idx = -1;
	int base_idx = -1;
	ProviderInfoDetail detail;
	std::string reg_date;
} DB_ProviderDetailInfo;

class CDataBaseProviderDetail : CDataBase
{
public:
	CDataBaseProviderDetail();
	~CDataBaseProviderDetail();

	int AddProviderDetailInfo(const int base_idx, const ProviderInfoDetail provider);
	ProviderInfoDetail GetProviderDetailInfo(const int idx, int* out_base_idx=NULL);
private:
	bool CheckDataSameValue(const ProviderInfoDetail provider);
	DB_ProviderDetailInfo GetLastInfo(void);

	static int sql_callback_get_provider(void *NotUsed, int argc, char **argv, char **azColName);
};

