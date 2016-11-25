// SystemInfo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


#ifdef _UNICODE
#define SPRINTF		swprintf_s
#define FGETS		fgetws
#define STRSTR		wcsstr
#define SSCANF		swscanf_s
#define FOPEN		_wfopen_s
#define STRCAT		wcscat_s
#define STRLEN		wcslen
#else
#define SPRINTF		sprintf_s
#define FGETS		fgets
#define STRSTR		strstr
#define SSCANF		sscanf_s
#define FOPEN		fopen_s
#define STRCAT		strcat_s
#define STRLEN		strlen
#endif

// CSystemInfoApp:
// See SystemInfo.cpp for the implementation of this class
//

class CSystemInfoApp : public CWinApp
{
protected:
	static HANDLE m_hTMutex;

protected:
	static DWORD WINAPI ThreadUpdate(LPVOID lpParam);
	static volatile BOOL m_bExitFlag;

protected:
	HMODULE			m_hDLL;
	CPUIDSDK		*m_pSDK;

//	Update thread handle
	HANDLE			m_hUpdateThread;

public:
	int				m_iCoreID;

public:
	void PrepareMask(CBitmap* pBmpSource, CBitmap* pBmpMask, COLORREF clrpTransColor, int iTransPixelX, int iTransPixelY);

	void DrawTransparentBitmap(CDC* pDC,
							   CBitmap	*bmpMask,
							   int xStart,  int yStart,
							   int wWidth,  int wHeight,
							   CDC* pTmpDC,
							   int xSource,
							   int ySource);

protected:
	BOOL bCreateUpdateThread();

public:
	CPUIDSDK *pGetSDKInstance() { return m_pSDK; }

public:
	CSystemInfoApp();

public:
	void vUpdate();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CSystemInfoApp theApp;