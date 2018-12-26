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
#include "CBookInList.h"

#include "CDataBaseBookInHistory.h"
#include "CDataBaseBookInHistoryDetail.h"
#include "CDataBaseBookSaleHistory.h"

typedef struct BookSaleDetailInfo {
	int db_idx = -1 ;
	BookIn_List_Info bookin_list_info;
	std::string memo;
	int trade_type=0;
} BookSaleDetailInfo;

class CBookSaleDetailList
{
public:
	CBookSaleDetailList(CListCtrl* p_list_ctrl);
	~CBookSaleDetailList();

	void SetListCtrl(CListCtrl* p_list_ctrl);

	void UpdateList(const std::string str_sale_code="");
	std::string GetMemo(const std::string str_sale_code);

	int SelectRefund(void);
private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	std::deque<BookSaleDetailInfo> m_book_sale;
};

