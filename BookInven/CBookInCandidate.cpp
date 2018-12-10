#include "CBookInCandidate.h"

CBookInCandidate::CBookInCandidate(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// 리스트 스타일 설정
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// 타이틀 삽입
	m_p_list_ctrl->InsertColumn(0, _T("선택"), LVCFMT_CENTER, 35, -1);
	m_p_list_ctrl->InsertColumn(1, _T("CODE"), LVCFMT_CENTER, 110, -1);
	m_p_list_ctrl->InsertColumn(2, _T("이름"), LVCFMT_CENTER, 200, -1);
	m_p_list_ctrl->InsertColumn(3, _T("저자"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(4, _T("출판사"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(5, _T("가격"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(6, _T("수량"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(7, _T("공급사"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(8, _T("공급률"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(9, _T("공급가"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(10, _T("할인가"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(11, _T("판매가"), LVCFMT_CENTER, 70, -1);
}


CBookInCandidate::~CBookInCandidate()
{
}

void CBookInCandidate::SetListCtrl(CListCtrl* p_list_ctrl)
{
	mutex_list_ctrl.lock();
	m_p_list_ctrl = p_list_ctrl;
	mutex_list_ctrl.unlock();
}