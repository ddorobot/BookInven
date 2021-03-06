// CDlgBookReturn.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgBookReturn.h"
#include "afxdialogex.h"


// CDlgBookReturn 대화 상자

IMPLEMENT_DYNAMIC(CDlgBookReturn, CDialogEx)

CDlgBookReturn::CDlgBookReturn(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK_RETURN, pParent)
{

}

CDlgBookReturn::~CDlgBookReturn()
{
}

void CDlgBookReturn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_RETURN, m_tree_return);
}


BEGIN_MESSAGE_MAP(CDlgBookReturn, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GOODS_SEARCH, &CDlgBookReturn::OnBnClickedButtonGoodsSearch)
	ON_BN_CLICKED(IDC_BUTTON_RETURN_ADD, &CDlgBookReturn::OnBnClickedButtonReturnAdd)
	ON_WM_WINDOWPOSCHANGED()
	ON_NOTIFY(NM_CLICK, IDC_TREE_RETURN, &CDlgBookReturn::OnClickTreeReturn)
	ON_BN_CLICKED(IDC_BUTTON_RETURN_DEL_LIST, &CDlgBookReturn::OnBnClickedButtonReturnDelList)
	ON_BN_CLICKED(IDC_BUTTON_RETURN_DEL_ALL_LIST, &CDlgBookReturn::OnBnClickedButtonReturnDelAllList)
	ON_BN_CLICKED(IDC_BUTTON_DO_RETURN, &CDlgBookReturn::OnBnClickedButtonDoReturn)
END_MESSAGE_MAP()


// CDlgBookReturn 메시지 처리기


BOOL CDlgBookReturn::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateTreeData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgBookReturn::UpdateTreeData(void)
{
	/* Example
	HTREEITEM provider = m_tree_return.InsertItem("북센");
	m_tree_return.InsertItem("바코드 | 도서명 | ", provider);
	m_tree_return.InsertItem("level 2 b", provider);

	m_tree_return.Expand(provider, TVM_EXPAND);
	*/
	m_tree_return.DeleteAllItems();

	//CReturn에서부터 정보를 얻는다.
	CReturn cls_return;
	std::vector<int> vec_return_bookin_index = cls_return.GetReturnAllIndex();
	int return_size = vec_return_bookin_index.size();

	//입고 정보를 얻는다
	//std::vector<BookReturnData> vec_return_data;
	m_vec_return_data.clear();

	CDataBaseBookInHistory cls_db_bookin_history;
	for (int i = 0; i < return_size; i++)
	{
		int return_index = vec_return_bookin_index[i];

		BookInHistory bookin = cls_db_bookin_history.GetInfo(return_index);

		//공급업체 정보 기준으로 정보를 정렬한다.
		//기존 데이타에 같은 provider index가 있으면 기존데이타에 push back한다.
		bool b_exist = false;
		int return_data_size = m_vec_return_data.size();
		for (int j = 0; j < return_data_size; j++)
		{
			int provider_index = m_vec_return_data[j].provider_index;

			if (provider_index == bookin.bookin_info.provider_info.base.idx)
			{
				m_vec_return_data[j].vec_bookin_history.push_back(bookin);
				b_exist = true;
				break;
			}
		}

		//기존 데이타에 같은 provider index가 없다면 새루운 데이타를 push back한다.
		if (b_exist == false)
		{
			BookReturnData return_data;
			return_data.provider_index = bookin.bookin_info.provider_info.base.idx;
			return_data.vec_bookin_history.push_back(bookin);

			m_vec_return_data.push_back(return_data);
		}
	}

	//데이타 표시
	int return_data_size = m_vec_return_data.size();

	for (int i = 0; i < return_data_size; i++) 
	{
		int bookin_size = m_vec_return_data[i].vec_bookin_history.size();

		HTREEITEM provider;
		if (bookin_size > 0)
		{
			if (m_vec_return_data[i].provider_index <= 0)
			{
				provider = m_tree_return.InsertItem("공급업체 정보 없음");
			}
			else
			{
				//DB에서 공급업체 정보 얻기
				CDataBaseProvider cls_db_provider;
				ProviderInfoBase provider_info = cls_db_provider.GetBaseInfo(m_vec_return_data[i].provider_index);

				if (provider_info.idx > 0)
				{
					provider = m_tree_return.InsertItem(provider_info.name.c_str());
				}
				else
				{
					provider = m_tree_return.InsertItem("삭제된 공급업체 정보");
				}
			}

			for (int j = 0; j < bookin_size; j++)
			{
				BookInHistory bookin = m_vec_return_data[i].vec_bookin_history[j];

				std::string dis_data;
				dis_data = bookin.bookin_info.book_info.isbn;
				dis_data += " | ";
				dis_data += bookin.bookin_info.book_info.name;
				dis_data += " | ";
				dis_data += bookin.reg_date;

				m_tree_return.InsertItem(dis_data.c_str(), provider);
			}

			m_tree_return.Expand(provider, TVM_EXPAND);
		}

		
	}
}

