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
#include "CDataBaseBookInHistory.h"
#include "CGetGoodsCount.h"

#include "CMatToBitmap.h"

#include"resource.h"

typedef struct SaleBooksInfo {
	BookInfo book_info;
	CBitmap* pBmp = NULL;
	int count = 0;
} SaleBooksInfo;

class CSaleBooksList
{
public:
	CSaleBooksList(CListCtrl* p_list_ctrl);
	~CSaleBooksList();

	void SetListCtrl(CListCtrl* p_list_ctrl);
	
	void UpdateList(void);

	void AddSaleBook(SaleBooksInfo sale_book_info);
	
	int GetCountInListInfo(const std::string isbn = "");

	void DelCheckedItem(void);

	int GetTotalPrice(void);

private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	std::deque<SaleBooksInfo> m_sale_books;

	CImageList m_image_list;
};

