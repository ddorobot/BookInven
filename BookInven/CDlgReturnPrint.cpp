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
}


BEGIN_MESSAGE_MAP(CDlgReturnPrint, CDialogEx)
END_MESSAGE_MAP()


// CDlgReturnPrint 메시지 처리기
