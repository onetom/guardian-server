// CPUInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoInc.h"
#include "SystemInfo.h"
#include "CPUInfoDlg.h"


// CCPUInfoDlg dialog

IMPLEMENT_DYNAMIC(CCPUInfoDlg, CPropertyPage)

CCPUInfoDlg::CCPUInfoDlg()
	: CPropertyPage(CCPUInfoDlg::IDD)
{

}

CCPUInfoDlg::~CCPUInfoDlg()
{
}

void CCPUInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CPUSEL, m_ComboCPUSelection);
}


BEGIN_MESSAGE_MAP(CCPUInfoDlg, CPropertyPage)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_CPUSEL, &CCPUInfoDlg::OnCbnSelchangeComboCpusel)
	ON_CBN_DROPDOWN(IDC_COMBO_CPUSEL, &CCPUInfoDlg::OnCbnDropdownComboCpusel)
END_MESSAGE_MAP()


// CCPUInfoDlg message handlers

BOOL CCPUInfoDlg::OnInitDialog()
{
	TCHAR buffer[256];
	int i;

	CPropertyPage::OnInitDialog();

	GetDlgItem(IDC_STATIC_CPU_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_CPU_NAMESTRING)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_CPU_CODENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TDP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_PACKAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_CORE_VOLTAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_CORE_STEPPING)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_PROCESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_CPU_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_CLOCK_MUL)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_FSB_FREQ)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_BUS_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_CPU_L1_D_SIZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_CPU_L1_I_SIZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_L2_SIZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_L3_SIZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_CPU_NBCORES)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_CPU_NBTHREADS)->EnableWindow(FALSE);

	m_ProcessorLogoBitmap.DeleteObject();
	m_bTransparentLogo = FALSE;

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return FALSE;

	for ( i=0; i<pSDK->GetNumberOfProcessors(); i++ )
	{
		SPRINTF(buffer, _countof(buffer), _T("Processor #%d"), i+1);
		m_ComboCPUSelection.AddString(buffer);
	}

	m_ComboCPUSelection.SetCurSel(0);

	if (pSDK->GetNumberOfProcessors() < 2)
	{
		GetDlgItem(IDC_COMBO_CPUSEL)->EnableWindow(FALSE);
	}

	m_iProcessorLogoWidth = 65;
	m_iProcessorLogoHeight = 81;

	int value = pSDK->GetProcessorID(0);
	switch (pSDK->GetProcessorID(0))
	{

///////////////////////////////////////////////////////////////
//	Intel
		case CPU_INTEL:
		case CPU_INTEL_386:
		case CPU_INTEL_486:
		case CPU_INTEL_P5:
		case CPU_INTEL_P6:
		case CPU_INTEL_NETBURST:
		case CPU_INTEL_MOBILE:
		case CPU_INTEL_CORE:
		case CPU_INTEL_CORE_2:
		case CPU_INTEL_NEHALEM:
		case CPU_INTEL_SANDY_BRIDGE:
		case CPU_INTEL_HASWELL:
		case CPU_INTEL_SALTWELL:
		case CPU_INTEL_SILVERMONT:
		case CPU_INTEL_GOLDMONT:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P1);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_MMX:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P1MMX);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_PRO:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_PPRO);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_2:
		case CPU_PENTIUM_2_M:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P2);
			break;

		case CPU_PENTIUM_3:
		case CPU_PENTIUM_3_S:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P3);
			break;

		case CPU_PENTIUM_3_M:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P3_M);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_M:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_PENTIUM_M);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_4:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P4);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_4_EE:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P4_EE);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_4_HT:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P4_HT);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_4_M:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_P4_M);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_D:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_PENTIUM_D);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_PENTIUM_XE:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_PENTIUM_XE);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_XEON_P2:
		case CPU_XEON_P3:
		case CPU_XEON_P4:
		case CPU_CORE_2_XEON:
		case CPU_NEHALEM_XEON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_XEON);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CELERON_D:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CELERON_D);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CELERON_M:
		case CPU_CORE_CELERON_M:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CELERON_M);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CELERON_P2:
		case CPU_CELERON_P3:
		case CPU_CELERON_P4:
		case CPU_CORE_CELERON:
		case CPU_CORE_2_CELERON:
		case CPU_CORE_2_CELERON_DC:
		case CPU_NEHALEM_CELERON:
		case CPU_SANDY_BRIDGE_CELERON:
		case CPU_HASWELL_CELERON:		
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CELERON);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CORE_DUO:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CORE_DUO);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CORE_SOLO:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CORE_SOLO);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CORE_2_DUO:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CORE2_DUO);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CORE_2_SOLO:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CORE2_SOLO);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CORE_2_QUAD:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CORE2_QUAD);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CORE_2_PENTIUM:
		case CPU_NEHALEM_PENTIUM:
		case CPU_SANDY_BRIDGE_PENTIUM:		
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_PENTIUM);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_CORE_2_EE:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CORE2_EE);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_INTEL_ITANIUM:
		case CPU_INTEL_ITANIUM_2:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_ITANIUM);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_BONNELL_ATOM:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_ATOM);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SALTWELL_ATOM:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_ATOM_V2);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SILVERMONT_ATOM:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_ATOM_V4);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_NEHALEM_CORE_I3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI3);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_NEHALEM_CORE_I5:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI5);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_NEHALEM_CORE_I7:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI7);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_NEHALEM_CORE_I7E:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI7_EE);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SANDY_BRIDGE_CORE_I7:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI7_V2);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SANDY_BRIDGE_CORE_I7E:
		case CPU_HASWELL_CORE_I7E:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI7XE_V2);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SANDY_BRIDGE_CORE_I5:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI5_V2);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SANDY_BRIDGE_CORE_I3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI3_V2);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SANDY_BRIDGE_XEON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_XEON_V2);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_HASWELL_CORE_I7:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI7_V4);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_HASWELL_CORE_I5:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI5_V4);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_HASWELL_CORE_I3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_COREI3_V4);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_HASWELL_XEON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_XEON_V4);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SILVERMONT_CELERON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_CELERON_V4);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_SILVERMONT_PENTIUM:
		case CPU_HASWELL_PENTIUM:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_INTEL_PENTIUM_V4);
			m_bTransparentLogo = TRUE;
			break;

