
// BookInvenDlg.h: 헤더 파일
//

#pragma once

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "GetBookInfo.h"
#include "CImageLoadUrl.h"

#include "opencv2/opencv.hpp"
#include "use_opencv_lib.h"


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
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	GetBookInfo m_cls_get_book_info;
};
