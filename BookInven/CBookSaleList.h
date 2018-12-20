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

#include "CDataBaseBookSaleHistory.h"

typedef struct BookSale_List_Info {
	int db_idx = -1;
	std::string code = "";
	int discount = 0;
	int sale_cost = 0;
	bool cash = false;
	std::string reg_date = "";
} BookSale_List_Info;


class CBookSaleList
{
public:
	CBookSaleList(CListCtrl* p_list_ctrl);
	~CBookSaleList();

	void SetListCtrl(CListCtrl* p_list_ctrl);

	void UpdateList(std::string str_date_start="", std::string str_date_end="");
private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	std::deque<BookSale_List_Info> m_book_sale;
};