void CDlgBookReturn::OnBnClickedButtonGoodsSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItem(IDC_EDIT_RETURN_CODE)->GetWindowText(str);

	std::string str_isbn = str;
	UpdateBookInfoOnTextbox(str_isbn);
}

void CDlgBookReturn::UpdateBookInfoOnTextbox(const std::string isbn)
{
	BookInfo bookinfo = m_cls_get_book_info.GetInfo(isbn);

	printf(" - name : %s\n", bookinfo.name.c_str());
	printf(" - author : %s\n", bookinfo.author.c_str());
	printf(" - price : %d\n", bookinfo.price);
	printf(" - publisher : %s\n", bookinfo.publisher.c_str());
	printf(" - publish date : %s\n", bookinfo.publish_date.c_str());
	printf(" - title url : %s\n", bookinfo.title_url.c_str());

	UpdateBookInfoOnTextbox(bookinfo);
}

void CDlgBookReturn::UpdateBookInfoOnTextbox(const BookInfo info)
{
	//IDC_EDIT_BOOK_INFO_ISBN
	//IDC_EDIT_BOOK_INFO_NAME
	//IDC_EDIT_BOOK_INFO_AUTHOR
	//IDC_EDIT_BOOK_INFO_PUBLISHER
	//IDC_EDIT_BOOK_INFO_PUBLISH_DATE
	//IDC_EDIT_BOOK_INFO_PRICE

	CString str;
	str.Format(_T("%s"), info.isbn.c_str());
	GetDlgItem(IDC_EDIT_RETURN_CODE)->SetWindowText(str);

	str.Format(_T("%s"), info.name.c_str());
	GetDlgItem(IDC_EDIT_RETURN_BOOK_INFO_NAME)->SetWindowText(str);

	str.Format(_T("%s"), info.author.c_str());
	GetDlgItem(IDC_EDIT_RETURN_BOOK_INFO_AUTHOR)->SetWindowText(str);

	str.Format(_T("%d"), info.price);
	GetDlgItem(IDC_EDIT_RETURN_BOOK_INFO_PRICE)->SetWindowText(str);

	str.Format(_T("%d"), 1);
	GetDlgItem(IDC_EDIT_BOOK_INFO_RETURN_COUNT)->SetWindowText(str);


	CGetGoodsCount cls_get_goods_count;
	int goods_count = cls_get_goods_count.GetCount(info.isbn); //cls_db_book_in_history.GetBookCount(str_isbn_);

	str.Format(_T("%d"), goods_count);
	GetDlgItem(IDC_EDIT_RETURN_BOOK_INFO_MY_COUNT)->SetWindowText(str);

	if (info.isbn.empty())	return;

	if (goods_count <= 0)
	{
		const int result = MessageBox("보유 재고가 없어 반품리스트에 추가되지 않았습니다.", "반품오류", MB_OK | MB_ICONASTERISK);
	}
	else
	{
		//공급사 정보를 얻는다.
		CDataBaseBookInHistory cls_db_bookin_history;
		int able_index = cls_db_bookin_history.GetAbleInCartIndex(info.isbn) ;

		//book 입고 index 설정
		str.Format(_T("%d"), able_index);
		GetDlgItem(IDC_EDIT_RETURN_INDEX)->SetWindowText(str);

		if (able_index >= 0)
		{
			BookInHistory bookin = cls_db_bookin_history.GetInfo(able_index);

			//공급사 정보 체우기
			//bookin.bookin_info.provider_info.base.idx;
			str.Format(_T("%d"), bookin.bookin_info.provider_info.base.idx);
			GetDlgItem(IDC_EDIT_RETURN_PROVIDER_INDEX)->SetWindowText(str);

			str.Format(_T("%s"), bookin.bookin_info.provider_info.base.name.c_str());
			GetDlgItem(IDC_EDIT_RETURN_PROVIDER_NAME)->SetWindowText(str);

			str.Format(_T("%s"), bookin.bookin_info.provider_info.base.lic.c_str());
			GetDlgItem(IDC_EDIT_RETURN_PROVIDER_LIC)->SetWindowText(str);

			str.Format(_T("%s"), bookin.reg_date.c_str());
			GetDlgItem(IDC_EDIT_RETURN_IN_DATE)->SetWindowText(str);
			
			
		}
		else
		{
			const int result = MessageBox("반품 가능 정보를 얻지 못하였습니다.", "반품오류", MB_OK | MB_ICONASTERISK);
		}
	}
}

