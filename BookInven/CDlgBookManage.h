#pragma once


// CDlgBookManage 대화 상자

class CDlgBookManage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBookManage)

public:
	CDlgBookManage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgBookManage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOOK_MANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
