// DisplayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoInc.h"
#include "SystemInfo.h"
#include "DisplayDlg.h"


// CDisplayDlg dialog

IMPLEMENT_DYNAMIC(CDisplayDlg, CPropertyPage)

CDisplayDlg::CDisplayDlg()
	: CPropertyPage(CDisplayDlg::IDD)
{

}

CDisplayDlg::~CDisplayDlg()
{
}

void CDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DISPLAY, m_Combo_DisplayAdapter);
	DDX_Control(pDX, IDC_COMBO_PERFLEVEL, m_Combo_PerfLevel);
}


BEGIN_MESSAGE_MAP(CDisplayDlg, CPropertyPage)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_DISPLAY, &CDisplayDlg::OnCbnSelchangeComboDisplay)
	ON_CBN_SELCHANGE(IDC_COMBO_PERFLEVEL, &CDisplayDlg::OnCbnSelchangeComboPerflevel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDisplayDlg message handlers

BOOL CDisplayDlg::OnInitDialog()
{
	char szBuffer[512];
	int i;

	CPropertyPage::OnInitDialog();

//	Get SDK instance
	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return FALSE;

	int NbAdapters = pSDK->GetNumberOfDisplayAdapter();
	for ( i=0; i<NbAdapters; i++ )
	{
		if (pSDK->GetDisplayAdapterName(i, szBuffer))
		{
		#ifdef _UNICODE
			TCHAR szTemp[512];
			int value = MultiByteToWideChar(CP_ACP,
											MB_PRECOMPOSED,
											szBuffer,
											-1,
											szTemp,
											512);
		#else
			TCHAR *szTemp = szBuffer;
		#endif
			m_Combo_DisplayAdapter.AddString(szTemp);
		}
	}
	m_Combo_DisplayAdapter.SetCurSel(0);
	vUpdateDisplayInfos();

	SetTimer(0, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDisplayDlg::vUpdateDisplayInfos()
{
	TCHAR Tbuffer[64];
	char szBuffer[512];
	float fValue;
	int size, type, bus_width;
	int j;

	int adapter_index = m_Combo_DisplayAdapter.GetCurSel();

	m_Combo_PerfLevel.ResetContent();

//	Get SDK instance
	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return;

	SPRINTF(Tbuffer, _countof(Tbuffer), _T(""));
	GetDlgItem(IDC_GPU_NAME)->SetWindowText(Tbuffer);
	GetDlgItem(IDC_GPU_CODENAME)->SetWindowText(Tbuffer);
	GetDlgItem(IDC_GPU_PROCESS)->SetWindowText(Tbuffer);
	GetDlgItem(IDC_VRAM_SIZE)->SetWindowText(Tbuffer);
	GetDlgItem(IDC_VRAM_TYPE)->SetWindowText(Tbuffer);
	GetDlgItem(IDC_VRAM_BUS_WIDTH)->SetWindowText(Tbuffer);

//	GPU name & codename
	if (pSDK->GetDisplayAdapterName(adapter_index, szBuffer))
	{
	#ifdef _UNICODE
		TCHAR szTemp[512];
		int value = MultiByteToWideChar(CP_ACP,
										MB_PRECOMPOSED,
										szBuffer,
										-1,
										szTemp,
										512);
	#else
		TCHAR *szTemp = szBuffer;
	#endif
		GetDlgItem(IDC_GPU_NAME)->SetWindowText(szTemp);
	}
	if (pSDK->GetDisplayAdapterCodeName(adapter_index, szBuffer))
	{
	#ifdef _UNICODE
		TCHAR szTemp[512];
		int value = MultiByteToWideChar(CP_ACP,
										MB_PRECOMPOSED,
										szBuffer,
										-1,
										szTemp,
										512);
	#else
		TCHAR *szTemp = szBuffer;
	#endif
		GetDlgItem(IDC_GPU_CODENAME)->SetWindowText(szTemp);
	}

//	GPU process
	fValue = pSDK->GetDisplayAdapterManufacturingProcess(adapter_index);
	if (IS_F_DEFINED(fValue))
	{
		if (fValue < 0.10f)
		{
			float fVal = fValue * 1000.0f;
			SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d nm"), (int)fVal);
		}
		else
		{
			SPRINTF(Tbuffer, _countof(Tbuffer), _T("%1.2f um"), fValue);
		}
		GetDlgItem(IDC_GPU_PROCESS)->SetWindowText(Tbuffer);
	}

//	PCI IDs
	int vendor_id, device_id, revision_id, sub_vendor_id, sub_model_id;
	if (pSDK->GetDisplayAdapterPCIID(adapter_index, &vendor_id, &device_id, &revision_id, &sub_vendor_id, &sub_model_id))
	{
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("0x%04X/0x%04X"), vendor_id, device_id);
		GetDlgItem(IDC_GPU_PCI_ID)->SetWindowText(Tbuffer);

		SPRINTF(Tbuffer, _countof(Tbuffer), _T("0x%04X/0x%04X"), sub_vendor_id, sub_model_id);
		GetDlgItem(IDC_GPU_PCI_SUBID)->SetWindowText(Tbuffer);
	}

//	Memory size
	if (pSDK->GetDisplayAdapterMemorySize(adapter_index, &size))
	{
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d MBytes"), size);
		GetDlgItem(IDC_VRAM_SIZE)->SetWindowText(Tbuffer);
	}

//	Memmory type
	if (pSDK->GetDisplayAdapterMemoryType(adapter_index, &type))
	{
		if (IS_I_DEFINED(type))
		{
			switch (type)
			{
				case MEMORY_TYPE_DDR:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("DDR")); break;
				case MEMORY_TYPE_DDR2:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("DDR2")); break;
				case MEMORY_TYPE_DDR3:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("DDR3")); break;
				case MEMORY_TYPE_GDDR3:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("GDDR3")); break;
				case MEMORY_TYPE_GDDR4:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("GDDR4")); break;
				case MEMORY_TYPE_GDDR5:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("GDDR5")); break;
				default:					SPRINTF(Tbuffer, _countof(Tbuffer), _T("0x%X"), type); break;
			}
			GetDlgItem(IDC_VRAM_TYPE)->SetWindowText(Tbuffer);
		}
	}

