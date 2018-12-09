// CDlgBookSale.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgBookSale.h"
#include "afxdialogex.h"


// CDlgBookSale 대화 상자

IMPLEMENT_DYNAMIC(CDlgBookSale, CDialogEx)

CDlgBookSale::CDlgBookSale(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK_SALE, pParent)
{

}

CDlgBookSale::~CDlgBookSale()
{
}

void CDlgBookSale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBookSale, CDialogEx)
END_MESSAGE_MAP()


// CDlgBookSale 메시지 처리기