///////////////////////////////////////////////////////////////
//	AMD
		case CPU_AMD:
		case CPU_AMD_386:
		case CPU_AMD_486:
		case CPU_AMD_K5:
		case CPU_AMD_K6:
		case CPU_AMD_K7:
		case CPU_AMD_K8:
		case CPU_K5:
		case CPU_K5_GEODE:
		case CPU_AMD_K10:
		case CPU_AMD_K15:
		case CPU_AMD_K16:
		case CPU_K15_A8T:
		case CPU_K15_A6T:
		case CPU_K15_A4T:		
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD);
			break;

		case CPU_AMD_K12:
		case CPU_AMD_K14:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_VISION);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K6:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K6);
			break;

		case CPU_K6_2:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K6_2);
			break;

		case CPU_K6_3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K6_3);
			break;

		case CPU_K7_ATHLON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON);
			break;

		case CPU_K7_ATHLON_XP:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON_XP);
			break;

		case CPU_K7_ATHLON_MP:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON_MP);
			break;

		case CPU_K8_ATHLON_64:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON64);
			break;

		case CPU_K8_ATHLON_64_M:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON64_M);
			break;

		case CPU_K8_ATHLON_64_FX:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON64_FX);
			break;

		case CPU_K8_OPTERON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_OPTERON);
			break;

		case CPU_K7_DURON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_DURON);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K7_SEMPRON:
		case CPU_K8_SEMPRON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_SEMPRON);
			break;

		case CPU_K10_SEMPRON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_SEMPRON_K10);
			break;

		case CPU_K7_SEMPRON_M:
		case CPU_K8_SEMPRON_M:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_SEMPRON_M);
			break;

		case CPU_K8_TURION_64:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_TURION64);
			break;

		case CPU_K8_TURION_64_X2:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_TURION64_X2);
			break;

		case CPU_K8_ATHLON_NEO:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON_NEO);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K8_ATHLON_64_X2:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON64_X2);
			break;

		case CPU_K10_ATHLON_64:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON_K10);
			break;

		case CPU_K10_OPTERON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_OPTERON_K10);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_PHENOM:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_PHENOM);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_PHENOM_X3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_PHENOM_X3);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_PHENOM_II:
		case CPU_K10_PHENOM_II_X3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_PHENOM2);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_PHENOM_II_X2:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_PHENOM2_X2);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_PHENOM_II_X4:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_PHENOM2_X4);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_PHENOM_II_X6:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_PHENOM2_X6);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_ATHLON_2_X2:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON2_X2);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_ATHLON_2:
		case CPU_K10_ATHLON_2_X4:
		case CPU_K10_ATHLON_2_X3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON2);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_PHENOM_FX:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_PHENOM_FX);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_TURION_64:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_TURION64_K10);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K10_TURION_64_ULTRA:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_TURION64_ULTRA);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_A10T:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K15_A10T);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_A10R:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K15_A10R);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_A8R:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K15_A8R);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_ATHLON_X4:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_ATHLON_X4_K15);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_FXB:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K15_FXB);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_FXV:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K15_FXV);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_OPTERON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K15_OPTERON);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_A6R:
		case CPU_K16_A6:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K16_A6K);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K15_A4R:
		case CPU_K16_A4:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K16_A4K);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K16_OPTERON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K16_OPTERON);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K16_ATHLON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K16_ATHLON);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_K16_SEMPRON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_AMD_K16_SEMPRON);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

