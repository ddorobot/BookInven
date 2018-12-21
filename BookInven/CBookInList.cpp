#include "CBookInList.h"

CBookInList::CBookInList(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// ����Ʈ ��Ÿ�� ����
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// Ÿ��Ʋ ����
	int list_index = 0;
	m_p_list_ctrl->InsertColumn(list_index++, _T(""), LVCFMT_CENTER, 20, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("�԰�¥"), LVCFMT_CENTER, 130, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 110, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("�̸�"), LVCFMT_CENTER, 150, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("����"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("���ǻ�"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("����"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("����"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("���޻�"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("���޹��"), LVCFMT_CENTER, 60, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("���޷�"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("���ް�"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("�ǸŰ�"), LVCFMT_CENTER, 70, -1);
}


CBookInList::~CBookInList()
{
}

void CBookInList::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}

int CBookInList::AddInfo(BookIn_Info info)
{
	int ret = 0;

	BookIn_List_Info list_info;
	list_info.bookin_info = info;

	
}

void CBookInList::UpdateList(std::string str_date_start, std::string str_date_end)
{
	if (m_p_list_ctrl == NULL) return;

	//mutex_candidate.lock();

	//-----
	m_book_in.clear();

	CDataBaseBookInHistory cls_db_bookin_history;
	std::vector<BookInHistory> vec_bookin_info;
		
	vec_bookin_info = cls_db_bookin_history.GetInfo(str_date_start, str_date_end);

	int history_size = vec_bookin_info.size();
	for (int i = 0; i < history_size; i++)
	{
		if (!vec_bookin_info[i].reg_date.empty())
		{
			BookIn_List_Info list_info;
			list_info.db_idx = vec_bookin_info[i].db_idx;
			list_info.bookin_info = vec_bookin_info[i].bookin_info;
			list_info.reg_date = vec_bookin_info[i].reg_date;

			m_book_in.push_back(list_info);
		}
	}
	//�԰� �����丮�� DB���� ��� ������ �´�.
	//-----

	int count = m_p_list_ctrl->GetItemCount();

	int book_in_size = m_book_in.size();

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

		if (i < book_in_size)
		{
			int list_index = 1;

			BookIn_List_Info bookin_info = m_book_in[i];

			CString cstr_data;

			if (std::string(str_date) != bookin_info.reg_date)
			{
				cstr_data.Format(_T("%s"), bookin_info.reg_date.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_isbn) != bookin_info.bookin_info.book_info.isbn)
			{
				cstr_data.Format(_T("%s"), bookin_info.bookin_info.book_info.isbn.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_name) != bookin_info.bookin_info.book_info.name)
			{
				cstr_data.Format(_T("%s"), bookin_info.bookin_info.book_info.name.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_author) != bookin_info.bookin_info.book_info.author)
			{
				cstr_data.Format(_T("%s"), bookin_info.bookin_info.book_info.author.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_publisher) != bookin_info.bookin_info.book_info.publisher)
			{
				cstr_data.Format(_T("%s"), bookin_info.bookin_info.book_info.publisher.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_price) != std::to_string(bookin_info.bookin_info.book_info.price))
			{
				cstr_data.Format(_T("%d"), bookin_info.bookin_info.book_info.price);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_count) != std::to_string(1))
			{
				cstr_data.Format(_T("%d"), 1);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_provider) != bookin_info.bookin_info.provider_info.base.name)
			{
				cstr_data.Format(_T("%s"), bookin_info.bookin_info.provider_info.base.name.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			std::string provide_type = "����";
			if(bookin_info.bookin_info.provider_info.detail.provide_type == credit ) provide_type = "��Ź";
			if (std::string(str_provide_type) != provide_type)
			{
				cstr_data.Format(_T("%s"), provide_type.c_str());
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			CString str_bookin_info_provide_rate;
			str_bookin_info_provide_rate.Format(_T("%.2f"), bookin_info.bookin_info.provider_info.detail.provide_rate);
			if (str_provide_rate != str_bookin_info_provide_rate)
			{
				//cstr_data.Format(_T("%.2f"), candidate.provider_info.provide_rate);
				m_p_list_ctrl->SetItemText(i, list_index, str_bookin_info_provide_rate);
			}
			list_index++;

			int provide_price = (int)roundf((float)bookin_info.bookin_info.book_info.price * (bookin_info.bookin_info.provider_info.detail.provide_rate / 100.0));
			if (std::string(str_provide_price) != std::to_string(provide_price) )
			{
				cstr_data.Format(_T("%d"), provide_price);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;

			if (std::string(str_sale_price) != std::to_string(bookin_info.bookin_info.sale_cost))
			{
				cstr_data.Format(_T("%d"), bookin_info.bookin_info.sale_cost);
				m_p_list_ctrl->SetItemText(i, list_index, cstr_data);
			}
			list_index++;
		}
	}

	if (count < book_in_size)
	{
		for (int index = count; index < book_in_size; index++)
		{
			BookIn_List_Info bookin_info = m_book_in[index];

			int list_index = 1;

			//����Ÿ �߰�
			//üũ�ڽ�
			CString cstr_data;
			m_p_list_ctrl->InsertItem(index, "");

			//�԰�¥
			cstr_data.Format(_T("%s"), bookin_info.reg_date.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//code
			cstr_data.Format(_T("%s"), bookin_info.bookin_info.book_info.isbn.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�̸�
			cstr_data.Format(_T("%s"), bookin_info.bookin_info.book_info.name.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����
			cstr_data.Format(_T("%s"), bookin_info.bookin_info.book_info.author.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����ó
			cstr_data.Format(_T("%s"), bookin_info.bookin_info.book_info.publisher.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����
			cstr_data.Format(_T("%d"), bookin_info.bookin_info.book_info.price);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//����
			cstr_data.Format(_T("%d"), 1);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//���޻�
			cstr_data.Format(_T("%s"), bookin_info.bookin_info.provider_info.base.name.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//���޹��
			std::string provide_type = "����";
			if (bookin_info.bookin_info.provider_info.detail.provide_type == credit) provide_type = "��Ź";
			cstr_data.Format(_T("%s"), provide_type.c_str());
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//���޷�
			cstr_data.Format(_T("%.2f"), bookin_info.bookin_info.provider_info.detail.provide_rate);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//���ް�
			int provide_price = (int)((float)bookin_info.bookin_info.book_info.price * (bookin_info.bookin_info.provider_info.detail.provide_rate/100.0));
			cstr_data.Format(_T("%d"), provide_price);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//�ǸŰ�
			cstr_data.Format(_T("%d"), bookin_info.bookin_info.sale_cost);
			m_p_list_ctrl->SetItem(index, list_index++, LVIF_TEXT, cstr_data, 0, 0, 0, NULL);

			//checkbox �⺻ üũ
			m_p_list_ctrl->SetCheck(index, TRUE);
		}
	}
	else if (count > book_in_size)
	{
		for (int index = book_in_size; index < count; index++)
		{
			m_p_list_ctrl->DeleteItem(index);
		}
	}

	m_p_list_ctrl->Invalidate(TRUE);

	//mutex_candidate.unlock();
}

int CBookInList::GetCheckedItemCount(void)
{
	int ret = 0;

	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		for (int i = 0; i < count; i++)
		{
			// üũ���� Ȯ��
			if (m_p_list_ctrl->GetCheck(i))
			{
				ret++;
			}
		}
	}

	return ret;
}

void CBookInList::DelCheckedItem(void)
{
	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		const int book_in_size = m_book_in.size();

		for (int i = 0; i < count; i++)
		{
			// üũ���� Ȯ��
			if (m_p_list_ctrl->GetCheck(i))
			{
				if (i < book_in_size)
				{
					//DB Delete
					CDataBaseBookInHistory cls_db_bookin_history;
					cls_db_bookin_history.Delete(m_book_in[i].db_idx);
				}
			}
		}

		//Update
		UpdateList();

		//���� ���� ���� �������� Checked�� FALSE���� �Ѵ�.
		count = m_p_list_ctrl->GetItemCount();
		for (int i = 0; i < count; i++)
		{
			m_p_list_ctrl->SetCheck(i, FALSE);
		}
	}
}