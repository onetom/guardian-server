#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDisplayDlg dialog

class CDisplayDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CDisplayDlg)

public:
	CDisplayDlg();
	virtual ~CDisplayDlg();

// Dialog Data
	enum { IDD = IDD_DISPLAY_DIALOG };

protected:
	void vUpdateDisplayInfos();
	void vUpdateDisplayClockInfos();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CComboBox m_Combo_DisplayAdapter;
	CComboBox m_Combo_PerfLevel;
public:
	afx_msg void OnCbnSelchangeComboDisplay();
	afx_msg void OnCbnSelchangeComboPerflevel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
