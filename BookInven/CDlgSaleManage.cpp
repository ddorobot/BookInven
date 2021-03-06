// CDlgSaleManage.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgSaleManage.h"
#include "afxdialogex.h"


// CDlgSaleManage 대화 상자

IMPLEMENT_DYNAMIC(CDlgSaleManage, CDialogEx)

CDlgSaleManage::CDlgSaleManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SALE_MANAGE, pParent)
	, m_p_list_sale_history(NULL)
	, m_p_list_sale_history_detail(NULL)
	, m_radio_search_option(FALSE)
{

}

CDlgSaleManage::~CDlgSaleManage()
{
	if (m_p_list_sale_history != NULL)
	{
		delete m_p_list_sale_history;
		m_p_list_sale_history = NULL;
	}

	if (m_p_list_sale_history_detail != NULL)
	{
		delete m_p_list_sale_history_detail;
		m_p_list_sale_history_detail = NULL;
	}
}

void CDlgSaleManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SALE_HISTORY, m_list_sale_history);
	DDX_Radio(pDX, IDC_RADIO_SALE_SEARCH_1, m_radio_search_option);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SALE_SEARCH_START, m_dtctrl_start);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SALE_SEARCH_END, m_dtctrl_end);
	DDX_Control(pDX, IDC_LIST_SALE_HISTORY_DETAIL, m_list_sale_history_detail);
}


BEGIN_MESSAGE_MAP(CDlgSaleManage, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_BUTTON_SALE_HISTORY_SEARCH, &CDlgSaleManage::OnBnClickedButtonSaleHistorySearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SALE_HISTORY, &CDlgSaleManage::OnClickListSaleHistory)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_REFUND, &CDlgSaleManage::OnBnClickedButtonSelectRefund)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SALE_HISTORY_DETAIL, &CDlgSaleManage::OnClickListSaleHistoryDetail)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_SALE_HISTORY, &CDlgSaleManage::OnCustomdrawListSaleHistory)
END_MESSAGE_MAP()


// CDlgSaleManage 메시지 처리기


BOOL CDlgSaleManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_p_list_sale_history = new CBookSaleList(&m_list_sale_history);

	m_radio_search_option = 0;
	UpdateData(FALSE);

	OnBnClickedButtonSaleHistorySearch();

	//Detail list
	m_p_list_sale_history_detail = new CBookSaleDetailList(&m_list_sale_history_detail);

	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CDlgSaleManage::ThreadFunction, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgSaleManage::ThreadFunction(void)
{
	CDrawToHDC cls_draw2hdc;

	CRect rect_image;															//display rect
	GetDlgItem(IDC_STATIC_SALE_IMAGE)->GetClientRect(&rect_image);			//get rect information on window
	CClientDC dc_display(GetDlgItem(IDC_STATIC_SALE_IMAGE));					//device context for display mfc control

	cv::Mat image = cv::Mat::zeros(cv::Size(rect_image.Width(), rect_image.Height()), CV_8UC3);

	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(100));

		if (this->IsWindowVisible())
		{
			cls_draw2hdc.DrawToHDC(image, dc_display.m_hDC, &rect_image);				//draw on display_rect
		}
	};
}

void CDlgSaleManage::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (this->IsWindowVisible())
	{
		if (m_p_list_sale_history)
		{
			OnBnClickedButtonSaleHistorySearch();

			if (m_p_list_sale_history_detail)
			{
				POSITION pos = m_list_sale_history.GetFirstSelectedItemPosition();

				if (pos != NULL)
				{
					int nItem = m_list_sale_history.GetNextSelectedItem(pos);

					std::string str_sale_code = m_p_list_sale_history->GetSaleCode(nItem);

					m_p_list_sale_history_detail->UpdateList(str_sale_code);

					std::string memo = m_p_list_sale_history_detail->GetMemo(str_sale_code);

					CString str;
					str.Format(_T("%s"), memo.c_str());
					GetDlgItem(IDC_EDIT_SALE_MEMO)->SetWindowText(str);

					str.Format(_T("SALE CODE : %s"), str_sale_code.c_str());
					GetDlgItem(IDC_STATIC_CODE_NAME)->SetWindowText(str);
				}
			}
		}
	}
}


void CDlgSaleManage::OnBnClickedButtonSaleHistorySearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//CString str_sel_button;
	//str_sel_button.Format(_T("%d"), m_radio_value_search);
	//AfxMessageBox(str_sel_button);

	if (m_p_list_sale_history == NULL) return;

	CMyTime cls_my_time;
	std::string cur_time = cls_my_time.GetNowDate();

	int total_cost = 0;
	int total_count = 0;

	switch (m_radio_search_option)
	{
	case 0:	//오늘
	{
		m_p_list_sale_history->UpdateList(cur_time, cur_time, &total_cost, &total_count);
	}
		break;

	case 1:	//1주일
	{
		std::string old_time = cls_my_time.GetPeriodDate(7);
		m_p_list_sale_history->UpdateList(old_time, cur_time, &total_cost, &total_count);
	}
		break;

	case 2:	//1개월
	{
		std::string old_time = cls_my_time.GetPeriodDate(30);
		m_p_list_sale_history->UpdateList(old_time, cur_time, &total_cost, &total_count);
	}
		break;

	case 3:	//기간 검색
	{
		SYSTEMTIME date_start;
		m_dtctrl_start.GetTime(&date_start);

		SYSTEMTIME date_end;
		m_dtctrl_end.GetTime(&date_end);

		CString csrt_start_date;
		csrt_start_date.Format(_T("%04d-%02d-%02d"), date_start.wYear, date_start.wMonth, date_start.wDay);

		CString csrt_end_date;
		csrt_end_date.Format(_T("%04d-%02d-%02d"), date_end.wYear, date_end.wMonth, date_end.wDay);

		m_p_list_sale_history->UpdateList(std::string(csrt_start_date), std::string(csrt_end_date), &total_cost, &total_count);
	}
		break;
	}

	CString str;
	str.Format(_T("판매액 합계 : %d 원"), total_cost);
	GetDlgItem(IDC_STATIC_SALE_TEXT)->SetWindowText(str);

	if (m_p_list_sale_history_detail == NULL) return;

	str.Format(_T(""));
	GetDlgItem(IDC_EDIT_SALE_MEMO)->SetWindowText(str);

	str.Format(_T("SALE CODE :"));
	GetDlgItem(IDC_STATIC_CODE_NAME)->SetWindowText(str);

	m_p_list_sale_history_detail->UpdateList();
}


