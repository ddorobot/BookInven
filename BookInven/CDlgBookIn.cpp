// CDlgBookIn.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgBookIn.h"
#include "afxdialogex.h"


// CDlgBookIn 대화 상자

IMPLEMENT_DYNAMIC(CDlgBookIn, CDialogEx)

CDlgBookIn::CDlgBookIn(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IN, pParent)
{

}

CDlgBookIn::~CDlgBookIn()
{
}

void CDlgBookIn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBookIn, CDialogEx)
END_MESSAGE_MAP()


// CDlgBookIn 메시지 처리기
