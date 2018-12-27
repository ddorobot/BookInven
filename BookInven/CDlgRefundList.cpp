// CDlgRefundList.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgRefundList.h"
#include "afxdialogex.h"


// CDlgRefundList 대화 상자

IMPLEMENT_DYNAMIC(CDlgRefundList, CDialogEx)

CDlgRefundList::CDlgRefundList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REFUND, pParent)
	, m_p_list_sale_history_detail(NULL)
{
	//Detail list
	//m_p_list_sale_history_detail = new CBookSaleDetailList(&m_list_able_refund);
}

CDlgRefundList::~CDlgRefundList()
{
	if (m_p_list_sale_history_detail != NULL)
	{
		delete m_p_list_sale_history_detail;
		m_p_list_sale_history_detail = NULL;
	}
}

void CDlgRefundList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REFUND, m_list_able_refund);
}


BEGIN_MESSAGE_MAP(CDlgRefundList, CDialogEx)
END_MESSAGE_MAP()


// CDlgRefundList 메시지 처리기


BOOL CDlgRefundList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (m_p_list_sale_history_detail == NULL)
	{
		m_p_list_sale_history_detail = new CBookSaleDetailList(&m_list_able_refund, true, true);
	}

	m_p_list_sale_history_detail->UpdateList(m_str_sale_code);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgRefundList::SetSaleCode(const std::string str_sale_code)
{
	m_str_sale_code = str_sale_code;
}

std::string CDlgRefundList::GetSaleCode(void)
{
	return m_str_sale_code;
}

int CDlgRefundList::RunCheckedRefund(void)
{
	int ret = 0;

	if (m_p_list_sale_history_detail != NULL)
	{
		ret = m_p_list_sale_history_detail->CheckedRefund();
	}

	return ret;
}