// CPUViewer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "math.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CPUTreeItem.h"
#include "CPUViewer.h"
#include "MainFrm.h"

#include "CPUViewerDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCPUViewerApp

BEGIN_MESSAGE_MAP(CCPUViewerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CCPUViewerApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


volatile BOOL CCPUViewerApp::m_bExitFlag = FALSE;

// CCPUViewerApp construction

CCPUViewerApp::CCPUViewerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_hDLL = NULL;
	m_pSDK = NULL;
	m_hUpdateThread = NULL;
	SPRINTF(m_szStatusMessage, _countof(m_szStatusMessage), _T("CPUID SDK status"));
}


// The one and only CCPUViewerApp object

CCPUViewerApp theApp;


// CCPUViewerApp initialization

BOOL CCPUViewerApp::InitInstance()
{
	TCHAR	szDllPath[512];
	TCHAR	szDllFilename[512];
	TCHAR	tmpBuffer[512];
	char	szBuffer[512];
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
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCPUViewerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLeftView));

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

#if defined (_M_AMD64)
	SPRINTF(szDllFilename, _countof(szDllFilename), _T("cpuidsdk64.dll"));
#else
	SPRINTF(szDllFilename, _countof(szDllFilename), _T("cpuidsdk.dll"));
#endif

	SPRINTF(szDllPath, _countof(szDllPath), _T("..\\..\\..\\bin"));
	SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("%s\\%s"), szDllPath, szDllFilename);
	m_hDLL = LoadLibrary(tmpBuffer);
	if (!m_hDLL)
	{
		szDllPath[0] = 0;
		SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("%s"), szDllFilename);
		m_hDLL = LoadLibrary(tmpBuffer);
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
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Driver error 0x%X."), extended_errorcode);
					break;

				case CPUIDSDK_ERROR_VM_RUNNING:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Virtual machine detected."));
					break;

				case CPUIDSDK_ERROR_LOCKED:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("SDK mutex locked."));
					break;

				default:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Error code 0x%X"), errorcode);
					break;
			}			
			MessageBox(NULL, tmpBuffer, _T("Error"), MB_ICONEXCLAMATION);
		}

		if (!result)
			return FALSE;
		else
		{
			SPRINTF(m_szStatusMessage, _countof(m_szStatusMessage), _T("Library status OK"));
		}

		int dll_version;
		m_pSDK->GetDLLVersion(&dll_version);
	}
	else
	{
		SPRINTF(m_szStatusMessage, _countof(m_szStatusMessage), _T("Library %s not found"), tmpBuffer);
	}

//	Send update message
	CFrameWnd *pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	if (pFrame)
	{
		pFrame->SendMessage(WM_UPDATE_TREE_VIEW);
	}

//	Create update thread
	result = bCreateUpdateThread();


	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

void CCPUViewerApp::vUpdate()
{
	if (m_pSDK)
	{
		m_pSDK->RefreshInformation();
	}
}

DWORD WINAPI CCPUViewerApp::ThreadUpdate(LPVOID lpParam)
{
	while (!m_bExitFlag)
	{
		theApp.vUpdate();
		Sleep(1000);
	}
	ExitThread(0);
	return 0;
}

BOOL CCPUViewerApp::bCreateUpdateThread()
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


// CCPUViewerApp message handlers


int CCPUViewerApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD errorcode;

//	Stop thread & wait
	m_bExitFlag = TRUE;
	errorcode = WaitForSingleObject(m_hUpdateThread, 5000);
	CloseHandle(m_hUpdateThread);
	m_hUpdateThread = NULL;

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


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CCPUViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}