#pragma once

#include <afxcmn.h>

#include <deque>
#include <iostream>

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "boost/algorithm/string.hpp"


#include "ProviderInfo.h"
#include "CDataBaseProvider.h"

class CProviderInfoList
{
public:
	CProviderInfoList(CListCtrl* p_list_ctrl);
	~CProviderInfoList();

	void SetListCtrl(CListCtrl* p_list_ctrl);
	void DelCheckedItem(void);
	ProviderInfo GetProviderInfoInList(const int index);
	int GetProviderInfoIndexInList(const int list_index);		//provider 정보에 DB index번호를 리턴
	void Search(const std::string keyword);

private:
	void UpdateList(void);
	 
	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	std::vector<ProviderInfo> m_vec_provider;

	std::string m_str_search;
};

