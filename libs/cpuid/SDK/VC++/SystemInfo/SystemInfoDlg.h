// SystemInfoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSystemInfoDlg dialog
class CSystemInfoDlg : public CDialog
{
// Construction
public:
	CSystemInfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SYSTEMINFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON		m_hIcon;

protected:
	void vActivateTabDialogs();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeMainTab(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	CMyTabCtl m_MainTab;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnDestroy();	
};