///////////////////////////////////////////////////////////////
//	VIA
		case CPU_VIA:			
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA);
			m_bTransparentLogo = FALSE;
			break;

		case CPU_VIA_WINCHIP:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_WINCHIP);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_VIA_C3:
		case CPU_C3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_C3);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_VIA_C7:
		case CPU_C7:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_C7);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_C7_M:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_C7_M);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_C7_D:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_C7_D);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_EDEN:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_EDEN);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_VIA_NANO:
		case CPU_NANO_X3:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_NANO);
			m_bTransparentLogo = FALSE;
			break;

		case CPU_NANO_X2:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_NANO_X2);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

		case CPU_EDEN_X2:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_EDEN_X2);
			m_bTransparentLogo = TRUE;
			break;

		case CPU_QUADCORE:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_VIA_QUADCORE);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

///////////////////////////////////////////////////////////////
//	Cyrix
		case CPU_CYRIX:
		case CPU_CYRIX_6X86:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_CYRIX);
			break;

///////////////////////////////////////////////////////////////
//	Transmeta
		case CPU_EFFICEON:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_TRANSMETA_EFFICEON);
			m_iProcessorLogoWidth = 93;
			m_iProcessorLogoHeight = 70;
			m_bTransparentLogo = TRUE;
			break;

///////////////////////////////////////////////////////////////
//	Others
		case CPU_UNKNOWN:
		default:
			m_ProcessorLogoBitmap.LoadBitmap(IDB_EMPTY);
			m_bTransparentLogo = TRUE;
			break;
	}
	if (m_bTransparentLogo)
		theApp.PrepareMask(&m_ProcessorLogoBitmap, &m_bmpMask, NULL, 0, 0);

	vRefreshGUI();
	SetTimer(0, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCPUInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
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

void CCPUInfoDlg::vRefreshGUI()
{
	TCHAR				buffer[512];
	char				szBuffer[512];
	int					proc_id, core_id, dummy;
	float				fValue;

	proc_id = m_ComboCPUSelection.GetCurSel();
	core_id = theApp.m_iCoreID;

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return;

//	Number of cores
	GetDlgItem(IDC_STATIC_CPU_NBCORES)->EnableWindow(TRUE);

	if (core_id < 0)
		core_id = 0;

	if (pSDK->GetProcessorCoreCount(proc_id) > 0)
	{
		if (core_id > (pSDK->GetProcessorCoreCount(proc_id) - 1))
			core_id = pSDK->GetProcessorCoreCount(proc_id) - 1;

		SPRINTF(buffer, _countof(buffer), _T("%d"), pSDK->GetProcessorCoreCount(proc_id));
		GetDlgItem(IDC_CPU1_NBCORES)->SetWindowText(buffer);
	}

//	Number of threads
	if (pSDK->GetProcessorThreadCount(proc_id) > 0)
	{
		GetDlgItem(IDC_STATIC_CPU_NBTHREADS)->EnableWindow(TRUE);
		SPRINTF(buffer, _countof(buffer), _T("%d"), pSDK->GetProcessorThreadCount(proc_id));
		GetDlgItem(IDC_CPU1_NBTHREADS)->SetWindowText(buffer);
	}

//	Caches
	int max_level = pSDK->GetProcessorMaxCacheLevel(proc_id);
	if (IS_I_DEFINED(max_level))
	{
		int NbCaches, CacheSize;
		int	linesize, associativity;

		if (max_level >= 1)
		{
		//	Data L1
			pSDK->GetProcessorCacheParameters(proc_id, 1, CACHE_TYPE_DATA, &NbCaches, &CacheSize);
			if (CacheSize > 0)
			{
				if (NbCaches > 1)
					SPRINTF(buffer, _countof(buffer), _T("%d x %d KBytes"), NbCaches, CacheSize);
				else
					SPRINTF(buffer, _countof(buffer), _T("%d KBytes"), CacheSize);

				GetDlgItem(IDC_STATIC_CPU_L1_D_SIZE)->EnableWindow(TRUE);
				GetDlgItem(IDC_CPU1_L1_D_SIZE)->SetWindowText(buffer);

				SPRINTF(buffer, _countof(buffer), _T(""));
				pSDK->GetProcessorExtendedCacheParameters(proc_id, 1, CACHE_TYPE_DATA, &associativity, &linesize);
				if (associativity > 0)
				{
					switch (associativity)
					{
						case CACHE_ASSOCIATIVITY_DIRECT_MAPPED:
							SPRINTF(buffer, _countof(buffer), _T("direct"));
							break;

						case CACHE_ASSOCIATIVITY_FULLY:
							SPRINTF(buffer, _countof(buffer), _T("fully"));
							break;

						default:
							{
								if (IS_I_DEFINED(associativity))
									SPRINTF(buffer, _countof(buffer), _T("%d-way"), associativity);
							}
							break;
					}
				}
				GetDlgItem(IDC_CPU1_L1_D_ASSO)->SetWindowText(buffer);
			}

		//	Instruction L1
			pSDK->GetProcessorCacheParameters(proc_id, 1, CACHE_TYPE_INSTRUCTION, &NbCaches, &CacheSize);
			if (CacheSize > 0)
			{
				if (NbCaches > 1)
					SPRINTF(buffer, _countof(buffer), _T("%d x %d KBytes"), NbCaches, CacheSize);
				else
					SPRINTF(buffer, _countof(buffer), _T("%d KBytes"), CacheSize);

				GetDlgItem(IDC_STATIC_CPU_L1_I_SIZE)->EnableWindow(TRUE);
				GetDlgItem(IDC_CPU1_L1_I_SIZE)->SetWindowText(buffer);

				SPRINTF(buffer, _countof(buffer), _T(""));
				pSDK->GetProcessorExtendedCacheParameters(proc_id, 1, CACHE_TYPE_INSTRUCTION, &associativity, &linesize);
				if (associativity > 0)
				{
					switch (associativity)
					{
						case CACHE_ASSOCIATIVITY_DIRECT_MAPPED:
							SPRINTF(buffer, _countof(buffer), _T("direct"));
							break;

						case CACHE_ASSOCIATIVITY_FULLY:
							SPRINTF(buffer, _countof(buffer), _T("fully"));
							break;

						default:
							{
								if (IS_I_DEFINED(associativity))
									SPRINTF(buffer, _countof(buffer), _T("%d-way"), associativity);
							}
							break;
					}
				}
				GetDlgItem(IDC_CPU1_L1_I_ASSO)->SetWindowText(buffer);
			}
			else
			{
			//	Trace cache
				pSDK->GetProcessorCacheParameters(proc_id, 1, CACHE_TYPE_TRACE_CACHE, &NbCaches, &CacheSize);
				if (CacheSize > 0)
				{
					if (NbCaches > 1)
						SPRINTF(buffer, _countof(buffer), _T("%d x %d Kuops"), NbCaches, CacheSize);
					else
						SPRINTF(buffer, _countof(buffer), _T("%d Kuops"), CacheSize);

					SetDlgItemText(IDC_STATIC_CPU_L1_I_SIZE, _T("L1 Trace"));
					GetDlgItem(IDC_STATIC_CPU_L1_I_SIZE)->EnableWindow(TRUE);
					GetDlgItem(IDC_CPU1_L1_I_SIZE)->SetWindowText(buffer);

					SPRINTF(buffer, _countof(buffer), _T(""));
					pSDK->GetProcessorExtendedCacheParameters(proc_id, 1, CACHE_TYPE_INSTRUCTION, &associativity, &linesize);
					if (associativity > 0)
					{
						SPRINTF(buffer, _countof(buffer), _T("%d-way"), associativity);
					}
					GetDlgItem(IDC_CPU1_L1_I_ASSO)->SetWindowText(buffer);
				}
			}
		}

	//	L2 Cache
		if (max_level >= 2)
		{
			pSDK->GetProcessorCacheParameters(proc_id, 2, CACHE_TYPE_UNIFIED, &NbCaches, &CacheSize);
			if (CacheSize > 0)
			{
				if (NbCaches > 1)
					SPRINTF(buffer, _countof(buffer), _T("%d x %d KBytes"), NbCaches, CacheSize);
				else
					SPRINTF(buffer, _countof(buffer), _T("%d KBytes"), CacheSize);

				GetDlgItem(IDC_STATIC_L2_SIZE)->EnableWindow(TRUE);
				GetDlgItem(IDC_CPU1_L2_SIZE)->SetWindowText(buffer);

				SPRINTF(buffer, _countof(buffer), _T(""));
				pSDK->GetProcessorExtendedCacheParameters(proc_id, 2, CACHE_TYPE_UNIFIED, &associativity, &linesize);
				if (associativity > 0)
				{
					switch (associativity)
					{
						case CACHE_ASSOCIATIVITY_DIRECT_MAPPED:
							SPRINTF(buffer, _countof(buffer), _T("direct"));
							break;

						case CACHE_ASSOCIATIVITY_FULLY:
							SPRINTF(buffer, _countof(buffer), _T("fully"));
							break;

						default:
							{
								if (IS_I_DEFINED(associativity))
									SPRINTF(buffer, _countof(buffer), _T("%d-way"), associativity);
							}
							break;
					}
				}
				GetDlgItem(IDC_CPU1_L2_ASSO)->SetWindowText(buffer);
			}
			else
			{
				int size_L2 = 0;
				pSDK->GetProcessorCacheParameters(proc_id, 2, CACHE_TYPE_INSTRUCTION, &NbCaches, &CacheSize);
				if (CacheSize > 0)
				{
					size_L2 += CacheSize;
				}
				pSDK->GetProcessorCacheParameters(proc_id, 2, CACHE_TYPE_DATA, &NbCaches, &CacheSize);
				if (CacheSize > 0)
				{
					size_L2 += CacheSize;

					if (NbCaches > 1)
						SPRINTF(buffer, _countof(buffer), _T("%d x %d KBytes"), NbCaches, size_L2);
					else
						SPRINTF(buffer, _countof(buffer), _T("%d KBytes"), size_L2);

					GetDlgItem(IDC_STATIC_L2_SIZE)->EnableWindow(TRUE);
					GetDlgItem(IDC_CPU1_L2_SIZE)->SetWindowText(buffer);
				}
			}
		}

	//	L3 Cache
		if (max_level >= 3)
		{
			pSDK->GetProcessorCacheParameters(proc_id, 3, CACHE_TYPE_UNIFIED, &NbCaches, &CacheSize);
			if (CacheSize > 0)
			{
				if (NbCaches > 1)
					SPRINTF(buffer, _countof(buffer), _T("%d x %d KBytes"), NbCaches, CacheSize);
				else
					SPRINTF(buffer, _countof(buffer), _T("%d KBytes"), CacheSize);

				GetDlgItem(IDC_STATIC_L3_SIZE)->EnableWindow(TRUE);
				GetDlgItem(IDC_CPU1_L3_SIZE)->SetWindowText(buffer);

				SPRINTF(buffer, _countof(buffer), _T(""));
				pSDK->GetProcessorExtendedCacheParameters(proc_id, 3, CACHE_TYPE_UNIFIED, &associativity, &linesize);
				if (associativity > 0)
				{
					switch (associativity)
					{
						case CACHE_ASSOCIATIVITY_DIRECT_MAPPED:
							SPRINTF(buffer, _countof(buffer), _T("direct"));
							break;

						case CACHE_ASSOCIATIVITY_FULLY:
							SPRINTF(buffer, _countof(buffer), _T("fully"));
							break;

						default:
							{
								if (IS_I_DEFINED(associativity))
									SPRINTF(buffer, _countof(buffer), _T("%d-way"), associativity);
							}
							break;
					}
				}
				GetDlgItem(IDC_CPU1_L3_ASSO)->SetWindowText(buffer);
			}
		}
	}

//	Processor name
	if (pSDK->GetProcessorName(proc_id, szBuffer))
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
		GetDlgItem(IDC_CPU1_NAME)->SetWindowText(szTemp);
	}

//	Specification
	if (pSDK->GetProcessorSpecification(proc_id, szBuffer))
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
		GetDlgItem(IDC_CPU1_NAMESTRING)->SetWindowText(szTemp);
	}

