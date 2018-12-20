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
{

}

CDlgSaleManage::~CDlgSaleManage()
{
	if (m_p_list_sale_history != NULL)
	{
		delete m_p_list_sale_history;
		m_p_list_sale_history = NULL;
	}
}

void CDlgSaleManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SALE_HISTORY, m_list_sale_history);
}


BEGIN_MESSAGE_MAP(CDlgSaleManage, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


// CDlgSaleManage 메시지 처리기


BOOL CDlgSaleManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_p_list_sale_history = new CBookSaleList(&m_list_sale_history);

	m_p_list_sale_history->UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgSaleManage::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (this->IsWindowVisible())
	{
		if (m_p_list_sale_history)
		{
			m_p_list_sale_history->UpdateList();
		}
	}
}
