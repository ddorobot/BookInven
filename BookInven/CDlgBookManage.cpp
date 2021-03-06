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
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_BOOKS, &CDlgBookManage::OnCustomdrawListBooks)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_BOOK_COVER, &CDlgBookManage::OnBnClickedButtonChangeBookCover)
	ON_BN_CLICKED(IDC_BUTTON_BOOKINFO_INFO_UPDAE, &CDlgBookManage::OnBnClickedButtonBookinfoInfoUpdae)
END_MESSAGE_MAP()


// CDlgBookManage 메시지 처리기


BOOL CDlgBookManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CLoadBitmap cls_load_bitmap;
	cls_load_bitmap.Load(IDB_BITMAP_BOOK2, 1.0, &m_mat_image_book_cover);
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
			if (GetDlgItem(IDC_EDIT_BOOK_INFO_IDX) && GetDlgItem(IDC_BUTTON_PROVIDER_INFO_UPDAE))
			{
				CString str;
				GetDlgItem(IDC_EDIT_BOOK_INFO_IDX)->GetWindowText(str);
				int book_info_index = atoi(str);

				CString str_button;
				GetDlgItem(IDC_BUTTON_PROVIDER_INFO_UPDAE)->GetWindowText(str_button);

				if (book_info_index > 0)
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
			}

			//printf("Book Manage\n");
			CString str_book_cover_path;
			GetDlgItem(IDC_EDIT_BOOK_INFO_IMAGE_PATH)->GetWindowText(str_book_cover_path);
			std::string str_book_cover_path_ = str_book_cover_path;

			cv::Mat image_book_cover;
			image_book_cover = cv::imread(str_book_cover_path_.c_str());

			if (image_book_cover.empty())
			{
				cls_draw2hdc.DrawToHDC(m_mat_image_base_book_cover, dc_display.m_hDC, &rect_book_cover);				//draw on display_rect
			}
			else
			{
				cls_draw2hdc.DrawToHDC(image_book_cover, dc_display.m_hDC, &rect_book_cover);				//draw on display_rect
			}
		}
	};
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
		BookInfo bookinfo_list = m_p_cls_books_list->GetBookInfoInList(iItem);
		
		BookInfo bookinfo_db = m_p_cls_books_list->GetBookInfoFromDB(bookinfo_list.idx);

		if (bookinfo_list.idx == bookinfo_db.idx)
		{
			SetBookInfoToCtrl(bookinfo_db);
		}
		else
		{
			BookInfo bookinfo;
			SetBookInfoToCtrl(bookinfo);
		}
	}

	m_list_mybooks.Invalidate(TRUE);

	*pResult = 0;
}

BookInfo CDlgBookManage::GetBookInfoFromCtrl(void)
{
	BookInfo bookinfo;

	CString str;
	GetDlgItem(IDC_EDIT_BOOK_INFO_IDX)->GetWindowText(str);
	bookinfo.idx = atoi(str);

	GetDlgItem(IDC_EDIT_BOOK_INFO_ISBN)->GetWindowText(str);
	bookinfo.isbn = str;

	GetDlgItem(IDC_EDIT_BOOK_INFO_NAME)->GetWindowText(str);
	bookinfo.name = str;

	GetDlgItem(IDC_EDIT_BOOK_INFO_AUTHOR)->GetWindowText(str);
	bookinfo.author = str;

	GetDlgItem(IDC_EDIT_BOOK_INFO_PUBLISHER)->GetWindowText(str);
	bookinfo.publisher = str;

	GetDlgItem(IDC_EDIT_BOOK_INFO_PUBLISH_DATE)->GetWindowText(str);
	bookinfo.publish_date = str;

	GetDlgItem(IDC_EDIT_BOOK_INFO_PRICE)->GetWindowText(str);
	bookinfo.price = atoi(str);

	GetDlgItem(IDC_EDIT_BOOK_INFO_IMAGE_PATH)->GetWindowText(str);
	bookinfo.title_url = str;

	return bookinfo;
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

	str.Format(_T("%s"), bookinfo.title_url.c_str());
	GetDlgItem(IDC_EDIT_BOOK_INFO_IMAGE_PATH)->SetWindowText(str);
}

void CDlgBookManage::OnBnClickedButtonProviderInfoNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BookInfo bookinfo;
	SetBookInfoToCtrl(bookinfo);
}


void CDlgBookManage::OnCustomdrawListBooks(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//*pResult = 0;

	LPNMLVCUSTOMDRAW pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	int ret = -1;
	if (m_p_cls_books_list != NULL)
	{
		ret = m_p_cls_books_list->GetBookInfoIndexInList(pLVCD->nmcd.dwItemSpec);
	}

	if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		//*pResult = CDRF_DODEFAULT;
	}
	else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		//idx
		CString str_book_index;
		GetDlgItem(IDC_EDIT_BOOK_INFO_IDX)->GetWindowText(str_book_index);
		int i_bookinfo_index = atoi(str_book_index);

		if (m_p_cls_books_list != NULL)
		{
			if (i_bookinfo_index == ret)
			{
				pLVCD->clrText = RGB(255, 255, 255); // 글자색 지정  
				pLVCD->clrTextBk = RGB(102, 193, 193); // 배경색 지정  
			}
		}
		*pResult = CDRF_DODEFAULT;
	}
}


void CDlgBookManage::OnBnClickedButtonChangeBookCover()
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
		if (m_p_cls_books_list != NULL)
		{
			GetDlgItem(IDC_EDIT_BOOK_INFO_IMAGE_PATH)->SetWindowText(sFilePath);
		}
	}
}


void CDlgBookManage::OnBnClickedButtonBookinfoInfoUpdae()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_p_cls_books_list != NULL)
	{
		CString str_book_index;
		GetDlgItem(IDC_EDIT_BOOK_INFO_IDX)->GetWindowText(str_book_index);
		int i_bookinfo_index = atoi(str_book_index);

		std::string str_message;
		std::string str_title;
		if (i_bookinfo_index > 0)
		{
			str_message = "기존의 정보가 수정 됩니다.\n수정 하시겠습니까?";
			str_title = "수정확인";
		}
		else
		{
			str_message = "새로운 정보가 추가 됩니다.\n추가 하시겠습니까?";
			str_title = "추가확인";
		}

		const int result = MessageBox(str_message.c_str(), str_title.c_str(), MB_YESNO | MB_ICONQUESTION);

		switch (result)
		{
		case IDYES:
		{
			BookInfo bookinfo = GetBookInfoFromCtrl();

			//책정보 중에 image path
			CString str_book_cover_path;
			GetDlgItem(IDC_EDIT_BOOK_INFO_IMAGE_PATH)->GetWindowText(str_book_cover_path);
			std::string str_book_cover_path_ = str_book_cover_path;

			cv::Mat image_book_cover;
			image_book_cover = cv::imread(str_book_cover_path_.c_str());

			CDataBaseImageSave cls_image_save;
			std::string image_save_file_name = bookinfo.isbn;
			image_save_file_name += ".png";

			std::string str_save_file_path = cls_image_save.Save(image_book_cover, image_save_file_name);

			//url의 주소를 실제로 local에 저장한 path로 변경 한다.
			bookinfo.title_url = str_save_file_path;

			m_p_cls_books_list->AddBookInfoToDB(bookinfo);
		}
		break;
		case IDNO:
			break;
		}
	}
}
