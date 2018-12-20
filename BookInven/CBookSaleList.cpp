#include "CBookSaleList.h"

CBookSaleList::CBookSaleList(CListCtrl* p_list_ctrl) :
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
	m_p_list_ctrl->InsertColumn(list_index++, _T("판매날짜"), LVCFMT_CENTER, 130, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 130, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("판매수량"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("판매금액"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("할인금액"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("결제방밥"), LVCFMT_CENTER, 70, -1);
}

CBookSaleList::~CBookSaleList()
{
}

void CBookSaleList::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}

void CBookSaleList::UpdateList(std::string str_date_start, std::string str_date_end)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

#if 1
	//-----
	m_book_sale.clear();

	CDataBaseBookSaleHistory cls_db_book_sale_history;
	std::vector<BookSaleInfo> vec_book_sale_info;
		
	vec_book_sale_info = cls_db_book_sale_history.GetInfo(str_date_start, str_date_end);

	int history_size = vec_book_sale_info.size();
	for (int i = 0; i < history_size; i++)
	{
		if (!vec_book_sale_info[i].db_sale_book_info.reg_date.empty())
		{
			BookSale_List_Info list_info;
			list_info.db_idx = vec_book_sale_info[i].db_sale_book_info.idx;
			list_info.code = vec_book_sale_info[i].db_sale_book_info.code;
			list_info.discount = vec_book_sale_info[i].db_sale_book_info.discount;
			list_info.count = vec_book_sale_info[i].db_sale_book_info.count;
			list_info.sale_cost = vec_book_sale_info[i].db_sale_book_info.sale_cost;
			list_info.cash = vec_book_sale_info[i].db_sale_book_info.cash;
			list_info.reg_date = vec_book_sale_info[i].db_sale_book_info.reg_date;

			int detail_info_size = vec_book_sale_info[i].vec_sale_books_info.size();

			for (int j = 0; j < detail_info_size; j++) 
			{
				list_info.count += vec_book_sale_info[i].vec_sale_books_info[j].count;
			}

			m_book_sale.push_back(list_info);
		}
	}
	//입고 히스토리를 DB에서 모두 가지고 온다.
	//-----

	int count = m_p_list_ctrl->GetItemCount();

	int book_in_size = m_book_sale.size();

	for (int i = 0; i < count; i++)
	{
		//m_p_list_ctrl->GetItemText(i, 0);

		/*
		m_p_list_ctrl->InsertColumn(list_index++, _T(""), LVCFMT_CENTER, 20, -1);
		m_p_list_ctrl->InsertColumn(list_index++, _T("판매날짜"), LVCFMT_CENTER, 130, -1);
		m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 200, -1);
		m_p_list_ctrl->InsertColumn(list_index++, _T("판매금액"), LVCFMT_CENTER, 150, -1);
		m_p_list_ctrl->InsertColumn(list_index++, _T("할인금액"), LVCFMT_CENTER, 150, -1);
		m_p_list_ctrl->InsertColumn(list_index++, _T("결제방밥"), LVCFMT_CENTER, 100, -1);
		*/
		//isbn
		int list_index = 1;
		CString str_date = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_code = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_count = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_sale_cost = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_discount = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_sale_type = m_p_list_ctrl->GetItemText(i, list_index++);

		if (i < book_in_size)
		{
			int list_index = 1;

			BookSale_List_Info book_sale_info = m_book_sale[i];

			CString cstr_data;

			if (std::string(str_date) != book_sale_info.reg_date)
			{
				cstr_data.Format(_T("%s"), book_sale_info.reg_date.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_code) != book_sale_info.code)
			{
				cstr_data.Format(_T("%s"), book_sale_info.code.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_count) != std::to_string(book_sale_info.count))
			{
				cstr_data.Format(_T("%d"), book_sale_info.count);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_sale_cost) != std::to_string(book_sale_info.sale_cost))
			{
				cstr_data.Format(_T("%d"), book_sale_info.sale_cost);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_discount) != std::to_string(book_sale_info.discount))
			{
				cstr_data.Format(_T("%d"), book_sale_info.discount);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			std::string str_sale_type_ = "카드 결제";
			if(book_sale_info.cash == true)	str_sale_type_ = "현금 결제";

			if (std::string(str_sale_type) != str_sale_type_)
			{
				cstr_data.Format(_T("%s"), str_sale_type_.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;
		}
	}

	if (count < book_in_size)
	{
		for (int index = count; index < book_in_size; index++)
		{
			BookSale_List_Info book_sale_info = m_book_sale[index];

			int list_index = 1;

			//데이타 추가
			//체크박스
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");
			/*
			m_p_list_ctrl->InsertColumn(list_index++, _T(""), LVCFMT_CENTER, 20, -1);
			m_p_list_ctrl->InsertColumn(list_index++, _T("판매날짜"), LVCFMT_CENTER, 130, -1);
			m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 200, -1);
			m_p_list_ctrl->InsertColumn(list_index++, _T("판매금액"), LVCFMT_CENTER, 150, -1);
			m_p_list_ctrl->InsertColumn(list_index++, _T("할인금액"), LVCFMT_CENTER, 150, -1);
			m_p_list_ctrl->InsertColumn(list_index++, _T("결제방밥"), LVCFMT_CENTER, 100, -1);
			*/
			//입고날짜
			cstr_data.Format(_T("%s"), book_sale_info.reg_date.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//code
			cstr_data.Format(_T("%s"), book_sale_info.code.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//count	
			cstr_data.Format(_T("%d"), book_sale_info.count);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//판매금액
			cstr_data.Format(_T("%d"), book_sale_info.sale_cost);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//할인금액
			cstr_data.Format(_T("%d"), book_sale_info.discount);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//결제방법
			std::string str_sale_type_ = "카드 결제";
			if (book_sale_info.cash == true)	str_sale_type_ = "현금 결제";
			cstr_data.Format(_T("%s"), str_sale_type_.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//checkbox 기본 체크
			m_p_list_ctrl->SetCheck(index, FALSE);
		}
	}
	else if (count > book_in_size)
	{
		for (int index = book_in_size; index < count; index++)
		{
			m_p_list_ctrl->DeleteItem(index);
		}
	}
#endif
	m_p_list_ctrl->Invalidate(TRUE);
}

