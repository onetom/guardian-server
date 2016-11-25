// HyperLink.cpp : implementation file
//

#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "HyperLink.h"


BYTE	g_byHandCur16ANDMask[32] = {0xF3, 0xFF, 0xE1, 0xFF, 0xE1, 0xFF, 0xE1, 0xFF, 
									0xE1, 0xFF, 0xE0, 0x7F, 0xC0, 0x0F, 0x80, 0x03, 
									0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x80, 0x00, 0x80, 0x01, 0xC0, 0x01};
BYTE	g_byHandCur16XORMask[32] = {0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 
									0x0C, 0x00, 0x0C, 0x00, 0x0D, 0x80, 0x2D, 0xB0, 
									0x6F, 0xF4, 0x6F, 0xFC, 0x6F, 0xFE, 0x6F, 0xFE, 
									0x7F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFC, 0x1F, 0xFC};
BYTE	g_byHandCur32ANDMask[128]= {0xF3, 0xFF, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFF, 
									0xE1, 0xFF, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFF, 
									0xE1, 0xFF, 0xFF, 0xFF, 0xE0, 0x7F, 0xFF, 0xFF, 
									0xC0, 0x0F, 0xFF, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 
									0x00, 0x01, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xFF, 
									0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
									0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0xFF, 0xFF, 
									0x80, 0x01, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
BYTE	g_byHandCur32XORMask[128]= {0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
									0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
									0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
									0x0D, 0x80, 0x00, 0x00, 0x2D, 0xB0, 0x00, 0x00, 
									0x6F, 0xF4, 0x00, 0x00, 0x6F, 0xFC, 0x00, 0x00, 
									0x6F, 0xFE, 0x00, 0x00, 0x6F, 0xFE, 0x00, 0x00, 
									0x7F, 0xFE, 0x00, 0x00, 0x3F, 0xFE, 0x00, 0x00, 
									0x3F, 0xFC, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// CHyperLink

IMPLEMENT_DYNAMIC(CHyperLink, CStatic)

CHyperLink::CHyperLink()
{
	m_hLinkCursor = NULL;
	m_LinkColor = RGB(0, 0, 238);
	m_strURL[0] = 0;
}

CHyperLink::~CHyperLink()
{
	m_UnderlineFont.DeleteObject();
}


BEGIN_MESSAGE_MAP(CHyperLink, CStatic)
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR_REFLECT()
//	ON_CONTROL_REFLECT(STN_CLICKED, &CHyperLink::OnStnClicked)
ON_CONTROL_REFLECT(STN_CLICKED, &CHyperLink::OnStnClicked)
ON_WM_NCHITTEST()
END_MESSAGE_MAP()



// CHyperLink message handlers


BOOL CHyperLink::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	if (m_hLinkCursor)
	{
		::SetCursor(m_hLinkCursor);
		return TRUE;
	}
	return FALSE;
	//return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CHyperLink::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD dwStyle = GetStyle();
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY /*| 0x10000000*/);

//	Set Font
	CFont* pFont = GetFont();
	if (!pFont)
	{
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		if (hFont == NULL)
		{
			hFont = (HFONT) GetStockObject(ANSI_VAR_FONT);
		}
		if (hFont)
		{
			pFont = CFont::FromHandle(hFont);
		}
	}
	ASSERT(pFont->GetSafeHandle());

    // Create the underline font
    LOGFONT lf;
    pFont->GetLogFont(&lf);
    lf.lfUnderline = (BYTE)TRUE;
    m_UnderlineFont.CreateFontIndirect(&lf);
	SetFont(&m_UnderlineFont);

//	Set cursor
	if (m_hLinkCursor == NULL)
	{
		int iCursorSize = ::GetSystemMetrics(SM_CXCURSOR);
		if (iCursorSize == 32)
		{
			m_hLinkCursor = ::CreateCursor(AfxGetInstanceHandle(), 8, 1, 32, 32, 
											g_byHandCur32ANDMask, g_byHandCur32XORMask);
		}
		else if (iCursorSize == 16)
		{
			m_hLinkCursor = ::CreateCursor(AfxGetInstanceHandle(), 4, 0, 16, 16, 
											g_byHandCur16ANDMask, g_byHandCur16XORMask);
		}
/*
	//	Get the windows directory
		CString strWndDir;
		GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
		strWndDir.ReleaseBuffer();

		strWndDir += _T("\\winhlp32.exe");
		// This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
		HMODULE hModule = LoadLibrary(strWndDir);
		if (hModule) 
		{
			HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
			if (hHandCursor)
			{
				m_hLinkCursor = CopyCursor(hHandCursor);
			}
		}
		FreeLibrary(hModule);
*/
	}

	CStatic::PreSubclassWindow();
}

HBRUSH CHyperLink::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// TODO:  Change any attributes of the DC here
	pDC->SetTextColor(m_LinkColor);
	pDC->SetBkMode(TRANSPARENT);

	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CHyperLink::OnStnClicked()
{
	// TODO: Add your control notification handler code here
	HINSTANCE ht = GotoURL(m_strURL, SW_SHOW);
}

LONG CHyperLink::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
    HKEY hkey;
    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

    if (retval == ERROR_SUCCESS)
	{
        long datasize = MAX_PATH;
        TCHAR data[MAX_PATH];
        RegQueryValue(hkey, NULL, data, &datasize);
        lstrcpy(retdata,data);
        RegCloseKey(hkey);
    }
    return retval;
}

HINSTANCE CHyperLink::GotoURL(LPCTSTR url, int showcmd)
{
    TCHAR key[MAX_PATH + MAX_PATH];

    // First try ShellExecute()
    HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL, NULL, showcmd);

    // If it failed, get the .htm regkey and lookup the program
    if ((UINT)result <= HINSTANCE_ERROR)
	{
        if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS)
		{
            lstrcat(key, _T("\\shell\\open\\command"));
            if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS)
			{
                TCHAR *pos;
                pos = _tcsstr(key, _T("\"%1\""));
                if (pos == NULL)
				{
                    pos = _tcsstr(key, _T("%1"));
                    if (pos == NULL)
                        pos = key+lstrlen(key)-1;
                    else
                        *pos = '\0';
                }
                else
				{
                    *pos = '\0';
				}

                lstrcat(pos, _T(" "));
                lstrcat(pos, url);
                USES_CONVERSION;
                result = (HINSTANCE)WinExec(T2A(key),showcmd);
            }
        }
    }
    return result;
}

void CHyperLink::vSetURL(TCHAR *_szURL)
{
#ifdef _UNICODE
	wcscpy_s(m_strURL, _countof(m_strURL), _szURL);
#else
	strcpy_s(m_strURL, _countof(m_strURL), _szURL);
#endif
}

LRESULT CHyperLink::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//return CStatic::OnNcHitTest(point);
	return HTCLIENT;
}
