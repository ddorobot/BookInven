#pragma once

#include "CBookSaleDetailList.h"

// CDlgRefundList 대화 상자

class CDlgRefundList : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRefundList)

public:
	CDlgRefundList(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgRefundList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REFUND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_able_refund;

	CBookSaleDetailList* m_p_list_sale_history_detail;
	virtual BOOL OnInitDialog();

	void SetSaleCode(const std::string str_sale_code);
	std::string GetSaleCode(void);

	int RunCheckedRefund(void);
private:
	std::string m_str_sale_code;
public:
	afx_msg void OnBnClickedOk();
};
