// MonitoringDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoInc.h"
#include "SystemInfo.h"
#include "MonitoringDlg.h"


// CMonitoringDlg dialog

IMPLEMENT_DYNAMIC(CMonitoringDlg, CPropertyPage)

CMonitoringDlg::CMonitoringDlg()
	: CPropertyPage(CMonitoringDlg::IDD)
{

}

CMonitoringDlg::~CMonitoringDlg()
{
}

void CMonitoringDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonitoringDlg, CPropertyPage)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CMonitoringDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	GetDlgItem(IDC_STATIC_VOLTAGE_1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_3)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_4)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_5)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_6)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_7)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_8)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_9)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_VOLTAGE_10)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_TEMPERATURE_1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_3)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_4)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_5)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_TEMPERATURE_C1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_C2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_C3)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_C4)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_C5)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TEMPERATURE_C6)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_FAN_1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_FAN_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_FAN_3)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_FAN_4)->EnableWindow(FALSE);

	vRefreshGUI();
	SetTimer(0, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMonitoringDlg::OnTimer(UINT_PTR nIDEvent)
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

void CMonitoringDlg::vRefreshGUI()
{
	TCHAR			szTemp[512];
	TCHAR			buffer[512];
	char			szName[512];
	int				device_index, nbsensors, value;
	int				voltage_index, temp_index, fan_index, i;
	unsigned int	raw_value, sensor_id;
	float			fValue, fMinValue, fMaxValue;
	BOOL			result;

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK)
		return;

	voltage_index = 0;
	for ( device_index = 0; device_index < pSDK->GetNumberOfDevices(); device_index++ )
	{
		switch (pSDK->GetDeviceClass(device_index))
		{
			case CLASS_DEVICE_MAINBOARD:
				{
					nbsensors = pSDK->GetNumberOfSensors(device_index, SENSOR_CLASS_VOLTAGE);
					for ( i=0; i<nbsensors; i++ )
					{
						result = pSDK->GetSensorInfos(device_index, i, SENSOR_CLASS_VOLTAGE, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result && (fValue > -MAX_FLOAT))
						{
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							SPRINTF(buffer, _countof(buffer), _T("%.2f V"), fValue);

							switch (voltage_index)
							{
								case 0: 
									GetDlgItem(IDC_STATIC_VOLTAGE_1)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_1)->SetWindowText(szTemp);
									GetDlgItem(IDC_VOLTAGE_1)->SetWindowText(buffer);
									break;

								case 1: 
									GetDlgItem(IDC_STATIC_VOLTAGE_2)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_2)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_2)->SetWindowText(buffer);
									break;

								case 2: 
									GetDlgItem(IDC_STATIC_VOLTAGE_3)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_3)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_3)->SetWindowText(buffer);
									break;

								case 3: 
									GetDlgItem(IDC_STATIC_VOLTAGE_4)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_4)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_4)->SetWindowText(buffer);
									break;

								case 4: 
									GetDlgItem(IDC_STATIC_VOLTAGE_5)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_5)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_5)->SetWindowText(buffer);
									break;

								case 5: 
									GetDlgItem(IDC_STATIC_VOLTAGE_6)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_6)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_6)->SetWindowText(buffer);
									break;

								case 6: 
									GetDlgItem(IDC_STATIC_VOLTAGE_7)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_7)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_7)->SetWindowText(buffer);
									break;

								case 7: 
									GetDlgItem(IDC_STATIC_VOLTAGE_8)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_8)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_8)->SetWindowText(buffer);
									break;

								case 8: 
									GetDlgItem(IDC_STATIC_VOLTAGE_9)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_9)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_9)->SetWindowText(buffer);
									break;

								case 9: 
									GetDlgItem(IDC_STATIC_VOLTAGE_10)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_VOLTAGE_10)->SetWindowText(szTemp);							
									GetDlgItem(IDC_VOLTAGE_10)->SetWindowText(buffer);
									break;

								default:
									break;
							}
							voltage_index++;
						}
					}
				}
				break;

			default:
				break;
		}
	}

	temp_index = 0;
	fan_index = 0;

	for ( device_index = 0; device_index < pSDK->GetNumberOfDevices(); device_index++ )
	{
		switch (pSDK->GetDeviceClass(device_index))
		{
			case CLASS_DEVICE_MAINBOARD:
				{
					nbsensors = pSDK->GetNumberOfSensors(device_index, SENSOR_CLASS_TEMPERATURE);
					for ( i=0; i<nbsensors; i++ )
					{
						result = pSDK->GetSensorInfos(device_index, i, SENSOR_CLASS_TEMPERATURE, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result && (fValue > -MAX_FLOAT))
						{
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							SPRINTF(buffer, _countof(buffer), _T("%.1f °C"), fValue);

							switch (temp_index)
							{
								case 0:
									GetDlgItem(IDC_STATIC_TEMPERATURE_1)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_TEMPERATURE_1)->SetWindowText(szTemp);
									GetDlgItem(IDC_TEMPERATURE_1)->SetWindowText(buffer);
									break;

								case 1:
									GetDlgItem(IDC_STATIC_TEMPERATURE_2)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_TEMPERATURE_2)->SetWindowText(szTemp);
									GetDlgItem(IDC_TEMPERATURE_2)->SetWindowText(buffer);
									break;

								case 2:
									GetDlgItem(IDC_STATIC_TEMPERATURE_3)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_TEMPERATURE_3)->SetWindowText(szTemp);
									GetDlgItem(IDC_TEMPERATURE_3)->SetWindowText(buffer);
									break;

								case 3:
									GetDlgItem(IDC_STATIC_TEMPERATURE_4)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_TEMPERATURE_4)->SetWindowText(szTemp);
									GetDlgItem(IDC_TEMPERATURE_4)->SetWindowText(buffer);
									break;

								case 4:
									GetDlgItem(IDC_STATIC_TEMPERATURE_5)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_TEMPERATURE_5)->SetWindowText(szTemp);
									GetDlgItem(IDC_TEMPERATURE_5)->SetWindowText(buffer);
									break;

								default:
									break;
							}
							temp_index++;
						}
					}

					nbsensors = pSDK->GetNumberOfSensors(device_index, SENSOR_CLASS_FAN);
					for ( i=0; i<nbsensors; i++ )
					{
						result = pSDK->GetSensorInfos(device_index, i, SENSOR_CLASS_FAN, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result && (((int)fValue) > 0))
						{
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							SPRINTF(buffer, _countof(buffer), _T("%d RPM"), (int)fValue);

							switch (fan_index)
							{
								case 0:
									GetDlgItem(IDC_STATIC_FAN_1)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_FAN_1)->SetWindowText(szTemp);
									GetDlgItem(IDC_FAN_1)->SetWindowText(buffer);
									break;

								case 1:
									GetDlgItem(IDC_STATIC_FAN_2)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_FAN_2)->SetWindowText(szTemp);
									GetDlgItem(IDC_FAN_2)->SetWindowText(buffer);
									break;

								case 2:
									GetDlgItem(IDC_STATIC_FAN_3)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_FAN_3)->SetWindowText(szTemp);
									GetDlgItem(IDC_FAN_3)->SetWindowText(buffer);
									break;

								case 3:
									GetDlgItem(IDC_STATIC_FAN_4)->EnableWindow(TRUE);
									GetDlgItem(IDC_STATIC_FAN_4)->SetWindowText(szTemp);
									GetDlgItem(IDC_FAN_4)->SetWindowText(buffer);
									break;

								default:
									break;
							}
							fan_index++;
						}
						else
						{
							GetDlgItem(IDC_STATIC_FAN_1)->EnableWindow(FALSE);
							GetDlgItem(IDC_FAN_1)->SetWindowText(_T(""));
						}
					}
				}
				break;

			case CLASS_DEVICE_PROCESSOR:
				{
					nbsensors = pSDK->GetNumberOfSensors(device_index, SENSOR_CLASS_TEMPERATURE);

					if (nbsensors > 0)
					{
						result = pSDK->GetSensorInfos(device_index, 0, SENSOR_CLASS_TEMPERATURE, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result)
						{
							GetDlgItem(IDC_STATIC_TEMPERATURE_C1)->EnableWindow(TRUE);
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							GetDlgItem(IDC_STATIC_TEMPERATURE_C1)->SetWindowText(szTemp);
							SPRINTF(buffer, _countof(buffer), _T("%.1f °C"), fValue);
							GetDlgItem(IDC_TEMPERATURE_C1)->SetWindowText(buffer);
						}
					}
					if (nbsensors > 1)
					{
						result = pSDK->GetSensorInfos(device_index, 1, SENSOR_CLASS_TEMPERATURE, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result)
						{
							GetDlgItem(IDC_STATIC_TEMPERATURE_C2)->EnableWindow(TRUE);
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							GetDlgItem(IDC_STATIC_TEMPERATURE_C2)->SetWindowText(szTemp);
							SPRINTF(buffer, _countof(buffer), _T("%.1f °C"), fValue);
							GetDlgItem(IDC_TEMPERATURE_C2)->SetWindowText(buffer);
						}
					}
					if (nbsensors > 2)
					{
						result = pSDK->GetSensorInfos(device_index, 2, SENSOR_CLASS_TEMPERATURE, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result)
						{
							GetDlgItem(IDC_STATIC_TEMPERATURE_C3)->EnableWindow(TRUE);
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							GetDlgItem(IDC_STATIC_TEMPERATURE_C3)->SetWindowText(szTemp);
							SPRINTF(buffer, _countof(buffer), _T("%.1f °C"), fValue);
							GetDlgItem(IDC_TEMPERATURE_C3)->SetWindowText(buffer);
						}
					}
					if (nbsensors > 3)
					{
						result = pSDK->GetSensorInfos(device_index, 3, SENSOR_CLASS_TEMPERATURE, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result)
						{
							GetDlgItem(IDC_STATIC_TEMPERATURE_C4)->EnableWindow(TRUE);
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							GetDlgItem(IDC_STATIC_TEMPERATURE_C4)->SetWindowText(szTemp);
							SPRINTF(buffer, _countof(buffer), _T("%.1f °C"), fValue);
							GetDlgItem(IDC_TEMPERATURE_C4)->SetWindowText(buffer);
						}
					}
					if (nbsensors > 4)
					{
						result = pSDK->GetSensorInfos(device_index, 4, SENSOR_CLASS_TEMPERATURE, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result)
						{
							GetDlgItem(IDC_STATIC_TEMPERATURE_C5)->EnableWindow(TRUE);
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							GetDlgItem(IDC_STATIC_TEMPERATURE_C5)->SetWindowText(szTemp);
							SPRINTF(buffer, _countof(buffer), _T("%.1f °C"), fValue);
							GetDlgItem(IDC_TEMPERATURE_C5)->SetWindowText(buffer);
						}
					}
					if (nbsensors > 5)
					{
						result = pSDK->GetSensorInfos(device_index, 5, SENSOR_CLASS_TEMPERATURE, &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue);
						if (result)
						{
							GetDlgItem(IDC_STATIC_TEMPERATURE_C6)->EnableWindow(TRUE);
					#ifdef _UNICODE
							value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
					#else
							memcpy(szTemp, szName, 512);
					#endif
							GetDlgItem(IDC_STATIC_TEMPERATURE_C6)->SetWindowText(szTemp);
							SPRINTF(buffer, _countof(buffer), _T("%.1f °C"), fValue);
							GetDlgItem(IDC_TEMPERATURE_C6)->SetWindowText(buffer);
						}
					}
				}
				break;

			default:
				break;
		}
	}
}