#include "CMyBooksList.h"

CMyBooksList::CMyBooksList(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// 리스트 스타일 설정
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/);
	// 타이틀 삽입
	int list_index = 0;
	m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 110, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("이름"), LVCFMT_CENTER, 150, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("저자"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("재고"), LVCFMT_CENTER, 50, -1);
}


CMyBooksList::~CMyBooksList()
{
}

void CMyBooksList::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}

BookInfo CMyBooksList::GetBookInfoInList(const int index)
{
	BookInfo ret_book_info;
	int bookinfo_size = m_mybook.size();

	if (index >= 0 && index < bookinfo_size)
	{
		ret_book_info = m_mybook[index].book_info;
	}

	return ret_book_info;
}

int CMyBooksList::GetBookInfoIndexInList(const int list_index)
{
	int ret = -1;
	int provider_size = m_mybook.size();

	if (list_index >= 0 && list_index < provider_size)
	{
		ret = m_mybook[list_index].book_info.idx;
	}

	return ret;
}



void CMyBooksList::UpdateList(int min_count)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

	//-----
	m_mybook.clear();

	CDataBaseBookInfo cls_db_book_info;
	std::vector<BookInfo> vec_book_info = cls_db_book_info.GetAllInfo();

	int book_info_size = vec_book_info.size();

	for (int i = 0; i < book_info_size; i++)
	{
		BookInfoList bookinfolist;

		//Book정보 얻기
		bookinfolist.book_info = vec_book_info[i];

		//Book정보의 isbn을 이용하여 입/출고 count를 이용하여 재고량 확인
		//입고량
		CDataBaseBookInHistory cls_db_book_in_history; 
		int book_in_count = cls_db_book_in_history.GetBookCount(bookinfolist.book_info.isbn);

		bookinfolist.count = book_in_count;

		m_mybook.push_back(bookinfolist);
	}
#if 0
	CDataBaseBookInHistory cls_db_bookin_history;
	std::vector<BookInHistory> vec_book_info;
		
	vec_book_info = cls_db_bookin_history.GetInfo(str_date_start, str_date_end);

	int history_size = vec_book_info.size();
	for (int i = 0; i < history_size; i++)
	{
		if (!vec_book_info[i].reg_date.empty())
		{
			BookIn_List_Info list_info;
			list_info.db_idx = vec_book_info[i].db_idx;
			list_info.book_info = vec_book_info[i].book_info;
			list_info.reg_date = vec_book_info[i].reg_date;

			m_mybook.push_back(list_info);
		}
	}
#endif
	//DB에서 정보를 가지고 온다.
	//-----

	int count = m_p_list_ctrl->GetItemCount();

	int book_in_size = m_mybook.size();

	for (int i = 0; i < count; i++)
	{
		//m_p_list_ctrl->GetItemText(i, 0);

		//isbn
		int list_index = 0;
		CString str_isbn = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_name = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_author = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_count = m_p_list_ctrl->GetItemText(i, list_index++);

		if (i < book_in_size)
		{
			int list_index = 0;

			BookInfo book_info = m_mybook[i].book_info;
			int book_count = m_mybook[i].count;

			CString cstr_data;

			if (std::string(str_isbn) != book_info.isbn)
			{
				cstr_data.Format(_T("%s"), book_info.isbn.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_name) != book_info.name)
			{
				cstr_data.Format(_T("%s"), book_info.name.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_author) != book_info.author)
			{
				cstr_data.Format(_T("%s"), book_info.author.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_count) != std::to_string(book_count))
			{
				cstr_data.Format(_T("%d"), book_count);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;
		}
	}

	if (count < book_in_size)
	{
		for (int index = count; index < book_in_size; index++)
		{
			BookInfo book_info = m_mybook[index].book_info;
			int book_count = m_mybook[index].count;

			int list_index = 1;

			//데이타 추가
			//체크박스
			CString cstr_data;

			//code
			cstr_data.Format(_T("%s"), book_info.isbn.c_str());
			m_p_list_ctrl->InsertItem(index, cstr_data);

			//이름
			cstr_data.Format(_T("%s"), book_info.name.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//저자
			cstr_data.Format(_T("%s"), book_info.author.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//수량
			cstr_data.Format(_T("%d"), book_count);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);
		}
	}
	else if (count > book_in_size)
	{
		for (int index = book_in_size; index < count; index++)
		{
			m_p_list_ctrl->DeleteItem(index);
		}
	}

	m_p_list_ctrl->Invalidate(TRUE);

	//mutex_candidate.unlock();
}
