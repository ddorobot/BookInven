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

#include "ProviderInfo.h"
#include "CDataBaseProvider.h"

class CProviderInfoList
{
public:
	CProviderInfoList(CListCtrl* p_list_ctrl);
	~CProviderInfoList();

	void SetListCtrl(CListCtrl* p_list_ctrl);

	void UpdateList(void);
	void DelCheckedItem(void);
private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;
};

