#include "CBookSaleDetailList.h"

CBookSaleDetailList::CBookSaleDetailList(CListCtrl* p_list_ctrl, bool b_check, bool b_only_able_refund) :
	m_p_list_ctrl(NULL)
	, m_b_only_able_refund(b_only_able_refund)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// 리스트 스타일 설정
	if (b_check)
	{
		m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	}
	else
	{
		m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	}

	// 타이틀 삽입
	int list_index = 0;
	//m_p_list_ctrl->InsertColumn(list_index++, _T(""), LVCFMT_CENTER, 20, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("날짜"), LVCFMT_CENTER, 130, -1);
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

int CBookSaleDetailList::CheckedRefund(void)
{
	int ret = 0;

	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		const int book_in_size = m_book_sale.size();

		int refund_count = 0;
		for (int i = 0; i < count; i++)
		{
			// 체크상태 확인
			if (m_p_list_ctrl->GetCheck(i))
			{
				if (i < book_in_size)
				{
					BookSaleDetailInfo sale_detail_info = m_book_sale[i];

#if 0
					CDataBaseBookSaleHistory cls_db_book_sale_history;
					BookSaleHistory sale_history = cls_db_book_sale_history.GetInfo(sale_detail_info.bookin_list_info.db_idx);

					//History Detail에 refund 상태 추가
					CDataBaseBookInHistoryDetail cls_db_book_in_detail;
					if (cls_db_book_in_detail.AddDetail(sale_detail_info.bookin_list_info.db_idx, 0, trade_refund, sale_history.code))
					{
						//refund된 정보를 새로 입고
						CDataBaseBookInHistory cls_db_bookin_history;
						cls_db_bookin_history.CopyAddBookInInfo(sale_detail_info.db_idx);
					}
#else
					CDataBaseBookInHistory cls_db_bookin_history;
					if (cls_db_bookin_history.Refund(sale_detail_info.db_idx))
					{
						refund_count++;
					}
#endif
				}
			}
		}

		if (refund_count == count)
		{
			ret = 1;
		}

		//삭제 되지 않은 아이템은 Checked가 FALSE여야 한다.
		/*
		count = m_p_list_ctrl->GetItemCount();
		for (int i = 0; i < count; i++)
		{
			m_p_list_ctrl->SetCheck(i, FALSE);
		}
		*/
	}

	return ret;
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

		std::vector<DB_BookInHistoryDetail> vec_history_detail_unit;
		if (m_b_only_able_refund)
		{
			//동일한 base_idx를 갖은 정보중에 가장 최근의 (idx가 큰) 값만 갖는다.
			//Detail 정보의 base index를 이용하여 Detail에서 재 검색. 
			for (int i=0; i < detail_size; i++ )
			{
				DB_BookInHistoryDetail detail = vec_history_detail[i];

				bool b_exist = false;
				int detail_unit_size = vec_history_detail_unit.size();
				for (int j = 0; j < detail_unit_size; j++)
				{
					DB_BookInHistoryDetail detail_unit = vec_history_detail_unit[j];

					if (detail.base_idx == detail_unit.base_idx)
					{
						if (detail.idx > detail_unit.idx)
						{
							//최근의 정보로 변경 한다.
							vec_history_detail_unit[j] = vec_history_detail[i];
						}

						b_exist = true;
					}
				}

				if (b_exist == false )
				{
					vec_history_detail_unit.push_back(detail);
				}
			}
		}
		else
		{
			vec_history_detail_unit = vec_history_detail;
		}
		
		detail_size = vec_history_detail_unit.size();
		

		//-----
		CDataBaseBookInHistory cls_db_bookin_history;
		BookInHistory bookin_info;

		//for (int i = 0; i < detail_size; i++)
		for (int i = detail_size-1; i >= 0; i--)
		{
			DB_BookInHistoryDetail detail = vec_history_detail_unit[i];

			//상태가 판매 상태(trade_sale) 이어야만 환불 가능 하다.
			if (detail.detail.type != trade_sale && m_b_only_able_refund )
			{
				continue;
			}

			bookin_info = cls_db_bookin_history.GetInfo(detail.base_idx);

			if (!bookin_info.reg_date.empty())
			{
				BookSaleDetailInfo list_info;
				list_info.db_idx = detail.idx;
				list_info.bookin_list_info.db_idx = bookin_info.db_idx;
				list_info.bookin_list_info.bookin_info = bookin_info.bookin_info;
				list_info.bookin_list_info.reg_date = detail.reg_date;

				//변동 수량 확인
				list_info.trade_type = detail.detail.type;
				list_info.bookin_list_info.bookin_info.count = detail.detail.book_count;
				
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
		int list_index = 0;
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
			int list_index = 0;

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
			//m_p_list_ctrl->InsertItem(index, "");

			//입고날짜
			cstr_data.Format(_T("%s"), book_sale_info.bookin_list_info.reg_date.c_str());
			//m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);
			m_p_list_ctrl->InsertItem(index, cstr_data);

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
			//m_p_list_ctrl->SetCheck(index, TRUE);
		}
	}
	else if (count > book_sale_size)
	{
		for (int index = book_sale_size; index < count; index++)
		{
			m_p_list_ctrl->DeleteItem(book_sale_size);
		}
	}

	m_p_list_ctrl->Invalidate(TRUE);
}

