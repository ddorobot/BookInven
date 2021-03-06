
// BookInvenDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "BookInvenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBookInvenDlg 대화 상자



CBookInvenDlg::CBookInvenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOKINVEN_DIALOG, pParent)
	,m_p_tab_dlg_window(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookInvenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MENU, m_tab_menu);
}

BEGIN_MESSAGE_MAP(CBookInvenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MENU, &CBookInvenDlg::OnSelchangeTabMenu)
END_MESSAGE_MAP()


// CBookInvenDlg 메시지 처리기

BOOL CBookInvenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CFont font_sel;
	font_sel.CreateFont(20, 0, 0, 0, FW_BOLD,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Times New Roman"));
	CFont font_unsel;
	font_sel.CreateFont(20, 0, 0, 0, FW_BOLD,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Times New Roman"));

	m_tab_menu.SetFonts(&font_sel, &font_unsel);

	// Delete the font object.
	font_sel.DeleteObject();
	font_unsel.DeleteObject();

	m_tab_menu.InsertItem(0, _T("판매"));
	m_tab_menu.InsertItem(1, _T("거래관리"));
	m_tab_menu.InsertItem(2, _T("입고관리"));
	m_tab_menu.InsertItem(3, _T("도서관리"));
	m_tab_menu.InsertItem(4, _T("반품관리"));
	m_tab_menu.InsertItem(5, _T("공급사정보"));
	m_tab_menu.InsertItem(6, _T("책방정보"));

	CRect rect_tab;
	m_tab_menu.GetClientRect(rect_tab);

	const int tab_margin_top = 30;
	const int tab_margin_left = 10;

	m_dlg_book_sale.Create(IDD_DIALOG_BOOK_SALE, &m_tab_menu);
	m_dlg_book_sale.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_sale_manage.Create(IDD_DIALOG_SALE_MANAGE, &m_tab_menu);
	m_dlg_sale_manage.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_book_in.Create(IDD_DIALOG_BOOK_IN, &m_tab_menu);
	m_dlg_book_in.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_book_manage.Create(IDD_DIALOG_BOOK_MANAGE, &m_tab_menu);
	m_dlg_book_manage.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_book_return.Create(IDD_DIALOG_BOOK_RETURN, &m_tab_menu);
	m_dlg_book_return.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_custom_manage.Create(IDD_DIALOG_CUSTOM_MANAGE, &m_tab_menu);
	m_dlg_custom_manage.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_store_info.Create(IDD_DIALOG_STORE_INFO, &m_tab_menu);
	m_dlg_store_info.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_p_tab_dlg_window = &m_dlg_book_sale;

	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CBookInvenDlg::ThreadFunction, this));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CBookInvenDlg::DrawAuthorInfo(cv::Mat image)
{
	//Text
	cv::Point textOrg(0, 0);
	// FreeType2 객체 생성
	cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
	// 바탕체 글꼴 불러오기
	ft2->loadFontData("C:\\Windows\\Fonts\\malgun.ttf", 0);

	int thickness = -1;
	int linestyle = 8;
	int baseline = 0;

	std::string text;
	std::wstring strUni;
	std::string strUTF8;
	char cstr_text[255];


	//Text
	int fontHeight = 10;
	sprintf(cstr_text, "제작자 : ddorobot@gmail.com");
	text = cstr_text;
	strUni = CA2W(text.c_str());
	strUTF8 = CW2A(strUni.c_str(), CP_UTF8);

	cv::Size textSize = ft2->getTextSize(strUTF8, fontHeight, thickness, &baseline);
	textSize.height = fontHeight;

	//image draw
	textOrg.x = (image.cols - textSize.width) / 2;
	textOrg.y = (image.rows - textSize.height);

	//cv::rectangle(image, cv::Rect(textOrg.x, textOrg.y, textSize.width, textSize.height), cv::Scalar(128, 128, 255), CV_FILLED);
	ft2->putText(image, strUTF8, textOrg, fontHeight, cv::Scalar(177, 177, 177), thickness, linestyle, true);
}

