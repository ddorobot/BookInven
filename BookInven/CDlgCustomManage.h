#pragma once


// CDlgCustomManage 대화 상자

class CDlgCustomManage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCustomManage)

public:
	CDlgCustomManage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgCustomManage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUSTOM_MANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