//	Family
	if (IS_I_DEFINED(pSDK->GetProcessorFamily(proc_id)))
	{	
		SPRINTF(buffer, _countof(buffer), _T("%X"), pSDK->GetProcessorFamily(proc_id));
		GetDlgItem(IDC_CPU1_FAMILY)->SetWindowText(buffer);
	}
//	Model
	if (IS_I_DEFINED(pSDK->GetProcessorModel(proc_id)))
	{
		SPRINTF(buffer, _countof(buffer), _T("%X"), pSDK->GetProcessorModel(proc_id));
		GetDlgItem(IDC_CPU1_MODEL)->SetWindowText(buffer);
	}
//	Stepping
	if (IS_I_DEFINED(pSDK->GetProcessorSteppingID(proc_id)))
	{
		SPRINTF(buffer, _countof(buffer), _T("%X"), pSDK->GetProcessorSteppingID(proc_id));
		GetDlgItem(IDC_CPU1_STEPPING)->SetWindowText(buffer);
	}
//	Extended family
	if (IS_I_DEFINED(pSDK->GetProcessorExtendedFamily(proc_id)))
	{
		SPRINTF(buffer, _countof(buffer), _T("%X"), pSDK->GetProcessorExtendedFamily(proc_id));
		GetDlgItem(IDC_CPU1_EXTFAMILY)->SetWindowText(buffer);
	}
