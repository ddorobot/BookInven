#pragma once

#include "CDataBase.h"
#include "ProviderInfo.h"

//table name
#define TABLE_NAME_BOOK_IN		"TProvider"
#define TABLE_DATA_BOOK_IN		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
								'name' TEXT, \
								'tel' TEXT, \
								'email' TEXT, \
								'adress' TEXT, \
								'base_provide_rate' TEXT, \
								'base_provide_type' TEXT, \
								'base_calc_date' INTEGER , \
								'memo' INTEGER , \
								'reg_date' TEXT"

typedef struct DB_ProviderInfo {
	int idx = -1;
	ProviderInfo provider_info;
	std::string memo;
} DB_ProviderInfo;

class CDataBaseProvider : CDataBase
{
public:
	CDataBaseProvider();
	~CDataBaseProvider();
};

