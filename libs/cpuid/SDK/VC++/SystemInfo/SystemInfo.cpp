// SystemInfo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SystemInfoInc.h"
#include "SystemInfo.h"
#include "MyTabCtl.h"
#include "SystemInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSystemInfoApp

BEGIN_MESSAGE_MAP(CSystemInfoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSystemInfoApp construction

volatile BOOL CSystemInfoApp::m_bExitFlag = TRUE;
HANDLE CSystemInfoApp::m_hTMutex = NULL;

CSystemInfoApp::CSystemInfoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_hUpdateThread = NULL;
	m_hDLL = NULL;
	m_pSDK = NULL;

	m_iCoreID = 0;
}


// The one and only CSystemInfoApp object

CSystemInfoApp theApp;


// CSystemInfoApp initialization

BOOL CSystemInfoApp::InitInstance()
{
	TCHAR	szDllPath[512];
	TCHAR	szDllFilename[512];
	TCHAR	tmpBuffer[512];
	int		errorcode, extended_errorcode;
	BOOL	result;

	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));

//	Create mutex
	m_hTMutex = CreateMutex(NULL, FALSE, _T("SYSTEMINFO"));
	switch (GetLastError())
	{
		case ERROR_ALREADY_EXISTS:
			return FALSE;

		default:
			break;
	}

#if defined (_M_AMD64)
	SPRINTF(szDllFilename, _countof(szDllFilename), _T("cpuidsdk64.dll"));
#else
	SPRINTF(szDllFilename, _countof(szDllFilename), _T("cpuidsdk.dll"));
#endif

//	TCHAR** lppPart = NULL;
//	GetFullPathName(szDllPath, 256, tmpBuffer, lppPart);
//	_tcscpy(szDllPath, tmpBuffer);

//	Why instead of receive the full path for the dll in Init method, you don't save the hModule for your dll at the DllMain 
//	and use GetModuleFileName at the Init internals to get the path name?

	SPRINTF(szDllPath, _countof(szDllPath), _T("..\\..\\..\\bin"));
	SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("%s\\%s"), szDllPath, szDllFilename);
	m_hDLL = LoadLibrary(tmpBuffer);
	if (!m_hDLL)
	{		
		SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("%s"), szDllFilename);
		m_hDLL = LoadLibrary(tmpBuffer);
		if (m_hDLL)
		{
		//	Dll found in current directory, we clean szDllPath
			szDllPath[0] = 0;
		}
	}
	if (!m_hDLL)
	{
		SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Unable to find %s\\%s"), szDllPath, szDllFilename);
		MessageBox(NULL,tmpBuffer, _T("Error"), MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (m_hDLL)
	{
		m_pSDK = new CPUIDSDK();

		result = m_pSDK->InitDll(m_hDLL);
		result = m_pSDK->CreateInstance();
#ifdef _UNICODE
		char szMultiBytePath[512];
		char szMultiByteDllFilename[512];
		DWORD ret;

		ret = WideCharToMultiByte(CP_ACP, 0, szDllPath, -1, szMultiBytePath, _countof(szMultiBytePath), NULL, NULL);
		ret = WideCharToMultiByte(CP_ACP, 0, szDllFilename, -1, szMultiByteDllFilename, _countof(szMultiByteDllFilename), NULL, NULL);		
		
		result = m_pSDK->Init(szMultiBytePath,
							  szMultiByteDllFilename,
							  CPUIDSDK_CONFIG_USE_EVERYTHING,
							  &errorcode,
							  &extended_errorcode);
#else
		errorcode = 0;
		result = m_pSDK->Init(szDllPath,
							  szDllFilename,
							  CPUIDSDK_CONFIG_USE_EVERYTHING,
							  &errorcode,
							  &extended_errorcode);
#endif

		if (errorcode != CPUIDSDK_ERROR_NO_ERROR)
		{
		//	Init failed, check errorcode
			switch (errorcode)
			{
				case CPUIDSDK_ERROR_EVALUATION:
					{
						switch (extended_errorcode)
						{
							case CPUIDSDK_EXT_ERROR_EVAL_1:
								SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("You are running a trial version of the DLL SDK. In order to make it work, please run CPU-Z at the same time."));
								break;

							case CPUIDSDK_EXT_ERROR_EVAL_2:
								SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Evaluation version has expired."));
								break;

							default:
								SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Eval version error 0x%X."), extended_errorcode);
								break;
						}
					}
					break;

				case CPUIDSDK_ERROR_DRIVER:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Driver error 0x%X (%d)"), extended_errorcode, extended_errorcode);
					break;

				case CPUIDSDK_ERROR_VM_RUNNING:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Virtual machine detected."));
					break;

				case CPUIDSDK_ERROR_LOCKED:
					{
						switch (extended_errorcode)
						{
							case ERROR_INVALID_HANDLE:	// 6
								SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("SDK mutex not created."));
								break;

							default:
								SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("SDK mutex locked."));
								break;
						}
					}
					break;

				case CPUIDSDK_ERROR_INVALID_DLL:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Invalid DLL"));
					break;

				default:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Error code 0x%X (%d)"), errorcode, errorcode);
					break;
			}
			MessageBox(NULL,tmpBuffer, _T("Error"), MB_ICONEXCLAMATION);
		}

		if (!result)
			return FALSE;
	}

	if (m_pSDK)
	{
		m_pSDK->RefreshInformation();
	}

