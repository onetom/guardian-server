#pragma once


// CMyTabCtl

class CMyTabCtl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtl)

protected:
	CPropertyPage	*m_PropertyPage[6];
	int				m_iNbPages;
	int				m_iCurrentPage;

protected:
	void vSetPage();

public:
	CMyTabCtl();
	virtual ~CMyTabCtl();

	void vInit();
	void vSetCurrentPage();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