//	Extended model
	if (IS_I_DEFINED(pSDK->GetProcessorExtendedModel(proc_id)))
	{
		SPRINTF(buffer, _countof(buffer), _T("%X"), pSDK->GetProcessorExtendedModel(proc_id));
		GetDlgItem(IDC_CPU1_EXTMODEL)->SetWindowText(buffer);
	}

//	TDP
	if (IS_F_DEFINED(pSDK->GetProcessorTDP(proc_id)))
	{
		GetDlgItem(IDC_STATIC_TDP)->EnableWindow(TRUE);
		SPRINTF(buffer, _countof(buffer), _T("%.1f W"), pSDK->GetProcessorTDP(proc_id));
		GetDlgItem(IDC_CPU1_TDP)->SetWindowText(buffer);
	}

//	Instructions set
	SPRINTF(buffer, _countof(buffer), _T(" "));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_MMX)?_T("MMX"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_EXTENDED_MMX)?_T(" (+)"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_3DNOW)?_T(", 3DNow!"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_EXTENDED_3DNOW)?_T(" (+)"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE)?_T(", SSE"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE2)?_T(", SSE2"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE3)?_T(", SSE3"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSSE3)?_T(", SSSE3"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE4_1)?_T(", SSE4.1"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE4_2)?_T(", SSE4.2"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE4A)?_T(", SSE4A"):_T(""));

	if (pSDK->GetProcessorID(proc_id) & CPU_INTEL)
		STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_X86_64)?_T(", EM64T"):_T(""));
	else
		STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_X86_64)?_T(", x86-64"):_T(""));

	if ((pSDK->GetProcessorID(proc_id) & CPU_INTEL) || (pSDK->GetProcessorID(proc_id) & CPU_VIA))
		STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_VMX)?_T(", VT-x"):_T(""));
	else
		STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_VMX)?_T(", AMD-V"):_T(""));

	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_AES)?_T(", AES"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_AVX)?_T(", AVX"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_AVX2)?_T(", AVX2"):_T(""));	
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_AVX512F)?_T(", AVX512F"):_T(""));	
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_XOP)?_T(", XOP"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_FMA3)?_T(", FMA3"):_T(""));
	STRCAT(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_FMA4)?_T(", FMA4"):_T(""));

	if (pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_RTM) &&
		pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_HLE))
	{
		STRCAT(buffer, _countof(buffer), _T(", TSX"));
	}
	else if (pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_RTM))
	{
		STRCAT(buffer, _countof(buffer), _T(", RTM"));
	}
	else if (pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_HLE))
	{
		STRCAT(buffer, _countof(buffer), _T(", HLE"));
	}

	GetDlgItem(IDC_CPU1_ISET)->SetWindowText(buffer);

