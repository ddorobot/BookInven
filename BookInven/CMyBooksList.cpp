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

void CMyBooksList::UpdateList(int min_count)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

	//-----
	m_mybook.clear();

#if 0
	CDataBaseBookInHistory cls_db_bookin_history;
	std::vector<BookInHistory> vec_bookin_info;
		
	vec_bookin_info = cls_db_bookin_history.GetInfo(str_date_start, str_date_end);

	int history_size = vec_bookin_info.size();
	for (int i = 0; i < history_size; i++)
	{
		if (!vec_bookin_info[i].reg_date.empty())
		{
			BookIn_List_Info list_info;
			list_info.db_idx = vec_bookin_info[i].db_idx;
			list_info.bookin_info = vec_bookin_info[i].bookin_info;
			list_info.reg_date = vec_bookin_info[i].reg_date;

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

			BookInfo bookin_info = m_mybook[i];

			CString cstr_data;

			if (std::string(str_isbn) != bookin_info.isbn)
			{
				cstr_data.Format(_T("%s"), bookin_info.isbn.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_name) != bookin_info.name)
			{
				cstr_data.Format(_T("%s"), bookin_info.name.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_author) != bookin_info.author)
			{
				cstr_data.Format(_T("%s"), bookin_info.author.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			int book_count = 0;
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
			BookInfo bookin_info = m_mybook[index];

			int list_index = 1;

			//데이타 추가
			//체크박스
			CString cstr_data;

			//code
			cstr_data.Format(_T("%s"), bookin_info.isbn.c_str());
			m_p_list_ctrl->InsertItem(index, cstr_data);

			//이름
			cstr_data.Format(_T("%s"), bookin_info.name.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//저자
			cstr_data.Format(_T("%s"), bookin_info.author.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//수량
			int book_count = 0;
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
