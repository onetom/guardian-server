// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CPUTreeItem.h"
#include "CPUViewer.h"
#include "CPUViewerDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CLeftView::OnTvnSelchanged)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
	m_pCPUTreeItemList = new tdCPUTreeItemList();
	m_pSelectedTreeItem = NULL;
}

CLeftView::~CLeftView()
{
	m_pCPUTreeItemList->vDeleteAllItems();
	delete m_pCPUTreeItemList;
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}


// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCPUViewerDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCPUViewerDoc)));
	return (CCPUViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView message handlers

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CTreeCtrl &tc = GetTreeCtrl();

	long style = GetWindowLong(tc.m_hWnd, GWL_STYLE);
	style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_DISABLEDRAGDROP;
	SetWindowLong(tc.m_hWnd, GWL_STYLE, style);

	UINT_PTR timer0 = SetTimer(0, 1000, NULL);

	return 0;
}

void CLeftView::vRefreshListView()
{
	if (m_pSelectedTreeItem)
	{
		// Get a pointer to the main frame window
		CFrameWnd *pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
		if (pFrame)
		{
			pFrame->SendMessage(WM_UPDATE_LIST_VIEW, (WPARAM)m_pSelectedTreeItem);
		}
	}
}

void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	CTreeCtrl &tc = GetTreeCtrl();
	HTREEITEM hSelectedItem = tc.GetSelectedItem();

	tdCPUTreeItemListParser cputreeitemparser(m_pCPUTreeItemList);
	CCPUTreeItem *pCPUTreeItem = cputreeitemparser.pGetRoot();
	while (pCPUTreeItem)
	{
		if (pCPUTreeItem->hGetTreeItem() == hSelectedItem)
		{
			m_pSelectedTreeItem = pCPUTreeItem;
			break;
		}
		pCPUTreeItem = cputreeitemparser.pGetNext();
	}

	vRefreshListView();

	*pResult = 0;
}

void CLeftView::vUpdate()
{
	TCHAR			buffer[512];
	CCPUTreeItem	*pCPUTreeItem;
	CPUIDSDK		*pSDK;
	int				NbProcessors, NbCores, NbThreads, ThreadPerCore;
	int				i, j, k;	

	pSDK = theApp.pGetSDKInstance();
	if (!pSDK) return;

	CTreeCtrl &tc = GetTreeCtrl();

	NbProcessors = pSDK->GetNumberOfProcessors();
	if (IS_I_DEFINED(NbProcessors))
	{
		for ( i=0; i<NbProcessors; i++ )
		{
			SPRINTF(buffer, _countof(buffer), _T("Processor %d"), i);
			HTREEITEM hproc = tc.InsertItem(buffer);			

		//	Create CPU item
			pCPUTreeItem = new CCPUTreeItem(hproc, TREE_ITEM_CLASS_PROCESSOR, i);
			if (!m_pSelectedTreeItem)
				m_pSelectedTreeItem = pCPUTreeItem;

		//	Add item in list
			m_pCPUTreeItemList->vAddItem(pCPUTreeItem);

			NbCores = pSDK->GetProcessorCoreCount(i);
			NbThreads = pSDK->GetProcessorThreadCount(i);

			if (IS_I_DEFINED(NbCores))
			{
				for ( j=0; j<NbCores; j++ )
				{
					SPRINTF(buffer, _countof(buffer), _T("Core %d"), j);
					HTREEITEM hcore = tc.InsertItem(buffer, hproc);					

				//	Create CPU item
					pCPUTreeItem = new CCPUTreeItem(hcore, TREE_ITEM_CLASS_CORE, i, j);

				//	Add item in list
					m_pCPUTreeItemList->vAddItem(pCPUTreeItem);
					
					ThreadPerCore = pSDK->GetProcessorCoreThreadCount(i, j);
					if (IS_I_DEFINED(ThreadPerCore))
					{
						for ( k=0; k<ThreadPerCore; k++ )
						{
							SPRINTF(buffer, _countof(buffer), _T("Thread %d"), k);
							HTREEITEM hthread = tc.InsertItem(buffer, hcore);

						//	Create CPU item
							pCPUTreeItem = new CCPUTreeItem(hthread, TREE_ITEM_CLASS_THREAD, i, j, k);

						//	Add item in list
							m_pCPUTreeItemList->vAddItem(pCPUTreeItem);
						}
					}
				}
			}
			tc.Expand(hproc, TVE_EXPAND);
		}
	}
	vRefreshListView();
}

void CLeftView::OnDestroy()
{
	CTreeView::OnDestroy();

	// TODO: Add your message handler code here
	CTreeCtrl &tc = GetTreeCtrl();
	BOOL result = tc.DeleteAllItems();
}

void CLeftView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
		case 0:
			{
				vRefreshListView();
			}
			break;

		default:
			break;
	}

	CTreeView::OnTimer(nIDEvent);
}
