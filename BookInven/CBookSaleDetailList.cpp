#include "CBookSaleDetailList.h"

CBookSaleDetailList::CBookSaleDetailList(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// 리스트 스타일 설정
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	//m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	// 타이틀 삽입
	int list_index = 0;
	m_p_list_ctrl->InsertColumn(list_index++, _T(""), LVCFMT_CENTER, 20, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("입고날짜"), LVCFMT_CENTER, 130, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 110, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("이름"), LVCFMT_CENTER, 150, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("저자"), LVCFMT_CENTER, 100, -1); 
	m_p_list_ctrl->InsertColumn(list_index++, _T("출판사"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("가격"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("거래(변동량)"), LVCFMT_CENTER, 85, -1); 
	m_p_list_ctrl->InsertColumn(list_index++, _T("공급사"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("공급방식"), LVCFMT_CENTER, 60, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("공급률"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("공급가"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("판매가"), LVCFMT_CENTER, 70, -1);
}

CBookSaleDetailList::~CBookSaleDetailList()
{
}

void CBookSaleDetailList::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}

std::string CBookSaleDetailList::GetMemo(const std::string str_sale_code)
{
	CDataBaseBookSaleHistory cls_db_book_sale_history;
	BookSaleHistory book_sale_info = cls_db_book_sale_history.GetInfo(str_sale_code);

	return book_sale_info.memo;
}

void CBookSaleDetailList::UpdateList(const std::string str_sale_code)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

	m_book_sale.clear();
	if (!str_sale_code.empty())
	{
		
		//입고 정보를 얻는다.
		CDataBaseBookInHistoryDetail cls_db_bookin_history_detail;
		std::vector<DB_BookInHistoryDetail> vec_history_detail = cls_db_bookin_history_detail.GetDetail_DB(str_sale_code);
		int detail_size = vec_history_detail.size();


		//-----
		CDataBaseBookInHistory cls_db_bookin_history;
		BookInHistory bookin_info;

		for (int i = 0; i < detail_size; i++)
		{
			bookin_info = cls_db_bookin_history.GetInfo(vec_history_detail[i].base_idx);

			if (!bookin_info.reg_date.empty())
			{
				BookSaleDetailInfo list_info;
				list_info.bookin_list_info.db_idx = bookin_info.db_idx;
				list_info.bookin_list_info.bookin_info = bookin_info.bookin_info;
				list_info.bookin_list_info.reg_date = bookin_info.reg_date;

				//변동 수량 확인
				list_info.trade_type = vec_history_detail[i].detail.type;
				/*
				trade_in,
	trade_sale,
	trade_refund,
	trade_return,
				*/
				if (list_info.trade_type == trade_in || list_info.trade_type == trade_refund)			list_info.bookin_list_info.bookin_info.count = 1;
				else if (list_info.trade_type == trade_sale || list_info.trade_type == trade_return)			list_info.bookin_list_info.bookin_info.count = -1;

				m_book_sale.push_back(list_info);
			}
		}
		//입고 히스토리를 DB에서 모두 가지고 온다.
		//-----
	}

	int count = m_p_list_ctrl->GetItemCount();
	int book_sale_size = m_book_sale.size();

	for (int i = 0; i < count; i++)
	{
		//m_p_list_ctrl->GetItemText(i, 0);

		//isbn
		int list_index = 1;
		CString str_date = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_isbn = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_name = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_author = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_publisher = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_price = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_count = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_provider = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_provide_type = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_provide_rate = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_provide_price = m_p_list_ctrl->GetItemText(i, list_index++);
		CString str_sale_price = m_p_list_ctrl->GetItemText(i, list_index++);

		if (i < book_sale_size)
		{
			int list_index = 1;

			BookSaleDetailInfo book_sale_info = m_book_sale[i];

			CString cstr_data;

			if (std::string(str_date) != book_sale_info.bookin_list_info.reg_date)
			{
				cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.reg_date.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_isbn) != book_sale_info.bookin_list_info.bookin_info.book_info.isbn)
			{
				cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.book_info.isbn.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_name) != book_sale_info.bookin_list_info.bookin_info.book_info.name)
			{
				cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.book_info.name.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_author) != book_sale_info.bookin_list_info.bookin_info.book_info.author)
			{
				cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.book_info.author.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_publisher) != book_sale_info.bookin_list_info.bookin_info.book_info.publisher)
			{
				cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.book_info.publisher.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_price) != std::to_string(book_sale_info.bookin_list_info.bookin_info.book_info.price))
			{
				cstr_data.Format(_T("%d"), book_sale_info.bookin_list_info.bookin_info.book_info.price);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			cstr_data.Format(_T("%s(%d)"), str_book_trade_type[book_sale_info.trade_type].c_str(), book_sale_info.bookin_list_info.bookin_info.count);
			if (str_count != cstr_data)
			{
				//cstr_data.Format(_T("%s(%d)"), str_book_trade_type[book_sale_info.trade_type], book_sale_info.bookin_list_info.bookin_info.count);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_provider) != book_sale_info.bookin_list_info.bookin_info.provider_info.base.name)
			{
				cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.provider_info.base.name.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			std::string provide_type = "현매";
			if (book_sale_info.bookin_list_info.bookin_info.provider_info.detail.provide_type == credit) provide_type = "위탁";
			if (std::string(str_provide_type) != provide_type)
			{
				cstr_data.Format(_T("%s"), provide_type.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			CString str_bookin_info_provide_rate;
			str_bookin_info_provide_rate.Format(_T("%.2f"), book_sale_info.bookin_list_info.bookin_info.provider_info.detail.provide_rate);
			if (str_provide_rate != str_bookin_info_provide_rate)
			{
				//cstr_data.Format(_T("%.2f"), candidate.provider_info.provide_rate);
				m_p_list_ctrl->SetItemText(i, list_index, str_bookin_info_provide_rate);
			}
			list_index++;

			int provide_price = (int)roundf((float)book_sale_info.bookin_list_info.bookin_info.book_info.price * (book_sale_info.bookin_list_info.bookin_info.provider_info.detail.provide_rate / 100.0));
			if (std::string(str_provide_price) != std::to_string(provide_price))
			{
				cstr_data.Format(_T("%d"), provide_price);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_sale_price) != std::to_string(book_sale_info.bookin_list_info.bookin_info.sale_cost))
			{
				cstr_data.Format(_T("%d"), book_sale_info.bookin_list_info.bookin_info.sale_cost);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;
		}
	}

	if (count < book_sale_size)
	{
		for (int index = count; index < book_sale_size; index++)
		{
			BookSaleDetailInfo book_sale_info = m_book_sale[index];

			int list_index = 1;

			//데이타 추가
			//체크박스
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");

			//입고날짜
			cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.reg_date.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//code
			cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.book_info.isbn.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//이름
			cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.book_info.name.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//저자
			cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.book_info.author.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//발행처
			cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.book_info.publisher.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//가격
			cstr_data.Format(_T("%d"), book_sale_info.bookin_list_info.bookin_info.book_info.price);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//수량
			//cstr_data.Format(_T("%d"), book_sale_info.bookin_list_info.bookin_info.count);
			cstr_data.Format(_T("%s(%d)"), str_book_trade_type[book_sale_info.trade_type].c_str(), book_sale_info.bookin_list_info.bookin_info.count);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//공급사
			cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.bookin_info.provider_info.base.name.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//공급방식
			std::string provide_type = "현매";
			if (book_sale_info.bookin_list_info.bookin_info.provider_info.detail.provide_type == credit) provide_type = "위탁";
			cstr_data.Format(_T("%s"), provide_type.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//공급률
			cstr_data.Format(_T("%.2f"), book_sale_info.bookin_list_info.bookin_info.provider_info.detail.provide_rate);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//공급가
			int provide_price = (int)((float)book_sale_info.bookin_list_info.bookin_info.book_info.price * (book_sale_info.bookin_list_info.bookin_info.provider_info.detail.provide_rate / 100.0));
			cstr_data.Format(_T("%d"), provide_price);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//판매가
			cstr_data.Format(_T("%d"), book_sale_info.bookin_list_info.bookin_info.sale_cost);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//checkbox 기본 체크
			m_p_list_ctrl->SetCheck(index, TRUE);
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
}