void CDlgBookReturn::OnBnClickedButtonReturnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_isbn;
	GetDlgItem(IDC_EDIT_RETURN_CODE)->GetWindowText(str_isbn);
	std::string str_isbn_ = str_isbn;

	CString str_count;
	GetDlgItem(IDC_EDIT_BOOK_INFO_RETURN_COUNT)->GetWindowText(str_count);
	int count = atoi(str_count);

	CString str_name;
	GetDlgItem(IDC_EDIT_RETURN_BOOK_INFO_NAME)->GetWindowText(str_name);

	CString str_index;
	GetDlgItem(IDC_EDIT_RETURN_INDEX)->GetWindowText(str_index);

	CGetGoodsCount cls_get_goods_count;
	int goods_count = cls_get_goods_count.GetCount(str_isbn_); //cls_db_book_in_history.GetBookCount(str_isbn_);

	if (goods_count <= 0)
	{
		CString str_info;
		str_info.Format(_T("[%s]\n반품 가능한 수량이 없습니다."), str_name.GetBuffer());

		const int result = MessageBox(str_info, "수량확인", MB_OK | MB_ICONASTERISK);
	}
	else
	{
		int add_count = count;
		if (add_count > goods_count)
		{
			add_count = goods_count;

			CString str_info;
			str_info.Format(_T("[%s]\n재고량이 %d 입니다. 반품 수량을 %d로 수정하여 추가 합니다."), str_name.GetBuffer(), goods_count, goods_count);

			const int result = MessageBox(str_info, "수량확인", MB_OK | MB_ICONASTERISK);
		}

		//카트에 추가
		int add_return_count = 0;
		for (int i = 0; i < add_count; i++)
		{
			CReturn cls_return;
			if (cls_return.AddReturn(str_isbn_))
			{
				add_return_count++;
			}
		}

		if (add_return_count != add_count)
		{
			CString str_info;
			str_info.Format(_T("재고 품목에 추가 된 수량을 확인하여 주시기 바랍니다.(%d/%d)"), add_return_count, add_count);

			const int result = MessageBox(str_info, "수량확인", MB_OK | MB_ICONASTERISK);
		}

		BookInfo reset_info;
		UpdateBookInfoOnTextbox(reset_info);
	}

	UpdateTreeData();
}


void CDlgBookReturn::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (this->IsWindowVisible())
	{
		UpdateTreeData();
	}
}

