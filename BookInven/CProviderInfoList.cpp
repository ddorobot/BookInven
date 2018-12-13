#include "CProviderInfoList.h"

CProviderInfoList::CProviderInfoList(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// ����Ʈ ��Ÿ�� ����
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// Ÿ��Ʋ ����
	m_p_list_ctrl->InsertColumn(0, _T(""), LVCFMT_CENTER, 20, -1);
	m_p_list_ctrl->InsertColumn(1, _T("�̸�"), LVCFMT_CENTER, 150, -1);
	m_p_list_ctrl->InsertColumn(2, _T("����ڵ�Ϲ�ȣ"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(3, _T("��ȭ��ȣ"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(4, _T("email"), LVCFMT_CENTER, 160, -1);
	m_p_list_ctrl->InsertColumn(5, _T("�ּ�"), LVCFMT_CENTER, 200, -1);
	m_p_list_ctrl->InsertColumn(6, _T("�⺻���޷�"), LVCFMT_CENTER, 100, -1); 
	m_p_list_ctrl->InsertColumn(7, _T("�⺻��������"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(8, _T("�⺻������"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(9, _T("��꼭�߱�"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(10, _T("��������"), LVCFMT_CENTER, 200, -1);
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

void CProviderInfoList::Search(const std::string keyword)
{
	CDataBaseProvider cls_db_provider;
	std::vector<ProviderInfo> vec_provider = cls_db_provider.GetInfo();
	int provider_size = vec_provider.size();

	std::vector<ProviderInfo> vec_search_provider;

	//std::cout << boost::algorithm::contains("å���", "å") << std::endl;

	for (int i = 0; i < provider_size; i++)
	{
		ProviderInfo provider = vec_provider[i];

		bool search = false;
		
		if (keyword.empty() || keyword == "*")
		{
			search = true;
		}

		//name
		size_t pos = -1;
		std::string find_string = provider.base.name;
		if (boost::algorithm::contains(find_string, keyword) && search == false && !find_string.empty())
		{
			search = true;
		}

		//std::cout << "test : " << find_string  << " vs " << keyword << " = " << boost::algorithm::contains(find_string, keyword) << std::endl;

		//lic
		pos = -1;
		find_string = provider.base.lic;
		if (boost::algorithm::contains(find_string, keyword) && search == false && !find_string.empty())
		{
			search = true;
		}

		//std::cout << "test : " << find_string << " vs " << keyword << " = " << boost::algorithm::contains(find_string, keyword) << std::endl;

		//tel
		pos = -1;
		find_string = provider.detail.tel;
		if (boost::algorithm::contains(find_string, keyword) && search == false && !find_string.empty())
		{
			search = true;
		}

		//std::cout << "test : " << find_string << " vs " << keyword << " = " << boost::algorithm::contains(find_string, keyword) << std::endl;

		//adree
		pos = -1;
		find_string = provider.detail.address;
		if (boost::algorithm::contains(find_string, keyword) && search == false && !find_string.empty())
		{
			search = true;
		}

		//std::cout << "test : " << find_string << " vs " << keyword << " = " << boost::algorithm::contains(find_string, keyword) << std::endl;

		//email
		pos = -1;
		find_string = provider.detail.email;
		if (boost::algorithm::contains(find_string, keyword) && search == false && !find_string.empty())
		{
			search = true;
		}

		//std::cout << "test : " << find_string << " vs " << keyword << " = " << boost::algorithm::contains(find_string, keyword) << std::endl;

		if (search)
		{
			vec_search_provider.push_back(vec_provider[i]);
		}
	}

	m_vec_provider.clear();
	m_vec_provider = vec_search_provider;

	UpdateList();
}

void CProviderInfoList::UpdateList(void)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

	int count = m_p_list_ctrl->GetItemCount();

	//����Ÿ ���̽��κ��� ������ ���´�.
	//CDataBaseProvider cls_db_provider;
	//m_vec_provider = cls_db_provider.GetInfo();
	int provider_size = m_vec_provider.size();

	for (int i = 0; i < count; i++)
	{
		//0�� checkbox��
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
			ProviderInfo provider = m_vec_provider[i];

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
				cstr_data.Format(_T("%s"), provider.detail.address.c_str());
				m_p_list_ctrl->SetItemText(i, 5, cstr_data);
			}

			if (atof(str_base_provide_rate) != provider.detail.provide_rate)
			{
				cstr_data.Format(_T("%.2f %%"), provider.detail.provide_rate);
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
				cstr_data.Format(_T("%d��"), provider.detail.calc_day);
				m_p_list_ctrl->SetItemText(i, 8, cstr_data);
			}

			//������ �߱� ����
			std::string receipt_able = "YES";
			if (provider.detail.receipt_able == false)	receipt_able = "NO";
			if (std::string(str_receipt_able) != receipt_able)
			{
				cstr_data.Format(_T("%s"), receipt_able.c_str());
				m_p_list_ctrl->SetItemText(i, 9, cstr_data);
			}

			//���� ����
			CString str_bank_;
			str_bank_.Format(_T("[%s] %s (������:%s)"), provider.detail.bank_name.c_str(), provider.detail.bank_num.c_str(), provider.detail.bank_author.c_str());
			//[] (������:)
			if (str_bank != str_bank_)
			{
				cstr_data = str_bank_;
				m_p_list_ctrl->SetItemText(i, 10, cstr_data);
			}
		}
	}

	if (count < provider_size)
	{
		for (int index = count; index < provider_size; index++)
		{
			ProviderInfo provider = m_vec_provider[index];

			//����Ÿ �߰�
			/*
			m_p_list_ctrl->InsertColumn(0, _T(""), LVCFMT_CENTER, 20, -1);
			m_p_list_ctrl->InsertColumn(1, _T("�̸�"), LVCFMT_CENTER, 80, -1);
			m_p_list_ctrl->InsertColumn(2, _T("����ڵ�Ϲ�ȣ"), LVCFMT_CENTER, 100, -1);
			m_p_list_ctrl->InsertColumn(3, _T("��ȭ��ȣ"), LVCFMT_CENTER, 100, -1);
			m_p_list_ctrl->InsertColumn(4, _T("email"), LVCFMT_CENTER, 160, -1);
			m_p_list_ctrl->InsertColumn(5, _T("�ּ�"), LVCFMT_CENTER, 200, -1);
			m_p_list_ctrl->InsertColumn(6, _T("�⺻���޷�"), LVCFMT_CENTER, 100, -1);
			m_p_list_ctrl->InsertColumn(7, _T("�⺻��������"), LVCFMT_CENTER, 100, -1);
			m_p_list_ctrl->InsertColumn(8, _T("�⺻������"), LVCFMT_CENTER, 70, -1);
			m_p_list_ctrl->InsertColumn(9, _T("��꼭�߱�"), LVCFMT_CENTER, 70, -1);
			m_p_list_ctrl->InsertColumn(10, _T("��������"), LVCFMT_CENTER, 200, -1);
			*/
			//��¥
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");

			//�̸�
			cstr_data.Format(_T("%s"), provider.base.name.c_str());
			m_p_list_ctrl->SetItem(index, 1, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����ڹ�ȣ
			cstr_data.Format(_T("%s"), provider.base.lic.c_str());
			m_p_list_ctrl->SetItem(index, 2, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//��ȭ��ȣ
			cstr_data.Format(_T("%s"), provider.detail.tel.c_str());
			m_p_list_ctrl->SetItem(index, 3, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//email
			cstr_data.Format(_T("%s"), provider.detail.email.c_str());
			m_p_list_ctrl->SetItem(index, 4, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�ּ�
			cstr_data.Format(_T("%s"), provider.detail.address.c_str());
			m_p_list_ctrl->SetItem(index, 5, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�⺻���޷�
			cstr_data.Format(_T("%.2f %%"), provider.detail.provide_rate);
			m_p_list_ctrl->SetItem(index, 6, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�⺻��������
			std::string provide_type = "����";
			if (provider.detail.provide_type == credit)	provide_type = "��Ź";
			cstr_data.Format(_T("%s"), provide_type.c_str());
			m_p_list_ctrl->SetItem(index, 7, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�⺻������
			cstr_data.Format(_T("%d��"), provider.detail.calc_day);
			m_p_list_ctrl->SetItem(index, 8, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//��꼭 �߱� ����
			std::string receipt_able = "YES";
			if (provider.detail.receipt_able == false)	receipt_able = "NO";
			cstr_data.Format(_T("%s"), receipt_able.c_str());
			m_p_list_ctrl->SetItem(index, 9, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����
			//���� ����
			cstr_data.Format(_T("[%s] %s (������:%s)"), provider.detail.bank_name.c_str(), provider.detail.bank_num.c_str(), provider.detail.bank_author.c_str());
			m_p_list_ctrl->SetItem(index, 10, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//checkbox �⺻ üũ
			m_p_list_ctrl->SetCheck(index, FALSE);
		}
	}
	else if (count > provider_size)
	{
		//printf("del list : provider_size=%d, count=%d\n", provider_size, count);

		for (int index = count-1; index >= provider_size; index--)	//list indexing�� �ڿ������� ����
		{
			//printf(" - del index : %d\n", index);

			m_p_list_ctrl->DeleteItem(index);
		}

		//int re_count = m_p_list_ctrl->GetItemCount();
		//printf(" - re_count : %d\n", re_count);
	}

	m_p_list_ctrl->Invalidate(TRUE);

	//mutex_candidate.unlock();
}

void CProviderInfoList::DelCheckedItem(void)
{
#if 1
	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		const int provider_size = m_vec_provider.size();

		if (count > 0)
		{
			CDataBaseProvider cls_db_provider;

			for (int i = 0; i < count; i++)
			{
				// üũ���� Ȯ��

				if (m_p_list_ctrl->GetCheck(i))
				{
					if (i < provider_size)
					{
						//DB�� ���� ����
						cls_db_provider.Delete(m_vec_provider[i].base.idx);
					}
				}
			}
		}
	}

	//Update List

#endif
}

ProviderInfo CProviderInfoList::GetProviderInfoInList(const int index)
{
	ProviderInfo ret_provider_info;
	int provider_size = m_vec_provider.size();

	if (index >= 0 && index < provider_size)
	{
		ret_provider_info = m_vec_provider[index];
	}

	return ret_provider_info;
}

int CProviderInfoList::GetProviderInfoIndexInList(const int list_index)
{
	int ret = -1;
	int provider_size = m_vec_provider.size();

	if (list_index >= 0 && list_index < provider_size)
	{
		ret = m_vec_provider[list_index].base.idx;
	}

	return ret;
}

