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
	, m_p_htmlwriter(NULL)
{

}

CDlgReturnPrint::~CDlgReturnPrint()
{
	if (m_p_htmlwriter != NULL)
	{
		delete m_p_htmlwriter;
		m_p_htmlwriter = NULL;
	}
}

void CDlgReturnPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EXPLORER_WEB, DISPID(), m_web);
	DDX_Control(pDX, IDC_EXPLORER_WEB, m_web);
}


BEGIN_MESSAGE_MAP(CDlgReturnPrint, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON1, &CDlgReturnPrint::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgReturnPrint::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgReturnPrint::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgReturnPrint 메시지 처리기


BOOL CDlgReturnPrint::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//m_web.Navigate("www.microsoft.com", NULL, NULL, NULL, NULL);
	m_web.Navigate(_T("about:blank"), NULL, NULL, NULL, NULL);

	if (m_p_htmlwriter == NULL)
	{
		m_p_htmlwriter = new CHTMLWriter(m_web.GetControlUnknown());
	}

	std::string html;
	html = "<style type=\"text/css\">" ;
	html += "table {border-collapse: collapse;} ";
	html += "th, td {border: 1px solid black; text-align: center;vertical-align: middle;padding: 3px 3px 3px 3px;} ";
	html += "th {background-color:rgb(200,200,200);} ";
	html += ".info {margin-top:30px;font-size:20px;} ";
	html += "</style>" ;
	html += "<body style=\"font-family:'Nanum Gothic', sans-serif;font-size:12px;\">"; 
	html += "<center><div style=\"font-size:20px;font-weight: bold;\">반품서</div></center>";
	html += "<div>업체명 : 북센</div>";
	html += "<div>날짜 : 2019년 1월 4일</div>";
	html += "<div>반품코드 : 20190104195320_RETVfxD</div>";
	html += "<div style=\"margin-top:10px;\">";
	html += "<table style='width:100%;border: 1px solid black;font-size:12px;padding:0px;'>" ;
	html += "  <tr>";
	html += "	<th width=40>번호</th>";
	html += "	<th width=100>입고일</th>";
	html += "	<th width=100>코드</th> ";
	html += "	<th>이름</th>";
	html += "	<th>저자</th>";
	html += "	<th width=100>공급가</th>";
	html += "  </tr>"; 
	html += "  <tr>";
	html += "	<td>1</td>";
	html += "	<td>2018-01-01</td>";
	html += "	<td>9788959895526</td> ";
	html += "	<td>책방 모도 화이팅</td>";
	html += "	<td>박주홍</td>";
	html += "	<td>14000</td>";
	html += "  </tr>";
	html += "  <tr>";
	html += "	<td>2</td>";
	html += "	<td>2018-01-01</td>";
	html += "	<td>9788959895526</td> ";
	html += "	<td>책방 모도 화이팅2</td>";
	html += "	<td>박주홍천재</td>";
	html += "	<td>10000</td>";
	html += "  </tr>";
	/*
	html += "  <tr>";
	html += "	<td>Jill</td>";
	html += "	<td>Smith</td> ";
	html += "	<td>50</td>";
	html += "  </tr>";
	html += "  <tr>";
	html += "	<td>Eve</td>";
	html += "	<td>Jackson</td> ";
	html += "	<td>94</td>";
	html += "  </tr>";
	*/
	html += "</table>";
	html += "</div>";
	html += "<div class='info'><center>책방 모도</center></div>";
	html += "</body>";

	m_p_htmlwriter->Write(html.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgReturnPrint::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CDialogEx::OnOK();
}


void CDlgReturnPrint::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_web.ExecWB(OLECMDID_PRINTPREVIEW, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

void CDlgReturnPrint::SetPrintData(std::vector<BookReturnData> vec_data)
{
	m_vec_data = vec_data;
}