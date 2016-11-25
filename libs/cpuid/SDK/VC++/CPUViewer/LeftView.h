// LeftView.h : interface of the CLeftView class
//


#pragma once

class CCPUViewerDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

protected:
	tdCPUTreeItemList	*m_pCPUTreeItemList;
	CCPUTreeItem		*m_pSelectedTreeItem;

// Attributes
public:
	CCPUViewerDoc* GetDocument();
	void vUpdate();

protected:
	void vRefreshListView();

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnDestroy();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CCPUViewerDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CCPUViewerDoc*>(m_pDocument); }
#endif