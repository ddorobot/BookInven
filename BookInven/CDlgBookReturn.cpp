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
	HTREEITEM provider = m_tree_return.InsertItem("북센");
	m_tree_return.InsertItem("바코드 | 도서명 | ", provider);
	m_tree_return.InsertItem("level 2 b", provider);

	m_tree_return.Expand(provider, TVM_EXPAND);
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