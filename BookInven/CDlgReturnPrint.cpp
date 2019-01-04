// CDlgReturnPrint.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgReturnPrint.h"
#include "afxdialogex.h"


// CDlgReturnPrint 대화 상자

IMPLEMENT_DYNAMIC(CDlgReturnPrint, CDialogEx)

CDlgReturnPrint::CDlgReturnPrint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RETURN_PRINT, pParent)
{

}

CDlgReturnPrint::~CDlgReturnPrint()
{
}

void CDlgReturnPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EXPLORER_WEB, DISPID(), m_web);
	DDX_Control(pDX, IDC_EXPLORER_WEB, m_web);
}


BEGIN_MESSAGE_MAP(CDlgReturnPrint, CDialogEx)
END_MESSAGE_MAP()


// CDlgReturnPrint 메시지 처리기


BOOL CDlgReturnPrint::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_web.Navigate("www.microsoft.com", NULL, NULL, NULL, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
