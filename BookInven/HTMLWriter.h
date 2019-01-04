#pragma once

#include <iostream>
#include <windows.h>
#include <tchar.h>

#include <mshtml.h>
#include <Exdisp.h>

class CHTMLWriter
{
protected:
	IUnknown * m_pUnk;
	IWebBrowser2 * m_pWB;
	IDispatch * m_pDoc;
	bool m_bReleaseIWebBrowserPtr;

public:
	CHTMLWriter( IUnknown * pUnk );
	CHTMLWriter( IWebBrowser2 * pWB );
	~CHTMLWriter( void );
	bool Write( LPCTSTR pszHTMLContent );
	bool Add( LPCTSTR pszHTMLContent );

private:
	CHTMLWriter( void ) {};
	bool GetDocumentPtr( void );
};