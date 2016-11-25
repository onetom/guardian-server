// SPDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoInc.h"
#include "SystemInfo.h"
#include "SPDDlg.h"
#include "math.h"


// CSPDDlg dialog

IMPLEMENT_DYNAMIC(CSPDDlg, CPropertyPage)

CSPDDlg::CSPDDlg()
	: CPropertyPage(CSPDDlg::IDD)
{

}

CSPDDlg::~CSPDDlg()
{
}

void CSPDDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SPD, m_Combo_SPD);
}


BEGIN_MESSAGE_MAP(CSPDDlg, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_SPD, &CSPDDlg::OnCbnSelchangeComboSpd)
END_MESSAGE_MAP()


// CSPDDlg message handlers

BOOL CSPDDlg::OnInitDialog()
{
	TCHAR	caption[64];
	int		i, nbslots;

	CPropertyPage::OnInitDialog();

	CDialog::OnInitDialog();

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return TRUE;

	nbslots = pSDK->GetNumberOfSPDModules();
	if (nbslots > 0)
	{
		GetDlgItem(IDC_COMBO_SPD)->EnableWindow(TRUE);
		for ( i=0; i<nbslots; i++ )
		{
			SPRINTF(caption, _countof(caption), _T("Slot #%d"), i+1);
			m_Combo_SPD.AddString(caption);
		}
		m_Combo_SPD.SetCurSel(0);
		vUpdateSPDInfos(0);
	}
	else
	{
		GetDlgItem(IDC_COMBO_SPD)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MEMORY_GENERAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_RAM_TYPE)->SetWindowText(_T(""));
		vCleanAll();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSPDDlg::vUpdateSPDInfos(int _index)
{
	TCHAR		Tbuffer[512];
	TCHAR		buffer2[512];
	char		buffer[512];
	int			i, j, nb_extended_profiles, profile, revision;

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return;

	vCleanAll();

	if (pSDK->GetNumberOfSPDModules() > 0)
	{
		int host_index, channel, address;
		BOOL result = pSDK->GetSPDModuleAddress(_index, &host_index, &channel, &address);

		switch (pSDK->GetSPDModuleType(_index))
		{
			case SPM_RAM:		SPRINTF(Tbuffer, _countof(Tbuffer), _T(" SPM RAM")); break;
			case RDRAM:			SPRINTF(Tbuffer, _countof(Tbuffer), _T(" RDRAM")); break;
			case EDO_RAM:		SPRINTF(Tbuffer, _countof(Tbuffer), _T(" EDO RAM")); break;
			case FPM_RAM:		SPRINTF(Tbuffer, _countof(Tbuffer), _T(" FPM RAM")); break;
			case SDRAM:			SPRINTF(Tbuffer, _countof(Tbuffer), _T(" SDRAM")); break;
			case DDR_SDRAM:		SPRINTF(Tbuffer, _countof(Tbuffer), _T(" DDR")); break;
			case DDR2_SDRAM:	SPRINTF(Tbuffer, _countof(Tbuffer), _T(" DDR2")); break;
			case DDR2_SDRAM_FB: SPRINTF(Tbuffer, _countof(Tbuffer), _T(" FB-DDR2")); break;
			case DDR3_SDRAM:	SPRINTF(Tbuffer, _countof(Tbuffer), _T(" DDR3")); break;
			case DDR4_SDRAM:	SPRINTF(Tbuffer, _countof(Tbuffer), _T(" DDR4")); break;
			default:			SPRINTF(Tbuffer, _countof(Tbuffer), _T(" unknown")); break;
		}

		if (pSDK->GetSPDModuleFormat(_index, buffer))
		{
			#ifdef _UNICODE
				TCHAR szTemp[512];
				int value = MultiByteToWideChar(CP_ACP,
												MB_PRECOMPOSED,
												buffer,
												-1,
												szTemp,
												512);
			#else
				TCHAR *szTemp = buffer;
			#endif
				STRCAT(Tbuffer, _countof(Tbuffer), _T(" ("));
				STRCAT(Tbuffer, _countof(Tbuffer), szTemp);
				STRCAT(Tbuffer, _countof(Tbuffer), _T(")"));
		}
		GetDlgItem(IDC_RAM_TYPE)->SetWindowText(Tbuffer);

		GetDlgItem(IDC_STATIC_SPD_MANUFACTURER)->EnableWindow(TRUE);
		if (pSDK->GetSPDModuleManufacturer(_index, buffer))
		{
		#ifdef _UNICODE
			TCHAR szTemp[512];
			int value = MultiByteToWideChar(CP_ACP,
											MB_PRECOMPOSED,
											buffer,
											-1,
											szTemp,
											512);
		#else
			TCHAR *szTemp = buffer;
		#endif
			GetDlgItem(IDC_SPD_MANUFACTURER)->SetWindowText(szTemp);

		//	Manufacturer ID
			{
				unsigned char manid[8];

				if (pSDK->GetSPDModuleManufacturerID(_index, manid))
				{
					int debug = 0;
				}
			}
		}

		if (pSDK->GetSPDModuleSpecification(_index, buffer))
		{
		#ifdef _UNICODE
			TCHAR szTemp[512];
			int value = MultiByteToWideChar(CP_ACP,
											MB_PRECOMPOSED,
											buffer,
											-1,
											szTemp,
											512);
		#else
			TCHAR *szTemp = buffer;
		#endif

			if (pSDK->GetSPDModuleMaxFrequency(_index) > 0)
				SPRINTF(Tbuffer, _countof(Tbuffer), _T("%s (%d MHz)"), szTemp, pSDK->GetSPDModuleMaxFrequency(_index));

			GetDlgItem(IDC_SPD_BANDWIDTH)->SetWindowText(Tbuffer);
			GetDlgItem(IDC_STATIC_SPD_BANDWIDTH)->EnableWindow(TRUE);
		}

		if (pSDK->GetSPDModulePartNumber(_index, buffer))
		{
		#ifdef _UNICODE
			TCHAR szTemp[512];
			int value = MultiByteToWideChar(CP_ACP,
											MB_PRECOMPOSED,
											buffer,
											-1,
											szTemp,
											512);
		#else
			TCHAR *szTemp = buffer;
		#endif
			GetDlgItem(IDC_SPD_PARTNUMBER)->SetWindowText(szTemp);
			GetDlgItem(IDC_STATIC_SPD_PARTNUMBER)->EnableWindow(TRUE);
		}

		if (pSDK->GetSPDModuleSerialNumber(_index, buffer))
		{
		#ifdef _UNICODE
			TCHAR szTemp[512];
			int value = MultiByteToWideChar(CP_ACP,
											MB_PRECOMPOSED,
											buffer,
											-1,
											szTemp,
											512);
		#else
			TCHAR *szTemp = buffer;
		#endif
			GetDlgItem(IDC_SPD_SERIALNUMBER)->SetWindowText(szTemp);
			GetDlgItem(IDC_STATIC_SPD_SERIALNUMBER)->EnableWindow(TRUE);
		}

		int year, week;
		if (pSDK->GetSPDModuleManufacturingDate(_index, &year, &week) && (year > 0) && (week > 0))
		{
			SPRINTF(Tbuffer, _countof(Tbuffer), _T("%02d / %02d"), week, year);
			GetDlgItem(IDC_SPD_DATE)->SetWindowText(Tbuffer);
			GetDlgItem(IDC_STATIC_SPD_DATE)->EnableWindow(TRUE);
		}

		if (pSDK->GetSPDModuleSize(_index) > 0)
		{
			SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d MBytes"), pSDK->GetSPDModuleSize(_index));
			GetDlgItem(IDC_SPD_SIZE)->SetWindowText(Tbuffer);
			GetDlgItem(IDC_STATIC_SPD_SIZE)->EnableWindow(TRUE);
		}

		int found = 0;
		SPRINTF(Tbuffer, _countof(Tbuffer), _T(""));
		if (pSDK->GetSPDModuleNumberOfAMPProfiles(_index, &revision) > 0)
		{
			STRCAT(Tbuffer, _countof(Tbuffer), _T(" AMP"));
			GetDlgItem(IDC_STATIC_SPD_EXT)->EnableWindow(TRUE);
			found = 1;
		}
		if (pSDK->GetSPDModuleNumberOfXMPProfiles(_index, &revision) > 0)
		{
			if (found)
				SPRINTF(buffer2, _countof(buffer2), _T(", XMP %d.%d"), (revision >> 4) & 0xF, revision & 0xF);
			else
				SPRINTF(buffer2, _countof(buffer2), _T("XMP %d.%d"), (revision >> 4) & 0xF, revision & 0xF);

			STRCAT(Tbuffer, _countof(Tbuffer), buffer2);
			GetDlgItem(IDC_STATIC_SPD_EXT)->EnableWindow(TRUE);
			found = 1;
		}
		if (pSDK->GetSPDModuleNumberOfEPPProfiles(_index, &revision) > 0)
		{
			if (found)
				SPRINTF(buffer2, _countof(buffer2), _T(", EPP %d.%d"), (revision >> 4) & 0xF, revision & 0xF);
			else
				SPRINTF(buffer2, _countof(buffer2), _T("EPP %d.%d"), (revision >> 4) & 0xF, revision & 0xF);

			STRCAT(Tbuffer, _countof(Tbuffer), buffer2);
			GetDlgItem(IDC_STATIC_SPD_EXT)->EnableWindow(TRUE);
		}
		GetDlgItem(IDC_SPD_EXT)->SetWindowText(Tbuffer);

		nb_extended_profiles = 0;
		profile = 0;
		
	//	AMP
		if (pSDK->GetSPDModuleNumberOfAMPProfiles(_index, &revision) > 0)
		{
			nb_extended_profiles += pSDK->GetSPDModuleNumberOfAMPProfiles(_index, &revision);

			profile = 4 - nb_extended_profiles;
			if (profile < 0) profile = 0;

			for ( i = 0;
				  i < pSDK->GetSPDModuleNumberOfAMPProfiles(_index, &revision);
				  i++, profile++ )
			{
				int frequency = I_UNDEFINED_VALUE;

				float CL = F_UNDEFINED_VALUE,
					  tRCD = F_UNDEFINED_VALUE,
					  tRAS = F_UNDEFINED_VALUE,
					  tRP = F_UNDEFINED_VALUE,
					  tRC = F_UNDEFINED_VALUE,
					  MinCycleTime = F_UNDEFINED_VALUE;

			//	Profile name
				SPRINTF(Tbuffer, _countof(Tbuffer), _T("AMP"));
				switch (profile)
				{
					case 0: GetDlgItem(IDC_SPD_PROFILE_NAME0)->SetWindowText(Tbuffer); break;
					case 1: GetDlgItem(IDC_SPD_PROFILE_NAME1)->SetWindowText(Tbuffer); break;
					case 2: GetDlgItem(IDC_SPD_PROFILE_NAME2)->SetWindowText(Tbuffer); break;
					case 3: GetDlgItem(IDC_SPD_PROFILE_NAME3)->SetWindowText(Tbuffer); break;
				}

				pSDK->GetSPDModuleAMPProfileInfos(_index, i, &frequency, &MinCycleTime, &CL, &tRCD, &tRAS, &tRP, &tRC);

			//	Frequency
				if (IS_I_DEFINED(frequency))
				{
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d MHz"), frequency);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_FREQUENCY0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_FREQUENCY1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_FREQUENCY2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_FREQUENCY3)->SetWindowText(Tbuffer); break;
						default: break;
					}
				}

				if (IS_F_DEFINED(CL))
				{
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.1f"), CL);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_CAS0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_CAS1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_CAS2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_CAS3)->SetWindowText(Tbuffer); break;
						default: break;
					}
				}

				if (IS_F_DEFINED(MinCycleTime))
				{
					if (IS_F_DEFINED(tRCD))
					{
						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)(tRCD * (1000.0f / MinCycleTime) / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_RASTOCAS0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_RASTOCAS1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_RASTOCAS2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_RASTOCAS3)->SetWindowText(Tbuffer); break;
							default: break;
						}
					}
					if (IS_F_DEFINED(tRP))
					{
						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)(tRP * (1000.0f / MinCycleTime) / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_RASPRECHARGE0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_RASPRECHARGE1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_RASPRECHARGE2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_RASPRECHARGE3)->SetWindowText(Tbuffer); break;
							default: break;
						}
					}
					if (IS_F_DEFINED(tRAS))
					{
						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)(tRAS * (1000.0f / MinCycleTime) / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_TRAS0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_TRAS1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_TRAS2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_TRAS3)->SetWindowText(Tbuffer); break;
							default: break;
						}
					}
					if (IS_F_DEFINED(tRC))
					{
						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)(tRC * (1000.0f / MinCycleTime) / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_TRC0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_TRC1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_TRC2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_TRC3)->SetWindowText(Tbuffer); break;
							default: break;
						}
					}
				}
			}
		}

	//	XMP
		if (pSDK->GetSPDModuleNumberOfXMPProfiles(_index, &revision) > 0)
		{
			nb_extended_profiles += pSDK->GetSPDModuleNumberOfXMPProfiles(_index, &revision);

			profile = 4 - nb_extended_profiles;
			if (profile < 0) profile = 0;

			GetDlgItem(IDC_STATIC_TIMINGSTABLE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_FREQUENCY)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_CAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_RASTOCAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_RASPRECHARGE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_TRAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_TRC)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_CR)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_VDD)->EnableWindow(TRUE);

			for ( i = 0;
				  i < pSDK->GetSPDModuleNumberOfXMPProfiles(_index, &revision);
				  i++, profile++ )
			{
				float max_CL, tRCD, tRAS, tRP, nominal_vdd;
				int max_freq;

				pSDK->GetSPDModuleXMPProfileInfos(_index, i, &tRCD, &tRAS, &tRP, &nominal_vdd, &max_freq, &max_CL);
				if (IS_I_DEFINED(max_freq))
				{
				//	Voltage
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.3f V"), nominal_vdd);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_VDD0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_VDD1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_VDD2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_VDD3)->SetWindowText(Tbuffer); break;
						default: break;
					}

				//	Profile name
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("XMP-%d"), 2 * max_freq);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_PROFILE_NAME0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_PROFILE_NAME1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_PROFILE_NAME2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_PROFILE_NAME3)->SetWindowText(Tbuffer); break;
					}

				//	Frequency
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d MHz"), max_freq);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_FREQUENCY0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_FREQUENCY1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_FREQUENCY2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_FREQUENCY3)->SetWindowText(Tbuffer); break;
						default: break;
					}

				//	Parse CAS# Table
					int NbCL = pSDK->GetSPDModuleXMPProfileNumberOfCL(_index, i);
					int mindelta = 999;
					int cas_index = -1;
					float CL, frequency;

					for ( j = 0; j < NbCL; j++ )
					{
						pSDK->GetSPDModuleXMPProfileCLInfos(_index, i, j, &frequency, &CL);
						if ((int)CL == (int)max_CL)
						{
							cas_index = j;
							break;
						}
						else
						{
							int delta = (int)CL - (int)max_CL;
							if (delta > 0)
							{
								if (delta < mindelta)
								{
									mindelta = delta;
									cas_index = j;
								}
							}
						}
					}

					if (cas_index >= 0)
					{
						pSDK->GetSPDModuleXMPProfileCLInfos(_index, i, cas_index, &frequency, &CL);

						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.1f"), CL);
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_CAS0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_CAS1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_CAS2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_CAS3)->SetWindowText(Tbuffer); break;
							default: break;
						}

						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRCD * frequency / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_RASTOCAS0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_RASTOCAS1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_RASTOCAS2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_RASTOCAS3)->SetWindowText(Tbuffer); break;
							default: break;
						}

						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRP * frequency / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_RASPRECHARGE0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_RASPRECHARGE1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_RASPRECHARGE2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_RASPRECHARGE3)->SetWindowText(Tbuffer); break;
							default: break;
						}

						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRAS * frequency / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_TRAS0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_TRAS1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_TRAS2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_TRAS3)->SetWindowText(Tbuffer); break;
							default: break;
						}
					}
					else
					{
						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.1f"), max_CL);
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_CAS0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_CAS1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_CAS2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_CAS3)->SetWindowText(Tbuffer); break;
							default: break;
						}

						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRCD * max_freq / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_RASTOCAS0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_RASTOCAS1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_RASTOCAS2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_RASTOCAS3)->SetWindowText(Tbuffer); break;
							default: break;
						}

						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRP * max_freq / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_RASPRECHARGE0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_RASPRECHARGE1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_RASPRECHARGE2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_RASPRECHARGE3)->SetWindowText(Tbuffer); break;
							default: break;
						}

						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRAS * max_freq / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_TRAS0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_TRAS1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_TRAS2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_TRAS3)->SetWindowText(Tbuffer); break;
							default: break;
						}
					}

	/*
					SPRINTF(buffer, _countof(buffer), _T("%d"), (int)ceil(pXMPProfile->m_fMinTRC * (float)pXMPProfile->m_iMaxFrequency / 1000.0f));
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_TRC0)->SetWindowText(buffer); break;
						case 1: GetDlgItem(IDC_SPD_TRC1)->SetWindowText(buffer); break;
						case 2: GetDlgItem(IDC_SPD_TRC2)->SetWindowText(buffer); break;
						case 3: GetDlgItem(IDC_SPD_TRC3)->SetWindowText(buffer); break;
						default: break;
					}

					if (pXMPProfile->m_iCMDRate > 0)
					{
						SPRINTF(buffer, _countof(buffer), _T("%dT"), pXMPProfile->m_iCMDRate);
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_CR0)->SetWindowText(buffer); break;
							case 1: GetDlgItem(IDC_SPD_CR1)->SetWindowText(buffer); break;
							case 2: GetDlgItem(IDC_SPD_CR2)->SetWindowText(buffer); break;
							case 3: GetDlgItem(IDC_SPD_CR3)->SetWindowText(buffer); break;
							default: break;
						}
					}
	*/
				}
			}
		}
		else if (pSDK->GetSPDModuleNumberOfEPPProfiles(_index, &revision) > 0)
		{
			nb_extended_profiles = pSDK->GetSPDModuleNumberOfEPPProfiles(_index, &revision);
			profile = 4 - nb_extended_profiles;
			if (profile < 0) profile = 0;

			GetDlgItem(IDC_STATIC_TIMINGSTABLE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_FREQUENCY)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_CAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_RASTOCAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_RASPRECHARGE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_TRAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_TRC)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_CR)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_VDD)->EnableWindow(TRUE);

			for ( i = 0;
				  i < nb_extended_profiles;
				  i++, profile++ )
			{
				float CL, tRCD, tRAS, tRP, tRC, vdd, frequency;

				pSDK->GetSPDModuleEPPProfileInfos(_index, i, &frequency, &CL, &tRCD, &tRAS, &tRP, &tRC, &vdd);

				SPRINTF(Tbuffer, _countof(Tbuffer), _T("EPP #%d"), i + 1);
				switch (profile)
				{
					case 0: GetDlgItem(IDC_SPD_PROFILE_NAME0)->SetWindowText(Tbuffer); break;
					case 1: GetDlgItem(IDC_SPD_PROFILE_NAME1)->SetWindowText(Tbuffer); break;
					case 2: GetDlgItem(IDC_SPD_PROFILE_NAME2)->SetWindowText(Tbuffer); break;
					case 3: GetDlgItem(IDC_SPD_PROFILE_NAME3)->SetWindowText(Tbuffer); break;
					default: break;
				}

				SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d MHz"), (int)frequency);
				switch (profile)
				{
					case 0: GetDlgItem(IDC_SPD_FREQUENCY0)->SetWindowText(Tbuffer); break;
					case 1: GetDlgItem(IDC_SPD_FREQUENCY1)->SetWindowText(Tbuffer); break;
					case 2: GetDlgItem(IDC_SPD_FREQUENCY2)->SetWindowText(Tbuffer); break;
					case 3: GetDlgItem(IDC_SPD_FREQUENCY3)->SetWindowText(Tbuffer); break;
					default: break;
				}

				if (CL > 0.0f)
				{
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.1f"), CL);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_CAS0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_CAS1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_CAS2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_CAS3)->SetWindowText(Tbuffer); break;
						default: break;
					}
				}
				SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRCD * frequency / 1000.0f));
				switch (profile)
				{
					case 0: GetDlgItem(IDC_SPD_RASTOCAS0)->SetWindowText(Tbuffer); break;
					case 1: GetDlgItem(IDC_SPD_RASTOCAS1)->SetWindowText(Tbuffer); break;
					case 2: GetDlgItem(IDC_SPD_RASTOCAS2)->SetWindowText(Tbuffer); break;
					case 3: GetDlgItem(IDC_SPD_RASTOCAS3)->SetWindowText(Tbuffer); break;
					default: break;
				}
				SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRP * frequency / 1000.0f));
				switch (profile)
				{
					case 0: GetDlgItem(IDC_SPD_RASPRECHARGE0)->SetWindowText(Tbuffer); break;
					case 1: GetDlgItem(IDC_SPD_RASPRECHARGE1)->SetWindowText(Tbuffer); break;
					case 2: GetDlgItem(IDC_SPD_RASPRECHARGE2)->SetWindowText(Tbuffer); break;
					case 3: GetDlgItem(IDC_SPD_RASPRECHARGE3)->SetWindowText(Tbuffer); break;
					default: break;
				}
				SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRAS * frequency / 1000.0f));
				switch (profile)
				{
					case 0: GetDlgItem(IDC_SPD_TRAS0)->SetWindowText(Tbuffer); break;
					case 1: GetDlgItem(IDC_SPD_TRAS1)->SetWindowText(Tbuffer); break;
					case 2: GetDlgItem(IDC_SPD_TRAS2)->SetWindowText(Tbuffer); break;
					case 3: GetDlgItem(IDC_SPD_TRAS3)->SetWindowText(Tbuffer); break;
					default: break;
				}
				if (tRC > 0.0f)
				{
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(tRC * frequency / 1000.0f));
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_TRC0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_TRC1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_TRC2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_TRC3)->SetWindowText(Tbuffer); break;
						default: break;
					}
				}

				//SPRINTF(Tbuffer, _countof(Tbuffer), _T("%dT"), pAProfile->m_iAddressCMDRate);
				//switch (profile)
				//{
				//	case 0: GetDlgItem(IDC_SPD_CR0)->SetWindowText(Tbuffer); break;
				//	case 1: GetDlgItem(IDC_SPD_CR1)->SetWindowText(Tbuffer); break;
				//	case 2: GetDlgItem(IDC_SPD_CR2)->SetWindowText(Tbuffer); break;
				//	case 3: GetDlgItem(IDC_SPD_CR3)->SetWindowText(Tbuffer); break;
				//	default: break;
				//}

				SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.3f V"), vdd);
				switch (profile)
				{
					case 0: GetDlgItem(IDC_SPD_VDD0)->SetWindowText(Tbuffer); break;
					case 1: GetDlgItem(IDC_SPD_VDD1)->SetWindowText(Tbuffer); break;
					case 2: GetDlgItem(IDC_SPD_VDD2)->SetWindowText(Tbuffer); break;
					case 3: GetDlgItem(IDC_SPD_VDD3)->SetWindowText(Tbuffer); break;
					default: break;
				}
			}
		}

		if (pSDK->GetSPDModuleNumberOfProfiles(_index) > 0)
		{
			GetDlgItem(IDC_STATIC_TIMINGSTABLE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_FREQUENCY)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_CAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_RASTOCAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_RASPRECHARGE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_TRAS)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SPD_TRC)->EnableWindow(TRUE);

			float min_tRCD = pSDK->GetSPDModuleMinTRCD(_index);
			float min_tRP = pSDK->GetSPDModuleMinTRP(_index);
			float min_tRAS = pSDK->GetSPDModuleMinTRAS(_index);
			float min_tRC = pSDK->GetSPDModuleMinTRC(_index);

			int nbprofiles = pSDK->GetSPDModuleNumberOfProfiles(_index);

			for ( i = nbprofiles - 1, profile = 4 - nb_extended_profiles - 1;
				  i >= 0;
				  i--, profile-- )
			{
				float CL, vdd, frequency;

				pSDK->GetSPDModuleProfileInfos(_index, i, &frequency, &CL, &vdd);

				if (profile >= 0)
				{
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("JEDEC #%d"), i + 1);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_PROFILE_NAME0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_PROFILE_NAME1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_PROFILE_NAME2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_PROFILE_NAME3)->SetWindowText(Tbuffer); break;
						default: break;
					}
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d MHz"), (int)frequency);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_FREQUENCY0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_FREQUENCY1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_FREQUENCY2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_FREQUENCY3)->SetWindowText(Tbuffer); break;
						default: break;
					}
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.1f"), CL);
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_CAS0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_CAS1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_CAS2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_CAS3)->SetWindowText(Tbuffer); break;
						default: break;
					}
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(min_tRCD * frequency / 1000.0f));
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_RASTOCAS0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_RASTOCAS1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_RASTOCAS2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_RASTOCAS3)->SetWindowText(Tbuffer); break;
						default: break;
					}
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(min_tRP * frequency / 1000.0f));
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_RASPRECHARGE0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_RASPRECHARGE1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_RASPRECHARGE2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_RASPRECHARGE3)->SetWindowText(Tbuffer); break;
						default: break;
					}
					SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(min_tRAS * frequency / 1000.0f));
					switch (profile)
					{
						case 0: GetDlgItem(IDC_SPD_TRAS0)->SetWindowText(Tbuffer); break;
						case 1: GetDlgItem(IDC_SPD_TRAS1)->SetWindowText(Tbuffer); break;
						case 2: GetDlgItem(IDC_SPD_TRAS2)->SetWindowText(Tbuffer); break;
						case 3: GetDlgItem(IDC_SPD_TRAS3)->SetWindowText(Tbuffer); break;
						default: break;
					}

					if (min_tRC > 0.0f)
					{
						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%d"), (int)ceil(min_tRC * frequency / 1000.0f));
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_TRC0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_TRC1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_TRC2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_TRC3)->SetWindowText(Tbuffer); break;
							default: break;
						}
					}

					if (vdd > 0.0f)
					{
						GetDlgItem(IDC_STATIC_SPD_VDD)->EnableWindow(TRUE);
						SPRINTF(Tbuffer, _countof(Tbuffer), _T("%.1f V"), vdd);
						switch (profile)
						{
							case 0: GetDlgItem(IDC_SPD_VDD0)->SetWindowText(Tbuffer); break;
							case 1: GetDlgItem(IDC_SPD_VDD1)->SetWindowText(Tbuffer); break;
							case 2: GetDlgItem(IDC_SPD_VDD2)->SetWindowText(Tbuffer); break;
							case 3: GetDlgItem(IDC_SPD_VDD3)->SetWindowText(Tbuffer); break;
							default: break;
						}
					}
				}
			}
		}

	//	Data
		{
			int i, size;
			unsigned char data;

			size = 256;
			if (pSDK->GetSPDModuleType(_index) == DDR4_SDRAM)
			{
				size = 512;
			}

			for ( i=0; i<size; i++ )
			{
				data = (unsigned char)pSDK->GetSPDModuleRawData(_index, i);
				int debug = 0;
			}
		}

	}
}

