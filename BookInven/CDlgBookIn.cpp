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
	DDX_Control(pDX, IDC_LIST_BOOKIN_CANDIDATE, m_list_candidate);
}


BEGIN_MESSAGE_MAP(CDlgBookIn, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BOOK_TITLE_IMAGE_CHANGE, &CDlgBookIn::OnBnClickedButtonBookTitleImageChange)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CANDIDATE_BOOKIN, &CDlgBookIn::OnBnClickedButtonAddCandidateBookin)
	ON_BN_CLICKED(IDC_BUTTON_BOOK_ISBN_SEARCH, &CDlgBookIn::OnBnClickedButtonBookIsbnSearch)
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

			UpdateBookInfoOnTextbox(str_isbn);
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
	m_mat_image_book_cover.copyTo(m_mat_image_base_book_cover);

	//m_list_candidate
	//Initialize list
	m_list_candidate.DeleteAllItems();
	// 리스트 스타일 설정
	m_list_candidate.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// 타이틀 삽입
	m_list_candidate.InsertColumn(0, _T("CODE"), LVCFMT_CENTER, 110, -1);
	m_list_candidate.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 200, -1);
	m_list_candidate.InsertColumn(2, _T("저자"), LVCFMT_CENTER, 100, -1);
	m_list_candidate.InsertColumn(3, _T("발행처"), LVCFMT_CENTER, 100, -1);
	m_list_candidate.InsertColumn(4, _T("가격"), LVCFMT_CENTER, 70, -1);
	m_list_candidate.InsertColumn(5, _T("수량"), LVCFMT_CENTER, 50, -1);

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
			cls_draw2hdc.DrawToHDC(GetImageBookCover(), dc_display.m_hDC, &rect_book_cover);				//draw on display_rect
		}
	};
}

void CDlgBookIn::UpdateBookInfoOnTextbox(const std::string isbn)
{
	BookInfo info = m_cls_get_book_info.GetInfo(isbn);

	printf(" - name : %s\n", info.name.c_str());
	printf(" - author : %s\n", info.author.c_str());
	printf(" - price : %d\n", info.price);
	printf(" - publisher : %s\n", info.publisher.c_str());
	printf(" - publish date : %s\n", info.publish_date.c_str());
	printf(" - title url : %s\n", info.title_url.c_str());

	UpdateBookInfoOnTextbox(info);

	if (!info.title_url.empty())
	{
		cv::Mat mat_image_read = cv::imread(info.title_url.c_str());

		if (!mat_image_read.empty())
		{
			SetImageBookCover(mat_image_read);
		}
		else
		{
			SetImageBookCover(m_mat_image_base_book_cover);
		}
	}
	else
	{
		SetImageBookCover(m_mat_image_base_book_cover);
	}
}

void CDlgBookIn::UpdateBookInfoOnTextbox(const BookInfo info)
{
	//IDC_EDIT_BOOK_INFO_ISBN
	//IDC_EDIT_BOOK_INFO_NAME
	//IDC_EDIT_BOOK_INFO_AUTHOR
	//IDC_EDIT_BOOK_INFO_PUBLISHER
	//IDC_EDIT_BOOK_INFO_PUBLISH_DATE
	//IDC_EDIT_BOOK_INFO_PRICE

	CString str;
	str.Format(_T("%s"), info.isbn.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_ISBN)->SetWindowText(str);

	str.Format(_T("%s"), info.name.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_NAME)->SetWindowText(str);

	str.Format(_T("%s"), info.author.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_AUTHOR)->SetWindowText(str);

	str.Format(_T("%s"), info.publisher.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_PUBLISHER)->SetWindowText(str);

	str.Format(_T("%s"), info.publish_date.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_PUBLISH_DATE)->SetWindowText(str);

	str.Format(_T("%d"), info.price);
	GetDlgItem(IDC_EDIT_BOOK_INFO_PRICE)->SetWindowText(str);
}

cv::Mat CDlgBookIn::GetImageBookCover(void)
{
	cv::Mat ret;
	mutex_image_book_cover.lock();
	//m_mat_image_book_cover.copyTo(ret);
	ret = m_mat_image_book_cover;
	mutex_image_book_cover.unlock();

	return ret;
}

void CDlgBookIn::SetImageBookCover(cv::Mat image)
{
	mutex_image_book_cover.lock();
	image.copyTo(m_mat_image_book_cover);
	mutex_image_book_cover.unlock();
}

void CDlgBookIn::OnBnClickedButtonBookTitleImageChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static char szFilter[] = "BMP (*.bmp)|*.bmp|PNG (*.png)|*.png|JPEG (*.jpg)|*.jpg|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE, _T("image"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilter, this);

	//현재 프로그램의 경로로 오픈한다.
	char cur_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, cur_path);
	dlg.m_ofn.lpstrInitialDir = cur_path;

	if (dlg.DoModal() == IDOK)
	{
		CString sFilePath = dlg.GetPathName();

		//printf("read image path = %s\n", sFilePath.GetBuffer());

		cv::Mat read_image = cv::imread(sFilePath.GetBuffer());
		SetImageBookCover(read_image);
	}
}


void CDlgBookIn::OnBnClickedButtonAddCandidateBookin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgBookIn::OnBnClickedButtonBookIsbnSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;
	GetDlgItem(IDC_EDIT_BOOK_INFO_ISBN)->GetWindowText(str);

	std::string str_isbn = str;
	UpdateBookInfoOnTextbox(str_isbn);
}