//	Create thread
	m_bExitFlag = FALSE;
	result = bCreateUpdateThread();

	CSystemInfoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CSystemInfoApp::ExitInstance()
{	
	DWORD errorcode;

//	Stop thread & wait
	m_bExitFlag = TRUE;
	errorcode = WaitForSingleObject(m_hUpdateThread, INFINITE);
	CloseHandle(m_hUpdateThread);
	m_hUpdateThread = NULL;

//	Close mutex
	if (m_hTMutex)
	{
		ReleaseMutex(m_hTMutex);
		CloseHandle(m_hTMutex);
		m_hTMutex = NULL;
	}
	if (m_pSDK)
	{
		m_pSDK->Close();
		m_pSDK->DestroyInstance();
		delete m_pSDK;
	}
	if (m_hDLL)
	{
		FreeLibrary(m_hDLL);
	}

	return CWinApp::ExitInstance();
}

void CSystemInfoApp::vUpdate()
{
	if (m_pSDK)
	{
		m_pSDK->RefreshInformation();
	}
}

DWORD WINAPI CSystemInfoApp::ThreadUpdate(LPVOID lpParam)
{
	while (!m_bExitFlag)
	{
		DWORD error = WaitForSingleObject(m_hTMutex, 50);
		switch (error)
		{
			case WAIT_OBJECT_0:
				{
					theApp.vUpdate();
					ReleaseMutex(m_hTMutex);
				}
				break;

			case WAIT_ABANDONED:
				{
					ReleaseMutex(m_hTMutex);
				}
				break;

			default:
				break;
		}
		Sleep(1000);
	}
	ExitThread(0);
	return 0;
}

BOOL CSystemInfoApp::bCreateUpdateThread()
{
	DWORD dwThreadId, dwThrdParam = 1;

	if (m_hUpdateThread)
		return FALSE;

	m_hUpdateThread = ::CreateThread(NULL,			// default security attributes 
									0,				// use default stack size  
									ThreadUpdate,	// thread function 
									this,			// argument to thread function 
									0,				// use default creation flags 
									&dwThreadId);	// returns the thread identifier 
	if (m_hUpdateThread == NULL) 
	{
		return FALSE;
	}
	else
	{
		::SetThreadPriority(m_hUpdateThread, THREAD_PRIORITY_NORMAL);
	}
	return TRUE;
}

void CSystemInfoApp::PrepareMask(CBitmap* pBmpSource, CBitmap* pBmpMask, COLORREF clrpTransColor, int iTransPixelX, int iTransPixelY)
{
	BITMAP bm;
	
	// Get the dimensions of the source bitmap
	pBmpSource->GetObject(sizeof(BITMAP), &bm);
	
	// Create the mask bitmap
	pBmpMask->DeleteObject();
	pBmpMask->CreateBitmap( bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	
	// We will need two DCs to work with. One to hold the Image
	// (the source), and one to hold the mask (destination).
	// When blitting onto a monochrome bitmap from a color, pixels
	// in the source color bitmap that are equal to the background
	// color are blitted as white. All the remaining pixels are
	// blitted as black.
	
	CDC hdcSrc, hdcDst;
	
	hdcSrc.CreateCompatibleDC(NULL);
	hdcDst.CreateCompatibleDC(NULL);
	
	// Load the bitmaps into memory DC
	CBitmap* hbmSrcT = (CBitmap*) hdcSrc.SelectObject(pBmpSource);
	CBitmap* hbmDstT = (CBitmap*) hdcDst.SelectObject(pBmpMask);
	
	// Dynamically get the transparent color
	COLORREF clrTrans;
	if (clrpTransColor == NULL)
	{
		// User did not specify trans color so get it from bmp
		clrTrans = hdcSrc.GetPixel(iTransPixelX, iTransPixelY);
	}
	else
	{
		clrTrans = clrpTransColor;
	}

	// Change the background to trans color
	COLORREF clrSaveBk  = hdcSrc.SetBkColor(clrTrans);
	
	// This call sets up the mask bitmap.
	hdcDst.BitBlt(0,0,bm.bmWidth, bm.bmHeight, &hdcSrc,0,0,SRCCOPY);
	
	// Now, we need to paint onto the original image, making
	// sure that the "transparent" area is set to black. What
	// we do is AND the monochrome image onto the color Image
	// first. When blitting from mono to color, the monochrome
	// pixel is first transformed as follows:
	// if  1 (black) it is mapped to the color set by SetTextColor().
	// if  0 (white) is is mapped to the color set by SetBkColor().
	// Only then is the raster operation performed.
	
	COLORREF clrSaveDstText = hdcSrc.SetTextColor(RGB(255,255,255));
	hdcSrc.SetBkColor(RGB(0,0,0));
	
	hdcSrc.BitBlt(0,0,bm.bmWidth, bm.bmHeight, &hdcDst,0,0,SRCAND);
	
	// Clean up by deselecting any objects, and delete the
	// DC's.
	hdcDst.SetTextColor(clrSaveDstText);
	
	hdcSrc.SetBkColor(clrSaveBk);
	hdcSrc.SelectObject(hbmSrcT);
	hdcDst.SelectObject(hbmDstT);
	
	hdcSrc.DeleteDC();
	hdcDst.DeleteDC();
}

void CSystemInfoApp::DrawTransparentBitmap(CDC* pDC, CBitmap	*bmpMask, int xStart, int yStart, int wWidth, int wHeight, CDC* pTmpDC, int xSource, int ySource)
{
	CDC hdcMem;
	hdcMem.CreateCompatibleDC(NULL);
	
	CBitmap* hbmT = hdcMem.SelectObject(bmpMask);
	
	pDC->BitBlt( xStart, yStart, wWidth, wHeight, &hdcMem, xSource, ySource, SRCAND);
	pDC->BitBlt(xStart, yStart, wWidth, wHeight, pTmpDC, xSource, ySource, SRCPAINT);

	hdcMem.SelectObject(hbmT);
	hdcMem.DeleteDC();
}