void CSPDDlg::vCleanAll()
{
	GetDlgItem(IDC_RAM_TYPE)->SetWindowText(_T(" Empty"));

	GetDlgItem(IDC_SPD_MANUFACTURER)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_MANUFACTURER)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_BANDWIDTH)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_BANDWIDTH)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_PARTNUMBER)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_PARTNUMBER)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_SERIALNUMBER)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_SERIALNUMBER)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_DATE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_DATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_SIZE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_SIZE)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_CORRECTION)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_CORRECTION)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_REGISTERED)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_REGISTERED)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_BUFFERED)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_BUFFERED)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_EXT)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SPD_EXT)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_TIMINGSTABLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SPD_FREQUENCY)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SPD_CAS)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SPD_RASTOCAS)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SPD_RASPRECHARGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SPD_TRAS)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SPD_TRC)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SPD_CR)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SPD_VDD)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPD_FREQUENCY0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_FREQUENCY1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_FREQUENCY2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_FREQUENCY3)->SetWindowText(_T(""));

	GetDlgItem(IDC_SPD_CAS0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_CAS1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_CAS2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_CAS3)->SetWindowText(_T(""));

	GetDlgItem(IDC_SPD_RASTOCAS0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_RASTOCAS1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_RASTOCAS2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_RASTOCAS3)->SetWindowText(_T(""));

	GetDlgItem(IDC_SPD_RASPRECHARGE0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_RASPRECHARGE1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_RASPRECHARGE2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_RASPRECHARGE3)->SetWindowText(_T(""));

	GetDlgItem(IDC_SPD_TRAS0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_TRAS1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_TRAS2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_TRAS3)->SetWindowText(_T(""));

	GetDlgItem(IDC_SPD_TRC0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_TRC1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_TRC2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_TRC3)->SetWindowText(_T(""));

	GetDlgItem(IDC_SPD_CR0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_CR1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_CR2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_CR3)->SetWindowText(_T(""));

	GetDlgItem(IDC_SPD_VDD0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_VDD1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_VDD2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_VDD3)->SetWindowText(_T(""));

	GetDlgItem(IDC_SPD_PROFILE_NAME0)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_PROFILE_NAME1)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_PROFILE_NAME2)->SetWindowText(_T(""));
	GetDlgItem(IDC_SPD_PROFILE_NAME3)->SetWindowText(_T(""));
}

void CSPDDlg::OnCbnSelchangeComboSpd()
{
	int sel = m_Combo_SPD.GetCurSel();
	vUpdateSPDInfos(sel);
}
