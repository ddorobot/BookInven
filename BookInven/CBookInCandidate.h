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

#include "CDataBaseProvider.h"
#include "CDataBaseBookInHistory.h"

typedef struct BookIn_Candidate_Info {
	BookIn_Info book_info;
	int count = 0;
} BookIn_Candidate_Info;

class CBookInCandidate
{
public:
	CBookInCandidate(CListCtrl* p_list_ctrl);
	~CBookInCandidate();

	void SetListCtrl(CListCtrl* p_list_ctrl);

	void AddCandidate(BookIn_Info candidate);
	void UpdateItem(const int index, const int col_index, const std::string data);
	void ChangeProviderBaseIndex(const int index, const int provider_index);
	void ChangeProvideType(const int index, const int provide_type);
	void UpdateList(void);
	int GetTotalBookCount(void);
	void DelItem(const int index);
	void DelCheckedItem(void);
	std::vector<BookIn_Info> GetCheckedItem(void);
	int CheckedAddDataBase(void);
private:

	boost::mutex mutex_list_ctrl;
	CListCtrl* m_p_list_ctrl;

	boost::mutex mutex_candidate;
	std::deque<BookIn_Candidate_Info> m_candidate;
};

