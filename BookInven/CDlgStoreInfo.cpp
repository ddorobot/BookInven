// CDlgStoreInfo.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgStoreInfo.h"
#include "afxdialogex.h"


// CDlgStoreInfo 대화 상자

IMPLEMENT_DYNAMIC(CDlgStoreInfo, CDialogEx)

CDlgStoreInfo::CDlgStoreInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STORE_INFO, pParent)
{

}

CDlgStoreInfo::~CDlgStoreInfo()
{
}

void CDlgStoreInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStoreInfo, CDialogEx)
END_MESSAGE_MAP()


// CDlgStoreInfo 메시지 처리기
