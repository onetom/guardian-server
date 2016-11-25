// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CPUTreeItem.h"
#include "CPUViewer.h"
#include "MainFrm.h"
#include "LeftView.h"
#include "CPUViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &CMainFrame::OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &CMainFrame::OnViewStyle)
	ON_MESSAGE(WM_UPDATE_TREE_VIEW, vUpdateTreeView)
	ON_MESSAGE(WM_REBUILD_LIST_VIEW, vRebuildListView)
	ON_MESSAGE(WM_UPDATE_LIST_VIEW, vUpdateListView)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PAGE, OnUpdatePage)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
	ID_INDICATOR_PAGE,
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

	//SetMenu(NULL);
	//::DestroyMenu(m_hMenuDefault);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(150, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCPUViewerView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.cx = 630;
	cs.cy = 420;
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


CCPUViewerView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CCPUViewerView* pView = DYNAMIC_DOWNCAST(CCPUViewerView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	if (!pCmdUI)
		return;

	// TODO: customize or extend this code to handle choices on the View menu

	CCPUViewerView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the View menu
	CCPUViewerView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CCPUViewerView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

LRESULT CMainFrame::vUpdateTreeView(WPARAM, LPARAM)
{
	CWnd *pWnd = m_wndSplitter.GetPane(0, 0);
	if (pWnd)
	{
		CLeftView *pLeftView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
		if (pLeftView)
		{
			pLeftView->vUpdate();
		}
	}
	return 0;
}

LRESULT CMainFrame::vUpdateListView(WPARAM wParam, LPARAM lParam)
{
	CWnd *pWnd = m_wndSplitter.GetPane(0, 1);
	if (pWnd)
	{
		CCPUViewerView *pListView= DYNAMIC_DOWNCAST(CCPUViewerView, pWnd);
		if (pListView)
		{
			pListView->vUpdate((CCPUTreeItem *)wParam);
		}
	}
	return 0;
}

LRESULT CMainFrame::vRebuildListView(WPARAM wParam, LPARAM lParam)
{
	CWnd *pWnd = m_wndSplitter.GetPane(0, 1);
	if (pWnd)
	{
		CCPUViewerView *pListView= DYNAMIC_DOWNCAST(CCPUViewerView, pWnd);
		if (pListView)
		{
			pListView->vRebuildList();
		}
	}
	return 0;
}

void CMainFrame::OnUpdatePage(CCmdUI *pCmdUI)
{
    pCmdUI->Enable();
	//pCmdUI->SetText(theApp.m_szStatusMessage);
	m_wndStatusBar.SetPaneText(0, theApp.m_szStatusMessage);
}