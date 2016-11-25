// HWMonitorView.h : interface of the CHWMonitorView class
//


#pragma once

#define ITEM_FLAG_LABEL			0x00000001
#define	ITEM_FLAG_EXPAND		0x00010000
#define	ITEM_FLAG_ALT_COLOR		0x00020000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CTreeItem
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CTreeItem;
typedef CTList<CTreeItem> tdTreeItemList;
typedef CTListParser<CTreeItem> tdTreeItemListParser;

class CTreeItem
{
public:
	int				m_iMonitorIndex;
	int				m_iDeviceIndex;
	int				m_iSensorIndex;
	unsigned int	m_uiSensorID;

public:
	HTREEITEM		m_hItem;
	unsigned int	m_uiFlag;

public:
	CTreeItem(int _monitor_index, int _device_index, int _sensor_index, unsigned int _sensor_id, HTREEITEM _hTreeItem);
	virtual ~CTreeItem();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CMonitorTreeItemList
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMonitorTreeItemList;
typedef CTList<CMonitorTreeItemList> tdMonitorTreeItemListList;
typedef CTListParser<CMonitorTreeItemList> tdMonitorTreeItemListListParser;

class CMonitorTreeItemList
{
public:
	int				m_iMonitorIndex;
	tdTreeItemList	*m_pTreeItemList;

public:
	CMonitorTreeItemList(int _monitor_index);
	virtual ~CMonitorTreeItemList();

	int iGetNumberOfSensor(int _device_index, unsigned int _sensor_class);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CHWMonitorView
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CHWMonitorView : public CColumnTreeView
{
protected: // create from serialization only
	CHWMonitorView();
	DECLARE_DYNCREATE(CHWMonitorView)

// Attributes
public:
	CHWMonitorDoc* GetDocument() const;

// Operations
public:
	void vCreateTree();

protected:
	void vUpdateTree(BOOL _bExpand = FALSE);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CHWMonitorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMonitor					*m_pSelectedMonitor;
	tdMonitorTreeItemListList	*m_pMonitorTreeItemListList;
	CImageList					m_ImgList;

protected:
	CMonitorTreeItemList *pGetMonitorTreeItemList(int _monitor_index);
	unsigned int uiFindFlag(HTREEITEM _hTreeItem);
	CTreeItem *pFindTreeItem(HTREEITEM _hTreeItem);
	CTreeItem *pFindTreeItem(int _monitor_index, int _device_index, int _sensor_index, int _sensor_id, unsigned int _flag);

	HTREEITEM hCreateLabelTreeItem(int _monitor_index,
								   int _device_index,
								   unsigned int _sensor_class,
								   HTREEITEM _parent,
								   CMonitorTreeItemList *_pMonitorTreeItemList);

	int iCountTreeItems(HTREEITEM hItem, BOOL _bRecurse);
	void vDeleteTreeItems(int _monitor_index, int _device_index, unsigned int _sensor_class);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTreeCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewClearminmax();
	afx_msg void OnFileSavesmbus();
};

#ifndef _DEBUG  // debug version in HWMonitorView.cpp
inline CHWMonitorDoc* CHWMonitorView::GetDocument() const
   { return reinterpret_cast<CHWMonitorDoc*>(m_pDocument); }
#endif