//	Code name
	if (pSDK->GetProcessorCodeName(proc_id, szBuffer))
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
		GetDlgItem(IDC_STATIC_CPU_CODENAME)->EnableWindow(TRUE);		
		GetDlgItem(IDC_CPU1_VENDOR)->SetWindowText(szTemp);
	}

//	Package
	if (pSDK->GetProcessorPackage(proc_id, szBuffer))
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
		GetDlgItem(IDC_STATIC_PACKAGE)->EnableWindow(TRUE);		
		GetDlgItem(IDC_CPU1_PACKAGE)->SetWindowText(szTemp);
	}

//	Process
	float fProcess = pSDK->GetProcessorManufacturingProcess(proc_id);
	if (IS_F_DEFINED(fProcess))
	{
		GetDlgItem(IDC_STATIC_PROCESS)->EnableWindow(TRUE);
		if (fProcess < 0.10f)
		{
			float fVal = fProcess * 1000.0f;
			SPRINTF(buffer, _countof(buffer), _T("%d nm"), (int)fVal);
		}
		else
		{
			SPRINTF(buffer, _countof(buffer), _T("%1.2f um"), fProcess);
		}
		GetDlgItem(IDC_CPU1_PROCESS)->SetWindowText(buffer);
	}
	else
	{
		GetDlgItem(IDC_STATIC_PROCESS)->EnableWindow(FALSE);
	}

