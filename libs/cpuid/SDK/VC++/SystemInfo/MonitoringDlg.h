#pragma once


// CMonitoringDlg dialog

class CMonitoringDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CMonitoringDlg)

public:
	CMonitoringDlg();
	virtual ~CMonitoringDlg();

// Dialog Data
	enum { IDD = IDD_MONITORING_DIALOG };

protected:
	void vRefreshGUI();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticVoltage18();
	afx_msg void OnStnClickedStaticVoltage11();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
