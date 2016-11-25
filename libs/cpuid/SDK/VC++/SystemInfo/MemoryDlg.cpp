// MemoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoInc.h"
#include "SystemInfo.h"
#include "MemoryDlg.h"


// CMemoryDlg dialog

IMPLEMENT_DYNAMIC(CMemoryDlg, CPropertyPage)

CMemoryDlg::CMemoryDlg()
	: CPropertyPage(CMemoryDlg::IDD)
{

}

CMemoryDlg::~CMemoryDlg()
{
}

void CMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMemoryDlg, CPropertyPage)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMemoryDlg message handlers

BOOL CMemoryDlg::OnInitDialog()
{
	TCHAR Tbuffer[512];

	CPropertyPage::OnInitDialog();

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return FALSE;

//	RAM size
	if (IS_I_DEFINED(pSDK->GetMemorySize()))
	{
		GetDlgItem(IDC_STATIC_RAM_SIZE)->EnableWindow(TRUE);
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d MBytes"), pSDK->GetMemorySize());
		GetDlgItem(IDC_RAM_SIZE)->SetWindowText(Tbuffer);
	}

//	Ram type
	switch (pSDK->GetMemoryType())
	{
		case FPM_RAM:			SPRINTF(Tbuffer, _countof(Tbuffer), _T(" FPG")); break;
		case EDO_RAM:			SPRINTF(Tbuffer, _countof(Tbuffer), _T(" EDO")); break;
		case SDRAM:				SPRINTF(Tbuffer, _countof(Tbuffer), _T(" SDRAM")); break;
		case RDRAM:				SPRINTF(Tbuffer, _countof(Tbuffer), _T(" RDRAM")); break;
		case DDR_SDRAM:			SPRINTF(Tbuffer, _countof(Tbuffer), _T(" DDR")); break;
		case DDR2_SDRAM:		SPRINTF(Tbuffer, _countof(Tbuffer), _T(" DDR2")); break;
		case DDR2_SDRAM_FB: 	SPRINTF(Tbuffer, _countof(Tbuffer), _T(" FB-DDR2")); break;
		case DDR3_SDRAM:		SPRINTF(Tbuffer, _countof(Tbuffer), _T(" DDR3")); break;
		case DDR4_SDRAM:		SPRINTF(Tbuffer, _countof(Tbuffer), _T(" DDR4")); break;
		default:				SPRINTF(Tbuffer, _countof(Tbuffer), _T("")); break;
	}	
	GetDlgItem(IDC_RAM_TYPE_2)->SetWindowText(Tbuffer);

//	Channels
	if (pSDK->GetMemoryNumberOfChannels() > 0)
	{
		GetDlgItem(IDC_STATIC_RAM_CHANNELS)->EnableWindow(TRUE);			
		switch (pSDK->GetMemoryNumberOfChannels())
		{
			case 1:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("Single")); break;
			case 2:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("Dual")); break;
			case 3:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("Triple")); break;
			case 4:		SPRINTF(Tbuffer, _countof(Tbuffer), _T("Quad")); break;
			default:	SPRINTF(Tbuffer, _countof(Tbuffer), _T("")); break;
		}
		GetDlgItem(IDC_RAM_CHANNELS)->SetWindowText(Tbuffer);
	}

//	DMI
	{
		char buffer[512];
		char location[128], usage[128], 
			 correction[128], format[128],
			 designation[128], type[128];
		int size, speed, total_width, data_width;
		BOOL result;

		result = pSDK->GetBIOSVendor(buffer);
		result = pSDK->GetBIOSDate(buffer);
		result = pSDK->GetBIOSType(buffer);

		int value = pSDK->GetBIOSROMSize();

		result = pSDK->GetMainboardVendor(buffer);
		result = pSDK->GetMainboardModel(buffer);
		result = pSDK->GetMainboardRevision(buffer);
		result = pSDK->GetMainboardSerialNumber(buffer);

		result = pSDK->GetMemoryInfosExt(location, usage, correction);

		int nbdevices = pSDK->GetNumberOfMemoryDevices();
		for ( int i=0; i<nbdevices; i++ )
		{
			result = pSDK->GetMemoryDeviceInfos(i, &size, format);
			result = pSDK->GetMemoryDeviceInfosExt(i, designation, type, &total_width, &data_width, &speed);
			int debug = 0;
		}
	}

	vRefreshGUI();
	SetTimer(0, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMemoryDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case 0:
			{
				vRefreshGUI();
			}
			break;

		default:
			break;
	}
	CPropertyPage::OnTimer(nIDEvent);
}

