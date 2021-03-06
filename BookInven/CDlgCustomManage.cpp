// CDlgCustomManage.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgCustomManage.h"
#include "afxdialogex.h"


// CDlgCustomManage 대화 상자

IMPLEMENT_DYNAMIC(CDlgCustomManage, CDialogEx)

CDlgCustomManage::CDlgCustomManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CUSTOM_MANAGE, pParent)
	, m_p_cls_provider_list(NULL)
{

}

CDlgCustomManage::~CDlgCustomManage()
{
	if (m_p_cls_provider_list != NULL)
	{
		delete m_p_cls_provider_list;
		m_p_cls_provider_list = NULL;
	}
}

void CDlgCustomManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROVIDER, m_list_provider);
	DDX_Control(pDX, IDC_COMBO_PROVIDE_TYPE, m_combo_provide_type);
	DDX_Control(pDX, IDC_COMBO_PROVIDE_RECEIPT, m_combo_receipt);
}


BEGIN_MESSAGE_MAP(CDlgCustomManage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PROVIDER_INFO_UPDAE, &CDlgCustomManage::OnBnClickedButtonProviderInfoUpdae)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PROVIDER, &CDlgCustomManage::OnDblclkListProvider)
	ON_BN_CLICKED(IDC_BUTTON_PROVIDER_INFO_NEW, &CDlgCustomManage::OnBnClickedButtonProviderInfoNew)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_PROVIDER, &CDlgCustomManage::OnCustomdrawListProvider)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgCustomManage::OnBnClickedButtonSearch)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_BUTTON_PROVIDER_DEL, &CDlgCustomManage::OnBnClickedButtonProviderDel)
END_MESSAGE_MAP()


// CDlgCustomManage 메시지 처리기


BOOL CDlgCustomManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_p_cls_provider_list = new CProviderInfoList(&m_list_provider);

	for (int i = 0; i < provide_type_size; i++)
	{
		m_combo_provide_type.AddString(str_provide_type[i].c_str());
	}
	m_combo_provide_type.SetCurSel(PROVIDE_BASE_TYPE);

	CString str;
	str.Format("%.2f", PROVIDE_BASE_RATE);
	GetDlgItem(IDC_EDIT_PROVIDE_RATE)->SetWindowText(str);

	str.Format("%d", PROVIDE_BASE_CALC_DAY);
	GetDlgItem(IDC_EDIT_PROVIDER_CALC_DAY)->SetWindowText(str);

	str.Format("%d", -1);
	GetDlgItem(IDC_EDIT_PROVIDER_INDEX)->SetWindowText(str);

	m_combo_receipt.AddString("NO");
	m_combo_receipt.AddString("YES");
	m_combo_receipt.SetCurSel(0);

	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CDlgCustomManage::ThreadFunction, this));

	//Thread 
	m_run_thread_ui = true;
	//cread thread
	m_thread_ui = boost::thread(boost::bind(&CDlgCustomManage::ThreadFunctionUI, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgCustomManage::ThreadFunction(void)
{
#if 0
	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(100));

		if (this->IsWindowVisible())
		{
			if (m_p_cls_provider_list != NULL)
			{
				m_p_cls_provider_list->UpdateList();
			}
		}
	};
#endif
}

void CDlgCustomManage::ThreadFunctionUI(void)
{
	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(100));

		if (this->IsWindowVisible())
		{
			CString str_provider_index;
			GetDlgItem(IDC_EDIT_PROVIDER_INDEX)->GetWindowText(str_provider_index);
			int provider_index = atoi(str_provider_index);

			std::string button_string = "업데이트";
			if (provider_index < 0)
			{
				button_string = "추가";
			}

			CString str_button;
			GetDlgItem(IDC_BUTTON_PROVIDER_INFO_UPDAE)->GetWindowText(str_button);

			if (std::string(str_button) != button_string)
			{
				GetDlgItem(IDC_BUTTON_PROVIDER_INFO_UPDAE)->SetWindowText(button_string.c_str());
			}

			//삭제 버튼의 정보 
			if (m_p_cls_provider_list != NULL)
			{
				int provider_total_count = m_p_cls_provider_list->GetCheckedCount();
				CString str;
				str.Format("%d개의 협력사 삭제", provider_total_count);

				CString button_str;
				GetDlgItem(IDC_BUTTON_PROVIDER_DEL)->GetWindowText(button_str);

				if (str != button_str)
				{
					GetDlgItem(IDC_BUTTON_PROVIDER_DEL)->SetWindowText(str);
				}

				if (provider_total_count <= 0)
				{
					GetDlgItem(IDC_BUTTON_PROVIDER_DEL)->EnableWindow(FALSE);
				}
				else
				{
					GetDlgItem(IDC_BUTTON_PROVIDER_DEL)->EnableWindow(TRUE);
				}
			}
		}
	};
}


