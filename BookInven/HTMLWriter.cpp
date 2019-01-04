#include "HTMLWriter.h"
#include <comdef.h>

CHTMLWriter::CHTMLWriter( IUnknown * pUnk )
{
	m_bReleaseIWebBrowserPtr = true;
	m_pUnk = pUnk;
	m_pDoc = NULL;
	if (m_pUnk)
	{
		if (FAILED( m_pUnk->QueryInterface( IID_IWebBrowser2, (void **) &m_pWB )))
			m_pWB = NULL;
	}
	else
		m_pWB = NULL;
}

CHTMLWriter::CHTMLWriter( IWebBrowser2 * pWB )
{
	m_bReleaseIWebBrowserPtr = false;
	m_pUnk = NULL;
	m_pDoc = NULL;
	m_pWB = pWB;
}

CHTMLWriter::~CHTMLWriter( void )
{
	if (m_pDoc)
		m_pDoc->Release();
	if (m_bReleaseIWebBrowserPtr && m_pWB)
		m_pWB->Release();
}

bool CHTMLWriter::Write( LPCTSTR pszHTMLContent )
{
	if (!pszHTMLContent)
		return false;
	if (!GetDocumentPtr())
		return false;

	IStream * pStream = NULL;
	IPersistStreamInit * pPSI = NULL;
	HGLOBAL hHTMLContent;
	HRESULT hr;
	bool bResult = false;

	// allocate global memory to copy the HTML content to
	hHTMLContent = ::GlobalAlloc( GPTR, ( ::_tcslen( pszHTMLContent ) + 1 ) * sizeof(TCHAR) );
	if (!hHTMLContent)
		return false;

	::_tcscpy( (TCHAR *) hHTMLContent, pszHTMLContent );

	// create a stream object based on the HTML content
	hr = ::CreateStreamOnHGlobal( hHTMLContent, TRUE, &pStream );
	if (SUCCEEDED(hr))
	{
		// request the IPersistStreamInit interface
		hr = m_pDoc->QueryInterface( IID_IPersistStreamInit, (void **) &pPSI );

		if (SUCCEEDED(hr))
		{
			// initialize the persist stream object
			hr = pPSI->InitNew();

			if (SUCCEEDED(hr))
			{
				// load the data into it
				hr = pPSI->Load( pStream );

				if (SUCCEEDED(hr))
					bResult = true;
			}

			pPSI->Release();
		}

		// implicitly calls ::GlobalFree to free the global memory
		pStream->Release();
	}

	return bResult;
}

bool CHTMLWriter::GetDocumentPtr( void )
{
	if (!m_pUnk && !m_pWB)
		return false;
	if (m_pDoc)
	{
		m_pDoc->Release();
		m_pDoc = NULL;
	}

	IDispatch * pDisp = NULL;
	HRESULT hr;

	// get the document's IDispatch*
	hr = m_pWB->get_Document( &pDisp );
	if (SUCCEEDED(hr))
	{
		m_pDoc = pDisp;
		return true;
	}
	else
		return false;
}

bool CHTMLWriter::Add( LPCTSTR pszHTMLContent )
{
	if (!pszHTMLContent)
		return false;
	if (!GetDocumentPtr())
		return false;

	IHTMLDocument2 * pHTMLDoc = NULL;
	IHTMLElement * pElem = NULL;
	HRESULT hr;
	bool bResult = false;

	// get an interface to the document object
	hr = m_pDoc->QueryInterface( IID_IHTMLDocument2, (void **) &pHTMLDoc );

	if (SUCCEEDED(hr))
	{
		// get the body element of the document
		hr = pHTMLDoc->get_body( &pElem );

		if (SUCCEEDED(hr))
		{
			// retrieve all the HTML content of the body object
			BSTR bstr;
			hr = pElem->get_innerHTML( &bstr );

			if (SUCCEEDED(hr))
			{
				// append the desired content to the HTML content of the document
				_bstr_t bstrContent( bstr );
				bstrContent += pszHTMLContent;

				// set the new HTML content of the document
				hr = pElem->put_innerHTML( bstrContent );

				if (SUCCEEDED(hr))
					bResult = true;

				::SysFreeString( bstr );
			}

			pElem->Release();
		}

		pHTMLDoc->Release();
	}

	return bResult;
}