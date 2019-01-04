#pragma once

#include "CWebBrowser2.h"

// CDlgReturnPrint 대화 상자

class CDlgReturnPrint : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReturnPrint)

public:
	CDlgReturnPrint(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgReturnPrint();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RETURN_PRINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CWebBrowser2 m_web;
};
