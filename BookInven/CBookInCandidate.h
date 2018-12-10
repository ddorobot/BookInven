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

typedef struct Candidate_BookInfo {
	BookInfo book_info;
	int count = 1;
	ProviderInfo provider_info;
	float sale_rate = 0.0;
	int salce_cost = 0;
} Candidate_BookInfo;

const int i_candidate_data_item_size = 12;
const std::string arr_str_candidate_data_item[] = {
"",
"CODE",
"이름",
"저자",
"출판사",
"가격",
"수량",
"공급사",
"공급방식",
"공급률",
"공급가",
"판매가"
};

const int arr_i_candidate_data_item_size[] = {
20,
110,
200,
100,
100,
70,
50,
50,
60,
50,
70,
70
};

class CBookInCandidate
{
public:
	CBookInCandidate(CListCtrl* p_list_ctrl);
	~CBookInCandidate();

	void SetListCtrl(CListCtrl* p_list_ctrl);

	void AddCandidate(const Candidate_BookInfo candidate);

	void UpdateList(void);
private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	boost::mutex mutex_candidate;
	std::deque<Candidate_BookInfo> m_candidate;
};

