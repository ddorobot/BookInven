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
{

}

CDlgSaleManage::~CDlgSaleManage()
{
}

void CDlgSaleManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSaleManage, CDialogEx)
END_MESSAGE_MAP()


// CDlgSaleManage 메시지 처리기
