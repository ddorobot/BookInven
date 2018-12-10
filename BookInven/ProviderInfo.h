#pragma once

#include <string>

typedef struct ProviderInfo {
	std::string id;
	std::string name;
	std::string tel;
	std::string email;
	float provide_rate = 70.0;
} ProviderInfo;