void CDlgBookReturn::CheckSiblings(BOOL bCheck, HTREEITEM hItem)
{
	// check or uncheck the child items recursively
	// also expand the item if checking its children
	HTREEITEM hNextItem;
	if (bCheck)
		m_tree_return.Expand(hItem, TVE_EXPAND);

	hNextItem = m_tree_return.GetChildItem(hItem);
	while (hNextItem)
	{
		m_tree_return.SetCheck(hNextItem, bCheck);
		if (m_tree_return.ItemHasChildren(hNextItem))
			CheckSiblings(bCheck, hNextItem);
		hNextItem = m_tree_return.GetNextItem(hNextItem, TVGN_NEXT);
	}
}

BOOL CDlgBookReturn::AllCheckSiblings(HTREEITEM hItem)
{
	// check or uncheck the child items recursively
	// also expand the item if checking its children
	BOOL Checked = FALSE;

	HTREEITEM hNextItem;

	hNextItem = m_tree_return.GetChildItem(hItem);
	while (hNextItem)
	{
		Checked = m_tree_return.GetCheck(hNextItem);
		if (Checked == FALSE)
			break;

		if (m_tree_return.ItemHasChildren(hNextItem))
			AllCheckSiblings(hNextItem);
		hNextItem = m_tree_return.GetNextItem(hNextItem, TVGN_NEXT);
	}

	return Checked;
}


void CDlgBookReturn::OnClickTreeReturn(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPoint    point;
	UINT      uFlags;
	HTREEITEM hItem;

	GetCursorPos(&point);
	m_tree_return.ScreenToClient(&point);
	hItem = m_tree_return.HitTest(point, &uFlags);
	BOOL bCheck;
	if (hItem)
	{
		// There is an item under the cursor.
		// See what exactly was under the cursor:
		switch (uFlags)
		{
		case TVHT_ONITEMSTATEICON://working
			if (hItem && m_tree_return.ItemHasChildren(hItem) && m_tree_return.GetCheck(hItem))
				bCheck = FALSE;
			else if (hItem && m_tree_return.ItemHasChildren(hItem) && !m_tree_return.GetCheck(hItem))
				bCheck = TRUE;
			
			CheckSiblings(bCheck, hItem);
		
			HTREEITEM hParents = m_tree_return.GetParentItem(hItem) ;
			if (hParents)
			{
				if (m_tree_return.GetCheck(hItem) == TRUE)	//아직 반영전이라 TRUE -> FALSE 로 넘어 가는 과정이다.
				{
					m_tree_return.SetCheck(hParents, FALSE);
				}
			}

			break;

			// ...and so on
		}
	}


	*pResult = 0;
}


void CDlgBookReturn::OnBnClickedButtonReturnDelList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	const int result = MessageBox("선택 된 상품을 반품 리스트에서 삭제 합니다.", "삭제 확인", MB_YESNO | MB_ICONQUESTION);

	switch (result)
	{
	case IDYES:
		break;
	case IDNO:
		return;
		break;
	}

	CReturn cls_return;

	HTREEITEM hRoot = m_tree_return.GetRootItem();

	int root_index = 0;
	int sub_index = 0;
	while (hRoot)
	{
		HTREEITEM hSub = m_tree_return.GetChildItem(hRoot);
		sub_index = 0;

		while (hSub)
		{
			if (m_tree_return.GetCheck(hSub))
			{
				//Delete 
				CString strTemp = m_tree_return.GetItemText(hSub);
				//printf("return (%d:%d) checked item : %s\n", root_index, sub_index, strTemp.GetBuffer());

				int provider_index = root_index;
				int book_index = sub_index;
				if (provider_index < m_vec_return_data.size() )
				{
					if (book_index < m_vec_return_data[provider_index].vec_bookin_history.size())
					{
						if (cls_return.DelReturnItem(m_vec_return_data[provider_index].vec_bookin_history[book_index].db_idx))
						{
							printf("return (%d:%d) checked item delete : %s\n", root_index, sub_index, strTemp.GetBuffer());
						}
						else
						{
							printf("return (%d:%d) checked item delete fail : %s\n", root_index, sub_index, strTemp.GetBuffer());
						}
					}
				}
			}

			// get the next sibling of the current item
			hSub = m_tree_return.GetNextSiblingItem(hSub);

			sub_index++;
		}

		hRoot = m_tree_return.GetNextSiblingItem(hRoot);

		root_index++;
	}

	UpdateTreeData();
}


