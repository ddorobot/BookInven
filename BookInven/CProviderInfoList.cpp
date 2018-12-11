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

	int provider_size = m_provider.size();

	for (int i = 0; i < count; i++)
	{
		//m_p_list_ctrl->GetItemText(i, 0);
		//isbn
		CString str_name = m_p_list_ctrl->GetItemText(i, 1);
		CString str_tel = m_p_list_ctrl->GetItemText(i, 2);
		CString str_email = m_p_list_ctrl->GetItemText(i, 3);
		CString str_address = m_p_list_ctrl->GetItemText(i, 4);
		CString str_base_provide_rate = m_p_list_ctrl->GetItemText(i, 5);
		CString str_base_provide_type = m_p_list_ctrl->GetItemText(i, 6);
		CString str_base_calc_day = m_p_list_ctrl->GetItemText(i, 7);

		if (i < provider_size)
		{
			ProviderInfo provider = m_provider[i];

			CString cstr_data;

			if (std::string(str_name) != provider.name)
			{
				cstr_data.Format(_T("%s"), provider.name.c_str());
				m_p_list_ctrl->SetItemText(i, 1, cstr_data);
			}

			if (std::string(str_tel) != provider.tel)
			{
				cstr_data.Format(_T("%s"), provider.tel.c_str());
				m_p_list_ctrl->SetItemText(i, 2, cstr_data);
			}

			if (std::string(str_email) != provider.email)
			{
				cstr_data.Format(_T("%s"), provider.email.c_str());
				m_p_list_ctrl->SetItemText(i, 3, cstr_data);
			}

			if (std::string(str_address) != provider.address)
			{
				cstr_data.Format(_T("%s"), provider.address);
				m_p_list_ctrl->SetItemText(i, 4, cstr_data);
			}

			if (atof(str_base_provide_rate) != provider.provide_rate)
			{
				cstr_data.Format(_T("%.2f"), provider.provide_rate);
				m_p_list_ctrl->SetItemText(i, 5, cstr_data);
			}

			std::string provide_type = "����";
			if(provider.provide_type == credit )	provide_type = "��Ź";
			if (std::string(str_base_provide_type) != provide_type)
			{
				cstr_data.Format(_T("%s"), provide_type.c_str());
				m_p_list_ctrl->SetItemText(i, 6, cstr_data);
			}

			if (std::string(str_base_calc_day) != std::to_string(provider.calc_day))
			{
				cstr_data.Format(_T("%d"), provider.calc_day);
				m_p_list_ctrl->SetItemText(i, 7, cstr_data);
			}

		}
	}

	if (count < provider_size)
	{
		for (int index = count; index < provider_size; index++)
		{
			ProviderInfo provider = m_provider[index];

			//����Ÿ �߰�
			//��¥
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");

			//�̸�
			cstr_data.Format(_T("%s"), provider.name.c_str());
			m_p_list_ctrl->SetItem(index, 1, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//��ȭ��ȣ
			cstr_data.Format(_T("%s"), provider.tel.c_str());
			m_p_list_ctrl->SetItem(index, 2, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//email
			cstr_data.Format(_T("%s"), provider.email.c_str());
			m_p_list_ctrl->SetItem(index, 3, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�ּ�
			cstr_data.Format(_T("%d"), provider.address.c_str());
			m_p_list_ctrl->SetItem(index, 4, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�⺻���޷�
			cstr_data.Format(_T("%.2f"), provider.provide_rate);
			m_p_list_ctrl->SetItem(index, 5, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�⺻��������
			std::string provide_type = "����";
			if (provider.provide_type == credit)	provide_type = "��Ź";
			cstr_data.Format(_T("%s"), provide_type.c_str());
			m_p_list_ctrl->SetItem(index, 6, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�⺻������
			cstr_data.Format(_T("%d"), provider.calc_day);
			m_p_list_ctrl->SetItem(index, 7, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//checkbox �⺻ üũ
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
			// üũ���� Ȯ��

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

		//���� ���� ���� �������� Checked�� FALSE���� �Ѵ�.
		count = m_p_list_ctrl->GetItemCount();
		for (int i = 0; i < count; i++)
		{
			m_p_list_ctrl->SetCheck(i, FALSE);
		}
	}
#endif
}