//	Memory bus width
	if (pSDK->GetDisplayAdapterMemoryBusWidth(adapter_index, &bus_width))
	{
		if (IS_I_DEFINED(bus_width))
		{
			SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d bits"), bus_width);
			GetDlgItem(IDC_VRAM_BUS_WIDTH)->SetWindowText(Tbuffer);
		}
	}

	m_Combo_PerfLevel.EnableWindow(FALSE);
	int NbPerfLevels = pSDK->GetDisplayAdapterNumberOfPerformanceLevels(adapter_index);
	if (NbPerfLevels > 0)
	{
		for ( j=0; j<NbPerfLevels; j++ )
		{
			if (pSDK->GetDisplayAdapterPerformanceLevelName(adapter_index, j, szBuffer))
			{
			#ifdef _UNICODE
				TCHAR szTemp[512];
				int value = MultiByteToWideChar(CP_ACP,
												MB_PRECOMPOSED,
												szBuffer,
												-1,
												szTemp,
												512);
			#else
				TCHAR *szTemp = szBuffer;
			#endif
				m_Combo_PerfLevel.AddString(szTemp);
			}
		}

		int sel = 0;
		if (NbPerfLevels > 1)
		{
			m_Combo_PerfLevel.EnableWindow(TRUE);
			m_Combo_PerfLevel.AddString(_T("Current"));

			int count = m_Combo_PerfLevel.GetCount();
			sel = count - 1;
		}

		m_Combo_PerfLevel.SetCurSel(sel);
		vUpdateDisplayClockInfos();
	}
}

void CDisplayDlg::vUpdateDisplayClockInfos()
{
	TCHAR szBuffer[512];
	float fValue;

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return;

	int adapter_index = m_Combo_DisplayAdapter.GetCurSel();
	int perf_level = 0;

	int NbPerfLevels = pSDK->GetDisplayAdapterNumberOfPerformanceLevels(adapter_index);
	if (NbPerfLevels > 1)
	{
		perf_level = m_Combo_PerfLevel.GetCurSel();
		if (perf_level >= NbPerfLevels)
		{
		//	Set to "current"
			perf_level = -1;
		}
	}

	SPRINTF(szBuffer, _countof(szBuffer), _T(""));
	GetDlgItem(IDC_CORE_CLOCK_CURRENT)->SetWindowText(szBuffer);
	GetDlgItem(IDC_SHADERS_CLOCK_CURRENT)->SetWindowText(szBuffer);
	GetDlgItem(IDC_MEMORY_CLOCK_CURRENT)->SetWindowText(szBuffer);

	fValue = pSDK->GetDisplayAdapterClock(adapter_index, perf_level, DISPLAY_CLOCK_DOMAIN_GRAPHICS);
	if (IS_F_DEFINED(fValue))
	{
		SPRINTF(szBuffer, _countof(szBuffer), _T("%d MHz"), (int)fValue);
		GetDlgItem(IDC_CORE_CLOCK_CURRENT)->SetWindowText(szBuffer);
	}
	fValue = pSDK->GetDisplayAdapterClock(adapter_index, perf_level, DISPLAY_CLOCK_DOMAIN_PROCESSOR);
	if (IS_F_DEFINED(fValue))
	{
		SPRINTF(szBuffer, _countof(szBuffer), _T("%d MHz"), (int)fValue);
		GetDlgItem(IDC_SHADERS_CLOCK_CURRENT)->SetWindowText(szBuffer);
	}
	fValue = pSDK->GetDisplayAdapterClock(adapter_index, perf_level, DISPLAY_CLOCK_DOMAIN_MEMORY);
	if (IS_F_DEFINED(fValue))
	{
		SPRINTF(szBuffer, _countof(szBuffer), _T("%d MHz"), (int)fValue);
		GetDlgItem(IDC_MEMORY_CLOCK_CURRENT)->SetWindowText(szBuffer);
	}
}

void CDisplayDlg::OnCbnSelchangeComboDisplay()
{
	vUpdateDisplayInfos();
}

void CDisplayDlg::OnCbnSelchangeComboPerflevel()
{
	vUpdateDisplayClockInfos();
}

void CDisplayDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case 0:
			{
				vUpdateDisplayClockInfos();
			}
			break;

		default:
			break;
	}
	CPropertyPage::OnTimer(nIDEvent);
}
