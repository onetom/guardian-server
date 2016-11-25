#ifndef _CMONITOR_H_
#define _CMONITOR_H_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CMonitor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLASS_MONITOR_LOCAL				0x00000000

class CMonitor;
typedef CTList<CMonitor> tdMonitorList;
typedef CTListParser<CMonitor> tdMonitorListParser;

class CMonitor
{
public:
	char	m_szName[256];
	int		m_iClass;

public:
	int iGetClass() { return m_iClass; }

public:
	virtual BOOL bInit() { return FALSE; }
	virtual void vClose() {}

//	Devices
	virtual int iGetNumberOfDevices() { return 0; }
	virtual unsigned int uiGetDeviceClass(int _device_index) { return I_UNDEFINED_VALUE; }
	virtual BOOL bGetDeviceName(int _device_index, char *_szBuffer) { return FALSE; }
	virtual BOOL bGetDeviceSerialNumber(int _device_index, char *_szBuffer) { return FALSE; }

//	Sensors	
	virtual int iGetNumberOfSensors(int _device_index, int _sensor_class) { return I_UNDEFINED_VALUE; }
	virtual BOOL bGetSensorInfos(int _device_index, int _sensor_index, unsigned int _sensor_class, unsigned int *_sensor_id, char *_szName, unsigned int *_raw_value, float *_value, float *_min_value, float *_max_value, unsigned int *_flags) { return FALSE; }

//	HWMonitors
	virtual int iGetNumberOfHardwareMonitors(int _device_index) { return 0; }
	virtual unsigned int uiGetHardwareMonitorClass(int _device_index, int _hwm_index) { return I_UNDEFINED_VALUE; }
	virtual unsigned int uiGetHardwareMonitorID(int _device_index, int _hwm_index) { return I_UNDEFINED_VALUE; }
	virtual BOOL bGetHardwareMonitorName(int _device_index, int _hwm_index, char *_szBuffer) { return FALSE; }

//	Misc
	virtual void vUpdate() {}
	virtual void vClearMinMax() {}

public:
	CMonitor(int _class, char *_szName);
	virtual ~CMonitor();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CLocalMonitor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CLocalMonitor : public CMonitor
{
protected:
//	SDK objects
	HMODULE			m_hDLL;
	CPUIDSDK		*m_pSDK;

public:
	virtual BOOL bInit();
	virtual void vClose();

	virtual int iGetNumberOfDevices();
	virtual unsigned int uiGetDeviceClass(int _device_index);
	virtual BOOL bGetDeviceName(int _device_index, char *_szBuffer);
	virtual BOOL bGetDeviceSerialNumber(int _device_index, char *_szBuffer);
	virtual int iGetNumberOfSensors(int _device_index, int _sensor_class);
	virtual BOOL bGetSensorInfos(int _device_index, int _sensor_index, unsigned int _sensor_class, unsigned int *_sensor_id, char *_szName, unsigned int *_raw_value, float *_value, float *_min_value, float *_max_value, unsigned int *_flags);
	virtual void vUpdate();
	virtual void vClearMinMax();

public:
	CLocalMonitor(char *_szName);
	virtual ~CLocalMonitor();
};

#endif //_CMONITOR_H_