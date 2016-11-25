// CPUViewerDoc.h : interface of the CCPUViewerDoc class
//


#pragma once


class CCPUViewerDoc : public CDocument
{
protected: // create from serialization only
	CCPUViewerDoc();
	DECLARE_DYNCREATE(CCPUViewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CCPUViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


