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
{

}

CDlgBookSale::~CDlgBookSale()
{
}

void CDlgBookSale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBookSale, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SALE_ADD, &CDlgBookSale::OnBnClickedButtonSaleAdd)
END_MESSAGE_MAP()


// CDlgBookSale 메시지 처리기


BOOL CDlgBookSale::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString str;
	str.Format(_T("%d"), 0);
	GetDlgItem(IDC_EDIT_BOOK_INFO_SALE_COUNT)->SetWindowText(str);

	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CDlgBookSale::ThreadFunction, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
