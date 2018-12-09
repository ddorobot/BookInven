#pragma once

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "opencv2/opencv.hpp"
#include "use_opencv_lib.h"


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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	//Comport Thread
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunction();
};
