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

	m_combo_receipt.AddString("NO");
	m_combo_receipt.AddString("YES");
	m_combo_receipt.SetCurSel(0);

	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CDlgCustomManage::ThreadFunction, this));

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
