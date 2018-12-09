
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
	font_sel.CreateFont(20, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Times New Roman"));
	CFont font_unsel;
	font_sel.CreateFont(20, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Times New Roman"));

	m_tab_menu.SetFonts(&font_sel, &font_unsel);

	// Delete the font object.
	font_sel.DeleteObject();
	font_unsel.DeleteObject();

	m_tab_menu.InsertItem(0, _T("판매"));
	m_tab_menu.InsertItem(1, _T("도서관리"));
	m_tab_menu.InsertItem(2, _T("판매관리"));
	m_tab_menu.InsertItem(3, _T("고객정보"));
	m_tab_menu.InsertItem(4, _T("책방정보"));

	CRect rect_tab;
	m_tab_menu.GetClientRect(rect_tab);

	const int tab_margin_top = 30;
	const int tab_margin_left = 10;

	m_dlg_book_in.Create(IDD_DIALOG_IN, &m_tab_menu);
	m_dlg_book_in.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_book_manage.Create(IDD_DIALOG_BOOK_MANAGE, &m_tab_menu);
	m_dlg_book_manage.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_sale_manage.Create(IDD_DIALOG_SALE_MANAGE, &m_tab_menu);
	m_dlg_sale_manage.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_custom_manage.Create(IDD_DIALOG_CUSTOM_MANAGE, &m_tab_menu);
	m_dlg_custom_manage.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_dlg_store_info.Create(IDD_DIALOG_STORE_INFO, &m_tab_menu);
	m_dlg_store_info.SetWindowPos(NULL, tab_margin_left, tab_margin_top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_p_tab_dlg_window = &m_dlg_book_in;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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



BOOL CBookInvenDlg::PreTranslateMessage(MSG* pMsg)
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
		m_dlg_book_in.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_book_in;
		break;
	case 1:
		m_dlg_book_manage.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_book_manage;
		break;
	case 2:
		m_dlg_sale_manage.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_sale_manage;
		break;
	case 3:
		m_dlg_custom_manage.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_custom_manage;
		break;
	case 4:
		m_dlg_store_info.ShowWindow(SW_SHOW);
		m_p_tab_dlg_window = &m_dlg_store_info;
		break;
	default:
		break;
	}

	*pResult = 0;
}
