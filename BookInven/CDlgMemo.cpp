// CDlgMemo.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgMemo.h"
#include "afxdialogex.h"


// CDlgMemo 대화 상자

IMPLEMENT_DYNAMIC(CDlgMemo, CDialogEx)

CDlgMemo::CDlgMemo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GET_MEMO, pParent)
{

}

CDlgMemo::~CDlgMemo()
{
}

void CDlgMemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMemo, CDialogEx)
END_MESSAGE_MAP()


// CDlgMemo 메시지 처리기
