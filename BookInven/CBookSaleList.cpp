#include "CBookSaleList.h"

CBookSaleList::CBookSaleList(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// 리스트 스타일 설정
	//m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	// 타이틀 삽입
	int list_index = 0;
	//m_p_list_ctrl->InsertColumn(list_index++, _T(""), LVCFMT_CENTER, 20, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("판매날짜"), LVCFMT_CENTER, 110, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 130, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("판매수량"), LVCFMT_CENTER, 60, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("판매금액"), LVCFMT_CENTER, 60, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("할인금액"), LVCFMT_CENTER, 60, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("결제방법"), LVCFMT_CENTER, 60, -1);
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

std::string CBookSaleList::GetSaleCode(const int index)
{
	std::string str_sale_code;
	
	int sale_size = m_book_sale.size();

	if (index < sale_size && index >= 0)
	{
		str_sale_code = m_book_sale[index].code;
	}

	return str_sale_code;
}

void CBookSaleList::UpdateList(std::string str_date_start, std::string str_date_end)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

#if 1
	//-----
	m_book_sale.clear();

	CDataBaseBookSaleHistory cls_db_book_sale_history;
	std::vector<BookSaleHistory> vec_book_sale_info;
		
	vec_book_sale_info = cls_db_book_sale_history.GetInfo(str_date_start, str_date_end);

	int history_size = vec_book_sale_info.size();
	for (int i = 0; i < history_size; i++)
	{
		if (!vec_book_sale_info[i].code.empty())
		{
			BookSale_List_Info list_info;
			list_info.code = vec_book_sale_info[i].code;
			list_info.discount = vec_book_sale_info[i].discount;
			list_info.count = vec_book_sale_info[i].count;
			list_info.sale_cost = vec_book_sale_info[i].sale_cost;
			list_info.cash = vec_book_sale_info[i].cash;
			list_info.reg_date = vec_book_sale_info[i].reg_date;

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
		int list_index = 0;
		CString str_date = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_code = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_count = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_sale_cost = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_discount = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_sale_type = m_p_list_ctrl->GetItemText(i, list_index++);

		if (i < book_in_size)
		{
			int list_index = 0;

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

			std::string str_sale_type_ = "카드";
			if(book_sale_info.cash == true)	str_sale_type_ = "현금";

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
			//m_p_list_ctrl->InsertItem(index, "");
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
			//m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);
			m_p_list_ctrl->InsertItem(index, cstr_data);

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
			std::string str_sale_type_ = "카드";
			if (book_sale_info.cash == true)	str_sale_type_ = "현금";
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
			m_p_list_ctrl->DeleteItem(book_in_size);
		}
	}
#endif
	m_p_list_ctrl->Invalidate(TRUE);
}

