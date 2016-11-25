// CPUViewer.h : main header file for the CPUViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#ifdef _UNICODE
#define SPRINTF	swprintf_s
#else
#define SPRINTF sprintf_s
#endif

///////////////////////////////////////////////////////////////////////////
//
//	CCPUViewerApp Messages
//
///////////////////////////////////////////////////////////////////////////

#define WM_UPDATE_TREE_VIEW		(WM_USER + 15)
#define WM_UPDATE_LIST_VIEW		(WM_USER + 16)
#define	WM_REBUILD_LIST_VIEW	(WM_USER + 17)


// CCPUViewerApp:
// See CPUViewer.cpp for the implementation of this class
//


class CCPUViewerApp : public CWinApp
{
protected:
	static DWORD WINAPI ThreadUpdate(LPVOID lpParam);
	static	volatile BOOL m_bExitFlag;

protected:
	HMODULE		m_hDLL;
	CPUIDSDK	*m_pSDK;

//	Update thread handle
	HANDLE		m_hUpdateThread;

public:
	TCHAR		m_szStatusMessage[512];

public:
	CCPUViewerApp();

	CPUIDSDK *pGetSDKInstance() { return m_pSDK; }

//	Update info
	void vUpdate();

protected:
	BOOL bCreateUpdateThread();	

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
	afx_msg void OnOptionsShowdutyclock();
	afx_msg void OnUpdateOptionsShowdutyclock(CCmdUI *pCmdUI);
};

extern CCPUViewerApp theApp;