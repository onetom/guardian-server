// MyTabCtl.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoInc.h"
#include "SystemInfo.h"
#include "CPUInfoDlg.h"
#include "MemoryDlg.h"
#include "MonitoringDlg.h"
#include "SPDDlg.h"
#include "DisplayDlg.h"
#include "MyTabCtl.h"


// CMyTabCtl

IMPLEMENT_DYNAMIC(CMyTabCtl, CTabCtrl)

CMyTabCtl::CMyTabCtl()
{
	m_PropertyPage[0] = new CCPUInfoDlg();
	m_PropertyPage[1] = new CMemoryDlg();
	m_PropertyPage[2] = new CMonitoringDlg();
	m_PropertyPage[3] = new CSPDDlg();	
	m_PropertyPage[4] = new CDisplayDlg();

	m_iNbPages = 5;
	m_iCurrentPage = 0;
}

CMyTabCtl::~CMyTabCtl()
{
	delete m_PropertyPage[0];
	delete m_PropertyPage[1];
	delete m_PropertyPage[2];
	delete m_PropertyPage[3];
	delete m_PropertyPage[4];
}

void CMyTabCtl::vInit()
{
	m_PropertyPage[0]->Create(IDD_SYSINFO_DIALOG, this);
	m_PropertyPage[1]->Create(IDD_MEMORY_DIALOG, this);
	m_PropertyPage[2]->Create(IDD_MONITORING_DIALOG, this);
	m_PropertyPage[3]->Create(IDD_SPD_DIALOG, this);
	m_PropertyPage[4]->Create(IDD_DISPLAY_DIALOG, this);

	vSetPage();
}

void CMyTabCtl::vSetPage()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX = itemRect.left;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom-nY - 1;

	m_PropertyPage[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for (int nCount=1; nCount < m_iNbPages; nCount++)
	{
		m_PropertyPage[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
}

void CMyTabCtl::vSetCurrentPage()
{
	if (m_iCurrentPage != GetCurFocus())
	{
		m_PropertyPage[m_iCurrentPage]->ShowWindow(SW_HIDE);
		m_iCurrentPage = GetCurFocus();
		m_PropertyPage[m_iCurrentPage]->ShowWindow(SW_SHOW);
		m_PropertyPage[m_iCurrentPage]->SetFocus();
	}
}

BEGIN_MESSAGE_MAP(CMyTabCtl, CTabCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMyTabCtl message handlers



void CMyTabCtl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CTabCtrl::OnLButtonDown(nFlags, point);
}