void CDlgCustomManage::OnBnClickedButtonProviderInfoUpdae()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//데이타 수집
	ProviderInfo provider = GetProviderInfoFromCtrl();

	CDataBaseProvider cls_db_provider;
	//기존에 같은 이름 혹은 lic정보로 저장된 데이타가 있는지 확인
	std::vector<ProviderInfo> vec_exist_provider = cls_db_provider.GetInfo(provider.base.name, provider.base.lic);
	int i_exist_provider_size = vec_exist_provider.size();

	CString str_provider_index;
	GetDlgItem(IDC_EDIT_PROVIDER_INDEX)->GetWindowText(str_provider_index);
	int provider_index = atoi(str_provider_index);

	if (provider_index < 0 )
	{
		if (i_exist_provider_size > 0)
		{
			//새롭게 추가 하는 데이타 인데 같은 이름 혹은 사업자등록 번호로 이미 DB에 저장되어 있다. 그럼에도 불구하고 추가 할 것인지 여부를 묻는다.
			CString message;
			message.Format("같은 이름,사업자등록번호를 갖는 정보가 이미 DB에 있습니다.\n그럼에도 추가 하시겠습니까?");

			// Show the message box with a question mark icon
			const int result = MessageBox(message, "중복확인", MB_YESNO | MB_ICONQUESTION);

			switch (result)
			{
			case IDYES:
				cls_db_provider.AddProviderInfo(provider);
				break;
			case IDNO:
				break;
			}
		}
		else
		{
			//추가 한다.
			cls_db_provider.AddProviderInfo(provider);
		}
	}
	else
	{
		//업데이트
		cls_db_provider.UpdateProviderInfo(provider_index, provider);
	}

	if (m_p_cls_provider_list != NULL)
	{
		m_p_cls_provider_list->Search("*");
	}

	OnBnClickedButtonProviderInfoNew();
}

ProviderInfo CDlgCustomManage::GetProviderInfoFromCtrl(void)
{
	CString str_provider_name;
	GetDlgItem(IDC_EDIT_PROVIDER_NAME)->GetWindowText(str_provider_name);

	CString str_provider_lic;
	GetDlgItem(IDC_EDIT_PROVIDER_LIC)->GetWindowText(str_provider_lic);

	CString str_provider_tel;
	GetDlgItem(IDC_EDIT_PROVIDER_TEL)->GetWindowText(str_provider_tel);

	CString str_provider_email;
	GetDlgItem(IDC_EDIT_PROVIDER_EMAIL)->GetWindowText(str_provider_email);

	CString str_provider_address;
	GetDlgItem(IDC_EDIT_PROVIDER_ADDRESS)->GetWindowText(str_provider_address);

	int i_provide_type = m_combo_provide_type.GetCurSel();

	CString str_provide_base_rate;
	GetDlgItem(IDC_EDIT_PROVIDE_RATE)->GetWindowText(str_provide_base_rate);

	CString str_provider_calc_day;
	GetDlgItem(IDC_EDIT_PROVIDER_CALC_DAY)->GetWindowText(str_provider_calc_day);

	int i_receipt_able = m_combo_receipt.GetCurSel();

	CString str_provider_bank_name;
	GetDlgItem(IDC_EDIT_PROVIDER_BANK_NAME)->GetWindowText(str_provider_bank_name);

	CString str_provider_bank_num;
	GetDlgItem(IDC_EDIT_PROVIDER_BANK_NUM)->GetWindowText(str_provider_bank_num);

	CString str_provider_bank_author;
	GetDlgItem(IDC_EDIT_PROVIDER_BANK_AUTHOR)->GetWindowText(str_provider_bank_author);

	//idx
	CString str_provider_index;
	GetDlgItem(IDC_EDIT_PROVIDER_INDEX)->GetWindowText(str_provider_index);
	int i_provider_index = atoi(str_provider_index);

	CString str_provider_memo;
	GetDlgItem(IDC_EDIT_PROVIDER_MEMO)->GetWindowText(str_provider_memo);

	ProviderInfo provider;
	provider.base.idx = i_provider_index;
	provider.base.name = str_provider_name;
	provider.base.lic = str_provider_lic;
	provider.detail.tel = str_provider_tel;
	provider.detail.email = str_provider_email;
	provider.detail.address = str_provider_address;
	provider.detail.provide_type = i_provide_type;
	provider.detail.provide_rate = atof(str_provide_base_rate);
	provider.detail.calc_day = atoi(str_provider_calc_day);
	provider.detail.receipt_able = (bool)i_receipt_able;
	provider.detail.bank_name = str_provider_bank_name;
	provider.detail.bank_num = str_provider_bank_num;
	provider.detail.bank_author = str_provider_bank_author;
	provider.detail.memo = str_provider_memo;

	return provider;
}

