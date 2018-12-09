// CDlgBookIn.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgBookIn.h"
#include "afxdialogex.h"


// CDlgBookIn 대화 상자

IMPLEMENT_DYNAMIC(CDlgBookIn, CDialogEx)

CDlgBookIn::CDlgBookIn(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK_IN, pParent)
{

}

CDlgBookIn::~CDlgBookIn()
{
}

void CDlgBookIn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBookIn, CDialogEx)
END_MESSAGE_MAP()


// CDlgBookIn 메시지 처리기


BOOL CDlgBookIn::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		UINT nChar = pMsg->wParam;

		std::string str_isbn = m_cls_get_book_info.GetISBNInfo(nChar);

		if (!str_isbn.empty())
		{
			printf("ISBN : %s\n", str_isbn.c_str());

			BookInfo info = m_cls_get_book_info.GetInfo(str_isbn);

			printf(" - name : %s\n", info.name.c_str());
			printf(" - author : %s\n", info.author.c_str());
			printf(" - price : %d\n", info.price);
			printf(" - publisher : %s\n", info.publisher.c_str());
			printf(" - publish date : %s\n", info.publish_date.c_str());
			printf(" - title url : %s\n", info.title_url.c_str());

#if 0
			if (!info.title_url.empty())
			{
				CImageLoadUrl cls_image_load_url;
				cv::Mat read_title_image = cls_image_load_url.Load(info.title_url.c_str());

				if (!read_title_image.empty())
				{
					cv::imshow("book title", read_title_image);
					cv::waitKey(0);
				}
			}
#endif
		}

		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;                // Do not process further
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CDlgBookIn::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CLoadBitmap cls_load_bitmap;
	cls_load_bitmap.Load(IDB_BITMAP_BOOK, 1.0, &m_mat_image_book_cover);

	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CDlgBookIn::ThreadFunction, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgBookIn::ThreadFunction(void)
{
	CDrawToHDC cls_draw2hdc;

	CRect rect_book_cover;															//display rect
	GetDlgItem(IDC_STATIC_BOOK_INFO_TITLE_IMAGE)->GetClientRect(&rect_book_cover);			//get rect information on window
	CClientDC dc_display(GetDlgItem(IDC_STATIC_BOOK_INFO_TITLE_IMAGE));					//device context for display mfc control

	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(10));

		if (this->IsWindowVisible())
		{
			//printf("Book Manage\n");
			cls_draw2hdc.DrawToHDC(m_mat_image_book_cover, dc_display.m_hDC, &rect_book_cover);				//draw on display_rect
		}
	};
}