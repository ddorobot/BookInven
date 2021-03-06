
// BookInvenDlg.h: 헤더 파일
//

#pragma once

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "opencv2/opencv.hpp"
#include "use_opencv_lib.h"

#include "CTabCtrlEx.h"

#include "CDlgBookSale.h"
#include "CDlgBookIn.h"
#include "CDlgBookManage.h"
#include "CDlgSaleManage.h"
#include "CDlgCustomManage.h"
#include "CDlgStoreInfo.h"
#include "CDlgBookReturn.h"

#include "boost/thread.hpp"
#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "opencv2/opencv.hpp"
#include "use_opencv_lib.h"

#include "CDrawToHDC.h"

#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "harfbuzz.lib")

// CBookInvenDlg 대화 상자
class CBookInvenDlg : public CDialogEx
{
// 생성입니다.
public:
	CBookInvenDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOKINVEN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CTabCtrlEx m_tab_menu;

	//Tab Dialog
	CDlgBookSale m_dlg_book_sale;
	CDlgBookIn m_dlg_book_in;
	CDlgBookManage m_dlg_book_manage;
	CDlgSaleManage m_dlg_sale_manage;
	CDlgBookReturn m_dlg_book_return;
	CDlgCustomManage m_dlg_custom_manage;
	CDlgStoreInfo m_dlg_store_info;

	CWnd* m_p_tab_dlg_window;
	afx_msg void OnSelchangeTabMenu(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//Thread
	bool m_run_thread;
	boost::thread m_thread;
	void ThreadFunction();

	void DrawAuthorInfo(cv::Mat image);
};
