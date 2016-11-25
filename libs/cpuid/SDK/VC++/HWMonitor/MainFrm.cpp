// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CMonitor.h"
#include "HWMonitor.h"
#include "HWMonitorDoc.h"
#include "ColumnTreeCtrl.h"
#include "ColumnTreeView.h"
#include "HWMonitorView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(WM_TREE_CREATE, vCreateTree)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	UINT ID, style;
	int width;

	m_wndStatusBar.GetPaneInfo(0, ID, style, width);
	m_wndStatusBar.SetPaneInfo(0, ID, style, 0);

    hSmallIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, 0);
    hLargeIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 32, 32, 0);

	//SetIcon(hLargeIcon, TRUE);		// Set big icon
	//SetIcon(hSmallIcon, FALSE);		// Set small icon

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.cx = 650;
	cs.cy = 800;
	cs.style &= ~(LONG)FWS_ADDTOTITLE;

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

LRESULT CMainFrame::vCreateTree(WPARAM, LPARAM)
{
	CHWMonitorView *pView = (CHWMonitorView *)GetActiveView();
	if (pView)
	{
		pView->vCreateTree();
	}
	return 0;
}

void CMainFrame::OnClose()
{
	CFrameWnd::OnClose();
}
