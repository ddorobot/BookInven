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
{

}

CDlgRefundList::~CDlgRefundList()
{
}

void CDlgRefundList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRefundList, CDialogEx)
END_MESSAGE_MAP()


// CDlgRefundList 메시지 처리기
