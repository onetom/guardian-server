// HWMonitorDoc.h : interface of the CHWMonitorDoc class
//


#pragma once


class CHWMonitorDoc : public CDocument
{
protected: // create from serialization only
	CHWMonitorDoc();
	DECLARE_DYNCREATE(CHWMonitorDoc)

// Attributes
public:
	static FILE *m_pOutputFile;
	//static void	vPrintOutput(const char *fmt, ...);

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CHWMonitorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

public:
	void vSaveSMBusDump(LPCTSTR lpszPathName);
};


