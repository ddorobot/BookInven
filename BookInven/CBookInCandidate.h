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

class CBookInCandidate
{
public:
	CBookInCandidate(CListCtrl* p_list_ctrl);
	~CBookInCandidate();

	void SetListCtrl(CListCtrl* p_list_ctrl);

	void AddCandidate(const Candidate_BookInfo candidate);
private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	std::deque<Candidate_BookInfo> m_candidate;
};

