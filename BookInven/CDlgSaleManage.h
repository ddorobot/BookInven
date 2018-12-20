#pragma once

#include "CBookSaleList.h"


// CDlgSaleManage 대화 상자

class CDlgSaleManage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSaleManage)

public:
	CDlgSaleManage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgSaleManage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SALE_MANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_sale_history;
	virtual BOOL OnInitDialog();

	CBookSaleList* m_p_list_sale_history;
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};
