#include "CCart.h"



CCart::CCart()
{
}

CCart::~CCart()
{
}

int CCart::AddCart(const std::string isbn)
{
	int ret = 0;

	//DB 입고 리스트의 수량을 확인
	CDataBaseBookInHistory cls_db_bookin;
	int bookin_count = cls_db_bookin.GetBookCount(isbn);
	int bookin_candidate_index = cls_db_bookin.GetAbleInCartIndex(isbn);

	//DB에 저장
	if (bookin_count > 0 && bookin_candidate_index >= 0 )
	{
		//카트 DB에 추가하고 입고수량에서는 임시적으로 1을 삭제 한다. 
		CDataBaseCart cls_db_cart;
		if (cls_db_cart.AddCart(bookin_candidate_index))
		{
			//DB에 추가 되었으니 입고수량에서 1을 삭제한다.
			if (cls_db_bookin.PushPopCount(bookin_candidate_index, -1))
			{
				ret = 1;
			}
		}
	}

	return ret;
}

int CCart::DelCart(const std::string isbn)
{
	int ret = 0;

	CDataBaseCart cls_db_cart;

	std::vector<DB_Cart> vec_cart = cls_db_cart.GetDBInfo();
	int cart_size = vec_cart.size();

	for (int i = 0; i < cart_size; i++)
	{
		int book_in_index = vec_cart[i].bookin_idx;

		CDataBaseBookInHistory cls_db_book_in_history;
		BookInHistory book_in_data = cls_db_book_in_history.GetInfo(book_in_index);

		if (book_in_data.bookin_info.book_info.isbn == isbn)
		{
			//카트 DB를 삭제(수량을 1을 줄이는 것과 같다)하고 입고수량에 1을 추가 한다. 
			if (cls_db_cart.PopCart(vec_cart[i].idx))
			{
				//입고수량에 1을 추가
				if (cls_db_book_in_history.PushPopCount(book_in_index, 1))
				{
					ret = 1;
				}
			}
		}
	}

	return ret;
}

int CCart::PopCart(const std::string isbn)
{
	int ret = 0;
	
	CDataBaseCart cls_db_cart;
	
	std::vector<DB_Cart> vec_cart = cls_db_cart.GetDBInfo();
	int cart_size = vec_cart.size();

	for (int i = 0; i < cart_size; i++)
	{
		int book_in_index = vec_cart[i].bookin_idx ;

		CDataBaseBookInHistory cls_db_book_in_history;
		BookInHistory book_in_data = cls_db_book_in_history.GetInfo(book_in_index);

		if (book_in_data.bookin_info.book_info.isbn == isbn)
		{
			//카트 DB를 삭제(수량을 1을 줄이는 것과 같다)하고 입고수량에 1을 추가 한다. 
			if (cls_db_cart.PopCart(vec_cart[i].idx))
			{
				//입고수량에 1을 추가
				if (cls_db_book_in_history.PushPopCount(book_in_index, 1))
				{
					ret = 1;
				}
			}

			break;
		}
	}

	return ret;
}

//카트에 담긴 특정 index의 수량이 몇개 인지 확인
int CCart::GetCount(const int index)
{
	CDataBaseCart cls_db_cart;

	int ret = cls_db_cart.GetCount(index);

	return ret;
}

//카트에 담긴 총 수량을 리턴
int CCart::GetCartCount(void)
{
	CDataBaseCart cls_db_cart;

	int ret = cls_db_cart.GetCount();

	return ret;
}

std::vector<int> CCart::GetCartAllIndex(void)
{
	CDataBaseCart cls_db_cart;

	std::vector<int> ret = cls_db_cart.GetInfo();

	return ret;
}

//BookInHistory GetInfo(const int idx);
std::vector<CartInfo> CCart::GetCartData(const std::string isbn)
{
	CDataBaseCart cls_db_cart;
	std::vector<int> vec_cart_index_info = cls_db_cart.GetInfo();

	int cart_size = vec_cart_index_info.size();

	std::deque<BookInHistory> books_data;
	for (int i = 0; i < cart_size; i++)
	{
		int book_in_index = vec_cart_index_info[i];

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

	//같은 정보 합치기
	std::vector<CartInfo> vec_cart_info;
	CartInfo cart_info;
	int books_data_size = books_data.size();

	for (int i = 0; i < books_data_size; i++)
	{
		//기존 cart정보와 비교
		int cart_info_size = vec_cart_info.size();

		bool b_same = false;
		int i_same = -1;
		for (int j = 0; j < cart_info_size; j++)
		{
			//isbn과 판매가격이 같으면 같은 제품으로 본다.
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
			CartInfo cart_info;
			cart_info.bookin_info = books_data[i].bookin_info;
			cart_info.count = 1;
			cart_info.db_idx = books_data[i].db_idx;

			vec_cart_info.push_back(cart_info);
		}
	}

	return vec_cart_info;
}