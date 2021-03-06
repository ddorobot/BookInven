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
	ON_BN_CLICKED(IDOK, &CDlgRefundList::OnBnClickedOk)
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

void CDlgRefundList::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	const int result = MessageBox("선택 상품을 환불 하시겠습니까?", "환불확인", MB_YESNO | MB_ICONQUESTION);

	switch (result)
	{
	case IDYES:
	{
		//환불 실행
		if (RunCheckedRefund())
		{
			//올바로 환불 됨
			const int result = MessageBox("선택 상품을 환불처리 하였습니다.", "환불확인", MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			const int result = MessageBox("일부 환불처리 되었습니다.", "환불확인", MB_OK | MB_ICONQUESTION);
		}
	}
	break;
	case IDNO:
		const int result = MessageBox("환불처리 취소 되었습니다.", "환불취소", MB_OK | MB_ICONHAND);
		break;
	}

	CDialogEx::OnOK();
}
