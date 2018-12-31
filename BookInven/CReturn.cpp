#include "CReturn.h"



CReturn::CReturn()
{
}

CReturn::~CReturn()
{
}

int CReturn::AddReturn(const std::string isbn)
{
	int ret = 0;

	//DB �԰� ����Ʈ�� ������ Ȯ��
	CDataBaseBookInHistory cls_db_bookin;
	int bookin_count = cls_db_bookin.GetBookCount(isbn);
	int bookin_candidate_index = cls_db_bookin.GetAbleInCartIndex(isbn);

	//DB�� ����
	if (bookin_count > 0 && bookin_candidate_index >= 0 )
	{
		//��ǰ DB�� �߰��ϰ� �԰���������� �ӽ������� 1�� ���� �Ѵ�. 
		CDataBaseReturn cls_db_return;
		if (cls_db_return.AddReturn(bookin_candidate_index))
		{
			//DB�� �߰� �Ǿ����� �԰�������� 1�� �����Ѵ�.
			if (cls_db_bookin.PushPopCount(bookin_candidate_index, -1, trade_return_add))
			{
				ret = 1;
			}
		}
	}

	return ret;
}

int CReturn::DelReturn(const std::string isbn, const bool bret)
{
	int ret = 0;

	CDataBaseReturn cls_db_return;

	std::vector<DB_Return> vec_cart = cls_db_return.GetDBInfo();
	int cart_size = vec_cart.size();

	for (int i = 0; i < cart_size; i++)
	{
		int book_in_index = vec_cart[i].bookin_idx;

		CDataBaseBookInHistory cls_db_book_in_history;
		BookInHistory book_in_data = cls_db_book_in_history.GetInfo(book_in_index);

		if (book_in_data.bookin_info.book_info.isbn == isbn)
		{
			//��ǰ DB�� ����(������ 1�� ���̴� �Ͱ� ����)�ϰ� �԰������ 1�� �߰� �Ѵ�. 
			if (cls_db_return.PopReturn(vec_cart[i].idx))
			{
				if (bret)
				{
					//�԰������ 1�� �߰�
					if (cls_db_book_in_history.PushPopCount(book_in_index, 1, trade_return_del))
					{
						ret = 1;
					}
				}
				else
				{
					ret = 1;
				}
			}
		}
	}
	return ret;
}

int CReturn::PopReturn(const std::string isbn)
{
	int ret = 0;

	CDataBaseReturn cls_db_return;
	
	std::vector<DB_Return> vec_cart = cls_db_return.GetDBInfo();
	int cart_size = vec_cart.size();

	for (int i = 0; i < cart_size; i++)
	{
		int book_in_index = vec_cart[i].bookin_idx ;

		CDataBaseBookInHistory cls_db_book_in_history;
		BookInHistory book_in_data = cls_db_book_in_history.GetInfo(book_in_index);

		if (book_in_data.bookin_info.book_info.isbn == isbn)
		{
			//��ǰ DB�� ����(������ 1�� ���̴� �Ͱ� ����)�ϰ� �԰������ 1�� �߰� �Ѵ�. 
			if (cls_db_return.PopReturn(vec_cart[i].idx))
			{
				//�԰������ 1�� �߰�
				if (cls_db_book_in_history.PushPopCount(book_in_index, 1, trade_return_del))
				{
					ret = 1;
				}
			}

			break;
		}
	}

	return ret;
}

//��ǰ�� ��� Ư�� index�� ������ � ���� Ȯ��
int CReturn::GetCount(const int index)
{
	CDataBaseReturn cls_db_return;

	int ret = cls_db_return.GetCount(index);

	return ret;
}

//��ǰ�� ��� �� ������ ����
int CReturn::GetReturnCount(void)
{
	CDataBaseReturn cls_db_return;

	int ret = cls_db_return.GetCount();

	return ret;
}

std::vector<int> CReturn::GetReturnAllIndex(void)
{
	CDataBaseReturn cls_db_return;

	std::vector<int> ret = cls_db_return.GetInfo();

	return ret;
}

//BookInHistory GetInfo(const int idx);
std::vector<ReturnInfo> CReturn::GetReturnData(const std::string isbn)
{
	CDataBaseReturn cls_db_return;
	std::vector<int> vec_return_index_info = cls_db_return.GetInfo();

	int cart_size = vec_return_index_info.size();

	std::deque<BookInHistory> books_data;
	for (int i = 0; i < cart_size; i++)
	{
		int book_in_index = vec_return_index_info[i];

		CDataBaseBookInHistory cls_db_book_in_history;
		BookInHistory book_in_data = cls_db_book_in_history.GetInfo(book_in_index);

		if (book_in_data.db_idx >= 0)
		{
			if (!isbn.empty())
			{
				if (isbn == book_in_data.bookin_info.book_info.isbn)
				{
					books_data.push_back(book_in_data);
				}
			}
			else
			{
				books_data.push_back(book_in_data);
			}
		}
	}

	//���� ���� ��ġ��
	std::vector<ReturnInfo> vec_cart_info;
	ReturnInfo cart_info;
	int books_data_size = books_data.size();

	for (int i = 0; i < books_data_size; i++)
	{
		//���� cart������ ��
		int cart_info_size = vec_cart_info.size();

		bool b_same = false;
		int i_same = -1;
		for (int j = 0; j < cart_info_size; j++)
		{
			//isbn�� �ǸŰ����� ������ ���� ��ǰ���� ����.
			if (vec_cart_info[j].bookin_info.book_info.isbn == books_data[i].bookin_info.book_info.isbn && 
				vec_cart_info[j].bookin_info.sale_cost == books_data[i].bookin_info.sale_cost )
			{
				b_same = true;
				i_same = j;
				break;
			}
		}

		if (b_same)
		{
			vec_cart_info[i_same].count++ ;
		}
		else
		{
			ReturnInfo cart_info;
			cart_info.bookin_info = books_data[i].bookin_info;
			cart_info.count = 1;
			cart_info.db_idx = books_data[i].db_idx;

			vec_cart_info.push_back(cart_info);
		}
	}

	return vec_cart_info;
}