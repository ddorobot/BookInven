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
	, m_p_cls_bookin_candidate(NULL)
	, m_p_cls_bookin_list(NULL)
	, m_candidate_iItem(-1)
	, m_candidate_iSubitem(-1)
	, m_radio_value_search(0)
{

}

CDlgBookIn::~CDlgBookIn()
{
	if (m_p_cls_bookin_candidate != NULL)
	{
		delete m_p_cls_bookin_candidate;
		m_p_cls_bookin_candidate = NULL;
	}

	if (m_p_cls_bookin_list != NULL)
	{
		delete m_p_cls_bookin_list;
		m_p_cls_bookin_list = NULL;
	}
}

void CDlgBookIn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOKIN_CANDIDATE, m_list_candidate);
	DDX_Control(pDX, IDC_COMBO_CEL, m_combo_change_cel);
	DDX_Control(pDX, IDC_LIST_BOOKIN_HISTORY, m_list_in);
	DDX_Radio(pDX, IDC_RADIO_SEARCH_1, m_radio_value_search);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SEARCH_START, m_dtctrl_start);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SEARCH_END, m_dtctrl_end);
	DDX_Control(pDX, IDC_COMBO_IN_TYPE, m_combo_in_type);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PROVIDE_DATE, m_date_provide);
}


BEGIN_MESSAGE_MAP(CDlgBookIn, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_BOOK_TITLE_IMAGE_CHANGE, &CDlgBookIn::OnBnClickedButtonBookTitleImageChange)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CANDIDATE_BOOKIN, &CDlgBookIn::OnBnClickedButtonAddCandidateBookin)
	ON_BN_CLICKED(IDC_BUTTON_BOOK_ISBN_SEARCH, &CDlgBookIn::OnBnClickedButtonBookIsbnSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BOOKIN_CANDIDATE, &CDlgBookIn::OnDblclkListBookinCandidate)
	ON_CBN_KILLFOCUS(IDC_COMBO_CEL, &CDlgBookIn::OnKillfocusComboCel)
	ON_CBN_SELCHANGE(IDC_COMBO_CEL, &CDlgBookIn::OnSelchangeComboCel)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BOOKIN, &CDlgBookIn::OnBnClickedButtonAddBookin)
	ON_BN_CLICKED(IDC_BUTTON_DEL_CANDIDATE_LIST, &CDlgBookIn::OnBnClickedButtonDelCandidateList)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BOOKIN_CANCEL, &CDlgBookIn::OnBnClickedButtonAddBookinCancel)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_BUTTON_BOOIN_HISTORY_SEARCH, &CDlgBookIn::OnBnClickedButtonBooinHistorySearch)
	ON_NOTIFY(NM_KILLFOCUS, IDC_DATETIMEPICKER_PROVIDE_DATE, &CDlgBookIn::OnKillfocusDatetimepickerProvideDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_PROVIDE_DATE, &CDlgBookIn::OnDatetimechangeDatetimepickerProvideDate)
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

			OnBnClickedButtonAddCandidateBookin();
		}

		if (nChar == VK_RETURN)
		{
			int nFocusCtrl = GetFocus()->GetDlgCtrlID();

			//printf("input code : %d\n", nChar);
			if (nFocusCtrl == IDC_EDIT_CEL)
			{
				if (nChar == VK_RETURN)
				{
					if (pMsg->hwnd == GetDlgItem(IDC_EDIT_CEL)->GetSafeHwnd())
					{

						CString str;
						GetDlgItemText(IDC_EDIT_CEL, str);
						if (m_p_cls_bookin_candidate != NULL)
						{
							m_p_cls_bookin_candidate->UpdateItem(m_candidate_iItem, m_candidate_iSubitem, std::string(str));
						}

						GetDlgItem(IDC_EDIT_CEL)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
					}

					return TRUE;                // Do not process further
				}
			}
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
	//Cell의 편집을 위한 Editor 컨트롤러
	GetDlgItem(IDC_EDIT_CEL)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	GetDlgItem(IDC_COMBO_CEL)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	GetDlgItem(IDC_DATETIMEPICKER_PROVIDE_DATE)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);

	CLoadBitmap cls_load_bitmap;
	cls_load_bitmap.Load(IDB_BITMAP_BOOK2, 1.0, &m_mat_image_book_cover);
	m_mat_image_book_cover.copyTo(m_mat_image_base_book_cover);

	m_p_cls_bookin_candidate = new CBookInCandidate(&m_list_candidate);
	m_p_cls_bookin_list = new CBookInList(&m_list_in);

	//type combo box
	m_combo_in_type.AddString("전체");
	m_combo_in_type.AddString("신규입고");
	m_combo_in_type.AddString("환불입고");
	m_combo_in_type.SetCurSel(1);

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
		boost::this_thread::sleep(boost::posix_time::millisec(100));

		if (this->IsWindowVisible())
		{
			if (m_p_cls_bookin_candidate != NULL)
			{
				m_p_cls_bookin_candidate->UpdateList();

				int book_total_count = m_p_cls_bookin_candidate->GetTotalBookCount();
				CString str;
				str.Format("%d권의 책 입고", book_total_count);

				CString button_str;
				GetDlgItem(IDC_BUTTON_ADD_BOOKIN)->GetWindowText(button_str);

				if (str != button_str)
				{
					GetDlgItem(IDC_BUTTON_ADD_BOOKIN)->SetWindowText(str);
				}

				if (book_total_count <= 0)
				{
					GetDlgItem(IDC_BUTTON_ADD_BOOKIN)->EnableWindow(FALSE);
				}
				else
				{
					GetDlgItem(IDC_BUTTON_ADD_BOOKIN)->EnableWindow(TRUE);
				}
			}

			if (m_p_cls_bookin_list != NULL)
			{
#if 0
				m_p_cls_bookin_list->UpdateList();
#endif
				int count_del = m_p_cls_bookin_list->GetCheckedItemCount();

				if (count_del > 0)
				{
					GetDlgItem(IDC_BUTTON_ADD_BOOKIN_CANCEL)->EnableWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_BUTTON_ADD_BOOKIN_CANCEL)->EnableWindow(FALSE);
				}
			}

			//printf("Book Manage\n");
			cls_draw2hdc.DrawToHDC(GetImageBookCover(), dc_display.m_hDC, &rect_book_cover);				//draw on display_rect
		}
	};
}

