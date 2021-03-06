#pragma once

#include <string>

#include "GetBookInfo.h"
#include "CGetGoodsCount.h"
#include "CReturn.h"
#include "CDataBaseProvider.h"
#include "CDlgReturnPrint.h"
#include "BookReturnData.h"

// CDlgBookReturn 대화 상자

class CDlgBookReturn : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBookReturn)

public:
	CDlgBookReturn(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgBookReturn();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOOK_RETURN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void UpdateTreeData(void);
	CTreeCtrl m_tree_return;
	afx_msg void OnBnClickedButtonGoodsSearch();

	GetBookInfo m_cls_get_book_info;
	void UpdateBookInfoOnTextbox(const std::string isbn);
	void UpdateBookInfoOnTextbox(const BookInfo info);
	afx_msg void OnBnClickedButtonReturnAdd();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnClickTreeReturn(NMHDR *pNMHDR, LRESULT *pResult);
	void CheckSiblings(BOOL bCheck, HTREEITEM hItem);
	BOOL AllCheckSiblings(HTREEITEM hItem);
	afx_msg void OnBnClickedButtonReturnDelList();

	std::vector<BookReturnData> m_vec_return_data;
	afx_msg void OnBnClickedButtonReturnDelAllList();
	afx_msg void OnBnClickedButtonDoReturn();
};
