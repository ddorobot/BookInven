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
		}
	};
}


void CDlgCustomManage::OnBnClickedButtonProviderInfoUpdae()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//데이타 수집
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

	ProviderInfo provider;
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
	}
}

