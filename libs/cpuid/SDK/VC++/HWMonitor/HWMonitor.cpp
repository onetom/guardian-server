// HWMonitor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "comutil.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CMonitor.h"
#include "HWMonitor.h"
#include "MainFrm.h"
#include "HWMonitorDoc.h"
#include "ColumnTreeCtrl.h"
#include "ColumnTreeView.h"
#include "HWMonitorView.h"
#include "hyperlink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

template <class T>
BSTR ToBSTR(T a_Str) 
{
	return(_bstr_t(a_Str).copy());
}

// CHWMonitorApp

BEGIN_MESSAGE_MAP(CHWMonitorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CHWMonitorApp::OnAppAbout)
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

volatile BOOL CHWMonitorApp::m_bExitFlag = FALSE;
HANDLE CHWMonitorApp::m_hTMutex = NULL;


// CHWMonitorApp construction

CHWMonitorApp::CHWMonitorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_hUpdateThread = NULL;
	m_iVersion[0] = m_iVersion[1] = m_iVersion[2] = m_iVersion[3] = 0;
}

// The one and only CHWMonitorApp object

CHWMonitorApp theApp;


// CHWMonitorApp initialization

BOOL CHWMonitorApp::InitInstance()
{
	TCHAR	szComputerName[512];
	BOOL	result;

	CWinApp::InitInstance();

//	Create mutex
	m_hTMutex = CreateMutex(NULL, FALSE, _T("HWMonitor"));
	switch (GetLastError())
	{
		case ERROR_ALREADY_EXISTS:
			{
				return FALSE;
			}
			break;

		default:
			break;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHWMonitorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHWMonitorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand

	m_pMonitorList = new tdMonitorList();

	DWORD size = 512;
	result = GetComputerName(szComputerName, &size);

//	Create local monitor
#ifdef _UNICODE
	char szTemp[512];
	int value = WideCharToMultiByte(CP_ACP,
									0,
									szComputerName,
									-1,
									szTemp,
									_countof(szTemp),
									NULL,
									NULL);

	CMonitor *pMonitor = new CLocalMonitor(szTemp);
#else
	CMonitor *pMonitor = new CLocalMonitor(szComputerName);
#endif
	m_pMonitorList->vAddItem(pMonitor);
	m_pLocalMonitor = pMonitor;
	result = pMonitor->bInit();

//	File version
	{
		HMODULE hModule = ::GetModuleHandle(NULL);
		TCHAR path[MAX_PATH];
		::GetModuleFileName(hModule, path, MAX_PATH);
		vGetFileVersion(path, m_iVersion);
	}

//	Send update message
	CFrameWnd *pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	if (pFrame)
	{
		pFrame->SendMessage(WM_TREE_CREATE);
	}

//	Create update thread	
	result = bCreateUpdateThread();

	return TRUE;
}

void CHWMonitorApp::vUpdate()
{
	tdMonitorListParser MonitorParser(m_pMonitorList);
	CMonitor *pMonitor = MonitorParser.pGetRoot();
	while (pMonitor)
	{
		pMonitor->vUpdate();
		pMonitor = MonitorParser.pGetNext();
	}
}

void CHWMonitorApp::vClearMinMax()
{
	tdMonitorListParser parser(m_pMonitorList);
	CMonitor *pMonitor = parser.pGetRoot();
	while (pMonitor)
	{
		pMonitor->vClearMinMax();
		pMonitor = parser.pGetNext();
	}
}

DWORD WINAPI CHWMonitorApp::ThreadUpdate(LPVOID lpParam)
{
	while (!m_bExitFlag)
	{
		DWORD error = WaitForSingleObject(CHWMonitorApp::m_hTMutex, 50);
		switch (error)
		{
			case WAIT_OBJECT_0:
				{
					theApp.vUpdate();
					ReleaseMutex(CHWMonitorApp::m_hTMutex);
				}
				break;

			case WAIT_ABANDONED:
				{
					ReleaseMutex(CHWMonitorApp::m_hTMutex);
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

BOOL CHWMonitorApp::bCreateUpdateThread()
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

// CHWMonitorApp message handlers


int CHWMonitorApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD errorcode;

//	Stop thread & wait
	m_bExitFlag = TRUE;
	errorcode = WaitForSingleObject(m_hUpdateThread, 5000);
	CloseHandle(m_hUpdateThread);
	m_hUpdateThread = NULL;

	if (m_hTMutex)
	{
		ReleaseMutex(m_hTMutex);
		CloseHandle(m_hTMutex);
	}

	tdMonitorListParser MonitorParser(m_pMonitorList);
	CMonitor *pMonitor = MonitorParser.pGetRoot();
	while (pMonitor)
	{
		pMonitor->vClose();
		pMonitor = MonitorParser.pGetNext();
	}

	if (m_pMonitorList)
	{
		m_pMonitorList->vDeleteAllItems();
		delete m_pMonitorList;
	}

	return CWinApp::ExitInstance();
}

int CHWMonitorApp::iGetMonitorIndex(CMonitor *_pMonitor)
{
	int monitor_index = 0;

	tdMonitorListParser parser(m_pMonitorList);
	CMonitor *pMonitor = parser.pGetRoot();
	while (pMonitor)
	{
		if (pMonitor == _pMonitor)
		{
			return monitor_index;
		}
		monitor_index++;
		pMonitor = parser.pGetNext();
	}
	return I_UNDEFINED_VALUE;
}

CMonitor *CHWMonitorApp::pGetMonitor(int _index)
{
	int monitor_index = 0;

	tdMonitorListParser parser(m_pMonitorList);
	CMonitor *pMonitor = parser.pGetRoot();
	while (pMonitor)
	{
		if (monitor_index == _index)
		{
			return pMonitor;
		}
		monitor_index++;
		pMonitor = parser.pGetNext();
	}
	return NULL;
}

void CHWMonitorApp::vGetFileVersion(TCHAR *_filename, int _version[])
{
	VS_FIXEDFILEINFO	*pVerInfo;
	DWORD				dwSize, dwTemp, dwHandle;
	BYTE				*pData;
	UINT				len;

#ifdef _UNICODE
	BSTR temp;
	temp = ToBSTR(_filename);
#else
	char *temp = _filename;
#endif

	pVerInfo = NULL;
	dwSize = GetFileVersionInfoSize(temp, &dwTemp);
	if (dwSize == 0)
	{
		return;
	}

	dwHandle = 0;
	pData = new BYTE[dwSize];
	if (!GetFileVersionInfo(temp, dwHandle, dwSize, pData))
	{
		delete[] pData;
		return;
	}

	if (!VerQueryValue(pData, _T("\\"), (void **)&pVerInfo, &len))
	{
		delete[] pData;
		return;
	}

	_version[0] = HIWORD(pVerInfo->dwFileVersionMS);
	_version[1] = LOWORD(pVerInfo->dwFileVersionMS);
	_version[2] = HIWORD(pVerInfo->dwFileVersionLS);
	_version[3] = LOWORD(pVerInfo->dwFileVersionLS);

	delete[] pData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	CHyperLink	m_HWM_Logo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HWM_LOGO, m_HWM_Logo);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	TCHAR buffer[1024];

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_HWM_Logo.vSetURL(_T("http://www.cpuid-pro.com/hwmonitor.php"));

	if (IS_I_DEFINED(theApp.m_iVersion[0]))
	{
		SPRINTF(buffer, _countof(buffer), 
			_T(" HWMonitor\n Copyright © CPUID - 2015\n Version %d.%d%d.%d\n"),
			theApp.m_iVersion[0],
			theApp.m_iVersion[1],
			theApp.m_iVersion[2],
			theApp.m_iVersion[3]);

		GetDlgItem(IDC_STATIC_ABOUT)->SetWindowText(buffer);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

// App command to run the dialog
void CHWMonitorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}