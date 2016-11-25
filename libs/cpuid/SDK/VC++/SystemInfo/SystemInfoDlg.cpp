// SystemInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoInc.h"
#include "SystemInfo.h"
#include "MyTabCtl.h"
#include "SystemInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSystemInfoDlg dialog

CSystemInfoDlg::CSystemInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemInfoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSystemInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_TAB, m_MainTab);
}

BEGIN_MESSAGE_MAP(CSystemInfoDlg, CDialog)
//	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAIN_TAB, OnSelchangeMainTab)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OK, &CSystemInfoDlg::OnBnClickedButtonOk)
	//ON_BN_CLICKED(IDC_BUTTON_APPLY, &CSystemInfoDlg::OnBnClickedButtonApply)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CSystemInfoDlg message handlers

BOOL CSystemInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_MainTab.DeselectAll(FALSE);

	TCITEM tabItem;
	tabItem.mask = TCIF_TEXT;

	tabItem.pszText = _T("CPU");
	m_MainTab.InsertItem(0, &tabItem);

	tabItem.pszText = _T("Memory");
	m_MainTab.InsertItem(1, &tabItem);

	tabItem.pszText = _T("Monitoring");
	m_MainTab.InsertItem(2, &tabItem);

	tabItem.pszText = _T("SPD");
	m_MainTab.InsertItem(3, &tabItem);

	tabItem.pszText = _T("Display");
	m_MainTab.InsertItem(4, &tabItem);

	m_MainTab.vInit();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSystemInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSystemInfoDlg::OnSelchangeMainTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_MainTab.vSetCurrentPage();
	*pResult = 0;
}

void CSystemInfoDlg::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSystemInfoDlg::OnDestroy()
{
	CDialog::OnDestroy();
}
