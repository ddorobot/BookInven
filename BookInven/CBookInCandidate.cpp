#include "CBookInCandidate.h"

CBookInCandidate::CBookInCandidate(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// 리스트 스타일 설정
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// 타이틀 삽입
	m_p_list_ctrl->InsertColumn(0, _T(""), LVCFMT_CENTER, 20, -1);
	m_p_list_ctrl->InsertColumn(1, _T("CODE"), LVCFMT_CENTER, 110, -1);
	m_p_list_ctrl->InsertColumn(2, _T("이름"), LVCFMT_CENTER, 150, -1);
	m_p_list_ctrl->InsertColumn(3, _T("저자"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(4, _T("출판사"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(5, _T("가격"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(6, _T("수량"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(7, _T("공급사"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(8, _T("공급방식"), LVCFMT_CENTER, 60, -1);
	m_p_list_ctrl->InsertColumn(9, _T("공급률"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(10, _T("공급가"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(11, _T("판매가"), LVCFMT_CENTER, 70, -1);
}


CBookInCandidate::~CBookInCandidate()
{
}

void CBookInCandidate::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}

void CBookInCandidate::AddCandidate(BookIn_Info candidate)
{
	//mutex_candidate.lock();

	//find
	int candidate_size = m_candidate.size();

	int exist_same_data_index = -1;

	for (int i = 0; i < candidate_size; i++)
	{
		if (candidate.book_info.isbn == m_candidate[i].book_info.isbn)
		{
			exist_same_data_index = i;
			break;
		}
	}

	if (exist_same_data_index >= 0)
	{
		//수량 수정
		m_candidate[exist_same_data_index].count += candidate.count;
	}
	else
	{
		candidate.sale_cost = candidate.book_info.price;
		int provide_price = (int)((float)candidate.book_info.price * (candidate.provider_info.detail.provide_rate / 100.0));
		candidate.provider_info.detail.provide_cost = provide_price;

		m_candidate.push_back(candidate);
	}

	//mutex_candidate.unlock();
}

void CBookInCandidate::UpdateList(void)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

	int count = m_p_list_ctrl->GetItemCount();

	int candidate_size = m_candidate.size();

	for (int i = 0; i < count; i++)
	{
		//m_p_list_ctrl->GetItemText(i, 0);

		//isbn
		CString str_isbn = m_p_list_ctrl->GetItemText(i, 1);
		CString str_name = m_p_list_ctrl->GetItemText(i, 2);
		CString str_author = m_p_list_ctrl->GetItemText(i, 3);
		CString str_publisher = m_p_list_ctrl->GetItemText(i, 4);
		CString str_price = m_p_list_ctrl->GetItemText(i, 5);
		CString str_count = m_p_list_ctrl->GetItemText(i, 6);
		CString str_provider = m_p_list_ctrl->GetItemText(i, 7);
		CString str_provide_type = m_p_list_ctrl->GetItemText(i, 8);
		CString str_provide_rate = m_p_list_ctrl->GetItemText(i, 9);
		CString str_provide_price = m_p_list_ctrl->GetItemText(i, 10);
		CString str_sale_price = m_p_list_ctrl->GetItemText(i, 11);

		if (i < candidate_size)
		{
			BookIn_Info candidate = m_candidate[i];

			CString cstr_data;
			if (std::string(str_isbn) != candidate.book_info.isbn)
			{
				cstr_data.Format(_T("%s"), candidate.book_info.isbn.c_str());
				m_p_list_ctrl->SetItemText(i, 1, cstr_data);
			}

			if (std::string(str_name) != candidate.book_info.name)
			{
				cstr_data.Format(_T("%s"), candidate.book_info.name.c_str());
				m_p_list_ctrl->SetItemText(i, 2, cstr_data);
			}

			if (std::string(str_author) != candidate.book_info.author)
			{
				cstr_data.Format(_T("%s"), candidate.book_info.author.c_str());
				m_p_list_ctrl->SetItemText(i, 3, cstr_data);
			}

			if (std::string(str_publisher) != candidate.book_info.publisher)
			{
				cstr_data.Format(_T("%s"), candidate.book_info.publisher.c_str());
				m_p_list_ctrl->SetItemText(i, 4, cstr_data);
			}

			if (std::string(str_price) != std::to_string(candidate.book_info.price))
			{
				cstr_data.Format(_T("%d"), candidate.book_info.price);
				m_p_list_ctrl->SetItemText(i, 5, cstr_data);
			}

			if (std::string(str_count) != std::to_string(candidate.count))
			{
				cstr_data.Format(_T("%d"), candidate.count);
				m_p_list_ctrl->SetItemText(i, 6, cstr_data);
			}

			if (std::string(str_provider) != candidate.provider_info.base.name)
			{
				cstr_data.Format(_T("%s"), candidate.provider_info.base.name.c_str());
				m_p_list_ctrl->SetItemText(i, 7, cstr_data);
			}

			std::string provide_type = "현매";
			if(candidate.provider_info.detail.provide_type == credit ) provide_type = "위탁";
			if (std::string(str_provide_type) != provide_type)
			{
				cstr_data.Format(_T("%s"), provide_type.c_str());
				m_p_list_ctrl->SetItemText(i, 8, cstr_data);
			}

			CString str_candidate_provide_rate; 
			str_candidate_provide_rate.Format(_T("%.2f"), candidate.provider_info.detail.provide_rate);
			if (str_provide_rate != str_candidate_provide_rate)
			{
				m_p_list_ctrl->SetItemText(i, 9, str_candidate_provide_rate);
			}

			if (std::string(str_provide_price) != std::to_string(candidate.provider_info.detail.provide_cost) )
			{
				cstr_data.Format(_T("%d"), candidate.provider_info.detail.provide_cost);
				m_p_list_ctrl->SetItemText(i, 10, cstr_data);
			}

			if (std::string(str_sale_price) != std::to_string(candidate.sale_cost))
			{
				cstr_data.Format(_T("%d"), candidate.sale_cost);
				m_p_list_ctrl->SetItemText(i, 11, cstr_data);
			}
		}
	}

	if (count < candidate_size)
	{
		for (int index = count; index < candidate_size; index++)
		{
			BookIn_Info candidate = m_candidate[index];

			//데이타 추가
			//날짜
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");

			//code
			cstr_data.Format(_T("%s"), candidate.book_info.isbn.c_str());
			m_p_list_ctrl->SetItem(index, 1, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//이름
			cstr_data.Format(_T("%s"), candidate.book_info.name.c_str());
			m_p_list_ctrl->SetItem(index, 2, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//저자
			cstr_data.Format(_T("%s"), candidate.book_info.author.c_str());
			m_p_list_ctrl->SetItem(index, 3, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//발행처
			cstr_data.Format(_T("%s"), candidate.book_info.publisher.c_str());
			m_p_list_ctrl->SetItem(index, 4, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//가격
			cstr_data.Format(_T("%d"), candidate.book_info.price);
			m_p_list_ctrl->SetItem(index, 5, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//수량
			cstr_data.Format(_T("%d"), candidate.count);
			m_p_list_ctrl->SetItem(index, 6, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//공급사
			cstr_data.Format(_T("%s"), candidate.provider_info.base.name.c_str());
			m_p_list_ctrl->SetItem(index, 7, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//공급방식
			std::string provide_type = "현매";
			if (candidate.provider_info.detail.provide_type == credit) provide_type = "위탁";
			cstr_data.Format(_T("%s"), provide_type.c_str());
			m_p_list_ctrl->SetItem(index, 8, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//공급률
			cstr_data.Format(_T("%.2f"), candidate.provider_info.detail.provide_rate);
			m_p_list_ctrl->SetItem(index, 9, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//공급가
			cstr_data.Format(_T("%d"), candidate.provider_info.detail.provide_cost);
			m_p_list_ctrl->SetItem(index, 10, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//판매가
			cstr_data.Format(_T("%d"), candidate.sale_cost);
			m_p_list_ctrl->SetItem(index, 11, LVIF_TEXT, cstr_data, 0, 0, 0, NULL); 

			//checkbox 기본 체크
			m_p_list_ctrl->SetCheck(index, TRUE);
		}
	}
	else if (count > candidate_size)
	{
		for (int index = candidate_size; index < count; index++)
		{
			m_p_list_ctrl->DeleteItem(index);
		}
	}

	//mutex_candidate.unlock();
}

int CBookInCandidate::GetTotalBookCount(void)
{
	int ret = 0;

	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();

		const int candidate_size = m_candidate.size();
		for (int i = 0; i < candidate_size; i++)
		{
			if (i < count)
			{
				if (m_p_list_ctrl->GetCheck(i))
				{
					ret += m_candidate[i].count;
				}
			}
		}
	}

	return ret;
}

void CBookInCandidate::ChangeProviderBaseIndex(const int index, const int provider_index)
{
	const int candidate_size = m_candidate.size();

	if (index >= 0 && index < candidate_size)
	{
		//DB로부터 정보를 가지고와서 base정보를 변경 한다.
		CDataBaseProvider cls_db_provider;
		ProviderInfoBase provider_info_base = cls_db_provider.GetBaseInfo(provider_index);

		if (provider_index == provider_info_base.idx)
		{
			m_candidate[index].provider_info.base = provider_info_base;
		}
	}
}

void CBookInCandidate::ChangeProvideType(const int index, const int provide_type)
{
	const int candidate_size = m_candidate.size();

	if (index >= 0 && index < candidate_size)
	{
		m_candidate[index].provider_info.detail.provide_type = provide_type;
	}
}


void CBookInCandidate::UpdateItem(const int index, const int col_index, const std::string data)
{
	const int candidate_size = m_candidate.size();

	if (index >= 0 && index < candidate_size)
	{
		switch (col_index)
		{
		case 0:
			//checkbox
			break;
		case 1:
			//code
			break;
		case 2:
			//이름
			m_candidate[index].book_info.name = data;
			break;
		case 3:
			//저자
			m_candidate[index].book_info.author = data;
			break;
		case 4:
			//출판사
			m_candidate[index].book_info.publisher = data;
			break;
		case 5:
			//가격
			m_candidate[index].book_info.price = std::stoi(data);
			//공급가도 변경
			m_candidate[index].provider_info.detail.provide_cost = (int)roundf((float)(m_candidate[index].book_info.price) * (m_candidate[index].provider_info.detail.provide_rate / 100.0));
			break;
		case 6:
			//수량
			m_candidate[index].count = std::stoi(data);
			break;
		case 7:
#if 0
			//공급사
			m_candidate[index].provider_info.base.name = data;
#endif
			break;
		case 8:
#if 0
		{
			//공급방식
			int provide_type = 0;
			if (data == "위탁") provide_type = 1;
			m_candidate[index].provider_info.detail.provide_type = provide_type;
		}
#endif
		break;
		case 9:
			//공급률
			m_candidate[index].provider_info.detail.provide_rate = std::stof(data);
			//공급가도 변경
			m_candidate[index].provider_info.detail.provide_cost = (int)roundf((float)(m_candidate[index].book_info.price) * (m_candidate[index].provider_info.detail.provide_rate / 100.0));
			break;
		case 10:
		{
			//공급가 가 변경 되면 공급률을 반영한 가격이 변경 된다.
			int provide_cost = std::stoi(data);

			if (provide_cost < m_candidate[index].book_info.price && provide_cost >= 0)
			{
				m_candidate[index].provider_info.detail.provide_cost = provide_cost;

#if 1		//가격을 변경하는게 아니라 공급률을 변경 해야 한다.
				if (m_candidate[index].book_info.price == m_candidate[index].provider_info.detail.provide_cost)
				{
					m_candidate[index].provider_info.detail.provide_rate = 0.0;
				}
				else
				{
					m_candidate[index].provider_info.detail.provide_rate = 100.0 - ((float)(m_candidate[index].book_info.price - m_candidate[index].provider_info.detail.provide_cost) / (float)(m_candidate[index].book_info.price)) * 100.0;
				}
			}
#else 
				//가격 = 공급가  / 공급률
				m_candidate[index].book_info.price = (int)roundf(m_candidate[index].provider_info.detail.provide_cost / (m_candidate[index].provider_info.detail.provide_rate / 100.0));
				//m_candidate[index].provider_info.provide_rate =   / (float)(m_candidate[index].book_info.price) * 100.0; 
				//가격도 변경 된다.
#endif
		}
			break;
		case 11:
			//판매가
			m_candidate[index].sale_cost = std::stoi(data);
			break;
		}
	}
}

std::vector<BookIn_Info> CBookInCandidate::GetCheckedItem(void)
{
	std::vector<BookIn_Info> ret_vec_info;

	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		const int candidate_size = m_candidate.size();

		for (int i = 0; i < count; i++)
		{
			// 체크상태 확인
			if (m_p_list_ctrl->GetCheck(i))
			{
				if (i < candidate_size)
				{
					ret_vec_info.push_back(m_candidate[i]);
				}
			}
		}
	}

	return ret_vec_info;
}

void CBookInCandidate::DelItem(const int index)
{
	if (m_p_list_ctrl != NULL)
	{
		int iter_count = 0;
		for (auto it = m_candidate.begin(); it != m_candidate.end(); )
		{
			if (index == iter_count)
			{
				it = m_candidate.erase(it);
			}
			else
			{
				++it;
			}

			iter_count++;
		}
	}
}

void CBookInCandidate::DelCheckedItem(void)
{
	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		const int candidate_size = m_candidate.size();

		std::deque<int> deque_del_index;
		for (int i = 0; i < count; i++)
		{
			// 체크상태 확인

			if (m_p_list_ctrl->GetCheck(i))
			{
				if (i < candidate_size)
				{
					deque_del_index.push_back(i);
				}
			}
		}

		int iter_count = 0;
		for (auto it = m_candidate.begin(); it != m_candidate.end(); ) 
		{
			int deque_del_size = deque_del_index.size();
			if (deque_del_size <= 0) break;

			int del_index = deque_del_index[0];

			if (del_index == iter_count)
			{
				it = m_candidate.erase(it);

				deque_del_index.pop_front();
			}
			else
			{
				++it;
			}

			iter_count++;
		}

		//삭제 되지 않은 아이템은 Checked가 FALSE여야 한다.
		count = m_p_list_ctrl->GetItemCount();
		for (int i = 0; i < count; i++)
		{
			m_p_list_ctrl->SetCheck(i, FALSE);
		}
	}
}

void CBookInCandidate::AddDataBase(void)
{
}