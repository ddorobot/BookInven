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
	, m_str_memo(_T(""))
	, m_str_static(_T(""))
{

}

CDlgMemo::~CDlgMemo()
{
}

void CDlgMemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MEMO, m_ctrl_edit_memo);
	DDX_Control(pDX, IDC_STATIC_MEMO_TEXT, m_ctrl_static_memo);
	DDX_Text(pDX, IDC_EDIT_MEMO, m_str_memo);
	DDX_Text(pDX, IDC_STATIC_MEMO_TEXT, m_str_static);
}


BEGIN_MESSAGE_MAP(CDlgMemo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgMemo::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgMemo 메시지 처리기


void CDlgMemo::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CDialogEx::OnOK();
}


BOOL CDlgMemo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
