// CDlgBookReturn.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgBookReturn.h"
#include "afxdialogex.h"


// CDlgBookReturn 대화 상자

IMPLEMENT_DYNAMIC(CDlgBookReturn, CDialogEx)

CDlgBookReturn::CDlgBookReturn(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK_RETURN, pParent)
{

}

CDlgBookReturn::~CDlgBookReturn()
{
}

void CDlgBookReturn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBookReturn, CDialogEx)
END_MESSAGE_MAP()


// CDlgBookReturn 메시지 처리기
