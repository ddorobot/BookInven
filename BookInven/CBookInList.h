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
#include "ProviderInfo.h"
#include "BookInInfo.h"
#include "CMyTime.h"

#include "CDataBaseProvider.h"
#include "CDataBaseBookInHistory.h"
#include "CCart.h"

typedef struct BookIn_List_Info {
	int db_idx = -1;
	int copy_from_detail_idx = -1;
	BookIn_Info bookin_info;
	std::string reg_date = "";
} BookIn_List_Info;

class CBookInList
{
public:
	CBookInList(CListCtrl* p_list_ctrl);
	~CBookInList();

	void SetListCtrl(CListCtrl* p_list_ctrl);

	int AddInfo(BookIn_Info candidate);
	void UpdateList(std::string str_date_start="", std::string str_date_end="");
	void DelCheckedItem(void);
	int GetCheckedItemCount(void);
private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	std::deque<BookIn_List_Info> m_book_in;
};

