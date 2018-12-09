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

	void UpdateBookInfoOnTextbox(const BookInfo info);

	cv::Mat GetImageBookCover(void);
	void SetImageBookCover(cv::Mat image);
private:
	boost::mutex mutex_image_book_cover;
	cv::Mat m_mat_image_book_cover;
	cv::Mat m_mat_image_base_book_cover;
};
