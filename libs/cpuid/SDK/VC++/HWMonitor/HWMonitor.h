// HWMonitor.h : main header file for the HWMonitor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#ifdef _UNICODE
#define SPRINTF	swprintf_s
#else
#define SPRINTF	sprintf_s
#endif

///////////////////////////////////////////////////////////////////////////
//
//	CHWMonitorApp Messages
//
///////////////////////////////////////////////////////////////////////////

#define WM_TREE_CREATE				(WM_USER + 1500)
#define WM_TREE_ADD_MONITOR			(WM_USER + 1501)


// CHWMonitorApp:
// See HWMonitor.cpp for the implementation of this class
//

class CHWMonitorApp : public CWinApp
{
public:
	static HANDLE m_hTMutex;

protected:
	static DWORD WINAPI ThreadUpdate(LPVOID lpParam);
	static volatile BOOL m_bExitFlag;

protected:
	tdMonitorList	*m_pMonitorList;
	CMonitor		*m_pLocalMonitor;

protected:
//	Update thread handle
	HANDLE			m_hUpdateThread;

public:
	TCHAR			m_szMessage[256];
	int				m_iVersion[4];

public:
	CHWMonitorApp();

	tdMonitorList *pGetMonitorList() { return m_pMonitorList; }
	int iGetMonitorIndex(CMonitor *_pMonitor);
	CMonitor *pGetMonitor(int _index);

//	Update info
	void vUpdate();

//	Clear min/max
	void vClearMinMax();

protected:
	void vGetFileVersion(TCHAR *_filename, int _version[]);
	BOOL bCreateUpdateThread();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CHWMonitorApp theApp;