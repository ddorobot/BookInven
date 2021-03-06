#pragma once

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "CMyBooksList.h"
#include "CDrawToHDC.h"
#include "CLoadBitmap.h"
#include "BookInfo.h"
#include "CDataBaseImageSave.h"

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
public:

	CMyBooksList *m_p_cls_books_list;
	CListCtrl m_list_mybooks;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);

	//Thread
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunction();

	void SetBookInfoToCtrl(const BookInfo bookinfo);
	BookInfo GetBookInfoFromCtrl(void);

private:
	boost::mutex mutex_image_book_cover;
	cv::Mat m_mat_image_book_cover;
	cv::Mat m_mat_image_base_book_cover;

public:
	afx_msg void OnDblclkListBooks(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonProviderInfoNew();
	afx_msg void OnCustomdrawListBooks(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonChangeBookCover();
	afx_msg void OnBnClickedButtonBookinfoInfoUpdae();
};