void CDlgBookIn::UpdateBookInfoOnTextbox(const std::string isbn)
{
	m_cur_book_info = m_cls_get_book_info.GetInfo(isbn);

	printf(" - name : %s\n", m_cur_book_info.name.c_str());
	printf(" - author : %s\n", m_cur_book_info.author.c_str());
	printf(" - price : %d\n", m_cur_book_info.price);
	printf(" - publisher : %s\n", m_cur_book_info.publisher.c_str());
	printf(" - publish date : %s\n", m_cur_book_info.publish_date.c_str());
	printf(" - title url : %s\n", m_cur_book_info.title_url.c_str());

	UpdateBookInfoOnTextbox(m_cur_book_info);

	if (!m_cur_book_info.title_url.empty())
	{
		cv::Mat mat_image_read = cv::imread(m_cur_book_info.title_url.c_str());

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

/*
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
*/

void CDlgBookIn::OnBnClickedButtonAddCandidateBookin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_isbn;
	GetDlgItem(IDC_EDIT_BOOK_INFO_ISBN)->GetWindowText(str_isbn);
	std::string str_isbn_ = str_isbn;

	CString str_name;
	GetDlgItem(IDC_EDIT_BOOK_INFO_NAME)->GetWindowText(str_name);
	std::string str_name_ = str_name;

	CString str_author;
	GetDlgItem(IDC_EDIT_BOOK_INFO_AUTHOR)->GetWindowText(str_author);
	std::string str_author_ = str_author;

	CString str_publisher;
	GetDlgItem(IDC_EDIT_BOOK_INFO_PUBLISHER)->GetWindowText(str_publisher);
	std::string str_publisher_ = str_publisher;

	CString str_publish_date;
	GetDlgItem(IDC_EDIT_BOOK_INFO_PUBLISH_DATE)->GetWindowText(str_publish_date);
	std::string str_publish_date_ = str_publish_date;

	CString str_price;
	GetDlgItem(IDC_EDIT_BOOK_INFO_NAME)->GetWindowText(str_price);
	std::string str_price_ = str_price;

	if (str_isbn_.empty() || str_name_.empty() || str_author_.empty() || str_publisher_.empty() || str_price_.empty())
	{
		return;
	}

	if (str_isbn_ != m_cur_book_info.isbn || str_name_ != m_cur_book_info.name || str_author_ != m_cur_book_info.author || str_publisher_ != m_cur_book_info.publisher )
	{
		return;
	}

	BookIn_Info candidate;
	candidate.book_info = m_cur_book_info;
	m_p_cls_bookin_candidate->AddCandidate(candidate);
}


void CDlgBookIn::OnBnClickedButtonBookIsbnSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;
	GetDlgItem(IDC_EDIT_BOOK_INFO_ISBN)->GetWindowText(str);

	std::string str_isbn = str;
	UpdateBookInfoOnTextbox(str_isbn);
}


