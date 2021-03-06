#pragma once

#include "CBookSaleList.h"
#include "CBookSaleDetailList.h"
#include "CMyTime.h"

#include "CDlgRefundList.h"
#include "CDrawToHDC.h"

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
	CBookSaleDetailList* m_p_list_sale_history_detail;
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	BOOL m_radio_search_option;
	CDateTimeCtrl m_dtctrl_start;
	CDateTimeCtrl m_dtctrl_end;
	afx_msg void OnBnClickedButtonSaleHistorySearch();
	CListCtrl m_list_sale_history_detail;
	afx_msg void OnClickListSaleHistory(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSelectRefund();
	afx_msg void OnClickListSaleHistoryDetail(NMHDR *pNMHDR, LRESULT *pResult);

	void SaleDetailListInfoUpdate(void);
	afx_msg void OnCustomdrawListSaleHistory(NMHDR *pNMHDR, LRESULT *pResult);

	//Thread
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunction();
};