void CBookInvenDlg::ThreadFunction(void)
{
	CDrawToHDC cls_draw2hdc;

	CRect rect_top;															//display rect
	GetDlgItem(IDC_STATIC_TOP)->GetClientRect(&rect_top);			//get rect information on window
	CClientDC dc_display(GetDlgItem(IDC_STATIC_TOP));					//device context for display mfc control

	cv::Mat mat_image_top;
	mat_image_top = cv::Mat::zeros(cv::Size(rect_top.Width(), rect_top.Height()), CV_8UC3);

	//logo
	cv::Mat mat_image_logo;
	mat_image_logo = cv::imread("../image/modo_logo.png");

	//Text
	cv::Point textOrg(0, 0);
	// FreeType2 객체 생성
	cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
	// 바탕체 글꼴 불러오기
	ft2->loadFontData("C:\\Windows\\Fonts\\H2HDRM.TTF", 0);

	int thickness = -1;
	int linestyle = 8;
	int baseline = 0;

	std::string text;
	std::wstring strUni;
	std::string strUTF8;
	char cstr_text[255];

	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(100));

		if (this->IsWindowVisible())
		{
			//Text
			//측정 중 표시
			int fontHeight = 30;
			sprintf(cstr_text, "책방 모도");
			text = cstr_text;
			strUni = CA2W(text.c_str());
			strUTF8 = CW2A(strUni.c_str(), CP_UTF8);

			cv::Size textSize = ft2->getTextSize(strUTF8, fontHeight, thickness, &baseline);
			textSize.height = fontHeight;

			int total_width = textSize.width;
			int padding = 0;
			if (!mat_image_logo.empty())
			{
				padding = 10;
				total_width += (mat_image_logo.cols + padding);
			}

			//image draw
			if (!mat_image_logo.empty())
			{
				cv::Rect dest_rect;
				dest_rect.x = (mat_image_top.cols - total_width) / 2;
				dest_rect.y = (mat_image_top.rows - mat_image_logo.rows) / 2;
				dest_rect.width = mat_image_logo.cols;
				dest_rect.height = mat_image_logo.rows;
				mat_image_logo.copyTo(mat_image_top(dest_rect));

				//center
				textOrg.x = dest_rect.x + dest_rect.width + padding;
				textOrg.y = (mat_image_top.rows - textSize.height) / 2 + textSize.height;
			}
			else
			{
				textOrg.x = (mat_image_top.cols - textSize.width) / 2;
				textOrg.y = (mat_image_top.rows - textSize.height) / 2 + textSize.height;
			}

			//cv::rectangle(image, cv::Rect(textOrg.x, textOrg.y, textSize.width, textSize.height), cv::Scalar(128, 128, 255), CV_FILLED);
			ft2->putText(mat_image_top, strUTF8, textOrg, fontHeight, cv::Scalar(193, 193, 102), thickness, linestyle, true);

			DrawAuthorInfo(mat_image_top);

			cls_draw2hdc.DrawToHDC(mat_image_top, dc_display.m_hDC, &rect_top);				//draw on display_rect
		}
	};

	mat_image_top.release();
}


void CBookInvenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBookInvenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBookInvenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//BOOL CBookInvenDlg::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	return CDialogEx::PreTranslateMessage(pMsg);
//}


void CBookInvenDlg::OnSelchangeTabMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_p_tab_dlg_window != NULL)
	{
		m_p_tab_dlg_window->ShowWindow(SW_HIDE);

		m_p_tab_dlg_window = NULL;
	}

	int tab_index = m_tab_menu.GetCurSel();

	switch (tab_index)
	{
	case 0:
		m_dlg_book_sale.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_book_sale;
		break;
	case 1:
		m_dlg_sale_manage.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_sale_manage;
		break;
	case 2:
		m_dlg_book_in.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_book_in;
		break;
	case 3:
		//m_dlg_book_manage
		m_dlg_book_manage.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_book_manage;
		break;
	case 4:
		m_dlg_book_return.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_book_return;
		break;
	case 5:
		m_dlg_custom_manage.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_custom_manage;
		break;
	case 6:
		m_dlg_store_info.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_store_info;
		break;
	default:
		break;
	}

	*pResult = 0;
}


BOOL CBookInvenDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		UINT nChar = pMsg->wParam;
		 
		//자식 윈도우로 메세지 전송
		if (m_p_tab_dlg_window == &m_dlg_book_in || m_p_tab_dlg_window == &m_dlg_book_sale || m_p_tab_dlg_window == &m_dlg_book_manage)
		{
			m_p_tab_dlg_window->PostMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
			return TRUE;
		}

		//메인 윈도우에서 Enter키와 Esc키의 입력을 무시
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
