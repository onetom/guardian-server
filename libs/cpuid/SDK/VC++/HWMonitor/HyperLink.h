#pragma once


// CHyperLink

class CHyperLink : public CStatic
{
	DECLARE_DYNAMIC(CHyperLink)

protected:
	TCHAR	m_strURL[512];
	HCURSOR  m_hLinkCursor;
	CFont    m_UnderlineFont;
	COLORREF m_LinkColor;	

protected:
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	HINSTANCE GotoURL(LPCTSTR url, int showcmd);

public:
	CHyperLink();
	virtual ~CHyperLink();

	void vSetURL(TCHAR *_szURL);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnStnClicked();
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
};


