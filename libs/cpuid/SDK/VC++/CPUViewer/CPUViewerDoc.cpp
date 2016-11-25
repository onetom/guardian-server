// CPUViewerDoc.cpp : implementation of the CCPUViewerDoc class
//

#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CPUTreeItem.h"
#include "CPUViewer.h"
#include "CPUViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCPUViewerDoc

IMPLEMENT_DYNCREATE(CCPUViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CCPUViewerDoc, CDocument)
END_MESSAGE_MAP()


// CCPUViewerDoc construction/destruction

CCPUViewerDoc::CCPUViewerDoc()
{
	// TODO: add one-time construction code here

}

CCPUViewerDoc::~CCPUViewerDoc()
{
}

BOOL CCPUViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCPUViewerDoc serialization

void CCPUViewerDoc::Serialize(CArchive& ar)
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


// CCPUViewerDoc diagnostics

#ifdef _DEBUG
void CCPUViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCPUViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCPUViewerDoc commands
