#include "CSaleBooksList.h"

CSaleBooksList::CSaleBooksList(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// 리스트 스타일 설정
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// 타이틀 삽입
	int list_index = 0;
	m_p_list_ctrl->InsertColumn(list_index++, _T(""), LVCFMT_CENTER, 20, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("수량"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("가격"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("이름"), LVCFMT_CENTER, 150, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("저자"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 110, -1);
	
}


CSaleBooksList::~CSaleBooksList()
{
}

void CSaleBooksList::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}

void CSaleBooksList::UpdateList(void)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

	//-----
	//m_sale_books.clear();
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

			m_sale_books.push_back(list_info);
		}
	}
#endif
	//DB에서 정보를 가지고 온다.
	//-----

	int count = m_p_list_ctrl->GetItemCount();

	int book_sale_size = m_sale_books.size();

	for (int i = 0; i < count; i++)
	{
		//m_p_list_ctrl->GetItemText(i, 0);

		//isbn
		int list_index = 1;
		CString str_isbn = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_name = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_author = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_count = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_price = m_p_list_ctrl->GetItemText(i, list_index++);

		if (i < book_sale_size)
		{
			int list_index = 1;

			BookInfo book_info = m_sale_books[i].book_info;
			int book_count = m_sale_books[i].count;

			CString cstr_data;

			if (std::string(str_count) != std::to_string(book_count))
			{
				cstr_data.Format(_T("%d"), book_count);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			int price = 0;
			if (std::string(str_price) != std::to_string(price))
			{
				cstr_data.Format(_T("%d"), price);
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

			if (std::string(str_isbn) != book_info.isbn)
			{
				cstr_data.Format(_T("%s"), book_info.isbn.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

		}
	}

	if (count < book_sale_size)
	{
		for (int index = count; index < book_sale_size; index++)
		{
			BookInfo book_info = m_sale_books[index].book_info;
			int book_count = m_sale_books[index].count;

			int list_index = 1;

			//데이타 추가
			//체크박스
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");

			//code
			cstr_data.Format(_T(""), book_info.isbn.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//이름
			cstr_data.Format(_T("%s"), book_info.name.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//저자
			cstr_data.Format(_T("%s"), book_info.author.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//수량
			cstr_data.Format(_T("%d"), book_count);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//가격
			int price = 0;
			cstr_data.Format(_T("%d"), price);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);
		}
	}
	else if (count > book_sale_size)
	{
		for (int index = book_sale_size; index < count; index++)
		{
			m_p_list_ctrl->DeleteItem(index);
		}
	}

	m_p_list_ctrl->Invalidate(TRUE);

	//mutex_candidate.unlock();
}

void CSaleBooksList::AddSaleBook(SaleBooksInfo sale_book_info)
{
	//같은 정보가 있는지 확인
	//m_sale_books
	//find
	int sale_size = m_sale_books.size();

	int exist_same_data_index = -1;

	for (int i = 0; i < sale_size; i++)
	{
		if (sale_book_info.book_info.isbn == m_sale_books[i].book_info.isbn)
		{
			exist_same_data_index = i;
			break;
		}
	}

	if (exist_same_data_index >= 0)
	{
		//수량 수정
		m_sale_books[exist_same_data_index].count += sale_book_info.count;
	}
	else
	{
		m_sale_books.push_back(sale_book_info);
	}
}