void CDlgBookIn::OnDblclkListBookinCandidate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;

	m_candidate_iItem = pNMITEM->iItem;
	m_candidate_iSubitem = pNMITEM->iSubItem;

	if (m_candidate_iItem != -1 && (m_candidate_iSubitem > 5 || m_candidate_iSubitem == 1/*출판사배송일*/) )
	{
		CRect rect;

		if (m_candidate_iSubitem == 0)
		{
			m_list_candidate.GetItemRect(m_candidate_iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_list_candidate.GetColumnWidth(0);
		}
		else
		{
			m_list_candidate.GetSubItemRect(m_candidate_iItem, m_candidate_iSubitem, LVIR_BOUNDS, rect);
		}

		m_list_candidate.ClientToScreen(rect);
		this->ScreenToClient(rect);

#if 0
		if (m_candidate_iSubitem == 1)		//공급사 배송일 
		{
			//GetDlgItem(IDC_DATETIMEPICKER_PROVIDE_DATE)->SetWindowText(m_list_candidate.GetItemText(m_candidate_iItem, m_candidate_iSubitem));
			GetDlgItem(IDC_DATETIMEPICKER_PROVIDE_DATE)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
			GetDlgItem(IDC_DATETIMEPICKER_PROVIDE_DATE)->SetFocus();
		}
		else 
#endif 
		if(m_candidate_iSubitem == SPECIAL_INDEX_PROVIDER_NAME /*공급사*/ || m_candidate_iSubitem == SPECIAL_INDEX_PROVIDER_TYPE /*공급방식*/ )
		{ 
			//GetDlgItem(IDC_COMBO_CEL)->Insert
			m_combo_change_cel.ResetContent();

			if (m_candidate_iSubitem == SPECIAL_INDEX_PROVIDER_NAME)	//공급사
			{
				//m_combo_change_cel.AddString(_T("-"));
				m_combo_change_cel.InsertString(0, _T("-"));
				m_combo_change_cel.SetItemData(0, -1);

				//DB에서 provider의 정보를 얻어 오는데. 이름만 필요하기 때문에 base정보만 얻어 온다.
				CDataBaseProvider cls_db_provider;
				std::vector<ProviderInfoBase> vec_provider_base_info = cls_db_provider.GetBaseInfo();

				int provider_base_info_size = vec_provider_base_info.size();

				for (int i = 0; i < provider_base_info_size; i++)
				{
					std::string provicer_info_name = vec_provider_base_info[i].name;
					if (!vec_provider_base_info[i].lic.empty())
					{
						provicer_info_name += "(" + vec_provider_base_info[i].lic + ")";
					}

					//m_combo_change_cel.AddString(provicer_info_name.c_str());
					m_combo_change_cel.InsertString(i+1, provicer_info_name.c_str());
					m_combo_change_cel.SetItemData(i + 1, vec_provider_base_info[i].idx);

					//printf("InsertString : %d, %s\n", vec_provider_base_info[i].idx, provicer_info_name.c_str()) ;
				}
			}
			else if (m_candidate_iSubitem == SPECIAL_INDEX_PROVIDER_TYPE)	//공급방식
			{
				//m_combo_change_cel.AddString(_T("-"));
				m_combo_change_cel.InsertString(0, _T("-"));
				m_combo_change_cel.SetItemData(0, -1);

				for (int i = 0; i < provide_type_size; i++)
				{
					//m_combo_change_cel.AddString(str_provide_type[i].c_str());
					m_combo_change_cel.InsertString(i + 1, str_provide_type[i].c_str());
					m_combo_change_cel.SetItemData(i + 1, i);
				}
			}

			m_combo_change_cel.SetCurSel(0);

			/*
			//Select 
			CString str;
			CString str_item = m_list_candidate.GetItemText(m_candidate_iItem, m_candidate_iSubitem);
			int sel_size = 3;
			for (int i = 0; i < sel_size; i++)
			{
				m_combo_change_cel.GetLBText(i, str);

				if (str_item == str)
				{
					m_combo_change_cel.SetCurSel(i);
					break;
				}
			}
			*/

			GetDlgItem(IDC_COMBO_CEL)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
			GetDlgItem(IDC_COMBO_CEL)->SetFocus();

			m_combo_change_cel.ShowDropDown(1);
		}
		else
		{
			GetDlgItem(IDC_EDIT_CEL)->SetWindowText(m_list_candidate.GetItemText(m_candidate_iItem, m_candidate_iSubitem));
			GetDlgItem(IDC_EDIT_CEL)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
			GetDlgItem(IDC_EDIT_CEL)->SetFocus();
		}
	}

	*pResult = 0;
}


