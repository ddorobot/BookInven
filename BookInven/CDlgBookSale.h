#pragma once


// CDlgBookSale 대화 상자

class CDlgBookSale : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBookSale)

public:
	CDlgBookSale(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgBookSale();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOOK_SALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
