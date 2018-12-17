// CDlgBookSale.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgBookSale.h"
#include "afxdialogex.h"


// CDlgBookSale 대화 상자

IMPLEMENT_DYNAMIC(CDlgBookSale, CDialogEx)

CDlgBookSale::CDlgBookSale(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK_SALE, pParent)
	, m_p_cls_sale_list(NULL)
{

}

CDlgBookSale::~CDlgBookSale()
{
	if (m_p_cls_sale_list != NULL)
	{
		delete m_p_cls_sale_list;
		m_p_cls_sale_list = NULL;
	}
}

void CDlgBookSale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SALE, m_list_sale);
}


BEGIN_MESSAGE_MAP(CDlgBookSale, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SALE_ADD, &CDlgBookSale::OnBnClickedButtonSaleAdd)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_BUTTON_GOODS_SEARCH, &CDlgBookSale::OnBnClickedButtonGoodsSearch)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SALE_ITEM, &CDlgBookSale::OnBnClickedButtonDelSaleItem)
END_MESSAGE_MAP()


// CDlgBookSale 메시지 처리기


BOOL CDlgBookSale::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString str;
	str.Format(_T("%d"), 0);
	GetDlgItem(IDC_EDIT_BOOK_INFO_SALE_COUNT)->SetWindowText(str);

	m_p_cls_sale_list = new CSaleBooksList(&m_list_sale);
	m_p_cls_sale_list->UpdateList();

	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CDlgBookSale::ThreadFunction, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgBookSale::DrawList(cv::Mat image, cv::Rect rect, std::vector<SaleBooksInfo> vec_list_info)
{
	cv::rectangle(image, rect, cv::Scalar(0, 0, 255), 1);

	int fontHeight = 25;
	int top_margin = 15;
	const int max_out_count = rect.height / (fontHeight+ top_margin);

	//Text 
	cv::Point textOrg(0, 0);
	// FreeType2 객체 생성
	cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
	// 바탕체 글꼴 불러오기
	ft2->loadFontData("C:\\Windows\\Fonts\\malgun.ttf", 0);

	int thickness = -1;
	int linestyle = 8;
	int baseline = 0;

	for (int i = 0; i < max_out_count; i++)
	{
		std::string text = std::to_string(i) + ". 책제목 : 가격 : 3권 = 30000원";
		std::wstring strUni;
		std::string strUTF8;

		//Text
		strUni = CA2W(text.c_str());
		strUTF8 = CW2A(strUni.c_str(), CP_UTF8);

		cv::Size textSize = ft2->getTextSize(strUTF8, fontHeight, thickness, &baseline);
		textSize.height = fontHeight;

		//image draw
		textOrg.x = rect.x;
		textOrg.y = (rect.y + textSize.height) + ((textSize.height+ top_margin)* i);

		//cv::rectangle(image, cv::Rect(textOrg.x, textOrg.y, textSize.width, textSize.height), cv::Scalar(128, 128, 255), CV_FILLED);
		ft2->putText(image, strUTF8, textOrg, fontHeight, cv::Scalar(255, 255, 255), thickness, linestyle, true);
	}
}

void CDlgBookSale::DrawTotalPrice(cv::Mat image, int price)
{
	std::string NumericString = std::to_string(price); // It should output 1,234,567,890

	std::string str_price;
	int endstring = NumericString.length(), i;
	for (i = endstring - 3; i >= 0; i -= 3) {
		if (i > 0) {
			str_price = "," + NumericString.substr(i, 3) + str_price;
		}
		else {
			str_price = NumericString.substr(i, 3) + str_price;
		}
	}
	if (i < 0) {
		str_price = NumericString.substr(0, 3 + i) + str_price;
	}

	//Text
	cv::Point textOrg(0, 0);
	// FreeType2 객체 생성
	cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
	// 바탕체 글꼴 불러오기
	ft2->loadFontData("C:\\Windows\\Fonts\\malgun.ttf", 0);

	int thickness = -1;
	int linestyle = 8;
	int baseline = 0;

	std::string text = "총 결제 금액 : " + str_price + "원" ;
	std::wstring strUni;
	std::string strUTF8;


	//Text
	int fontHeight = 40;
	strUni = CA2W(text.c_str());
	strUTF8 = CW2A(strUni.c_str(), CP_UTF8);

	cv::Size textSize = ft2->getTextSize(strUTF8, fontHeight, thickness, &baseline);
	textSize.height = fontHeight;

	//image draw
	textOrg.x = (image.cols - textSize.width) / 2;
	textOrg.y = (image.rows - textSize.height);

	//cv::rectangle(image, cv::Rect(textOrg.x, textOrg.y, textSize.width, textSize.height), cv::Scalar(128, 128, 255), CV_FILLED);
	ft2->putText(image, strUTF8, textOrg, fontHeight, cv::Scalar(193, 193, 102), thickness, linestyle, true);
}


void CDlgBookSale::ThreadFunction(void)
{
	CDrawToHDC cls_draw2hdc;

	CRect rect_sale;															//display rect
	GetDlgItem(IDC_STATIC_SALE_IMAGE)->GetClientRect(&rect_sale);			//get rect information on window
	CClientDC dc_display(GetDlgItem(IDC_STATIC_SALE_IMAGE));					//device context for display mfc control

	cv::Mat draw_image = cv::Mat::zeros(cv::Size(rect_sale.Width(), rect_sale.Height()), CV_8UC3);

	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(100));

		if (this->IsWindowVisible())
		{
			draw_image = 0;
			 
			std::vector<SaleBooksInfo> vec_list_info;
			DrawList(draw_image, cv::Rect(20,20,draw_image.cols/2-20, draw_image.rows*(70.0/100.0)), vec_list_info);
			DrawTotalPrice(draw_image, 35000);

			cls_draw2hdc.DrawToHDC(draw_image, dc_display.m_hDC, &rect_sale);				//draw on display_rect
		}
	};
}