void CDlgBookIn::OnKillfocusComboCel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_COMBO_CEL)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
}


void CDlgBookIn::OnSelchangeComboCel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;

	int sel = m_combo_change_cel.GetCurSel();
	m_combo_change_cel.GetLBText(sel, str);
	
	if (m_p_cls_bookin_candidate != NULL)
	{
		if (m_candidate_iSubitem == SPECIAL_INDEX_PROVIDER_NAME)	//공급사
		{
			//공급사의 정보를 변경
			int index = m_combo_change_cel.GetItemData(sel);
			m_p_cls_bookin_candidate->ChangeProviderBaseIndex(m_candidate_iItem, index);
		}
		else if (m_candidate_iSubitem == SPECIAL_INDEX_PROVIDER_TYPE)	//공급방식
		{
			//공급 방식을 변경
			int index = m_combo_change_cel.GetItemData(sel);

			if (index >= 0 && index < provide_type_size)
			{
				m_p_cls_bookin_candidate->ChangeProvideType(m_candidate_iItem, index);
			}
		}
		else
		{
			m_p_cls_bookin_candidate->UpdateItem(m_candidate_iItem, m_candidate_iSubitem, std::string(str));
		}
	}

	GetDlgItem(IDC_COMBO_CEL)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
}


void CDlgBookIn::OnBnClickedButtonAddBookin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_p_cls_bookin_candidate != NULL)
	{
		int ret = m_p_cls_bookin_candidate->CheckedAddDataBase();

		std::string str_message = "모두 입고 처리 하였습니다.";
		if (ret > 0)
		{
			str_message = "일부만 입고 처리 되었습니다.";
		}

		const int result = MessageBox(str_message.c_str(), "입고", MB_OK | MB_ICONASTERISK);

	}

	//선택되었던 정보를 삭제
	//OnBnClickedButtonDelCandidateList();

