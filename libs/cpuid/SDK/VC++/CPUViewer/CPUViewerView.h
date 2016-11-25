// CPUViewerView.h : interface of the CCPUViewerView class
//


#pragma once


class CCPUViewerView : public CListView
{
protected: // create from serialization only
	CCPUViewerView();
	DECLARE_DYNCREATE(CCPUViewerView)

// Attributes
public:
	CCPUViewerDoc* GetDocument() const;
	void vUpdate(CCPUTreeItem *_pCPUTreeItem);

protected:
	CCPUTreeItem *m_hCurrentTreeItem;

// Operations
public:

protected:
	void vAddItem(TCHAR *_szTitle, LPCSTR _szValue, int _item, BOOL _bUpdate);

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CCPUViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void vRebuildList() { m_hCurrentTreeItem = NULL; }

protected:

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in CPUViewerView.cpp
inline CCPUViewerDoc* CCPUViewerView::GetDocument() const
   { return reinterpret_cast<CCPUViewerDoc*>(m_pDocument); }
#endif

