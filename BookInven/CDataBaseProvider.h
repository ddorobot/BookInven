#pragma once

#include "CDataBase.h"
#include "ProviderInfo.h"
#include "CDataBaseProviderDetail.h"

//table name
#define TABLE_NAME_PROVIDER		"TProvider"
#define TABLE_DATA_PROVIDER		"'idx'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
								'detail_idx' INTEGER, \
								'name' TEXT, \
								'lic' TEXT, \
								'reg_date' TEXT"

typedef struct DB_ProviderInfo {
	int idx = -1;
	int detail_idx = -1;
	ProviderInfoBase base;
	std::string reg_date;
} DB_ProviderInfo;

class CDataBaseProvider : CDataBase
{
public:
	CDataBaseProvider();
	~CDataBaseProvider();

	void AddProviderInfo(const ProviderInfo provider);
	std::vector<ProviderInfo> GetInfo(const std::string name, const std::string lic);
	std::vector<ProviderInfo> GetInfo(void);
	void SetDetailIndex(const int base_idx, const int detail_idx);
	DB_ProviderInfo GetLastInfo(void);

	int GetProviderSize(void);

	void UpdateProviderInfo(const int base_index, const ProviderInfo provider);

private:
	bool CheckData(const ProviderInfoBase provider);
	bool CheckDataSameValue(const ProviderInfo provider);
	DB_ProviderInfo GetLastInfo(const std::string name, const std::string lic);

	int AddProviderBaseInfo(ProviderInfoBase provider);

	static int sql_callback_get_provider(void *NotUsed, int argc, char **argv, char **azColName);
	static int sql_callback_get_count(void *count, int argc, char **argv, char **azColName);
};