void CDlgBookReturn::OnBnClickedButtonReturnDelAllList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	const int result = MessageBox("모든 상품을 반품 리스트에서 삭제 합니다.", "삭제 확인", MB_YESNO | MB_ICONQUESTION);

	switch (result)
	{
	case IDYES:
		break;
	case IDNO:
		return;
		break;
	}

	CReturn cls_return;

	cls_return.DelReturnItem();

	UpdateTreeData();
}


void CDlgBookReturn::OnBnClickedButtonDoReturn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//DB에 반품 정보를 저장.
	CReturn cls_return;

	//반품 정보 출력 다이얼로그 생성
	CDlgReturnPrint cls_dlg_return_print;

	cls_dlg_return_print.SetPrintData(m_vec_return_data);

	cls_dlg_return_print.DoModal();

#if 0
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	CReturn cls_return;
	std::vector<int> vec_return_bookin_index = cls_return.GetReturnAllIndex();
	int return_size = vec_return_bookin_index.size();

	std::vector<BookReturnData> vec_return_data;

	CDataBaseBookInHistory cls_db_bookin_history;
	for (int i = 0; i < return_size; i++)
	{
		int return_index = vec_return_bookin_index[i];

		BookInHistory bookin = cls_db_bookin_history.GetInfo(return_index);

		//공급업체 정보 기준으로 정보를 정렬한다.
		//기존 데이타에 같은 provider index가 있으면 기존데이타에 push back한다.
		bool b_exist = false;
		int return_data_size = vec_return_data.size();
		for (int j = 0; j < return_data_size; j++)
		{
			int provider_index = vec_return_data[j].provider_index;

			if (provider_index == bookin.bookin_info.provider_info.base.idx)
			{
				vec_return_data[j].vec_bookin_history.push_back(bookin);
				b_exist = true;
				break;
			}
		}

		//기존 데이타에 같은 provider index가 없다면 새루운 데이타를 push back한다.
		if (b_exist == false)
		{
			BookReturnData return_data;
			return_data.provider_index = bookin.bookin_info.provider_info.base.idx;
			return_data.vec_bookin_history.push_back(bookin);

			vec_return_data.push_back(return_data);
		}
	}

	//데이타 표시
	int return_data_size = vec_return_data.size();

	for (int i = 0; i < return_data_size; i++)
	{
		int bookin_size = vec_return_data[i].vec_bookin_history.size();

		HTREEITEM provider;
		if (bookin_size > 0)
		{
			if (vec_return_data[i].provider_index <= 0)
			{
				provider = m_tree_return.InsertItem("공급업체 정보 없음");
			}
			else
			{
				//DB에서 공급업체 정보 얻기
				CDataBaseProvider cls_db_provider;
				ProviderInfoBase provider_info = cls_db_provider.GetBaseInfo(vec_return_data[i].provider_index);

				if (provider_info.idx > 0)
				{
					provider = m_tree_return.InsertItem(provider_info.name.c_str());
				}
				else
				{
					provider = m_tree_return.InsertItem("삭제된 공급업체 정보");
				}
			}

			for (int j = 0; j < bookin_size; j++)
			{
				BookInHistory bookin = vec_return_data[i].vec_bookin_history[j];

				std::string dis_data;
				dis_data = bookin.bookin_info.book_info.isbn;
				dis_data += " | ";
				dis_data += bookin.bookin_info.book_info.name;
				dis_data += " | ";
				dis_data += bookin.reg_date;

				m_tree_return.InsertItem(dis_data.c_str(), provider);
			}

			m_tree_return.Expand(provider, TVM_EXPAND);
		}


	}
#endif
}
