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
{

}

CDlgCustomManage::~CDlgCustomManage()
{
}

void CDlgCustomManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCustomManage, CDialogEx)
END_MESSAGE_MAP()


// CDlgCustomManage 메시지 처리기