BOOL CDlgBookSale::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		UINT nChar = pMsg->wParam;

		std::string str_isbn = m_cls_get_book_info.GetISBNInfo(nChar);

		if (!str_isbn.empty())
		{
			printf("ISBN : %s\n", str_isbn.c_str());

			UpdateBookInfoOnTextbox(str_isbn);

			OnBnClickedButtonSaleAdd();
		}

		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;                // Do not process further
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgBookSale::OnBnClickedButtonSaleAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//Book정보의 isbn을 이용하여 입/출고 count를 이용하여 재고량 확인
	//입고량
	CString str_isbn;
	GetDlgItem(IDC_EDIT_SALE_CODE)->GetWindowText(str_isbn);
	std::string str_isbn_ = str_isbn; 

	CString str_count;
	GetDlgItem(IDC_EDIT_BOOK_INFO_SALE_COUNT)->GetWindowText(str_count);
	int count = atoi(str_count); 

	CString str_name;
	GetDlgItem(IDC_EDIT_BOOK_INFO_NAME)->GetWindowText(str_name);

	CGetGoodsCount cls_get_goods_count;
	int goods_count = cls_get_goods_count.GetCount(str_isbn_); //cls_db_book_in_history.GetBookCount(str_isbn_);
	int goods_count_in_list = 0;
	if (m_p_cls_sale_list != NULL)
	{
		goods_count_in_list = m_p_cls_sale_list->GetCountInListInfo(str_isbn_);
	}

	goods_count -= goods_count_in_list;

	if (goods_count <= 0)
	{
		CString str_info;
		str_info.Format(_T("[%s]\n판매 가능한 수량이 없습니다."), str_name.GetBuffer());

		const int result = MessageBox(str_info, "수량확인", MB_OK | MB_ICONASTERISK);
	}
	else
	{
		if (m_p_cls_sale_list != NULL )
		{
			CDataBaseBookInfo cls_db_bookinfo;
			SaleBooksInfo sale_info;
			BookInfo bookinfo;
			
			if (cls_db_bookinfo.GetBookInfo(str_isbn_, &bookinfo))
			{
				sale_info.book_info = bookinfo;
				sale_info.count = count;

				if (sale_info.count > goods_count)
				{
					sale_info.count = goods_count;

					CString str_info;
					str_info.Format(_T("[%s]\n재료량이 %d 입니다. 판매 수량을 %d로 수정하여 추가 합니다."), str_name.GetBuffer(), goods_count, goods_count);

					const int result = MessageBox(str_info, "수량확인", MB_OK | MB_ICONASTERISK);
				}

				m_p_cls_sale_list->AddSaleBook(sale_info);
			}
		}
	}

	if (m_p_cls_sale_list != NULL)
	{
		m_p_cls_sale_list->UpdateList();
	}
}

void CDlgBookSale::UpdateBookInfoOnTextbox(const std::string isbn)
{
	BookInfo info = m_cls_get_book_info.GetInfo(isbn);

	printf(" - name : %s\n", info.name.c_str());
	printf(" - author : %s\n", info.author.c_str());
	printf(" - price : %d\n", info.price);
	printf(" - publisher : %s\n", info.publisher.c_str());
	printf(" - publish date : %s\n", info.publish_date.c_str());
	printf(" - title url : %s\n", info.title_url.c_str());

	UpdateBookInfoOnTextbox(info); 
}

void CDlgBookSale::UpdateBookInfoOnTextbox(const BookInfo info)
{
	//IDC_EDIT_BOOK_INFO_ISBN
	//IDC_EDIT_BOOK_INFO_NAME
	//IDC_EDIT_BOOK_INFO_AUTHOR
	//IDC_EDIT_BOOK_INFO_PUBLISHER
	//IDC_EDIT_BOOK_INFO_PUBLISH_DATE
	//IDC_EDIT_BOOK_INFO_PRICE

	CString str;
	str.Format(_T("%s"), info.isbn.c_str());
	GetDlgItem(IDC_EDIT_SALE_CODE)->SetWindowText(str);

	str.Format(_T("%s"), info.name.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_NAME)->SetWindowText(str);

	str.Format(_T("%s"), info.author.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_AUTHOR)->SetWindowText(str);

	str.Format(_T("%d"), info.price);
	GetDlgItem(IDC_EDIT_BOOK_INFO_PRICE)->SetWindowText(str);

	str.Format(_T("%d"), 1);
	GetDlgItem(IDC_EDIT_BOOK_INFO_SALE_COUNT)->SetWindowText(str);
	
}


void CDlgBookSale::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (this->IsWindowVisible())
	{
		if (m_p_cls_sale_list)
		{
			m_p_cls_sale_list->UpdateList(); 
		}
	}
}


void CDlgBookSale::OnBnClickedButtonGoodsSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItem(IDC_EDIT_SALE_CODE)->GetWindowText(str);

	std::string str_isbn = str;
	UpdateBookInfoOnTextbox(str_isbn);
}


void CDlgBookSale::OnBnClickedButtonDelSaleItem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_p_cls_sale_list != NULL)
	{
		m_p_cls_sale_list->DelCheckedItem();

		m_p_cls_sale_list->UpdateList();
	}
}