void CMemoryDlg::vRefreshGUI()
{
	TCHAR Tbuffer[512];

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return;

//	RAM Frequency
	if (pSDK->GetMemoryClockFrequency() > 0.0f)
	{
		GetDlgItem(IDC_STATIC_RAM_FREQUENCY)->EnableWindow(TRUE);			
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.1f MHz"), pSDK->GetMemoryClockFrequency());			
	}
	else
	{
		GetDlgItem(IDC_STATIC_RAM_FREQUENCY)->EnableWindow(FALSE);
		Tbuffer[0] = 0;
	}
	GetDlgItem(IDC_RAM_FREQUENCY)->SetWindowText(Tbuffer);

//	Timings
	if (pSDK->GetMemoryCASLatency() > 0.0f)
	{
		GetDlgItem(IDC_STATIC_RAM_CAS_L)->EnableWindow(TRUE);			
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%1.1f clocks"), pSDK->GetMemoryCASLatency());
		GetDlgItem(IDC_RAM_CAS_LATENCY)->SetWindowText(Tbuffer);
	}
	else
	{
		GetDlgItem(IDC_STATIC_RAM_CAS_L)->EnableWindow(FALSE);
	}
		
	if (pSDK->GetMemoryRAStoCASDelay() > 0)
	{
		GetDlgItem(IDC_STATIC_RAM_RTOC)->EnableWindow(TRUE);			
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d clocks"), pSDK->GetMemoryRAStoCASDelay());
		GetDlgItem(IDC_RAM_RAS_TO_CAS)->SetWindowText(Tbuffer);
	}
	else
	{
		GetDlgItem(IDC_STATIC_RAM_RTOC)->EnableWindow(FALSE);
	}
		
	if (pSDK->GetMemoryRASPrecharge() > 0)
	{
		GetDlgItem(IDC_STATIC_RAM_RPRE)->EnableWindow(TRUE);			
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d clocks"), pSDK->GetMemoryRASPrecharge());
		GetDlgItem(IDC_RAM_RAS_PRECHARGE)->SetWindowText(Tbuffer);
	}
	else
	{
		GetDlgItem(IDC_STATIC_RAM_RPRE)->EnableWindow(FALSE);
	}
		
	if (pSDK->GetMemoryTRAS() < 0)
	{
		GetDlgItem(IDC_STATIC_RAM_TRAS)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_RAM_TRAS)->EnableWindow(TRUE);			
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d clocks"), pSDK->GetMemoryTRAS());
		GetDlgItem(IDC_RAM_TRAS)->SetWindowText(Tbuffer);
	}
		
	if (pSDK->GetMemoryTRC() < 0)
	{
		GetDlgItem(IDC_STATIC_RAM_TRC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_RAM_TRC)->EnableWindow(TRUE);			
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d clocks"), pSDK->GetMemoryTRC());
		GetDlgItem(IDC_RAM_TRC)->SetWindowText(Tbuffer);
	}
		
	if (!IS_I_DEFINED(pSDK->GetMemoryCommandRate()))
	{
		GetDlgItem(IDC_STATIC_RAM_COMMAND_RATE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_RAM_COMMAND_RATE)->EnableWindow(TRUE);			
		SPRINTF(Tbuffer, _countof(Tbuffer), _T("%dT"), pSDK->GetMemoryCommandRate());
		GetDlgItem(IDC_RAM_COMMAND_RATE)->SetWindowText(Tbuffer);
	}
}