#if 0
	if (m_p_cls_bookin_list != NULL)
	{
		m_p_cls_bookin_list->UpdateList();
	}
#else
	m_radio_value_search = 0;
	UpdateData(FALSE);

	OnBnClickedButtonBooinHistorySearch();
#endif
}


void CDlgBookIn::OnBnClickedButtonDelCandidateList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_p_cls_bookin_candidate != NULL)
	{
		m_p_cls_bookin_candidate->DelCheckedItem();
	}
}


void CDlgBookIn::OnBnClickedButtonAddBookinCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	const int result = MessageBox("삭제하시겠습니까?", "입고취소확인", MB_YESNO | MB_ICONQUESTION);

	switch (result)
	{
	case IDYES:
		{
			if (m_p_cls_bookin_list != NULL)
			{
				m_p_cls_bookin_list->DelCheckedItem();

				//m_p_cls_bookin_list->UpdateList();
			}
			OnBnClickedButtonBooinHistorySearch();
		}
		break;
	case IDNO:
		break;
	}
}


void CDlgBookIn::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (this->IsWindowVisible())
	{
		OnBnClickedButtonBooinHistorySearch();
	}
	
}


void CDlgBookIn::OnBnClickedButtonBooinHistorySearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//CString str_sel_button;
	//str_sel_button.Format(_T("%d"), m_radio_value_search);
	//AfxMessageBox(str_sel_button);

	CMyTime cls_my_time;
	std::string cur_time = cls_my_time.GetNowDate();

	int type = m_combo_in_type.GetCurSel();

	switch (m_radio_value_search)
	{
	case 0:	//오늘
		if (m_p_cls_bookin_list != NULL)
		{
			m_p_cls_bookin_list->UpdateList(cur_time, cur_time, type); 
		}
		break;

	case 1:	//1주일
		if (m_p_cls_bookin_list != NULL)
		{
			std::string old_time = cls_my_time.GetPeriodDate(7);
			m_p_cls_bookin_list->UpdateList(old_time, cur_time, type);
		}
		break;

	case 2:	//1개월
		if (m_p_cls_bookin_list != NULL)
		{
			std::string old_time = cls_my_time.GetPeriodDate(30);
			m_p_cls_bookin_list->UpdateList(old_time, cur_time, type);
		}
		break;

	case 3:	//기간 검색
		if (m_p_cls_bookin_list != NULL)
		{
			SYSTEMTIME date_start;
			m_dtctrl_start.GetTime(&date_start);

			SYSTEMTIME date_end;
			m_dtctrl_end.GetTime(&date_end);

			CString csrt_start_date;
			csrt_start_date.Format(_T("%04d-%02d-%02d"), date_start.wYear, date_start.wMonth, date_start.wDay);

			CString csrt_end_date;
			csrt_end_date.Format(_T("%04d-%02d-%02d"), date_end.wYear, date_end.wMonth, date_end.wDay);

			m_p_cls_bookin_list->UpdateList(std::string(csrt_start_date), std::string(csrt_end_date), type);
		}
		break;
	}
}


void CDlgBookIn::OnKillfocusDatetimepickerProvideDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_DATETIMEPICKER_PROVIDE_DATE)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);

	*pResult = 0;
}


void CDlgBookIn::OnDatetimechangeDatetimepickerProvideDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_p_cls_bookin_candidate != NULL)
	{
		SYSTEMTIME date_provide;
		m_date_provide.GetTime(&date_provide);

		CString str;
		str.Format(_T("%04d-%02d-%02d"), date_provide.wYear, date_provide.wMonth, date_provide.wDay);
		m_p_cls_bookin_candidate->UpdateItem(m_candidate_iItem, m_candidate_iSubitem, std::string(str));
	}	

	*pResult = 0;
}
