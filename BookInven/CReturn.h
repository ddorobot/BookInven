#pragma once

#include <string>

#include "BookInInfo.h"
#include "CDataBaseBookInHistory.h"
#include "CDataBaseReturn.h"

typedef struct ReturnInfo {
	int db_idx = -1;
	BookIn_Info bookin_info;
	int count = 0;
} ReturnInfo;

class CReturn
{
public:
	CReturn();
	~CReturn();

	int AddReturn(const std::string isbn);		//isbn�� �ش�Ǵ� ��ǰ�� ���� 1�� �߰�
	int PopReturn(const std::string isbn);		//isbn�� �ش�Ǵ� ��ǰ�� ���� 1�� ����
	int DelReturn(const std::string isbn, const bool bret=true);		//isbn�� �ش�Ǵ� ��ǰ�� ��� ���� ����
	int GetReturnCount(void);
	std::vector<int> GetReturnAllIndex(void);
	std::vector<ReturnInfo> GetReturnData(const std::string isbn="");
	int GetCount(const int index);

	int DelReturnItem(const int bookin_index);
};

