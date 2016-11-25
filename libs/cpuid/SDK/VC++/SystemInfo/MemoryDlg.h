#pragma once


// CMemoryDlg dialog

class CMemoryDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CMemoryDlg)

public:
	CMemoryDlg();
	virtual ~CMemoryDlg();

// Dialog Data
	enum { IDD = IDD_MEMORY_DIALOG };

protected:
	void vRefreshGUI();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
