// CDlgBookManage.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgBookManage.h"
#include "afxdialogex.h"


// CDlgBookManage 대화 상자

IMPLEMENT_DYNAMIC(CDlgBookManage, CDialogEx)

CDlgBookManage::CDlgBookManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK_MANAGE, pParent)
{

}

CDlgBookManage::~CDlgBookManage()
{
}

void CDlgBookManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBookManage, CDialogEx)
END_MESSAGE_MAP()


// CDlgBookManage 메시지 처리기
