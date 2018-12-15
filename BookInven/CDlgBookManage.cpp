// CDlgBookManage.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgBookManage.h"
#include "afxdialogex.h"


// CDlgBookManage 대화 상자

IMPLEMENT_DYNAMIC(CDlgBookManage, CDialogEx)

CDlgBookManage::CDlgBookManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK_MANAGE, pParent)
	, m_p_cls_books_list(NULL)
{

}

CDlgBookManage::~CDlgBookManage()
{
	if (m_p_cls_books_list != NULL)
	{
		delete m_p_cls_books_list;
		m_p_cls_books_list = NULL;
	}
}

void CDlgBookManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOKS, m_list_mybooks);
}


BEGIN_MESSAGE_MAP(CDlgBookManage, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BOOKS, &CDlgBookManage::OnDblclkListBooks)
	ON_BN_CLICKED(IDC_BUTTON_PROVIDER_INFO_NEW, &CDlgBookManage::OnBnClickedButtonProviderInfoNew)
END_MESSAGE_MAP()


// CDlgBookManage 메시지 처리기


BOOL CDlgBookManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CLoadBitmap cls_load_bitmap;
	cls_load_bitmap.Load(IDB_BITMAP_BOOK, 1.0, &m_mat_image_book_cover);
	m_mat_image_book_cover.copyTo(m_mat_image_base_book_cover);

	CString str;
	str.Format(_T("%d"), -1);
	GetDlgItem(IDC_EDIT_BOOK_INFO_IDX)->SetWindowText(str);

	m_p_cls_books_list = new CMyBooksList(&m_list_mybooks);

	m_p_cls_books_list->UpdateList();

	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CDlgBookManage::ThreadFunction, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgBookManage::ThreadFunction(void)
{
	CDrawToHDC cls_draw2hdc;

	CRect rect_book_cover;															//display rect
	GetDlgItem(IDC_STATIC_BOOK_INFO_TITLE_IMAGE)->GetClientRect(&rect_book_cover);			//get rect information on window
	CClientDC dc_display(GetDlgItem(IDC_STATIC_BOOK_INFO_TITLE_IMAGE));					//device context for display mfc control

	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(100));

		if (this->IsWindowVisible())
		{
			CString str;
			GetDlgItem(IDC_EDIT_BOOK_INFO_IDX)->GetWindowText(str);
			int book_info_index = atoi(str);

			CString str_button;
			GetDlgItem(IDC_BUTTON_PROVIDER_INFO_UPDAE)->GetWindowText(str_button);

			if (book_info_index > 0 )
			{
				if (str_button != "업데이트")
				{
					GetDlgItem(IDC_BUTTON_PROVIDER_INFO_UPDAE)->SetWindowText("업데이트");
				}
			}
			else 
			{
				if (str_button != "추가")
				{
					GetDlgItem(IDC_BUTTON_PROVIDER_INFO_UPDAE)->SetWindowText("추가");
				}
			}

			//printf("Book Manage\n");
			cls_draw2hdc.DrawToHDC(GetImageBookCover(), dc_display.m_hDC, &rect_book_cover);				//draw on display_rect
		}
	};
}

cv::Mat CDlgBookManage::GetImageBookCover(void)
{
	cv::Mat ret;
	mutex_image_book_cover.lock();
	//m_mat_image_book_cover.copyTo(ret);
	ret = m_mat_image_book_cover;
	mutex_image_book_cover.unlock();

	return ret;
}

void CDlgBookManage::SetImageBookCover(cv::Mat image)
{
	mutex_image_book_cover.lock();
	image.copyTo(m_mat_image_book_cover);
	mutex_image_book_cover.unlock();
}

BOOL CDlgBookManage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgBookManage::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (this->IsWindowVisible())
	{
		if (m_p_cls_books_list)
		{
			m_p_cls_books_list->UpdateList();
		}
	}
}


void CDlgBookManage::OnDblclkListBooks(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;

	int iItem = pNMITEM->iItem;
	//int iSubitem = pNMITEM->iSubItem;
	if (m_p_cls_books_list != NULL)
	{
		BookInfo bookinfo = m_p_cls_books_list->GetBookInfoInList(iItem);

		SetBookInfoToCtrl(bookinfo);
	}

	m_list_mybooks.Invalidate(TRUE);

	*pResult = 0;
}

void CDlgBookManage::SetBookInfoToCtrl(const BookInfo bookinfo)
{
	CString str;

	str.Format(_T("%d"), bookinfo.idx);
	GetDlgItem(IDC_EDIT_BOOK_INFO_IDX)->SetWindowText(str);

	str.Format(_T("%s"), bookinfo.isbn.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_ISBN)->SetWindowText(str);

	str.Format(_T("%s"), bookinfo.name.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_NAME)->SetWindowText(str);

	str.Format(_T("%s"), bookinfo.author.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_AUTHOR)->SetWindowText(str);

	str.Format(_T("%s"), bookinfo.publisher.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_PUBLISHER)->SetWindowText(str);

	str.Format(_T("%s"), bookinfo.publish_date.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_PUBLISH_DATE)->SetWindowText(str);

	str.Format(_T("%d"), bookinfo.price);
	GetDlgItem(IDC_EDIT_BOOK_INFO_PRICE)->SetWindowText(str);

	//Image
	if (!bookinfo.title_url.empty())
	{
		cv::Mat cover_image = cv::imread(bookinfo.title_url);

		if (!cover_image.empty())
		{
			SetImageBookCover(cover_image);
		}
	}

}

void CDlgBookManage::OnBnClickedButtonProviderInfoNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BookInfo bookinfo;
	SetBookInfoToCtrl(bookinfo);
}