//	Core version
	if (pSDK->GetProcessorStepping(proc_id, szBuffer))
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
		GetDlgItem(IDC_STATIC_CORE_STEPPING)->EnableWindow(TRUE);		
		GetDlgItem(IDC_CPU1_CORE_STEPPING)->SetWindowText(szTemp);
	}

//	Clocks
	SPRINTF(buffer, _countof(buffer), _T("Clocks (Core #%d)"), core_id);
	SetDlgItemText(IDC_STATIC_GROUP_CLOCKS, buffer);

	fValue = pSDK->GetProcessorCoreClockFrequency(proc_id, core_id);
	if (IS_F_DEFINED(fValue))
	{
		GetDlgItem(IDC_STATIC_CPU_SPEED)->EnableWindow(TRUE);
		SPRINTF(buffer, _countof(buffer), _T("%.1f MHz"), fValue);			
		GetDlgItem(IDC_CPU1_CLOCK)->SetWindowText(buffer);
	}

	fValue = pSDK->GetProcessorCoreClockMultiplier(proc_id, core_id);
	if (IS_F_DEFINED(fValue))
	{
		GetDlgItem(IDC_STATIC_CLOCK_MUL)->EnableWindow(TRUE);
		int coeff = (int)(100.0f * fValue);
		if (coeff % 10)
			SPRINTF(buffer, _countof(buffer), _T("x %.2f"), fValue);
		else
			SPRINTF(buffer, _countof(buffer), _T("x %.1f"), fValue);

		GetDlgItem(IDC_CPU1_CLOCK_MULTIPLIER)->SetWindowText(buffer);
	}

