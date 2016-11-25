
#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CMonitor.h"
#include "HWMonitor.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CMonitor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMonitor::CMonitor(int _class, char *_szName)
{
	m_iClass = _class;
	sprintf_s(m_szName, _countof(m_szName), _szName);
}

CMonitor::~CMonitor()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CLocalMonitor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CLocalMonitor::CLocalMonitor(char *_szName) 
: CMonitor(CLASS_MONITOR_LOCAL, _szName)
{
   m_pSDK = NULL;
}

CLocalMonitor::~CLocalMonitor()
{
}

BOOL CLocalMonitor::bInit()
{
	TCHAR	tmpBuffer[512];
	TCHAR	szDllPath[512];
	TCHAR	szDllFilename[512];
	int		errorcode, extended_errorcode;
	BOOL	result;

	GetCurrentDirectory(256, tmpBuffer);

	SPRINTF(szDllPath, _countof(szDllPath), _T("..\\..\\..\\bin"));
#if defined (_M_AMD64)
	SPRINTF(szDllFilename, _countof(szDllFilename), _T("cpuidsdk64.dll"));
#else
	SPRINTF(szDllFilename, _countof(szDllFilename), _T("cpuidsdk.dll"));
#endif

	SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("%s\\%s"), szDllPath, szDllFilename);
	m_hDLL = LoadLibrary(tmpBuffer);
	if (!m_hDLL)
	{
		szDllPath[0] = 0;
		SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("%s"), szDllFilename);
		m_hDLL = LoadLibrary(tmpBuffer);
	}
	if (m_hDLL)
	{
		m_pSDK = new CPUIDSDK();

		result = m_pSDK->InitDll(m_hDLL);
		result = m_pSDK->CreateInstance();
#ifdef _UNICODE
		char szMultiBytePath[512];
		char szMultiByteDllFilename[512];
		DWORD ret;

		ret = WideCharToMultiByte(CP_ACP, 0, szDllPath, -1, szMultiBytePath, _countof(szMultiBytePath), NULL, NULL);
		ret = WideCharToMultiByte(CP_ACP, 0, szDllFilename, -1, szMultiByteDllFilename, _countof(szMultiByteDllFilename), NULL, NULL);

		result = m_pSDK->Init(szMultiBytePath,
							  szMultiByteDllFilename,
							  CPUIDSDK_CONFIG_USE_EVERYTHING,
							  &errorcode,
							  &extended_errorcode);
#else
		errorcode = 0;
		result = m_pSDK->Init(szDllPath,
							  szDllFilename,
							  CPUIDSDK_CONFIG_USE_EVERYTHING,
							  &errorcode,
							  &extended_errorcode);
#endif
		if (errorcode != CPUIDSDK_ERROR_NO_ERROR)
		{
		//	Init failed, check errorcode
			switch (errorcode)
			{
				case CPUIDSDK_ERROR_EVALUATION:
					{
						switch (extended_errorcode)
						{
							case CPUIDSDK_EXT_ERROR_EVAL_1:
								SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("You are running a trial version of the DLL SDK. In order to make it work, please run CPU-Z at the same time."));
								break;

							case CPUIDSDK_EXT_ERROR_EVAL_2:
								SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Evaluation version has expired."));
								break;

							default:
								SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Eval version error 0x%X."), extended_errorcode);
								break;
						}
					}
					break;

				case CPUIDSDK_ERROR_DRIVER:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Driver error 0x%X."), extended_errorcode);
					break;

				case CPUIDSDK_ERROR_VM_RUNNING:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Virtual machine detected."));
					break;

				case CPUIDSDK_ERROR_LOCKED:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("SDK mutex locked."));
					break;

				default:
					SPRINTF(tmpBuffer, _countof(tmpBuffer), _T("Error code 0x%X"), errorcode);
					break;
			}			
			MessageBox(NULL,tmpBuffer, _T("Error"), MB_ICONEXCLAMATION);
		}

		if (!result)
			return FALSE;
	}
	return TRUE;
}

void CLocalMonitor::vClose()
{
 	if (m_pSDK)
	{
		m_pSDK->Close();
		m_pSDK->DestroyInstance();
		delete m_pSDK;
	}
	if (m_hDLL)
	{
		FreeLibrary(m_hDLL);
	}
}

void CLocalMonitor::vUpdate()
{
	if (m_pSDK)
	{
		m_pSDK->RefreshInformation();
	}
}

void CLocalMonitor::vClearMinMax()
{
	int device, sensor;

	if (m_pSDK)
	{
		for ( device = 0; device < iGetNumberOfDevices(); device++ )
		{
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_VOLTAGE); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_VOLTAGE);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_TEMPERATURE); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_TEMPERATURE);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_FAN); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_FAN);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_CURRENT); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_CURRENT);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_POWER); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_POWER);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_FAN_PWM); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_FAN_PWM);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_PUMP_PWM); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_PUMP_PWM);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_WATER_LEVEL); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_WATER_LEVEL);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_POSITION); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_POSITION);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_CAPACITY); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_CAPACITY);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_CASEOPEN); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_CASEOPEN);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_LEVEL); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_LEVEL);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_COUNTER); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_COUNTER);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_UTILIZATION); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_UTILIZATION);
			}
			for ( sensor = 0; sensor < iGetNumberOfSensors(device, SENSOR_CLASS_CLOCK_SPEED); sensor++ )
			{
				m_pSDK->SensorClearMinMax(device, sensor, SENSOR_CLASS_CLOCK_SPEED);
			}
		}
	}
}

int CLocalMonitor::iGetNumberOfDevices()
{
	if (m_pSDK)
	{
		return m_pSDK->GetNumberOfDevices();
	}
	return 0;
}

unsigned int CLocalMonitor::uiGetDeviceClass(int _device_index)
{
	if (m_pSDK)
	{
		return (unsigned int)m_pSDK->GetDeviceClass(_device_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CLocalMonitor::bGetDeviceName(int _device_index, char *_szBuffer)
{
	if (m_pSDK)
	{
		return m_pSDK->GetDeviceName(_device_index, _szBuffer);
	}
	return FALSE;
}

BOOL CLocalMonitor::bGetDeviceSerialNumber(int _device_index, char *_szBuffer)
{
	if (m_pSDK)
	{
		return m_pSDK->GetDeviceSerialNumber(_device_index, _szBuffer);
	}
	return FALSE;
}

int CLocalMonitor::iGetNumberOfSensors(int _device_index, int _sensor_class)
{
	if (m_pSDK)
	{
		return m_pSDK->GetNumberOfSensors(_device_index, _sensor_class);
	}
	return 0;
}

BOOL CLocalMonitor::bGetSensorInfos(int _device_index,
									int _sensor_index,
									unsigned int _sensor_class,
									unsigned int *_sensor_id,
									char *_szName,
									unsigned int *_raw_value,
									float *_value,
									float *_min_value,
									float *_max_value,
									unsigned int *_flags)
{
	if (m_pSDK)
	{
		return m_pSDK->GetSensorInfos(_device_index,
									  _sensor_index,
									  _sensor_class,
									  _sensor_id,
									  _szName,
									  _raw_value,
									  _value,
									  _min_value,
									  _max_value);
	}
	return FALSE;
}