void CDlgSaleManage::OnClickListSaleHistory(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

#if 0
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;

	int iItem = pNMITEM->iItem;
	//int iSubitem = pNMITEM->iSubItem;
	if (m_p_list_sale_history != NULL)
	{
		//Sale Code
		std::string str_sale_code = m_p_list_sale_history->GetSaleCode(iItem);

		if (!str_sale_code.empty())
		{
			m_p_list_sale_history_detail->UpdateList(str_sale_code);

			std::string memo = m_p_list_sale_history_detail->GetMemo(str_sale_code);

			CString str;
			str.Format(_T("%s"), memo.c_str());
			GetDlgItem(IDC_EDIT_SALE_MEMO)->SetWindowText(str);

			str.Format(_T("SALE CODE : %s"), str_sale_code.c_str());
			GetDlgItem(IDC_STATIC_CODE_NAME)->SetWindowText(str);
		}
	}
#else
	SaleDetailListInfoUpdate();
#endif

	*pResult = 0;
}

void CDlgSaleManage::SaleDetailListInfoUpdate(void)
{
	//Detail list정보 업데이트
	if (m_p_list_sale_history_detail)
	{
		POSITION pos = m_list_sale_history.GetFirstSelectedItemPosition();

		if (pos != NULL)
		{
			int nItem = m_list_sale_history.GetNextSelectedItem(pos);

			std::string str_sale_code = m_p_list_sale_history->GetSaleCode(nItem);

			m_p_list_sale_history_detail->UpdateList(str_sale_code);

			std::string memo = m_p_list_sale_history_detail->GetMemo(str_sale_code);

			CString str;
			str.Format(_T("%s"), memo.c_str());
			GetDlgItem(IDC_EDIT_SALE_MEMO)->SetWindowText(str);

			str.Format(_T("SALE CODE : %s"), str_sale_code.c_str());
			GetDlgItem(IDC_STATIC_CODE_NAME)->SetWindowText(str);
		}
	}
}

void CDlgSaleManage::OnBnClickedButtonSelectRefund()
{
	CDlgRefundList cls_dlg_refund_list;

	//
	//Sale Code
	std::string str_sale_code;
	POSITION pos = m_list_sale_history.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_list_sale_history.GetNextSelectedItem(pos);

		str_sale_code = m_p_list_sale_history->GetSaleCode(nItem);
	}
	//

	cls_dlg_refund_list.SetSaleCode(str_sale_code);

	if (cls_dlg_refund_list.DoModal() == IDOK)
	{
		OnBnClickedButtonSaleHistorySearch();
		SaleDetailListInfoUpdate();
	}
}


void CDlgSaleManage::OnClickListSaleHistoryDetail(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	LVHITTESTINFO info;
	info.pt = pNMListView->ptAction;
	m_list_sale_history_detail.HitTest(&info);

	if (info.flags == LVHT_ONITEMSTATEICON) {

		// 체크박스가 클릭되면 여기로 들어온다.

		// 여기서 체크박스 상태를 확인 후 처리를 추가하면된다.
		if (m_list_sale_history_detail.GetCheck(pNMListView->iItem)) 
		{
			// 체크된 상태일 때 처리
		}
		else 
		{

			// 체크되지 않은 상태일 때 처리
		}
	}

	*pResult = 0;
}


void CDlgSaleManage::OnCustomdrawListSaleHistory(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//*pResult = 0;

	LPNMLVCUSTOMDRAW pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	CString strWhatToDo = m_list_sale_history.GetItemText(pLVCD->nmcd.dwItemSpec, 5);

	// 내가 알아서 조건을 주어야겠죠.  
	COLORREF text_color = RGB(0, 0, 0);
	COLORREF bg_color = RGB(255, 255, 255);

	if (strWhatToDo == _T("환불"))
	{
		text_color = RGB(128, 128, 128);
		bg_color = RGB(230,230,230);
	}
	else if (strWhatToDo == _T("현금"))
	{
		text_color = RGB(0, 0, 0);
	}
	else if (strWhatToDo == _T("카드"))
	{
		text_color = RGB(0, 0, 255);
	}


	//LPNMLVCUSTOMDRAW pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		//*pResult = CDRF_DODEFAULT;
	}
	else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		pLVCD->clrText = text_color; // 글자색 지정  
		pLVCD->clrTextBk = bg_color; // 배경색 지정  

		*pResult = CDRF_DODEFAULT;
	}
}
