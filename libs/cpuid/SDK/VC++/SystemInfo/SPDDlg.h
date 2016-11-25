#pragma once
#include "afxwin.h"


// CSPDDlg dialog

class CSPDDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CSPDDlg)

public:
	CSPDDlg();
	virtual ~CSPDDlg();

// Dialog Data
	enum { IDD = IDD_SPD_DIALOG };

protected:
	void vUpdateSPDInfos(int _index);
	void vCleanAll();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_SPD;
	afx_msg void OnCbnSelchangeComboSpd();
};
