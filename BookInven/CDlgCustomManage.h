#pragma once

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "CProviderInfoList.h"
#include "CDataBaseProvider.h"

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
public:
	virtual BOOL OnInitDialog();

	//Thread
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunction();

	//Thread
	bool m_run_thread_ui;
	boost::thread m_thread_ui;
	void ThreadFunctionUI();

	ProviderInfo GetProviderInfoFromCtrl(void);
	void SetProviderInfoToCtrl(const ProviderInfo provider);

private:
	CProviderInfoList* m_p_cls_provider_list;
public:
	CListCtrl m_list_provider;
	CComboBox m_combo_provide_type;
	CComboBox m_combo_receipt;
	afx_msg void OnBnClickedButtonProviderInfoUpdae();
	afx_msg void OnDblclkListProvider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonProviderInfoNew();
	afx_msg void OnCustomdrawListProvider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedButtonProviderDel();
};
