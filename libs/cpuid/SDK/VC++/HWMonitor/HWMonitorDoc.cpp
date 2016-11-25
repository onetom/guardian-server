// HWMonitorDoc.cpp : implementation of the CHWMonitorDoc class
//

#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CMonitor.h"
#include "HWMonitor.h"
#include "HWMonitorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHWMonitorDoc

IMPLEMENT_DYNCREATE(CHWMonitorDoc, CDocument)

BEGIN_MESSAGE_MAP(CHWMonitorDoc, CDocument)
END_MESSAGE_MAP()


FILE *CHWMonitorDoc::m_pOutputFile = NULL;

// CHWMonitorDoc construction/destruction

CHWMonitorDoc::CHWMonitorDoc()
{
	// TODO: add one-time construction code here

}

CHWMonitorDoc::~CHWMonitorDoc()
{
}

BOOL CHWMonitorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CHWMonitorDoc serialization

void CHWMonitorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CHWMonitorDoc diagnostics

#ifdef _DEBUG
void CHWMonitorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHWMonitorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHWMonitorDoc commands

BOOL CHWMonitorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return TRUE;
}

void CHWMonitorDoc::vSaveSMBusDump(LPCTSTR lpszPathName)
{
}
