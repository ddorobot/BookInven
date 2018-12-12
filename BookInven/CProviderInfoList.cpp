#include "CProviderInfoList.h"

CProviderInfoList::CProviderInfoList(CListCtrl* p_list_ctrl) :
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
	m_p_list_ctrl->InsertColumn(1, _T("이름"), LVCFMT_CENTER, 80, -1);
	m_p_list_ctrl->InsertColumn(2, _T("사업자등록번호"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(3, _T("전화번호"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(4, _T("email"), LVCFMT_CENTER, 160, -1);
	m_p_list_ctrl->InsertColumn(5, _T("주소"), LVCFMT_CENTER, 200, -1);
	m_p_list_ctrl->InsertColumn(6, _T("기본공급률"), LVCFMT_CENTER, 100, -1); 
	m_p_list_ctrl->InsertColumn(7, _T("기본공급형태"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(8, _T("기본정산일"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(9, _T("계산서발급"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(10, _T("계좌정보"), LVCFMT_CENTER, 200, -1);
}


CProviderInfoList::~CProviderInfoList()
{
}

void CProviderInfoList::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}

void CProviderInfoList::UpdateList(void)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

	int count = m_p_list_ctrl->GetItemCount();

	//데이타 베이스로부터 정보를 얻어온다.
	CDataBaseProvider cls_db_provider;
	std::vector<ProviderInfo> vec_provider = cls_db_provider.GetInfo();
	int provider_size = vec_provider.size();

	for (int i = 0; i < count; i++)
	{
		//0은 checkbox임
		CString str_name = m_p_list_ctrl->GetItemText(i, 1);
		CString str_lic = m_p_list_ctrl->GetItemText(i, 2);
		CString str_tel = m_p_list_ctrl->GetItemText(i, 3);
		CString str_email = m_p_list_ctrl->GetItemText(i, 4);
		CString str_address = m_p_list_ctrl->GetItemText(i, 5);
		CString str_base_provide_rate = m_p_list_ctrl->GetItemText(i, 6);
		CString str_base_provide_type = m_p_list_ctrl->GetItemText(i, 7);
		CString str_base_calc_day = m_p_list_ctrl->GetItemText(i, 8);
		CString str_receipt_able = m_p_list_ctrl->GetItemText(i, 9);
		CString str_bank = m_p_list_ctrl->GetItemText(i, 10);

		if (i < provider_size)
		{
			ProviderInfo provider = vec_provider[i];

			CString cstr_data;

			if (std::string(str_name) != provider.base.name)
			{
				cstr_data.Format(_T("%s"), provider.base.name.c_str());
				m_p_list_ctrl->SetItemText(i, 1, cstr_data);
			}

			if (std::string(str_lic) != provider.base.lic)
			{
				cstr_data.Format(_T("%s"), provider.base.lic.c_str());
				m_p_list_ctrl->SetItemText(i, 2, cstr_data);
			}

			if (std::string(str_tel) != provider.detail.tel)
			{
				cstr_data.Format(_T("%s"), provider.detail.tel.c_str());
				m_p_list_ctrl->SetItemText(i, 3, cstr_data);
			}

			if (std::string(str_email) != provider.detail.email)
			{
				cstr_data.Format(_T("%s"), provider.detail.email.c_str());
				m_p_list_ctrl->SetItemText(i, 4, cstr_data);
			}

			if (std::string(str_address) != provider.detail.address)
			{
				cstr_data.Format(_T("%s"), provider.detail.address);
				m_p_list_ctrl->SetItemText(i, 5, cstr_data);
			}

			if (atof(str_base_provide_rate) != provider.detail.provide_rate)
			{
				cstr_data.Format(_T("%.2f"), provider.detail.provide_rate);
				m_p_list_ctrl->SetItemText(i, 6, cstr_data);
			}

			std::string provide_type = str_provide_type[cash];
			if(provider.detail.provide_type == credit )	provide_type = str_provide_type[credit];
			if (std::string(str_base_provide_type) != provide_type)
			{
				cstr_data.Format(_T("%s"), provide_type.c_str());
				m_p_list_ctrl->SetItemText(i, 7, cstr_data);
			}

			if (std::string(str_base_calc_day) != std::to_string(provider.detail.calc_day))
			{
				cstr_data.Format(_T("%d"), provider.detail.calc_day);
				m_p_list_ctrl->SetItemText(i, 8, cstr_data);
			}

			//영수증 발급 가능
			std::string receipt_able = "YES";
			if (provider.detail.receipt_able == false)	receipt_able = "NO";
			if (std::string(str_receipt_able) != receipt_able)
			{
				cstr_data.Format(_T("%s"), receipt_able.c_str());
				m_p_list_ctrl->SetItemText(i, 9, cstr_data);
			}

			//은행 정보
			CString str_bank_;
			str_bank_.Format(_T("[%s] %s (예금주:%s)"), provider.detail.bank_name.c_str(), provider.detail.bank_num.c_str(), provider.detail.bank_author.c_str());
			//[] (예금주:)
			if (str_bank != str_bank_)
			{
				str_bank = str_bank_;
				m_p_list_ctrl->SetItemText(i, 10, cstr_data);
			}
		}
	}

	if (count < provider_size)
	{
		for (int index = count; index < provider_size; index++)
		{
			ProviderInfo provider = vec_provider[index];

			//데이타 추가
			/*
			m_p_list_ctrl->InsertColumn(0, _T(""), LVCFMT_CENTER, 20, -1);
			m_p_list_ctrl->InsertColumn(1, _T("이름"), LVCFMT_CENTER, 80, -1);
			m_p_list_ctrl->InsertColumn(2, _T("사업자등록번호"), LVCFMT_CENTER, 100, -1);
			m_p_list_ctrl->InsertColumn(3, _T("전화번호"), LVCFMT_CENTER, 100, -1);
			m_p_list_ctrl->InsertColumn(4, _T("email"), LVCFMT_CENTER, 160, -1);
			m_p_list_ctrl->InsertColumn(5, _T("주소"), LVCFMT_CENTER, 200, -1);
			m_p_list_ctrl->InsertColumn(6, _T("기본공급률"), LVCFMT_CENTER, 100, -1);
			m_p_list_ctrl->InsertColumn(7, _T("기본공급형태"), LVCFMT_CENTER, 100, -1);
			m_p_list_ctrl->InsertColumn(8, _T("기본정산일"), LVCFMT_CENTER, 70, -1);
			m_p_list_ctrl->InsertColumn(9, _T("계산서발급"), LVCFMT_CENTER, 70, -1);
			m_p_list_ctrl->InsertColumn(10, _T("계좌정보"), LVCFMT_CENTER, 200, -1);
			*/
			//날짜
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");

			//이름
			cstr_data.Format(_T("%s"), provider.base.name.c_str());
			m_p_list_ctrl->SetItem(index, 1, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//사업자번호
			cstr_data.Format(_T("%s"), provider.base.lic.c_str());
			m_p_list_ctrl->SetItem(index, 2, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//전화번호
			cstr_data.Format(_T("%s"), provider.detail.tel.c_str());
			m_p_list_ctrl->SetItem(index, 3, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//email
			cstr_data.Format(_T("%s"), provider.detail.email.c_str());
			m_p_list_ctrl->SetItem(index, 4, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//주소
			cstr_data.Format(_T("%d"), provider.detail.address.c_str());
			m_p_list_ctrl->SetItem(index, 5, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//기본공급률
			cstr_data.Format(_T("%.2f"), provider.detail.provide_rate);
			m_p_list_ctrl->SetItem(index, 6, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//기본공급형태
			std::string provide_type = "현매";
			if (provider.detail.provide_type == credit)	provide_type = "위탁";
			cstr_data.Format(_T("%s"), provide_type.c_str());
			m_p_list_ctrl->SetItem(index, 7, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//기본정산일
			cstr_data.Format(_T("%d"), provider.detail.calc_day);
			m_p_list_ctrl->SetItem(index, 8, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//계산서 발급 여부
			std::string receipt_able = "YES";
			if (provider.detail.receipt_able == false)	receipt_able = "NO";
			cstr_data.Format(_T("%s"), receipt_able.c_str());
			m_p_list_ctrl->SetItem(index, 9, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//은행
			//은행 정보
			cstr_data.Format(_T("[%s] %s (예금주:%s)"), provider.detail.bank_name.c_str(), provider.detail.bank_num.c_str(), provider.detail.bank_author.c_str());
			m_p_list_ctrl->SetItem(index, 10, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//checkbox 기본 체크
			m_p_list_ctrl->SetCheck(index, FALSE);
		}
	}
	else if (count > provider_size)
	{
		for (int index = provider_size; index < count; index++)
		{
			m_p_list_ctrl->DeleteItem(index);
		}
	}

	//mutex_candidate.unlock();
}

void CProviderInfoList::DelCheckedItem(void)
{
#if 0
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
#endif
}
