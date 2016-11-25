#pragma once
#include "afxwin.h"


// CCPUInfoDlg dialog

class CCPUInfoDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CCPUInfoDlg)

public:
	CComboBox m_ComboCPUSelection;

protected:
	CBitmap		m_bmpPlmain;
	CBitmap		m_bmpMask;
	CBitmap		m_ProcessorLogoBitmap;
	BOOL		m_bTransparentLogo;
	int			m_iProcessorLogoWidth;
	int			m_iProcessorLogoHeight;

public:
	CCPUInfoDlg();
	virtual ~CCPUInfoDlg();

// Dialog Data
	enum { IDD = IDD_CPUINFO_DIALOG };

protected:
	void vRefreshGUI();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeComboCpusel();
	afx_msg void OnCbnDropdownComboCpusel();
};
