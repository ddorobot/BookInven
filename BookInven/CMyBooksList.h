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

#include "BookInfo.h"
#include "CMyTime.h"
#include "CDataBaseBookInfo.h"

class CMyBooksList
{
public:
	CMyBooksList(CListCtrl* p_list_ctrl);
	~CMyBooksList();

	void SetListCtrl(CListCtrl* p_list_ctrl);

	void UpdateList(int min_count = 0);
private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	std::deque<BookInfo> m_mybook;
};

