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


BOOL CDlgBookManage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CDlgBookManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//Thread 
	m_run_thread = true;
	//cread thread
	m_thread = boost::thread(boost::bind(&CDlgBookManage::ThreadFunction, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgBookManage::ThreadFunction(void)
{
	while (m_run_thread)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(10));

		if (this->IsWindowVisible())
		{
			//printf("Book Manage\n");
		}
	};
}