#pragma once

#include "CMyBooksList.h"
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
};
