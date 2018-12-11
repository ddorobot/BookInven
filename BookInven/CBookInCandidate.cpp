#include "CBookInCandidate.h"

CBookInCandidate::CBookInCandidate(CListCtrl* p_list_ctrl) :
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
	m_p_list_ctrl->InsertColumn(1, _T("CODE"), LVCFMT_CENTER, 110, -1);
	m_p_list_ctrl->InsertColumn(2, _T("�̸�"), LVCFMT_CENTER, 200, -1);
	m_p_list_ctrl->InsertColumn(3, _T("����"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(4, _T("���ǻ�"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(5, _T("����"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(6, _T("����"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(7, _T("���޻�"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(8, _T("���޹��"), LVCFMT_CENTER, 60, -1);
	m_p_list_ctrl->InsertColumn(9, _T("���޷�"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(10, _T("���ް�"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(11, _T("�ǸŰ�"), LVCFMT_CENTER, 70, -1);
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

void CBookInCandidate::AddCandidate(Candidate_BookInfo candidate)
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
		//���� ����
		m_candidate[exist_same_data_index].count += candidate.count;
	}
	else
	{
		candidate.sale_cost = candidate.book_info.price;
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
			Candidate_BookInfo candidate = m_candidate[i];

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

			if (std::string(str_provider) != candidate.provider_info.name)
			{
				cstr_data.Format(_T("%s"), candidate.provider_info.name.c_str());
				m_p_list_ctrl->SetItemText(i, 7, cstr_data);
			}

			if (std::string(str_provide_type) != candidate.provider_info.type)
			{
				cstr_data.Format(_T("%s"), candidate.provider_info.type.c_str());
				m_p_list_ctrl->SetItemText(i, 8, cstr_data);
			}

			CString str_candidate_provide_rate; 
			str_candidate_provide_rate.Format(_T("%.2f"), candidate.provider_info.provide_rate);
			if (str_provide_rate != str_candidate_provide_rate)
			{
				//cstr_data.Format(_T("%.2f"), candidate.provider_info.provide_rate);
				m_p_list_ctrl->SetItemText(i, 9, str_candidate_provide_rate);
			}

			int provide_price = (int)roundf((float)candidate.book_info.price * (candidate.provider_info.provide_rate / 100.0));
			if (std::string(str_provide_price) != std::to_string(provide_price) )
			{
				cstr_data.Format(_T("%d"), provide_price);
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
			Candidate_BookInfo candidate = m_candidate[index];

			//����Ÿ �߰�
			//��¥
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");

			//code
			cstr_data.Format(_T("%s"), candidate.book_info.isbn.c_str());
			m_p_list_ctrl->SetItem(index, 1, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�̸�
			cstr_data.Format(_T("%s"), candidate.book_info.name.c_str());
			m_p_list_ctrl->SetItem(index, 2, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����
			cstr_data.Format(_T("%s"), candidate.book_info.author.c_str());
			m_p_list_ctrl->SetItem(index, 3, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����ó
			cstr_data.Format(_T("%s"), candidate.book_info.publisher.c_str());
			m_p_list_ctrl->SetItem(index, 4, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����
			cstr_data.Format(_T("%d"), candidate.book_info.price);
			m_p_list_ctrl->SetItem(index, 5, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����
			cstr_data.Format(_T("%d"), candidate.count);
			m_p_list_ctrl->SetItem(index, 6, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//���޻�
			cstr_data.Format(_T("%s"), candidate.provider_info.name.c_str());
			m_p_list_ctrl->SetItem(index, 7, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//���޹��
			cstr_data.Format(_T("%s"), candidate.provider_info.type.c_str());
			m_p_list_ctrl->SetItem(index, 8, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//���޷�
			cstr_data.Format(_T("%.2f"), candidate.provider_info.provide_rate);
			m_p_list_ctrl->SetItem(index, 9, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//���ް�
			int provide_price = (int)((float)candidate.book_info.price * (candidate.provider_info.provide_rate/100.0));
			cstr_data.Format(_T("%d"), provide_price);
			m_p_list_ctrl->SetItem(index, 10, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�ǸŰ�
			cstr_data.Format(_T("%d"), candidate.sale_cost);
			m_p_list_ctrl->SetItem(index, 11, LVIF_TEXT, cstr_data, 0, 0, 0, NULL); 

			//checkbox �⺻ üũ
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

void CBookInCandidate::UpdateItem(const int index, const int col_index, const std::string data)
{
	const int candidate_size = m_candidate.size();

	if (index >= 0 && index < candidate_size)
	{
		switch(col_index)
		{
		case 0 : 
			//checkbox
			break;
		case 1:
			//code
			break;
		case 2:
			//�̸�
			m_candidate[index].book_info.name = data;
			break;
		case 3:
			//����
			m_candidate[index].book_info.author = data;
			break;
		case 4:
			//���ǻ�
			m_candidate[index].book_info.publisher = data;
			break;
		case 5:
			//����
			m_candidate[index].book_info.price = std::stoi(data);
			break;
		case 6:
			//����
			m_candidate[index].count = std::stoi(data);
			break;
		case 7:
			//���޻�
			m_candidate[index].provider_info.name = data;
			break;
		case 8:
			//���޹��
			m_candidate[index].provider_info.type = data;
			break;
		case 9:
			//���޷�
			m_candidate[index].provider_info.provide_rate = std::stof(data);
			//���ް��� ����
			//int price = (int)((float)(m_candidate[index].book_info.price) * (m_candidate[index].provider_info.provide_rate / 100.0));
			break;
		case 10:
			//���ް� �� ���� �Ǹ� ���޷��� �ݿ��� ������ ���� �ȴ�.
			//���� = ���ް�  / ���޷�
			m_candidate[index].book_info.price = (int)roundf(std::stof(data) / (m_candidate[index].provider_info.provide_rate/100.0));
			//m_candidate[index].provider_info.provide_rate =   / (float)(m_candidate[index].book_info.price) * 100.0; 
			//���ݵ� ���� �ȴ�.
			
			break;
		case 11:
			//�ǸŰ�
			m_candidate[index].sale_cost = std::stoi(data);
			break;
		}
	}
}