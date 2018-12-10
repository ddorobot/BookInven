#include "CBookInCandidate.h"

CBookInCandidate::CBookInCandidate(CListCtrl* p_list_ctrl) :
	m_p_list_ctrl(NULL)
{
	SetListCtrl(p_list_ctrl);

	//m_list_candidate
	//Initialize list
	m_p_list_ctrl->DeleteAllItems();
	// ����Ʈ ��Ÿ�� ����
	m_p_list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// Ÿ��Ʋ ����
	m_p_list_ctrl->InsertColumn(0, _T("����"), LVCFMT_CENTER, 35, -1);
	m_p_list_ctrl->InsertColumn(1, _T("CODE"), LVCFMT_CENTER, 110, -1);
	m_p_list_ctrl->InsertColumn(2, _T("�̸�"), LVCFMT_CENTER, 200, -1);
	m_p_list_ctrl->InsertColumn(3, _T("����"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(4, _T("���ǻ�"), LVCFMT_CENTER, 100, -1);
	m_p_list_ctrl->InsertColumn(5, _T("����"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(6, _T("����"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(7, _T("���޻�"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(8, _T("���޷�"), LVCFMT_CENTER, 50, -1);
	m_p_list_ctrl->InsertColumn(9, _T("���ް�"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(10, _T("���ΰ�"), LVCFMT_CENTER, 70, -1);
	m_p_list_ctrl->InsertColumn(11, _T("�ǸŰ�"), LVCFMT_CENTER, 70, -1);
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