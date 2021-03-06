#pragma once

#include "GetBookInfo.h"
#include "CImageLoadUrl.h"

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "opencv2/opencv.hpp"
#include "use_opencv_lib.h"

#include "CLoadBitmap.h"

#include "CDrawToHDC.h"

#include "CBookInCandidate.h"
#include "CBookInList.h"

#include "CDataBaseProvider.h"
 
#define SPECIAL_INDEX_PROVIDER_NAME	8
#define SPECIAL_INDEX_PROVIDER_TYPE	9

// CDlgBookIn 대화 상자

class CDlgBookIn : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBookIn)

public:
	CDlgBookIn(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgBookIn();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOOK_IN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	//Thread
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunction();

	GetBookInfo m_cls_get_book_info;

	void UpdateBookInfoOnTextbox(const std::string isbn);
	void UpdateBookInfoOnTextbox(const BookInfo info);

	cv::Mat GetImageBookCover(void);
	void SetImageBookCover(cv::Mat image);
private:
	boost::mutex mutex_image_book_cover;
	cv::Mat m_mat_image_book_cover;
	cv::Mat m_mat_image_base_book_cover;

	BookInfo m_cur_book_info;

	int m_candidate_iItem;
	int m_candidate_iSubitem;
public:
	//afx_msg void OnBnClickedButtonBookTitleImageChange();
	afx_msg void OnBnClickedButtonAddCandidateBookin();
	CListCtrl m_list_candidate;
	afx_msg void OnBnClickedButtonBookIsbnSearch();

	CBookInCandidate* m_p_cls_bookin_candidate;
	CBookInList* m_p_cls_bookin_list;

	afx_msg void OnDblclkListBookinCandidate(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_combo_change_cel;
	afx_msg void OnKillfocusComboCel();
	afx_msg void OnSelchangeComboCel();
	afx_msg void OnBnClickedButtonAddBookin();
	afx_msg void OnBnClickedButtonDelCandidateList();
	CListCtrl m_list_in;
	afx_msg void OnBnClickedButtonAddBookinCancel();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	int m_radio_value_search;
	afx_msg void OnBnClickedButtonBooinHistorySearch();
	CDateTimeCtrl m_dtctrl_start;
	CDateTimeCtrl m_dtctrl_end;
	CComboBox m_combo_in_type;
	afx_msg void OnKillfocusDatetimepickerProvideDate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDatetimechangeDatetimepickerProvideDate(NMHDR *pNMHDR, LRESULT *pResult);
	CDateTimeCtrl m_date_provide;
};
