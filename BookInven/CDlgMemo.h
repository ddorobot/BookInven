#pragma once


// CDlgMemo 대화 상자

class CDlgMemo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMemo)

public:
	CDlgMemo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgMemo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GET_MEMO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrl_edit_memo;
	CStatic m_ctrl_static_memo;
	CString m_str_memo;
	CString m_str_static;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