void CDlgCustomManage::SetProviderInfoToCtrl(const ProviderInfo provider)
{
	//AfxMessageBox("%d", provider.base.idx);
	//printf("Select Item index = %d\n", provider.base.idx);

	CString str_provider_name;
	str_provider_name.Format(_T("%s"), provider.base.name.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_NAME)->SetWindowText(str_provider_name);

	CString str_provider_lic;
	str_provider_lic.Format(_T("%s"), provider.base.lic.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_LIC)->SetWindowText(str_provider_lic);

	CString str_provider_tel;
	str_provider_tel.Format(_T("%s"), provider.detail.tel.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_TEL)->SetWindowText(str_provider_tel);

	CString str_provider_email;
	str_provider_email.Format(_T("%s"), provider.detail.email.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_EMAIL)->SetWindowText(str_provider_email);

	CString str_provider_address;
	str_provider_address.Format(_T("%s"), provider.detail.address.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_ADDRESS)->SetWindowText(str_provider_address);

	m_combo_provide_type.SetCurSel(provider.detail.provide_type);
	
	CString str_provide_base_rate;
	str_provide_base_rate.Format(_T("%.2f"), provider.detail.provide_rate);
	GetDlgItem(IDC_EDIT_PROVIDE_RATE)->SetWindowText(str_provide_base_rate);

	CString str_provider_calc_day;
	str_provider_calc_day.Format(_T("%d"), provider.detail.calc_day);
	GetDlgItem(IDC_EDIT_PROVIDER_CALC_DAY)->SetWindowText(str_provider_calc_day);

	m_combo_receipt.SetCurSel((int)provider.detail.receipt_able);

	CString str_provider_bank_name;
	str_provider_bank_name.Format(_T("%s"), provider.detail.bank_name.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_BANK_NAME)->SetWindowText(str_provider_bank_name);

	CString str_provider_bank_num;
	str_provider_bank_num.Format(_T("%s"), provider.detail.bank_num.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_BANK_NUM)->SetWindowText(str_provider_bank_num);

	CString str_provider_bank_author;
	str_provider_bank_author.Format(_T("%s"), provider.detail.bank_author.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_BANK_AUTHOR)->SetWindowText(str_provider_bank_author);

	//idx
	CString str_provider_index;
	str_provider_index.Format(_T("%d"), provider.base.idx);
	GetDlgItem(IDC_EDIT_PROVIDER_INDEX)->SetWindowText(str_provider_index);

	//memo
	CString str_provider_memo;
	str_provider_memo.Format(_T("%s"), provider.detail.memo.c_str());
	GetDlgItem(IDC_EDIT_PROVIDER_MEMO)->SetWindowText(str_provider_memo);

}

void CDlgCustomManage::OnDblclkListProvider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;

	int iItem = pNMITEM->iItem;
	//int iSubitem = pNMITEM->iSubItem;
	if (m_p_cls_provider_list != NULL)
	{
		ProviderInfo provider = m_p_cls_provider_list->GetProviderInfoInList(iItem);

		SetProviderInfoToCtrl(provider);
	}

	m_list_provider.Invalidate(TRUE);

	*pResult = 0;
}


void CDlgCustomManage::OnBnClickedButtonProviderInfoNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ProviderInfo provider;
	SetProviderInfoToCtrl(provider);
}


void CDlgCustomManage::OnCustomdrawListProvider(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//*pResult = 0;

	LPNMLVCUSTOMDRAW pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	int ret = -1;
	if (m_p_cls_provider_list != NULL)
	{
		ret = m_p_cls_provider_list->GetProviderInfoIndexInList(pLVCD->nmcd.dwItemSpec);
	}

	if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		//*pResult = CDRF_DODEFAULT;
	}
	else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		//idx
		CString str_provider_index;
		GetDlgItem(IDC_EDIT_PROVIDER_INDEX)->GetWindowText(str_provider_index);
		int i_provider_index = atoi(str_provider_index);

		if (m_p_cls_provider_list != NULL)
		{
			if (i_provider_index == ret)
			{
				pLVCD->clrText = RGB(255, 255, 255); // 글자색 지정  
				pLVCD->clrTextBk = RGB(102, 193, 193); // 배경색 지정  
			}
		}
		*pResult = CDRF_DODEFAULT;
	}
}


void CDlgCustomManage::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_search;
	GetDlgItem(IDC_EDIT_PROVIDER_SEARCH)->GetWindowText(str_search);

	if (m_p_cls_provider_list != NULL)
	{
		m_p_cls_provider_list->Search(std::string(str_search));
	}
}


void CDlgCustomManage::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (this->IsWindowVisible())
	{
		if (m_p_cls_provider_list != NULL)
		{
			CString str_search;
			GetDlgItem(IDC_EDIT_PROVIDER_SEARCH)->GetWindowText(str_search);
			std::string str_search_ = str_search;

			if (!str_search_.empty())
			{
				m_p_cls_provider_list->Search(std::string(str_search));
			}
			else
			{
				m_p_cls_provider_list->Search("*");
			}
		}
	}
}


void CDlgCustomManage::OnBnClickedButtonProviderDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Show the message box with a question mark icon
	const int result = MessageBox("삭제 된 데이타는 복구되지 않습니다.\n정말로 삭제하시겠습니까?", "삭제확인", MB_YESNO | MB_ICONQUESTION);

	switch (result)
	{
	case IDYES:
		{
			if (m_p_cls_provider_list != NULL)
			{
				m_p_cls_provider_list->DelCheckedItem();
			}
		}
		break;
	case IDNO:
		break;
	}
}