//	Base freq + link
	fValue = pSDK->GetBusFrequency();
	if (IS_F_DEFINED(fValue))
	{
		GetDlgItem(IDC_STATIC_FSB_FREQ)->EnableWindow(TRUE);
		SPRINTF(buffer, _countof(buffer), _T("%.1f MHz"), fValue);
		GetDlgItem(IDC_CPU1_FSB_FREQUENCY)->SetWindowText(buffer);
	}

	fValue = pSDK->GetProcessorRatedBusFrequency(proc_id);
	if (IS_F_DEFINED(fValue))
	{
		unsigned int cpu_family = pSDK->GetProcessorID(proc_id) & CPU_FAMILY_MASK;
		if ((cpu_family == CPU_AMD_K8) || 
			(cpu_family == CPU_AMD_K10))
		{
			GetDlgItem(IDC_STATIC_BUS_SPEED)->SetWindowText(_T("HT Link"));
		}
		if (cpu_family == CPU_INTEL_NEHALEM)
		{
			GetDlgItem(IDC_STATIC_BUS_SPEED)->SetWindowText(_T("QPI Link"));
		}

		GetDlgItem(IDC_STATIC_BUS_SPEED)->EnableWindow(TRUE);
		SPRINTF(buffer, _countof(buffer), _T("%.1f MHz"), fValue);
		GetDlgItem(IDC_CPU1_BUS_FREQUENCY)->SetWindowText(buffer);
	}

//	Core voltage
	fValue = pSDK->GetSensorTypeValue(SENSOR_VOLTAGE_VCORE_CPU0, &dummy, &dummy);
	if (IS_F_DEFINED(fValue))
	{
		SPRINTF(buffer, _countof(buffer), _T("%.3f V"), fValue);
		GetDlgItem(IDC_STATIC_CORE_VOLTAGE)->EnableWindow(TRUE);	
		GetDlgItem(IDC_STATIC_CORE_VOLTAGE)->SetWindowText(_T("Core Voltage"));
		GetDlgItem(IDC_CPU1_CORE_VOLTAGE)->SetWindowText(buffer);
	}

//	HDDs
	{
		unsigned char data[6];
		int i, j, id, flags, value, worst;
		BOOL result;

		for ( i=0; i<pSDK->GetNumberOfHDD(); i++ )
		{
			result = pSDK->GetHDDName(i, szBuffer);
			result = pSDK->GetHDDSerialNumber(i, szBuffer);

			for ( j=0; j<pSDK->GetHDDNumberOfAttributes(i); j++ )
			{
				result = pSDK->GetHDDAttribute(i, j, &id, &flags, &value, &worst, data);
				int debug = 0;
			}
		}
	}
}

void CCPUInfoDlg::OnDestroy()
{
	CPropertyPage::OnDestroy();

	m_ProcessorLogoBitmap.DeleteObject();
}

void CCPUInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CDC DCMem;

	DCMem.CreateCompatibleDC(&dc);
	CBitmap *hbmT = DCMem.SelectObject(&m_ProcessorLogoBitmap);

	RECT logorect; 
	GetDlgItem(IDC_CPU_LOGO)->GetWindowRect(&logorect);
	ScreenToClient(&logorect);

	//int X = logorect.left;
	int X = logorect.right - (m_iProcessorLogoWidth / 2);	
	int Y = logorect.bottom - (m_iProcessorLogoHeight / 2);

	if (m_bTransparentLogo)
		theApp.DrawTransparentBitmap(&dc, &m_bmpMask, X, Y, m_iProcessorLogoWidth, m_iProcessorLogoHeight, &DCMem, 0, 0);
	else
		dc.BitBlt(X, Y, m_iProcessorLogoWidth, m_iProcessorLogoHeight, &DCMem, 0, 0, SRCCOPY);

	DCMem.SelectObject(hbmT);
	DCMem.DeleteDC();

	// Do not call CPropertyPage::OnPaint() for painting messages
}

void CCPUInfoDlg::OnCbnSelchangeComboCpusel()
{
	vRefreshGUI();
}

void CCPUInfoDlg::OnCbnDropdownComboCpusel()
{
    int nNumEntries = m_ComboCPUSelection.GetCount();
    int nWidth = 0;
    CString str;

    CClientDC dc(&m_ComboCPUSelection);
    int nSave = dc.SaveDC();
    dc.SelectObject(m_ComboCPUSelection.GetFont());

    int nScrollWidth = ::GetSystemMetrics(SM_CXVSCROLL);

    for ( int i=0; i<nNumEntries; i++ )
    {
        m_ComboCPUSelection.GetLBText(i, str);
        int nLength = dc.GetTextExtent(str).cx + nScrollWidth;
        nWidth = max(nWidth, nLength);
    }
    
    // Add margin space to the calculations
    nWidth += dc.GetTextExtent(_T("0")).cx;

    dc.RestoreDC(nSave);
    m_ComboCPUSelection.SetDroppedWidth(nWidth);		
}
