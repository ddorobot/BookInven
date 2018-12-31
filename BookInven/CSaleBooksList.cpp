#include "CSaleBooksList.h"

CSaleBooksList::CSaleBooksList(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
	, m_p_book_bmp(NULL)
{
	SetListCtrl(p_list_ctrl);

	m_p_book_bmp = new CBitmap;
	m_p_book_bmp->LoadBitmap(IDB_BITMAP_BOOK2);

	//image list
	m_image_list.Create(150, 200, ILC_COLOR24, 8, 1);
	m_image_list.Add(m_p_book_bmp, RGB(0, 0, 0));

	//m_p_list_ctrl->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

	m_p_list_ctrl->SetImageList(&m_image_list, LVSIL_NORMAL);
	//m_p_list_ctrl->Attach(&m_image_list);

#if 0
	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// 리스트 스타일 설정
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// 타이틀 삽입 
	int list_index = 0;
	m_p_list_ctrl->InsertColumn(list_index++, _T(""), LVCFMT_CENTER, 20, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("수량"), LVCFMT_CENTER, 35, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("가격"), LVCFMT_CENTER, 60, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("이름"), LVCFMT_CENTER, 150, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("저자"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(list_index++, _T("CODE"), LVCFMT_CENTER, 110, -1);
#endif
}


CSaleBooksList::~CSaleBooksList()
{
	int book_sale_size = m_sale_books.size();

	for (int i = 0; i < book_sale_size; i++)
	{
		if (m_sale_books[i].pBmp != NULL)
		{
			delete m_sale_books[i].pBmp;
			m_sale_books[i].pBmp = NULL;
		}
	}

	if (m_p_book_bmp != NULL)
	{
		delete m_p_book_bmp;
		m_p_book_bmp = NULL;
	}
}

void CSaleBooksList::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}

void CSaleBooksList::UpdateList(void)
{
	if (m_p_list_ctrl == NULL) return;

#if 0		//test
	int count = m_p_list_ctrl->GetItemCount();

	int book_sale_size = m_sale_books.size();

	for (int i = 0; i < count; i++)
	{
		CString szText = m_p_list_ctrl->GetItemText(i, 0);

		CString str;
		str.Format(_T("%s\n가격:%d x 수량:%d = %d원"), m_sale_books[i].book_info.name.c_str(), m_sale_books[i].book_info.price, m_sale_books[i].count, m_sale_books[i].book_info.price*m_sale_books[i].count);

		if (szText != str)
		{
			m_p_list_ctrl->SetItemText(i, 0, str);
		}
	}
#endif

#if 1
	//-----
	//Data from Cart DB
	//DelAllItem();
	int sale_size = m_sale_books.size();
	for (int i = 0; i < sale_size; i++)
	{
		if (m_sale_books[i].pBmp != NULL)
		{
			delete m_sale_books[i].pBmp;
			m_sale_books[i].pBmp = NULL;
		}
	}
	m_sale_books.clear();
	m_p_list_ctrl->DeleteAllItems();

	//카트 정보
	CCart cls_cart;
	std::vector<CartInfo> vec_cart_info = cls_cart.GetCartData();

	//정보 변경
	int cart_info_size = vec_cart_info.size();
	for (int i = 0; i < cart_info_size; i++)
	{
		SaleBooksInfo sale_info;
		sale_info.book_info = vec_cart_info[i].bookin_info.book_info;
		sale_info.book_info.price = vec_cart_info[i].bookin_info.sale_cost;
		sale_info.count = vec_cart_info[i].count;

		m_sale_books.push_back(sale_info);
	}
	//DB에서 정보를 가지고 온다.
	//-----
#endif

	int count = m_p_list_ctrl->GetItemCount();
	int book_sale_size = m_sale_books.size();

#if 1
	for (int i = 0; i < book_sale_size; i++)
	{
		if (i < count)
		{
#if 0
			LVITEM tempItem;
			ZeroMemory(&tempItem, sizeof(tempItem));
			tempItem.mask = LVIF_TEXT | LVIF_IMAGE;
			tempItem.iItem = i;
			m_p_list_ctrl->GetItem(&tempItem);
#endif
			CString szText = m_p_list_ctrl->GetItemText(i, 0);

			CString str;
			str.Format(_T("%s\n가격:%d x 수량:%d = %d원"), m_sale_books[i].book_info.name.c_str(), m_sale_books[i].book_info.price, m_sale_books[i].count, m_sale_books[i].book_info.price*m_sale_books[i].count);

			if (szText != str)
			{
				//m_p_list_ctrl->SetItemText(i, 0, str);

				int image_list_index = 0;
				if (m_sale_books[i].pBmp != NULL)
				{
					image_list_index = m_sale_books[i].idxImageList;
				}

				//m_p_list_ctrl->InsertItem(&lvItem);
				m_p_list_ctrl->SetItem(i, 0, LVIF_TEXT | LVIF_IMAGE, str, image_list_index, 0,0,NULL);
			}
		}
	}
#endif

	printf("count = %d, book_sale_size=%d\n", count, book_sale_size);
	if (count < book_sale_size)
	{
		for (int index = count; index < book_sale_size; index++)
		{
			//새로운 데이타 추가
			CMatToBitmap cls_mat_to_bitmap;
			cv::Mat image = cv::imread(m_sale_books[index].book_info.title_url);

			CBitmap* pBmp = cls_mat_to_bitmap.Cvt(image);

			if (pBmp != NULL)
			{
				if (m_sale_books[index].pBmp != NULL)
				{
					delete m_sale_books[index].pBmp;
					m_sale_books[index].pBmp = NULL;
				}

				m_sale_books[index].pBmp = pBmp;
			}			

			if (m_sale_books[index].pBmp != NULL)
			{
				m_image_list.Add(m_sale_books[index].pBmp, RGB(0, 0, 0));
				int image_list_count = m_image_list.GetImageCount();
				m_sale_books[index].idxImageList = image_list_count - 1;
			}
			else
			{
				m_sale_books[index].idxImageList = 0;
			}

			printf("index = %d, book_sale_size=%d\n", index, book_sale_size);
			//printf("image_list_count = %d\n", image_list_count);

			CString str;
			str.Format(_T("%s\n가격:%d x 수량:%d = %d원"), m_sale_books[index].book_info.name.c_str(), m_sale_books[index].book_info.price, m_sale_books[index].count, m_sale_books[index].book_info.price*m_sale_books[index].count);

			int ret = m_p_list_ctrl->InsertItem(index, str, m_sale_books[index].idxImageList);
			printf("insert item ret=%d\n", ret);

			//m_p_list_ctrl->SetItemText(index, 1, _T(""));
		}
	}
	else if (count > book_sale_size)
	{
		for (int index = book_sale_size; index < count; index++)
		{
			//m_image_list.Remove(index);
			m_p_list_ctrl->DeleteItem(book_sale_size);
		}
	}

	m_p_list_ctrl->Invalidate(TRUE);
}

int CSaleBooksList::GetCountInListInfo(const std::string isbn)
{
	int ret = 0;

	int sale_size = m_sale_books.size();

	int exist_same_data_index = -1;

	if (isbn.empty())
	{
		for (int i = 0; i < sale_size; i++)
		{
			ret += m_sale_books[i].count;
		}
	}
	else
	{
		for (int i = 0; i < sale_size; i++)
		{
			if (isbn == m_sale_books[i].book_info.isbn)
			{
				ret = m_sale_books[i].count;
				break;
			}
		}
	}

	return ret;
}

int CSaleBooksList::Pay(const std::string memo, const int discount, const bool cash)
{
	int ret = 0;

	//Cart의 정보를 결제 정보로 저장!
	//카트 정보
	CCart cls_cart;
	std::vector<int> vec_cart_index = cls_cart.GetCartAllIndex();

	int cart_size = vec_cart_index.size();

	//DB 저장
	BookSaleHistory book_sale_info;

	book_sale_info.count = cart_size;
	book_sale_info.discount = discount;
	book_sale_info.cash = cash;
	book_sale_info.sale_cost = GetTotalPrice();
	book_sale_info.memo = memo;
	book_sale_info.vec_bookin = vec_cart_index;

	CDataBaseBookSaleHistory cls_db_book_sale_history;
	std::string code = cls_db_book_sale_history.AddBookSaleInfo(book_sale_info);

	if (!code.empty())	ret = 1;

	return ret;
}

void CSaleBooksList::DelCheckedItem(const bool bret)
{
	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		const int candidate_size = m_sale_books.size();

		std::deque<int> deque_del_index;
		for (int i = 0; i < count; i++)
		{
			// 체크상태 확인
			//if (m_p_list_ctrl->GetCheck(i))
			if (m_p_list_ctrl->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			{
				if (i < candidate_size)
				{
					CCart cls_cart;
					cls_cart.DelCart(m_sale_books[i].book_info.isbn, bret);

					deque_del_index.push_back(i);
				}
			}
		}

#if 1
		//상품 삭제
		int iter_count = 0;
		for (auto it = m_sale_books.begin(); it != m_sale_books.end(); )
		{
			int deque_del_size = deque_del_index.size();
			if (deque_del_size <= 0) break;

			int del_index = deque_del_index[0];

			if (del_index == iter_count)
			{
				//Release bitmap
				if (it->pBmp != NULL)
				{
					delete it->pBmp;
					it->pBmp = NULL;
				}

				it = m_sale_books.erase(it);

				deque_del_index.pop_front();
			}
			else
			{
				++it;
			}

			iter_count++;
		}

		if (m_sale_books.size() <= 0)
		{
			ResetImageList();
		}
#endif
	}
}

void CSaleBooksList::ResetImageList(void)
{
	int image_count = m_image_list.GetImageCount();

	for (int i = 1; i < image_count; i++)
	{
		m_image_list.Remove(i);
	}
}

int CSaleBooksList::GetCheckedItemCount(void)
{
	int ret = 0;

	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();

		for (int i = 0; i < count; i++)
		{
			// 체크상태 확인
			if (m_p_list_ctrl->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			{
				ret++;
			}
		}
	}

	return ret;
}

void CSaleBooksList::PlusCheckedItem(void)
{
	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		const int candidate_size = m_sale_books.size();

		for (int i = 0; i < count; i++)
		{
			// 체크상태 확인
			if (m_p_list_ctrl->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			{
				if (i < candidate_size)
				{
					CGetGoodsCount cls_get_goods_count;
					int goods_count = cls_get_goods_count.GetCount(m_sale_books[i].book_info.isbn); //cls_db_book_in_history.GetBookCount(str_isbn_);

					if (goods_count <= 0)
					{
						CString str_info;
						str_info.Format(_T("[%s]\n판매 가능한 수량이 없습니다."), m_sale_books[i].book_info.name.c_str());

						printf("%s\n", str_info.GetBuffer());
					}
					else
					{
						CCart cls_cart;
						if (cls_cart.AddCart(m_sale_books[i].book_info.isbn))
						{
							
						}
						//m_sale_books[i].count++;
					}

				}
			}
		}

		//UpdateList();
	}
}

void CSaleBooksList::MinusCheckedItem(void)
{
	if (m_p_list_ctrl != NULL)
	{
		int count = m_p_list_ctrl->GetItemCount();
		const int candidate_size = m_sale_books.size();

		std::deque<int> deque_del_index;
		for (int i = 0; i < count; i++)
		{
			// 체크상태 확인
			if (m_p_list_ctrl->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			{
				if (i < candidate_size)
				{
					if (m_sale_books[i].count > 0)
					{
						//m_sale_books[i].count-- ;
						CCart cls_cart;
						cls_cart.PopCart(m_sale_books[i].book_info.isbn);
					}

					if (m_sale_books[i].count <= 0)
					{
						deque_del_index.push_back(i);
					}
				}
			}
		}

#if 1
		//수량이 0인 상품은 삭제
		int iter_count = 0;
		for (auto it = m_sale_books.begin(); it != m_sale_books.end(); )
		{
			int deque_del_size = deque_del_index.size();
			if (deque_del_size <= 0) break;

			int del_index = deque_del_index[0];

			if (del_index == iter_count)
			{
				//Release bitmap
				if (it->pBmp != NULL)
				{
					delete it->pBmp;
					it->pBmp = NULL;
				}

				it = m_sale_books.erase(it);

				deque_del_index.pop_front();
			}
			else
			{
				++it;
			}

			iter_count++;
		}

		if (m_sale_books.size() <= 0)
		{
			ResetImageList();
		}
#endif

		//UpdateList();
	}
}

void CSaleBooksList::DelAllItem(const bool bret)
{
	if (m_p_list_ctrl != NULL)
	{

		int count = m_p_list_ctrl->GetItemCount();

		for (int i = 0; i < count; i++)
		{
			//m_p_list_ctrl->SetCheck(i, TRUE);
			m_p_list_ctrl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
		}

		DelCheckedItem(bret);
	}
}

int CSaleBooksList::GetTotalPrice(void)
{
	int price = 0;

	int sale_size = m_sale_books.size();
	for (int i = 0; i < sale_size; i++)
	{
		int cost = m_sale_books[i].count * m_sale_books[i].book_info.price;

		price += cost;
	}

	return price;
}