#pragma once

#include <afxcmn.h>

#include <string>
#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "CDrawToHDC.h"
#include "CLoadBitmap.h"
#include "GetBookInfo.h"
#include "CGetGoodsCount.h"

#include "CSaleBooksList.h"
#include "CDataBaseBookInfo.h"
#include "CCart.h"
#include "CDlgMemo.h"
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
public:
	virtual BOOL OnInitDialog();

	//Thread
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunction();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonSaleAdd();

	GetBookInfo m_cls_get_book_info;
	void UpdateBookInfoOnTextbox(const std::string isbn);
	void UpdateBookInfoOnTextbox(const BookInfo info);

	CSaleBooksList *m_p_cls_sale_list;
	CListCtrl m_list_sale;
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedButtonGoodsSearch();

	void DrawTotalPrice(cv::Mat image, int count, int price);
	void DrawList(cv::Mat image, cv::Rect rect, std::vector<SaleBooksInfo> vec_list_info);
	afx_msg void OnBnClickedButtonPayCancel();
	afx_msg void OnBnClickedButtonPayCancelAll();
	afx_msg void OnBnClickedButtonPayCountPlus();
	afx_msg void OnBnClickedButtonPayCountMinus();
	afx_msg void OnBnClickedButtonPayCash();
	afx_msg void OnBnClickedButtonPayCard();
	afx_msg void OnBnClickedButtonEstimate();
};
