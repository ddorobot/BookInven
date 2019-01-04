// CDlgReturnPrint.cpp: 구현 파일
//

#include "stdafx.h"
#include "BookInven.h"
#include "CDlgReturnPrint.h"
#include "afxdialogex.h"


// CDlgReturnPrint 대화 상자

IMPLEMENT_DYNAMIC(CDlgReturnPrint, CDialogEx)

CDlgReturnPrint::CDlgReturnPrint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RETURN_PRINT, pParent)
{

}

CDlgReturnPrint::~CDlgReturnPrint()
{
}

void CDlgReturnPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EXPLORER_WEB, DISPID(), m_web);
	DDX_Control(pDX, IDC_EXPLORER_WEB, m_web);
}


BEGIN_MESSAGE_MAP(CDlgReturnPrint, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgReturnPrint::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgReturnPrint 메시지 처리기


BOOL CDlgReturnPrint::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//m_web.Navigate("www.microsoft.com", NULL, NULL, NULL, NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgReturnPrint::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_web.Navigate(_T("about:blank"), NULL, NULL, NULL, NULL);

	CHTMLWriter htmlWriter(m_web.GetControlUnknown());

	htmlWriter.Write(_T("<html><head><title>My page</title></head>\n")
		_T("<body><p><font face=verdana size=2>This page is written dynamically to the\n")
		_T("WebBrowser control using the CHTMLWriter class.")
		_T("<br><br><a href=\"mailto:ehsan@beginthread.com\">Email me</a></font></p></body></html>"));

	///////////
#if 0
	std::string html;
	std::wstring strUni;
	std::string strUTF8;

	html = "<html><body><h1>My Header</h1><p>Some text below the header</p></body></html>";

	//Text
	strUni = CA2W(html.c_str());
	strUTF8 = CW2A(strUni.c_str(), CP_UTF8);

	IDispatch* pHtmlDoc = m_web.get_Document();
	if (!pHtmlDoc)
	{
		printf("%s : !pHtmlDoc\n", __func__);
		return ;
	}
	CComPtr<IHTMLDocument2> doc2;
	doc2.Attach((IHTMLDocument2*)pHtmlDoc);
	if (!doc2)
	{
		printf("%s : !doc2\n", __func__);
		return ;
	}
	// Creates a new one-dimensional array
	SAFEARRAY* psaStrings = SafeArrayCreateVector(VT_VARIANT, 0, 1);
	if (!psaStrings)
	{
		printf("%s : !psaStrings\n", __func__);
		return ;
	}
	BSTR bstr = SysAllocString(strUni.c_str());
	if (bstr)
	{
		VARIANT* param;
		HRESULT hr = SafeArrayAccessData(psaStrings, (LPVOID*)&param);
		if (SUCCEEDED(hr))
		{
			param->vt = VT_BSTR;
			param->bstrVal = bstr;
			hr = SafeArrayUnaccessData(psaStrings);
			if (SUCCEEDED(hr))
			{
				doc2->write(psaStrings);
				doc2->close();
			}
		}
	}
	// SafeArrayDestroy calls SysFreeString for each BSTR!
	if (psaStrings)
		SafeArrayDestroy(psaStrings);
	///////////

#endif
}
