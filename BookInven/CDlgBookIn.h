#pragma once


// CDlgBookIn 대화 상자

class CDlgBookIn : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBookIn)

public:
	CDlgBookIn(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgBookIn();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
