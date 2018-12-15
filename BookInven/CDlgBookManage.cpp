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
	, m_p_cls_books_list(NULL)
{

}

CDlgBookManage::~CDlgBookManage()
{
	if (m_p_cls_books_list != NULL)
	{
		delete m_p_cls_books_list;
		m_p_cls_books_list = NULL;
	}
}

void CDlgBookManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOKS, m_list_mybooks);
}


BEGIN_MESSAGE_MAP(CDlgBookManage, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


// CDlgBookManage 메시지 처리기


BOOL CDlgBookManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_p_cls_books_list = new CMyBooksList(&m_list_mybooks);

	m_p_cls_books_list->UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDlgBookManage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgBookManage::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (this->IsWindowVisible())
	{
		if (m_p_cls_books_list)
		{
			m_p_cls_books_list->UpdateList();
		}
	}
}
