
#include "stdafx.h"
#include "cpuidsdk.h"

CPUIDSDK::CPUIDSDK()
{
	objptr = NULL;

	CPUIDSDK_fp_CreateInstance = NULL;
	CPUIDSDK_fp_DestroyInstance = NULL;
	CPUIDSDK_fp_Init = NULL;
	CPUIDSDK_fp_Close = NULL;
	CPUIDSDK_fp_RefreshInformation = NULL;
	CPUIDSDK_fp_GetDLLVersion = NULL;

	CPUIDSDK_fp_GetNbProcessors = NULL;
	CPUIDSDK_fp_GetProcessorFamily = NULL;
	CPUIDSDK_fp_GetProcessorExtendedFamily = NULL;
	CPUIDSDK_fp_GetProcessorModel = NULL;
	CPUIDSDK_fp_GetProcessorExtendedModel = NULL;
	CPUIDSDK_fp_GetProcessorSteppingID = NULL;
	CPUIDSDK_fp_GetProcessorTDP = NULL;
	CPUIDSDK_fp_GetProcessorCoreCount = NULL;
	CPUIDSDK_fp_GetProcessorThreadCount = NULL;
	CPUIDSDK_fp_GetProcessorCoreThreadCount = NULL;
	CPUIDSDK_fp_GetProcessorThreadAPICID = NULL;
	CPUIDSDK_fp_GetProcessorName = NULL;
	CPUIDSDK_fp_GetProcessorCodeName = NULL;
	CPUIDSDK_fp_GetProcessorSpecification = NULL;
	CPUIDSDK_fp_GetProcessorPackage = NULL;
	CPUIDSDK_fp_GetProcessorManufacturingProcess = NULL;
	CPUIDSDK_fp_GetProcessorStepping = NULL;
	CPUIDSDK_fp_GetProcessorCoreClockFrequency = NULL;	
	CPUIDSDK_fp_GetProcessorStockClockFrequency = NULL;
	CPUIDSDK_fp_GetProcessorStockBusFrequency = NULL;
	CPUIDSDK_fp_GetBusFrequency = NULL;
	CPUIDSDK_fp_GetProcessorRatedBusFrequency = NULL;
	CPUIDSDK_fp_GetProcessorCoreTemperature = NULL;
	CPUIDSDK_fp_IsProcessorInstructionSetAvailable = NULL;
	CPUIDSDK_fp_GetProcessorCoreClockMultiplier = NULL;
	CPUIDSDK_fp_GetProcessorMaxCacheLevel = NULL;
	CPUIDSDK_fp_GetProcessorCacheParameters = NULL;
	CPUIDSDK_fp_GetProcessorExtendedCacheParameters = NULL;
	CPUIDSDK_fp_GetHyperThreadingStatus = NULL;
	CPUIDSDK_fp_GetVirtualTechnologyStatus = NULL;
	CPUIDSDK_fp_GetProcessorID = NULL;
	CPUIDSDK_fp_GetProcessorVoltageID = NULL;

	CPUIDSDK_fp_GetMemoryType = NULL;
	CPUIDSDK_fp_GetMemorySize = NULL;
	CPUIDSDK_fp_GetMemoryNumberOfChannels = NULL;
	CPUIDSDK_fp_GetMemoryClockFrequency = NULL;
	CPUIDSDK_fp_GetMemoryCASLatency = NULL;
	CPUIDSDK_fp_GetMemoryRAStoCASDelay = NULL;
	CPUIDSDK_fp_GetMemoryRASPrecharge = NULL;
	CPUIDSDK_fp_GetMemoryTRAS = NULL;
	CPUIDSDK_fp_GetMemoryTRC = NULL;
	CPUIDSDK_fp_GetMemoryCommandRate = NULL;
	CPUIDSDK_fp_ComputeMemoryFrequency = NULL;

	CPUIDSDK_fp_GetNorthBridgeVendor = NULL;
	CPUIDSDK_fp_GetNorthBridgeModel = NULL;
	CPUIDSDK_fp_GetNorthBridgeRevision = NULL;
	CPUIDSDK_fp_GetSouthBridgeVendor = NULL;
	CPUIDSDK_fp_GetSouthBridgeModel = NULL;
	CPUIDSDK_fp_GetSouthBridgeRevision = NULL;

	CPUIDSDK_fp_GetBIOSVendor = NULL;
	CPUIDSDK_fp_GetBIOSVersion = NULL;
	CPUIDSDK_fp_GetBIOSDate = NULL;
	CPUIDSDK_fp_GetBIOSType = NULL;
	CPUIDSDK_fp_GetBIOSROMSize = NULL;
	CPUIDSDK_fp_GetMainboardVendor = NULL;
	CPUIDSDK_fp_GetMainboardModel = NULL;
	CPUIDSDK_fp_GetMainboardRevision = NULL;
	CPUIDSDK_fp_GetMainboardSerialNumber = NULL;
	CPUIDSDK_fp_GetSystemManufacturer = NULL;
	CPUIDSDK_fp_GetSystemProductName = NULL;
	CPUIDSDK_fp_GetSystemVersion = NULL;
	CPUIDSDK_fp_GetSystemSerialNumber = NULL;
	CPUIDSDK_fp_GetSystemUUID = NULL;
	CPUIDSDK_fp_GetChassisManufacturer = NULL;
	CPUIDSDK_fp_GetChassisType = NULL;
	CPUIDSDK_fp_GetChassisSerialNumber = NULL;
	CPUIDSDK_fp_GetMemoryInfosExt = NULL;
	CPUIDSDK_fp_GetNumberOfMemoryDevices = NULL;
	CPUIDSDK_fp_GetMemoryDeviceInfos = NULL;
	CPUIDSDK_fp_GetMemoryDeviceInfosExt = NULL;
	CPUIDSDK_fp_GetMemorySlotsConfig = NULL;

	CPUIDSDK_fp_GetNumberOfSPDModules = NULL;
	CPUIDSDK_fp_GetSPDModuleAddress = NULL;
	CPUIDSDK_fp_GetSPDModuleType = NULL;
	CPUIDSDK_fp_GetSPDModuleSize = NULL;
	CPUIDSDK_fp_GetSPDModuleFormat = NULL;
	CPUIDSDK_fp_GetSPDModuleManufacturer = NULL;
	CPUIDSDK_fp_GetSPDModuleManufacturerID = NULL;
	CPUIDSDK_fp_GetSPDModuleMaxFrequency = NULL;
	CPUIDSDK_fp_GetSPDModuleSpecification = NULL;
	CPUIDSDK_fp_GetSPDModulePartNumber = NULL;
	CPUIDSDK_fp_GetSPDModuleSerialNumber = NULL;
	CPUIDSDK_fp_GetSPDModuleMinTRCD = NULL;
	CPUIDSDK_fp_GetSPDModuleMinTRP = NULL;
	CPUIDSDK_fp_GetSPDModuleMinTRAS = NULL;
	CPUIDSDK_fp_GetSPDModuleMinTRC = NULL;
	CPUIDSDK_fp_GetSPDModuleManufacturingDate = NULL;
	CPUIDSDK_fp_GetSPDModuleNumberOfBanks = NULL;
	CPUIDSDK_fp_GetSPDModuleDataWidth = NULL;
	CPUIDSDK_fp_GetSPDModuleNumberOfProfiles = NULL;
	CPUIDSDK_fp_GetSPDModuleProfileInfos = NULL;
	CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles = NULL;
	CPUIDSDK_fp_GetSPDModuleEPPProfileInfos = NULL;
	CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles = NULL;
	CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL = NULL;
	CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos = NULL;
	CPUIDSDK_fp_GetSPDModuleXMPProfileInfos = NULL;
	CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles = NULL;
	CPUIDSDK_fp_GetSPDModuleAMPProfileInfos = NULL;
	CPUIDSDK_fp_GetSPDModuleRawData = NULL;

	CPUIDSDK_fp_GetNumberOfDevices = NULL;
	CPUIDSDK_fp_GetDeviceClass = NULL;
	CPUIDSDK_fp_GetDeviceName = NULL;
	CPUIDSDK_fp_GetDeviceSerialNumber = NULL;
	CPUIDSDK_fp_GetNumberOfSensors = NULL;
	CPUIDSDK_fp_GetSensorInfos = NULL;
	CPUIDSDK_fp_SensorClearMinMax = NULL;
	CPUIDSDK_fp_GetSensorTypeValue = NULL;

	CPUIDSDK_fp_GetNumberOfDisplayAdapter = NULL;
	CPUIDSDK_fp_GetDisplayAdapterName = NULL;
	CPUIDSDK_fp_GetDisplayAdapterCodeName = NULL;
	CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels = NULL;
	CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel = NULL;
	CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName = NULL;
	CPUIDSDK_fp_GetDisplayAdapterClock = NULL;
	CPUIDSDK_fp_GetDisplayAdapterStockClock = NULL;
	CPUIDSDK_fp_GetDisplayAdapterTemperature = NULL;
	CPUIDSDK_fp_GetDisplayAdapterFanSpeed = NULL;
	CPUIDSDK_fp_GetDisplayAdapterFanPWM = NULL;
	CPUIDSDK_fp_GetDisplayAdapterMemoryType = NULL;
	CPUIDSDK_fp_GetDisplayAdapterMemorySize = NULL;
	CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth = NULL;
	CPUIDSDK_fp_GetDisplayDriverVersion = NULL;
	CPUIDSDK_fp_GetDirectXVersion = NULL;
	CPUIDSDK_fp_GetDisplayAdapterBusInfos = NULL;
	CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess = NULL;
	CPUIDSDK_fp_GetDisplayAdapterPCIID = NULL;

	CPUIDSDK_fp_GetNumberOfHDD = NULL;
	CPUIDSDK_fp_GetHDDName = NULL;
	CPUIDSDK_fp_GetHDDRevision = NULL;
	CPUIDSDK_fp_GetHDDSerialNumber = NULL;
	CPUIDSDK_fp_GetHDDTemperature = NULL;
	CPUIDSDK_fp_GetHDDNumberOfVolumes = NULL;
	CPUIDSDK_fp_GetHDDVolumeLetter = NULL;
	CPUIDSDK_fp_GetHDDVolumeName = NULL;
	CPUIDSDK_fp_GetHDDVolumeSize = NULL;
	CPUIDSDK_fp_GetHDDVolumeSerial = NULL;
	CPUIDSDK_fp_GetHDDNumberOfAttributes = NULL;
	CPUIDSDK_fp_GetHDDAttribute = NULL;
}

CPUIDSDK::~CPUIDSDK()
{
}

BOOL CPUIDSDK::InitDll(HMODULE _hDll)
{
	void *(_stdcall *fpQueryInterface)(DWORD);
	(FARPROC&)fpQueryInterface = GetProcAddress(_hDll, "QueryInterface");
	if (fpQueryInterface)
	{
		CPUIDSDK_fp_CreateInstance = (TCPUIDSDK_fp_CreateInstance)fpQueryInterface(0x21452459);
		CPUIDSDK_fp_DestroyInstance = (TCPUIDSDK_fp_DestroyInstance)fpQueryInterface(0x30571113);
		CPUIDSDK_fp_Init = (TCPUIDSDK_fp_Init)fpQueryInterface(0x19937329);
		CPUIDSDK_fp_Close = (TCPUIDSDK_fp_Close)fpQueryInterface(0x14862213);
		CPUIDSDK_fp_RefreshInformation = (TCPUIDSDK_fp_RefreshInformation)fpQueryInterface(0x75030260);
		CPUIDSDK_fp_GetDLLVersion = (TCPUIDSDK_fp_GetDLLVersion)fpQueryInterface(0x61956551);

		CPUIDSDK_fp_GetNbProcessors = (TCPUIDSDK_fp_GetNbProcessors)fpQueryInterface(0x74126687);
		CPUIDSDK_fp_GetProcessorFamily = (TCPUIDSDK_fp_GetProcessorFamily)fpQueryInterface(0x32350046);
		CPUIDSDK_fp_GetProcessorExtendedFamily = (TCPUIDSDK_fp_GetProcessorExtendedFamily)fpQueryInterface(0x10298827);
		CPUIDSDK_fp_GetProcessorModel = (TCPUIDSDK_fp_GetProcessorModel)fpQueryInterface(0x07858760);
		CPUIDSDK_fp_GetProcessorExtendedModel = (TCPUIDSDK_fp_GetProcessorExtendedModel)fpQueryInterface(0x95010448);
		CPUIDSDK_fp_GetProcessorSteppingID = (TCPUIDSDK_fp_GetProcessorSteppingID)fpQueryInterface(0x98218919);
		CPUIDSDK_fp_GetProcessorTDP = (TCPUIDSDK_fp_GetProcessorTDP)fpQueryInterface(0x79867689);
		CPUIDSDK_fp_GetProcessorCoreCount = (TCPUIDSDK_fp_GetProcessorCoreCount)fpQueryInterface(0x70028077);
		CPUIDSDK_fp_GetProcessorThreadCount = (TCPUIDSDK_fp_GetProcessorThreadCount)fpQueryInterface(0x36189448);
		CPUIDSDK_fp_GetProcessorCoreThreadCount = (TCPUIDSDK_fp_GetProcessorCoreThreadCount)fpQueryInterface(0x63895059);
		CPUIDSDK_fp_GetProcessorThreadAPICID = (TCPUIDSDK_fp_GetProcessorThreadAPICID)fpQueryInterface(0x05805773);
		CPUIDSDK_fp_GetProcessorName = (TCPUIDSDK_fp_GetProcessorName)fpQueryInterface(0x20310671);
		CPUIDSDK_fp_GetProcessorCodeName = (TCPUIDSDK_fp_GetProcessorCodeName)fpQueryInterface(0x49828055);
		CPUIDSDK_fp_GetProcessorSpecification = (TCPUIDSDK_fp_GetProcessorSpecification)fpQueryInterface(0x40463981);
		CPUIDSDK_fp_GetProcessorPackage = (TCPUIDSDK_fp_GetProcessorPackage)fpQueryInterface(0x01341414);
		CPUIDSDK_fp_GetProcessorStepping = (TCPUIDSDK_fp_GetProcessorStepping)fpQueryInterface(0x28151889);
		CPUIDSDK_fp_GetProcessorManufacturingProcess =(TCPUIDSDK_fp_GetProcessorManufacturingProcess)fpQueryInterface(0x23977925);
		CPUIDSDK_fp_IsProcessorInstructionSetAvailable = (TCPUIDSDK_fp_IsProcessorInstructionSetAvailable)fpQueryInterface(0x81550931);
		CPUIDSDK_fp_GetProcessorCoreClockMultiplier = (TCPUIDSDK_fp_GetProcessorCoreClockMultiplier)fpQueryInterface(0x12802281);
		CPUIDSDK_fp_GetProcessorCoreClockFrequency = (TCPUIDSDK_fp_GetProcessorCoreClockFrequency)fpQueryInterface(0x03472558);
		CPUIDSDK_fp_GetProcessorCoreTemperature = (TCPUIDSDK_fp_GetProcessorCoreTemperature)fpQueryInterface(0x20560624);
		CPUIDSDK_fp_GetBusFrequency = (TCPUIDSDK_fp_GetBusFrequency)fpQueryInterface(0x09851369);
		CPUIDSDK_fp_GetProcessorRatedBusFrequency = (TCPUIDSDK_fp_GetProcessorRatedBusFrequency)fpQueryInterface(0x33371080);
		CPUIDSDK_fp_GetProcessorStockClockFrequency = (TCPUIDSDK_fp_GetProcessorStockClockFrequency)fpQueryInterface(0x09585365);
		CPUIDSDK_fp_GetProcessorStockBusFrequency = (TCPUIDSDK_fp_GetProcessorStockBusFrequency)fpQueryInterface(0x81130419);
		CPUIDSDK_fp_GetProcessorMaxCacheLevel = (TCPUIDSDK_fp_GetProcessorMaxCacheLevel)fpQueryInterface(0x11105429);
		CPUIDSDK_fp_GetProcessorCacheParameters = (TCPUIDSDK_fp_GetProcessorCacheParameters)fpQueryInterface(0x34341922);
		CPUIDSDK_fp_GetProcessorExtendedCacheParameters = (TCPUIDSDK_fp_GetProcessorExtendedCacheParameters)fpQueryInterface(0x12706329);
		CPUIDSDK_fp_GetHyperThreadingStatus = (TCPUIDSDK_fp_GetHyperThreadingStatus)fpQueryInterface(0x94166705);
		CPUIDSDK_fp_GetVirtualTechnologyStatus = (TCPUIDSDK_fp_GetVirtualTechnologyStatus)fpQueryInterface(0x03875338);
		CPUIDSDK_fp_GetProcessorID = (TCPUIDSDK_fp_GetProcessorID)fpQueryInterface(0x11017670);
		CPUIDSDK_fp_GetProcessorVoltageID = (TCPUIDSDK_fp_GetProcessorVoltageID)fpQueryInterface(0x12381437);

		CPUIDSDK_fp_GetMemoryType = (TCPUIDSDK_fp_GetMemoryType)fpQueryInterface(0x29342710);
		CPUIDSDK_fp_GetMemorySize = (TCPUIDSDK_fp_GetMemorySize)fpQueryInterface(0x62110385);
		CPUIDSDK_fp_GetMemoryNumberOfChannels = (TCPUIDSDK_fp_GetMemoryNumberOfChannels)fpQueryInterface(0x85438592);
		CPUIDSDK_fp_GetMemoryClockFrequency = (TCPUIDSDK_fp_GetMemoryClockFrequency)fpQueryInterface(0x90020894);
		CPUIDSDK_fp_GetMemoryCASLatency = (TCPUIDSDK_fp_GetMemoryCASLatency)fpQueryInterface(0x84046156);
		CPUIDSDK_fp_GetMemoryRAStoCASDelay = (TCPUIDSDK_fp_GetMemoryRAStoCASDelay)fpQueryInterface(0x79190623);
		CPUIDSDK_fp_GetMemoryRASPrecharge = (TCPUIDSDK_fp_GetMemoryRASPrecharge)fpQueryInterface(0x39535851);
		CPUIDSDK_fp_GetMemoryTRAS = (TCPUIDSDK_fp_GetMemoryTRAS)fpQueryInterface(0x71291988);
		CPUIDSDK_fp_GetMemoryTRC = (TCPUIDSDK_fp_GetMemoryTRC)fpQueryInterface(0x55020883);
		CPUIDSDK_fp_GetMemoryCommandRate = (TCPUIDSDK_fp_GetMemoryCommandRate)fpQueryInterface(0x78298296);
		CPUIDSDK_fp_ComputeMemoryFrequency = (TCPUIDSDK_fp_ComputeMemoryFrequency)fpQueryInterface(0x09093128);

		CPUIDSDK_fp_GetNorthBridgeVendor = (TCPUIDSDK_fp_GetNorthBridgeVendor)fpQueryInterface(0x10414802);
		CPUIDSDK_fp_GetNorthBridgeModel = (TCPUIDSDK_fp_GetNorthBridgeModel)fpQueryInterface(0x07726825);
		CPUIDSDK_fp_GetNorthBridgeRevision = (TCPUIDSDK_fp_GetNorthBridgeRevision)fpQueryInterface(0x51134157);
		CPUIDSDK_fp_GetSouthBridgeVendor = (TCPUIDSDK_fp_GetSouthBridgeVendor)fpQueryInterface(0x11173275);
		CPUIDSDK_fp_GetSouthBridgeModel = (TCPUIDSDK_fp_GetSouthBridgeModel)fpQueryInterface(0x86002729);
		CPUIDSDK_fp_GetSouthBridgeRevision = (TCPUIDSDK_fp_GetSouthBridgeRevision)fpQueryInterface(0x35194959);

		CPUIDSDK_fp_GetBIOSVendor = (TCPUIDSDK_fp_GetBIOSVendor)fpQueryInterface(0x08870551);
		CPUIDSDK_fp_GetBIOSVersion = (TCPUIDSDK_fp_GetBIOSVersion)fpQueryInterface(0x75071585);
		CPUIDSDK_fp_GetBIOSDate = (TCPUIDSDK_fp_GetBIOSDate)fpQueryInterface(0x17547205);
		CPUIDSDK_fp_GetBIOSType = (TCPUIDSDK_fp_GetBIOSType)fpQueryInterface(0x09304835);
		CPUIDSDK_fp_GetBIOSROMSize = (TCPUIDSDK_fp_GetBIOSROMSize)fpQueryInterface(0x30702502);
		CPUIDSDK_fp_GetMainboardVendor = (TCPUIDSDK_fp_GetMainboardVendor)fpQueryInterface(0x59275458);
		CPUIDSDK_fp_GetMainboardModel = (TCPUIDSDK_fp_GetMainboardModel)fpQueryInterface(0x52979740);
		CPUIDSDK_fp_GetMainboardRevision = (TCPUIDSDK_fp_GetMainboardRevision)fpQueryInterface(0x88673334);
		CPUIDSDK_fp_GetMainboardSerialNumber = (TCPUIDSDK_fp_GetMainboardSerialNumber)fpQueryInterface(0x34029267);
		CPUIDSDK_fp_GetSystemManufacturer = (TCPUIDSDK_fp_GetSystemManufacturer)fpQueryInterface(0x69289762);
		CPUIDSDK_fp_GetSystemProductName = (TCPUIDSDK_fp_GetSystemProductName)fpQueryInterface(0x83146519);
		CPUIDSDK_fp_GetSystemVersion = (TCPUIDSDK_fp_GetSystemVersion)fpQueryInterface(0x90340390);
		CPUIDSDK_fp_GetSystemSerialNumber = (TCPUIDSDK_fp_GetSystemSerialNumber)fpQueryInterface(0x51914170);
		CPUIDSDK_fp_GetSystemUUID = (TCPUIDSDK_fp_GetSystemUUID)fpQueryInterface(0x59942501);
		CPUIDSDK_fp_GetChassisManufacturer = (TCPUIDSDK_fp_GetChassisManufacturer)fpQueryInterface(0x68873846);
		CPUIDSDK_fp_GetChassisType = (TCPUIDSDK_fp_GetChassisType)fpQueryInterface(0x71205454);
		CPUIDSDK_fp_GetChassisSerialNumber = (TCPUIDSDK_fp_GetChassisSerialNumber)fpQueryInterface(0x14260747);
		CPUIDSDK_fp_GetMemoryInfosExt = (TCPUIDSDK_fp_GetMemoryInfosExt)fpQueryInterface(0x47918636);
		CPUIDSDK_fp_GetNumberOfMemoryDevices = (TCPUIDSDK_fp_GetNumberOfMemoryDevices)fpQueryInterface(0x22697876);
		CPUIDSDK_fp_GetMemoryDeviceInfos = (TCPUIDSDK_fp_GetMemoryDeviceInfos)fpQueryInterface(0x92217148);
		CPUIDSDK_fp_GetMemorySlotsConfig = (TCPUIDSDK_fp_GetMemorySlotsConfig)fpQueryInterface(0x09748908);
		CPUIDSDK_fp_GetMemoryDeviceInfosExt = (TCPUIDSDK_fp_GetMemoryDeviceInfosExt)fpQueryInterface(0x84480656);

		CPUIDSDK_fp_GetNumberOfSPDModules = (TCPUIDSDK_fp_GetNumberOfSPDModules)fpQueryInterface(0x95984869);
		CPUIDSDK_fp_GetSPDModuleAddress = (TCPUIDSDK_fp_GetSPDModuleAddress)fpQueryInterface(0x81476325);
		CPUIDSDK_fp_GetSPDModuleType = (TCPUIDSDK_fp_GetSPDModuleType)fpQueryInterface(0x73560137);
		CPUIDSDK_fp_GetSPDModuleSize = (TCPUIDSDK_fp_GetSPDModuleSize)fpQueryInterface(0x17926572);
		CPUIDSDK_fp_GetSPDModuleFormat = (TCPUIDSDK_fp_GetSPDModuleFormat)fpQueryInterface(0x43266541);
		CPUIDSDK_fp_GetSPDModuleManufacturer = (TCPUIDSDK_fp_GetSPDModuleManufacturer)fpQueryInterface(0x20020212);
		CPUIDSDK_fp_GetSPDModuleManufacturerID = (TCPUIDSDK_fp_GetSPDModuleManufacturerID)fpQueryInterface(0x05650041);
		CPUIDSDK_fp_GetSPDModuleMaxFrequency = (TCPUIDSDK_fp_GetSPDModuleMaxFrequency)fpQueryInterface(0x61240771);
		CPUIDSDK_fp_GetSPDModuleSpecification = (TCPUIDSDK_fp_GetSPDModuleSpecification)fpQueryInterface(0x66920432);
		CPUIDSDK_fp_GetSPDModulePartNumber = (TCPUIDSDK_fp_GetSPDModulePartNumber)fpQueryInterface(0x67418601);
		CPUIDSDK_fp_GetSPDModuleSerialNumber = (TCPUIDSDK_fp_GetSPDModuleSerialNumber)fpQueryInterface(0x88405126);
		CPUIDSDK_fp_GetSPDModuleMinTRCD = (TCPUIDSDK_fp_GetSPDModuleMinTRCD)fpQueryInterface(0x03395383);
		CPUIDSDK_fp_GetSPDModuleMinTRP = (TCPUIDSDK_fp_GetSPDModuleMinTRP)fpQueryInterface(0x42080663);
		CPUIDSDK_fp_GetSPDModuleMinTRAS = (TCPUIDSDK_fp_GetSPDModuleMinTRAS)fpQueryInterface(0x28029203);
		CPUIDSDK_fp_GetSPDModuleMinTRC = (TCPUIDSDK_fp_GetSPDModuleMinTRC)fpQueryInterface(0x86021092);
		CPUIDSDK_fp_GetSPDModuleManufacturingDate = (TCPUIDSDK_fp_GetSPDModuleManufacturingDate)fpQueryInterface(0x21472874);
		CPUIDSDK_fp_GetSPDModuleNumberOfBanks = (TCPUIDSDK_fp_GetSPDModuleNumberOfBanks)fpQueryInterface(0x02931381);
		CPUIDSDK_fp_GetSPDModuleDataWidth = (TCPUIDSDK_fp_GetSPDModuleDataWidth)fpQueryInterface(0x73627103);
		CPUIDSDK_fp_GetSPDModuleNumberOfProfiles = (TCPUIDSDK_fp_GetSPDModuleNumberOfProfiles)fpQueryInterface(0x61286404);
		CPUIDSDK_fp_GetSPDModuleProfileInfos = (TCPUIDSDK_fp_GetSPDModuleProfileInfos)fpQueryInterface(0x19109521);
		CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles = (TCPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles)fpQueryInterface(0x71453072);
		CPUIDSDK_fp_GetSPDModuleEPPProfileInfos = (TCPUIDSDK_fp_GetSPDModuleEPPProfileInfos)fpQueryInterface(0x49734767);
		CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles = (TCPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles)fpQueryInterface(0x27872643);
		CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL = (TCPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL)fpQueryInterface(0x40772909);
		CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos = (TCPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos)fpQueryInterface(0x19772059);
		CPUIDSDK_fp_GetSPDModuleXMPProfileInfos = (TCPUIDSDK_fp_GetSPDModuleXMPProfileInfos)fpQueryInterface(0x76279884);
		CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles = (TCPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles)fpQueryInterface(0x57184768);
		CPUIDSDK_fp_GetSPDModuleAMPProfileInfos = (TCPUIDSDK_fp_GetSPDModuleAMPProfileInfos)fpQueryInterface(0x73365255);
		CPUIDSDK_fp_GetSPDModuleRawData = (TCPUIDSDK_fp_GetSPDModuleRawData)fpQueryInterface(0x85485813);

		CPUIDSDK_fp_GetNumberOfDevices = (TCPUIDSDK_fp_GetNumberOfDevices)fpQueryInterface(0x25057433);
		CPUIDSDK_fp_GetDeviceClass = (TCPUIDSDK_fp_GetDeviceClass)fpQueryInterface(0x36807526);
		CPUIDSDK_fp_GetDeviceName = (TCPUIDSDK_fp_GetDeviceName)fpQueryInterface(0x39542713);
		CPUIDSDK_fp_GetDeviceSerialNumber = (TCPUIDSDK_fp_GetDeviceSerialNumber)fpQueryInterface(0x80210169);
		CPUIDSDK_fp_GetNumberOfSensors = (TCPUIDSDK_fp_GetNumberOfSensors)fpQueryInterface(0x95629590);
		CPUIDSDK_fp_GetSensorInfos = (TCPUIDSDK_fp_GetSensorInfos)fpQueryInterface(0x49543122);
		CPUIDSDK_fp_SensorClearMinMax = (TCPUIDSDK_fp_SensorClearMinMax)fpQueryInterface(0x33549146);
		CPUIDSDK_fp_GetSensorTypeValue = (TCPUIDSDK_fp_GetSensorTypeValue)fpQueryInterface(0x12013410);

		CPUIDSDK_fp_GetNumberOfDisplayAdapter = (TCPUIDSDK_fp_GetNumberOfDisplayAdapter)fpQueryInterface(0x21249495);
		CPUIDSDK_fp_GetDisplayAdapterName = (TCPUIDSDK_fp_GetDisplayAdapterName)fpQueryInterface(0x92905207);
		CPUIDSDK_fp_GetDisplayAdapterCodeName = (TCPUIDSDK_fp_GetDisplayAdapterCodeName)fpQueryInterface(0x36601485);
		CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels = (TCPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels)fpQueryInterface(0x70614420);
		CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel = (TCPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel)fpQueryInterface(0x38305572);
		CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName = (TCPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName)fpQueryInterface(0x74800436);
		CPUIDSDK_fp_GetDisplayAdapterClock = (TCPUIDSDK_fp_GetDisplayAdapterClock)fpQueryInterface(0x58160354);
		CPUIDSDK_fp_GetDisplayAdapterStockClock = (TCPUIDSDK_fp_GetDisplayAdapterStockClock)fpQueryInterface(0x98839608);
		CPUIDSDK_fp_GetDisplayAdapterTemperature = (TCPUIDSDK_fp_GetDisplayAdapterTemperature)fpQueryInterface(0x89591134);
		CPUIDSDK_fp_GetDisplayAdapterFanSpeed = (TCPUIDSDK_fp_GetDisplayAdapterFanSpeed)fpQueryInterface(0x47296089);
		CPUIDSDK_fp_GetDisplayAdapterFanPWM = (TCPUIDSDK_fp_GetDisplayAdapterFanPWM)fpQueryInterface(0x95172240);
		CPUIDSDK_fp_GetDisplayAdapterMemoryType = (TCPUIDSDK_fp_GetDisplayAdapterMemoryType)fpQueryInterface(0x58437098);
		CPUIDSDK_fp_GetDisplayAdapterMemorySize = (TCPUIDSDK_fp_GetDisplayAdapterMemorySize)fpQueryInterface(0x25764630);
		CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth = (TCPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth)fpQueryInterface(0x62256484);
		CPUIDSDK_fp_GetDisplayDriverVersion = (TCPUIDSDK_fp_GetDisplayDriverVersion)fpQueryInterface(0x40381382);
		CPUIDSDK_fp_GetDirectXVersion = (TCPUIDSDK_fp_GetDirectXVersion)fpQueryInterface(0x04336787);
		CPUIDSDK_fp_GetDisplayAdapterBusInfos = (TCPUIDSDK_fp_GetDisplayAdapterBusInfos)fpQueryInterface(0x29194080);
		CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess = (TCPUIDSDK_fp_GetDisplayAdapterManufacturingProcess)fpQueryInterface(0x15062802);
		CPUIDSDK_fp_GetDisplayAdapterPCIID = (TCPUIDSDK_fp_GetDisplayAdapterPCIID)fpQueryInterface(0x41020899);

		CPUIDSDK_fp_GetNumberOfHDD = (TCPUIDSDK_fp_GetNumberOfHDD)fpQueryInterface(0x70194191);
		CPUIDSDK_fp_GetHDDName = (TCPUIDSDK_fp_GetHDDName)fpQueryInterface(0x14281523);
		CPUIDSDK_fp_GetHDDRevision = (TCPUIDSDK_fp_GetHDDRevision)fpQueryInterface(0x20439067);
		CPUIDSDK_fp_GetHDDSerialNumber = (TCPUIDSDK_fp_GetHDDSerialNumber)fpQueryInterface(0x84456446);
		CPUIDSDK_fp_GetHDDTemperature = (TCPUIDSDK_fp_GetHDDTemperature)fpQueryInterface(0x02542642);
		CPUIDSDK_fp_GetHDDNumberOfVolumes = (TCPUIDSDK_fp_GetHDDNumberOfVolumes)fpQueryInterface(0x03560569);
		CPUIDSDK_fp_GetHDDVolumeLetter = (TCPUIDSDK_fp_GetHDDVolumeLetter)fpQueryInterface(0x33850175);
		CPUIDSDK_fp_GetHDDVolumeName = (TCPUIDSDK_fp_GetHDDVolumeName)fpQueryInterface(0x32324888);
		CPUIDSDK_fp_GetHDDVolumeSize = (TCPUIDSDK_fp_GetHDDVolumeSize)fpQueryInterface(0x49680854);
		CPUIDSDK_fp_GetHDDVolumeSerial = (TCPUIDSDK_fp_GetHDDVolumeSerial)fpQueryInterface(0x83859347);
		CPUIDSDK_fp_GetHDDNumberOfAttributes = (TCPUIDSDK_fp_GetHDDNumberOfAttributes)fpQueryInterface(0x47656581);
		CPUIDSDK_fp_GetHDDAttribute = (TCPUIDSDK_fp_GetHDDAttribute)fpQueryInterface(0x34762833);
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Instance management
///////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CPUIDSDK::CreateInstance()
{
	if (CPUIDSDK_fp_CreateInstance)
	{
		objptr = CPUIDSDK_fp_CreateInstance();
		if (objptr) return TRUE;
	}
	return FALSE;
}

void CPUIDSDK::DestroyInstance()
{
	if (CPUIDSDK_fp_DestroyInstance)
	{
		CPUIDSDK_fp_DestroyInstance(objptr);
	}
}

BOOL CPUIDSDK::Init(char *_szDllPath, char *_szDllFilename, int _config_flag, int *_errorcode, int *_extended_errorcode)
{
	if (CPUIDSDK_fp_Init)
	{
		return CPUIDSDK_fp_Init(objptr, (BSTR)_szDllPath, (BSTR)_szDllFilename, _config_flag, _errorcode, _extended_errorcode);
	}
	else
	{
		*_errorcode = CPUIDSDK_ERROR_INVALID_DLL;
	}
	return FALSE;
}

void CPUIDSDK::Close()
{
	if (CPUIDSDK_fp_Close)
	{
		CPUIDSDK_fp_Close(objptr);
	}
}

void CPUIDSDK::RefreshInformation()
{
	if (CPUIDSDK_fp_RefreshInformation)
	{
		CPUIDSDK_fp_RefreshInformation(objptr);
	}
}

void CPUIDSDK::GetDLLVersion(int *_version)
{
	if (CPUIDSDK_fp_GetDLLVersion)
	{
		CPUIDSDK_fp_GetDLLVersion(objptr, _version);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Processor
///////////////////////////////////////////////////////////////////////////////////////////////////

int CPUIDSDK::GetNumberOfProcessors()
{
	if (CPUIDSDK_fp_GetNbProcessors)
	{
		return CPUIDSDK_fp_GetNbProcessors(objptr);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorFamily(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorFamily)
	{
		return CPUIDSDK_fp_GetProcessorFamily(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorExtendedFamily(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorExtendedFamily)
	{
		return CPUIDSDK_fp_GetProcessorExtendedFamily(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorModel(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorModel)
	{
		return CPUIDSDK_fp_GetProcessorModel(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorExtendedModel(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorExtendedModel)
	{
		return CPUIDSDK_fp_GetProcessorExtendedModel(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorSteppingID(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorSteppingID)
	{
		return CPUIDSDK_fp_GetProcessorSteppingID(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorCoreCount(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorCoreCount)
	{
		return CPUIDSDK_fp_GetProcessorCoreCount(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorThreadCount(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorThreadCount)
	{
		return CPUIDSDK_fp_GetProcessorThreadCount(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorCoreThreadCount(int _proc_index, int _core_index)
{
	if (CPUIDSDK_fp_GetProcessorCoreThreadCount)
	{
		return CPUIDSDK_fp_GetProcessorCoreThreadCount(objptr, _proc_index, _core_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorThreadAPICID(int _proc_index, int _core_index, int _thread_index)
{
	if (CPUIDSDK_fp_GetProcessorThreadAPICID)
	{
		return CPUIDSDK_fp_GetProcessorThreadAPICID(objptr, _proc_index, _core_index, _thread_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetProcessorName(int _proc_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetProcessorName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetProcessorName(objptr, _proc_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetProcessorCodeName(int _proc_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetProcessorCodeName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetProcessorCodeName(objptr, _proc_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetProcessorPackage(int _proc_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetProcessorPackage)
	{
		BSTR szTmp = CPUIDSDK_fp_GetProcessorPackage(objptr, _proc_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetProcessorSpecification(int _proc_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetProcessorSpecification)
	{
		BSTR szTmp = CPUIDSDK_fp_GetProcessorSpecification(objptr, _proc_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetProcessorStepping(int _proc_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetProcessorStepping)
	{
		BSTR szTmp = CPUIDSDK_fp_GetProcessorStepping(objptr, _proc_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

float CPUIDSDK::GetProcessorTDP(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorTDP)
	{
		return CPUIDSDK_fp_GetProcessorTDP(objptr, _proc_index);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetProcessorManufacturingProcess(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorManufacturingProcess)
	{
		return CPUIDSDK_fp_GetProcessorManufacturingProcess(objptr, _proc_index);
	}
	return F_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::IsProcessorInstructionSetAvailable(int _proc_index, int _iset)
{
	if (CPUIDSDK_fp_IsProcessorInstructionSetAvailable)
	{
		return ((CPUIDSDK_fp_IsProcessorInstructionSetAvailable(objptr, _proc_index, _iset) == 1)?TRUE:FALSE);
	}
	return FALSE;
}

float CPUIDSDK::GetProcessorCoreClockFrequency(int _proc_index, int _core_index)
{
	if (CPUIDSDK_fp_GetProcessorCoreClockFrequency)
	{
		return CPUIDSDK_fp_GetProcessorCoreClockFrequency(objptr, _proc_index, _core_index);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetProcessorCoreTemperature(int _proc_index, int _core_index)
{
	if (CPUIDSDK_fp_GetProcessorCoreTemperature)
	{
		return CPUIDSDK_fp_GetProcessorCoreTemperature(objptr, _proc_index, _core_index);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetProcessorCoreClockMultiplier(int _proc_index, int _core_index)
{
	if (CPUIDSDK_fp_GetProcessorCoreClockMultiplier)
	{
		return CPUIDSDK_fp_GetProcessorCoreClockMultiplier(objptr, _proc_index, _core_index);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetBusFrequency()
{
	if (CPUIDSDK_fp_GetBusFrequency)
	{
		return CPUIDSDK_fp_GetBusFrequency(objptr);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetProcessorRatedBusFrequency(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorRatedBusFrequency)
	{
		return CPUIDSDK_fp_GetProcessorRatedBusFrequency(objptr, _proc_index);
	}
	return F_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorStockClockFrequency(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorStockClockFrequency)
	{
		return CPUIDSDK_fp_GetProcessorStockClockFrequency(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorStockBusFrequency(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorStockBusFrequency)
	{
		return CPUIDSDK_fp_GetProcessorStockBusFrequency(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetProcessorMaxCacheLevel(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorMaxCacheLevel)
	{
		return CPUIDSDK_fp_GetProcessorMaxCacheLevel(objptr, _proc_index);
	}
	return I_UNDEFINED_VALUE;
}

void CPUIDSDK::GetProcessorCacheParameters(int _proc_index, int _cache_level, int _cache_type, int *_NbCaches, int *_size)
{
	*_NbCaches = I_UNDEFINED_VALUE;

	if (CPUIDSDK_fp_GetProcessorCacheParameters)
	{
		CPUIDSDK_fp_GetProcessorCacheParameters(objptr, _proc_index, _cache_level, _cache_type, _NbCaches, _size);
	}
}

void CPUIDSDK::GetProcessorExtendedCacheParameters(int _proc_index, int _cache_level, int _cache_type, int *_associativity, int *_line_size)
{
	*_associativity = I_UNDEFINED_VALUE;
	*_line_size = I_UNDEFINED_VALUE;

	if (CPUIDSDK_fp_GetProcessorExtendedCacheParameters)
	{
		CPUIDSDK_fp_GetProcessorExtendedCacheParameters(objptr, _proc_index, _cache_level, _cache_type, _associativity, _line_size);
	}
}

BOOL CPUIDSDK::GetHyperThreadingStatus(int _proc_index, int *_supported, int *_enabled)
{
	if (CPUIDSDK_fp_GetHyperThreadingStatus)
	{
		return ((CPUIDSDK_fp_GetHyperThreadingStatus(objptr, _proc_index, _supported, _enabled) == 1)?TRUE:FALSE);
	}
	return FALSE;
}

BOOL CPUIDSDK::GetVirtualTechnologyStatus(int _proc_index, int *_supported, int *_enabled)
{
	if (CPUIDSDK_fp_GetVirtualTechnologyStatus)
	{
		return ((CPUIDSDK_fp_GetVirtualTechnologyStatus(objptr, _proc_index, _supported, _enabled) == 1)?TRUE:FALSE);
	}
	return FALSE;
}

unsigned int CPUIDSDK::GetProcessorID(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorID)
	{
		return (unsigned int)CPUIDSDK_fp_GetProcessorID(objptr, _proc_index);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Processor FID/VID
///////////////////////////////////////////////////////////////////////////////////////////////////

float CPUIDSDK::GetProcessorVoltageID(int _proc_index)
{
	if (CPUIDSDK_fp_GetProcessorVoltageID)
	{
		return CPUIDSDK_fp_GetProcessorVoltageID(objptr, _proc_index);
	}
	return F_UNDEFINED_VALUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Memory
///////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CPUIDSDK::GetNorthBridgeVendor(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetNorthBridgeVendor)
	{
		BSTR szTmp = CPUIDSDK_fp_GetNorthBridgeVendor(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetNorthBridgeModel(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetNorthBridgeModel)
	{
		BSTR szTmp = CPUIDSDK_fp_GetNorthBridgeModel(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetNorthBridgeRevision(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetNorthBridgeRevision)
	{
		BSTR szTmp = CPUIDSDK_fp_GetNorthBridgeRevision(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSouthBridgeVendor(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSouthBridgeVendor)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSouthBridgeVendor(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSouthBridgeModel(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSouthBridgeModel)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSouthBridgeModel(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSouthBridgeRevision(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSouthBridgeRevision)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSouthBridgeRevision(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

int CPUIDSDK::GetMemoryType()
{
	if (CPUIDSDK_fp_GetMemoryType)
	{
		return CPUIDSDK_fp_GetMemoryType(objptr);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetMemorySize()
{
	if (CPUIDSDK_fp_GetMemorySize)
	{
		return CPUIDSDK_fp_GetMemorySize(objptr);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetMemoryNumberOfChannels()
{
	if (CPUIDSDK_fp_GetMemoryNumberOfChannels)
	{
		return CPUIDSDK_fp_GetMemoryNumberOfChannels(objptr);
	}
	return I_UNDEFINED_VALUE;
}

float CPUIDSDK::GetMemoryClockFrequency()
{
	if (CPUIDSDK_fp_GetMemoryClockFrequency)
	{
		return CPUIDSDK_fp_GetMemoryClockFrequency(objptr);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetMemoryCASLatency()
{
	if (CPUIDSDK_fp_GetMemoryCASLatency)
	{
		return CPUIDSDK_fp_GetMemoryCASLatency(objptr);
	}
	return F_UNDEFINED_VALUE;
}

int CPUIDSDK::GetMemoryRAStoCASDelay()
{
	if (CPUIDSDK_fp_GetMemoryRAStoCASDelay)
	{
		return CPUIDSDK_fp_GetMemoryRAStoCASDelay(objptr);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetMemoryRASPrecharge()
{
	if (CPUIDSDK_fp_GetMemoryRASPrecharge)
	{
		return CPUIDSDK_fp_GetMemoryRASPrecharge(objptr);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetMemoryTRAS()
{
	if (CPUIDSDK_fp_GetMemoryTRAS)
	{
		return CPUIDSDK_fp_GetMemoryTRAS(objptr);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetMemoryTRC()
{
	if (CPUIDSDK_fp_GetMemoryTRC)
	{
		return CPUIDSDK_fp_GetMemoryTRC(objptr);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetMemoryCommandRate()
{
	if (CPUIDSDK_fp_GetMemoryCommandRate)
	{
		return CPUIDSDK_fp_GetMemoryCommandRate(objptr);
	}
	return I_UNDEFINED_VALUE;
}

float CPUIDSDK::ComputeMemoryFrequency(float _fsb, float _cpu_clock_multiplier)
{
	if (CPUIDSDK_fp_ComputeMemoryFrequency)
	{
		return CPUIDSDK_fp_ComputeMemoryFrequency(objptr, _fsb, _cpu_clock_multiplier);
	}
	return F_UNDEFINED_VALUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// BIOS & Mainboard
///////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CPUIDSDK::GetBIOSVendor(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetBIOSVendor)
	{
		BSTR szTmp = CPUIDSDK_fp_GetBIOSVendor(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetBIOSVersion(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetBIOSVersion)
	{
		BSTR szTmp = CPUIDSDK_fp_GetBIOSVersion(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetBIOSDate(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetBIOSDate)
	{
		BSTR szTmp = CPUIDSDK_fp_GetBIOSDate(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetBIOSType(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetBIOSType)
	{
		BSTR szTmp = CPUIDSDK_fp_GetBIOSType(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

int CPUIDSDK::GetBIOSROMSize()
{
	if (CPUIDSDK_fp_GetBIOSROMSize)
	{
		return CPUIDSDK_fp_GetBIOSROMSize(objptr);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetMainboardVendor(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetMainboardVendor)
	{
		BSTR szTmp = CPUIDSDK_fp_GetMainboardVendor(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetMainboardModel(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetMainboardModel)
	{
		BSTR szTmp = CPUIDSDK_fp_GetMainboardModel(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetMainboardRevision(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetMainboardRevision)
	{
		BSTR szTmp = CPUIDSDK_fp_GetMainboardRevision(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetMainboardSerialNumber(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetMainboardSerialNumber)
	{
		BSTR szTmp = CPUIDSDK_fp_GetMainboardSerialNumber(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSystemManufacturer(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSystemManufacturer)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSystemManufacturer(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSystemProductName(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSystemProductName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSystemProductName(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSystemVersion(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSystemVersion)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSystemVersion(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSystemSerialNumber(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSystemSerialNumber)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSystemSerialNumber(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSystemUUID(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSystemUUID)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSystemUUID(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetChassisManufacturer(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetChassisManufacturer)
	{
		BSTR szTmp = CPUIDSDK_fp_GetChassisManufacturer(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetChassisType(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetChassisType)
	{
		BSTR szTmp = CPUIDSDK_fp_GetChassisType(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetChassisSerialNumber(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetChassisSerialNumber)
	{
		BSTR szTmp = CPUIDSDK_fp_GetChassisSerialNumber(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetMemoryInfosExt(char *_szLocation, char *_szUsage, char *_szCorrection)
{
	BSTR szLocation, szUsage, szCorrection;

	if (CPUIDSDK_fp_GetMemoryInfosExt)
	{
		if (CPUIDSDK_fp_GetMemoryInfosExt(objptr, &szLocation, &szUsage, &szCorrection))
		{
			if (_szLocation)
			{
				sprintf_s(_szLocation, 128, (char *)szLocation);
				SysFreeString(szLocation);
			}
			if (_szUsage)
			{
				sprintf_s(_szUsage, 128, (char *)szUsage);
				SysFreeString(szUsage);
			}
			if (_szCorrection)
			{
				sprintf_s(_szCorrection, 128, (char *)szCorrection);
				SysFreeString(szCorrection);
			}
			return TRUE;
		}
	}
	return FALSE;
}

int CPUIDSDK::GetNumberOfMemoryDevices()
{
	if (CPUIDSDK_fp_GetNumberOfMemoryDevices)
	{
		return CPUIDSDK_fp_GetNumberOfMemoryDevices(objptr);
	}
	return 0;
}

BOOL CPUIDSDK::GetMemoryDeviceInfos(int _device_index, int *_size, char *_szFormat)
{
	BSTR szName;

	if (CPUIDSDK_fp_GetMemoryDeviceInfos)
	{
		if (CPUIDSDK_fp_GetMemoryDeviceInfos(objptr, _device_index, _size, &szName))
		{
			if (_szFormat)
			{
				sprintf_s(_szFormat, 128, (char *)szName);
				SysFreeString(szName);
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetMemoryDeviceInfosExt(int _device_index, char *_szDesignation, char *_szType, int *_total_width, int *_data_width, int *_speed)
{
	BSTR szDesignation, szType;

	if (CPUIDSDK_fp_GetMemoryDeviceInfosExt)
	{
		if (CPUIDSDK_fp_GetMemoryDeviceInfosExt(objptr, _device_index, &szDesignation, &szType, _total_width, _data_width, _speed))
		{
			if (_szDesignation)
			{
				sprintf_s(_szDesignation, 128, (char *)szDesignation);
				SysFreeString(szDesignation);
			}
			if (_szType)
			{
				sprintf_s(_szType, 128, (char *)szType);
				SysFreeString(szType);
			}
			return TRUE;
		}
	}
	return FALSE;
}

void CPUIDSDK::GetMemorySlotsConfig(int *_nbslots, int *_nbusedslots, int *_slotmap, int *_maxmodulesize)
{
	if (CPUIDSDK_fp_GetMemorySlotsConfig)
	{
		return CPUIDSDK_fp_GetMemorySlotsConfig(objptr, _nbslots, _nbusedslots, _slotmap, _maxmodulesize);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// SPD
///////////////////////////////////////////////////////////////////////////////////////////////////

int CPUIDSDK::GetNumberOfSPDModules()
{
	if (CPUIDSDK_fp_GetNumberOfSPDModules)
	{
		return CPUIDSDK_fp_GetNumberOfSPDModules(objptr);
	}
	return 0;
}

BOOL CPUIDSDK::GetSPDModuleAddress(int _spd_index, int *_host_index, int *_channel, int *_address)
{
	if (CPUIDSDK_fp_GetSPDModuleAddress)
	{
		return ((CPUIDSDK_fp_GetSPDModuleAddress(objptr, _spd_index, _host_index, _channel, _address) == 1)?TRUE:FALSE);
	}
	return FALSE;

}

int CPUIDSDK::GetSPDModuleType(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleType)
	{
		return CPUIDSDK_fp_GetSPDModuleType(objptr, _spd_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetSPDModuleSize(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleSize)
	{
		return CPUIDSDK_fp_GetSPDModuleSize(objptr, _spd_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetSPDModuleFormat(int _spd_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSPDModuleFormat)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSPDModuleFormat(objptr, _spd_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSPDModuleManufacturingDate(int _spd_index, int *_year, int *_week)
{
	if (CPUIDSDK_fp_GetSPDModuleManufacturingDate)
	{
		return CPUIDSDK_fp_GetSPDModuleManufacturingDate(objptr, _spd_index, _year, _week);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetSPDModuleNumberOfBanks(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleNumberOfBanks)
	{
		return CPUIDSDK_fp_GetSPDModuleNumberOfBanks(objptr, _spd_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetSPDModuleDataWidth(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleDataWidth)
	{
		return CPUIDSDK_fp_GetSPDModuleDataWidth(objptr, _spd_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetSPDModuleManufacturer(int _spd_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSPDModuleManufacturer)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSPDModuleManufacturer(objptr, _spd_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSPDModuleManufacturerID(int _spd_index, unsigned char *_id)
{
	if (CPUIDSDK_fp_GetSPDModuleManufacturerID)
	{
		return CPUIDSDK_fp_GetSPDModuleManufacturerID(objptr, _spd_index,_id);
	}
	return FALSE;
}

int CPUIDSDK::GetSPDModuleMaxFrequency(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleMaxFrequency)
	{
		return CPUIDSDK_fp_GetSPDModuleMaxFrequency(objptr, _spd_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetSPDModuleSpecification(int _spd_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSPDModuleSpecification)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSPDModuleSpecification(objptr, _spd_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSPDModulePartNumber(int _spd_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSPDModulePartNumber)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSPDModulePartNumber(objptr, _spd_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetSPDModuleSerialNumber(int _spd_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetSPDModuleSerialNumber)
	{
		BSTR szTmp = CPUIDSDK_fp_GetSPDModuleSerialNumber(objptr, _spd_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

float CPUIDSDK::GetSPDModuleMinTRCD(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleMinTRCD)
	{
		return CPUIDSDK_fp_GetSPDModuleMinTRCD(objptr, _spd_index);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetSPDModuleMinTRP(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleMinTRP)
	{
		return CPUIDSDK_fp_GetSPDModuleMinTRP(objptr, _spd_index);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetSPDModuleMinTRAS(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleMinTRAS)
	{
		return CPUIDSDK_fp_GetSPDModuleMinTRAS(objptr, _spd_index);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetSPDModuleMinTRC(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleMinTRC)
	{
		return CPUIDSDK_fp_GetSPDModuleMinTRC(objptr, _spd_index);
	}
	return F_UNDEFINED_VALUE;
}

int CPUIDSDK::GetSPDModuleNumberOfProfiles(int _spd_index)
{
	if (CPUIDSDK_fp_GetSPDModuleNumberOfProfiles)
	{
		return CPUIDSDK_fp_GetSPDModuleNumberOfProfiles(objptr, _spd_index);
	}
	return I_UNDEFINED_VALUE;
}

void CPUIDSDK::GetSPDModuleProfileInfos(int _spd_index, int _profile_index, float *_frequency, float *_tCL, float *_nominal_vdd)
{
	if (CPUIDSDK_fp_GetSPDModuleProfileInfos)
	{
		CPUIDSDK_fp_GetSPDModuleProfileInfos(objptr, _spd_index, _profile_index, _frequency, _tCL, _nominal_vdd);
	}
}

int CPUIDSDK::GetSPDModuleNumberOfEPPProfiles(int _spd_index, int *_epp_revision)
{
	if (CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles)
	{
		return CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles(objptr, _spd_index, _epp_revision);
	}
	return I_UNDEFINED_VALUE;
}

void CPUIDSDK::GetSPDModuleEPPProfileInfos(int _spd_index, int _profile_index, float *_frequency, float *_tCL, float *_tRCD, float *_tRAS, float *_tRP, float *_tRC, float *_nominal_vdd)
{
	if (CPUIDSDK_fp_GetSPDModuleEPPProfileInfos)
	{
		CPUIDSDK_fp_GetSPDModuleEPPProfileInfos(objptr, _spd_index, _profile_index, _frequency, _tCL, _tRCD, _tRAS, _tRP, _tRC, _nominal_vdd);
	}
}

int CPUIDSDK::GetSPDModuleNumberOfXMPProfiles(int _spd_index, int *_xmp_revision)
{
	if (CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles)
	{
		return CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles(objptr, _spd_index, _xmp_revision);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetSPDModuleXMPProfileNumberOfCL(int _spd_index, int _profile_index)
{
	if (CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL)
	{
		return CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL(objptr, _spd_index, _profile_index);
	}
	return I_UNDEFINED_VALUE;
}

void CPUIDSDK::GetSPDModuleXMPProfileCLInfos(int _spd_index, int _profile_index, int _cl_index, float *_frequency, float *_CL)
{
	if (CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos)
	{
		CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos(objptr, _spd_index, _profile_index, _cl_index, _frequency, _CL);
	}
}

void CPUIDSDK::GetSPDModuleXMPProfileInfos(int _spd_index, int _profile_index, float *_tRCD, float *_tRAS, float *_tRP, float *_nominal_vdd, int *_max_freq, float *_max_CL)
{
	if (CPUIDSDK_fp_GetSPDModuleXMPProfileInfos)
	{
		CPUIDSDK_fp_GetSPDModuleXMPProfileInfos(objptr, _spd_index, _profile_index, _tRCD, _tRAS, _tRP, _nominal_vdd, _max_freq, _max_CL);
	}
}

int CPUIDSDK::GetSPDModuleNumberOfAMPProfiles(int _spd_index, int *_amp_revision)
{
	if (CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles)
	{
		return CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles(objptr, _spd_index, _amp_revision);
	}
	return I_UNDEFINED_VALUE;
}

void CPUIDSDK::GetSPDModuleAMPProfileInfos(int _spd_index, int _profile_index, int *_frequency, float *_fMinCycleTime, float *_tCL, float *_tRCD, float *_tRAS, float *_tRP, float *_tRC)
{
	if (CPUIDSDK_fp_GetSPDModuleAMPProfileInfos)
	{
		CPUIDSDK_fp_GetSPDModuleAMPProfileInfos(objptr, _spd_index, _profile_index, _frequency, _fMinCycleTime, _tCL, _tRCD, _tRAS, _tRP, _tRC);
	}
}

int CPUIDSDK::GetSPDModuleRawData(int _spd_index, int _offset)
{
	if (CPUIDSDK_fp_GetSPDModuleRawData)
	{
		return CPUIDSDK_fp_GetSPDModuleRawData(objptr, _spd_index, _offset);
	}
	return I_UNDEFINED_VALUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Display
///////////////////////////////////////////////////////////////////////////////////////////////////

int CPUIDSDK::GetNumberOfDisplayAdapter()
{
	if (CPUIDSDK_fp_GetNumberOfDisplayAdapter)
	{
		return CPUIDSDK_fp_GetNumberOfDisplayAdapter(objptr);
	}
	return 0;
}

BOOL CPUIDSDK::GetDisplayAdapterName(int _adapter_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetDisplayAdapterName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetDisplayAdapterName(objptr, _adapter_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetDisplayAdapterCodeName(int _adapter_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetDisplayAdapterCodeName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetDisplayAdapterCodeName(objptr, _adapter_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

int CPUIDSDK::GetDisplayAdapterNumberOfPerformanceLevels(int _adapter_index)
{
	if (CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels)
	{
		return CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels(objptr, _adapter_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetDisplayAdapterCurrentPerformanceLevel(int _adapter_index)
{
	if (CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel)
	{
		return CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel(objptr, _adapter_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetDisplayAdapterPerformanceLevelName(int _adapter_index, int _perf_level, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName(objptr, _adapter_index, _perf_level);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

float CPUIDSDK::GetDisplayAdapterClock(int _adapter_index, int _perf_level, int _domain)
{
	if (CPUIDSDK_fp_GetDisplayAdapterClock)
	{
		return CPUIDSDK_fp_GetDisplayAdapterClock(objptr, _adapter_index, _perf_level, _domain);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetDisplayAdapterStockClock(int _adapter_index, int _perf_level, int _domain)
{
	if (CPUIDSDK_fp_GetDisplayAdapterStockClock)
	{
		return CPUIDSDK_fp_GetDisplayAdapterStockClock(objptr, _adapter_index, _perf_level, _domain);
	}
	return F_UNDEFINED_VALUE;
}

float CPUIDSDK::GetDisplayAdapterTemperature(int _adapter_index, int _domain)
{
	if (CPUIDSDK_fp_GetDisplayAdapterTemperature)
	{
		return CPUIDSDK_fp_GetDisplayAdapterTemperature(objptr, _adapter_index, _domain);
	}
	return F_UNDEFINED_VALUE;
}

int CPUIDSDK::GetDisplayAdapterFanSpeed(int _adapter_index)
{
	if (CPUIDSDK_fp_GetDisplayAdapterFanSpeed)
	{
		return CPUIDSDK_fp_GetDisplayAdapterFanSpeed(objptr, _adapter_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetDisplayAdapterFanPWM(int _adapter_index)
{
	if (CPUIDSDK_fp_GetDisplayAdapterFanPWM)
	{
		return CPUIDSDK_fp_GetDisplayAdapterFanPWM(objptr, _adapter_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetDisplayAdapterMemoryType(int _adapter_index, int *_type)
{
	if (CPUIDSDK_fp_GetDisplayAdapterMemoryType)
	{
		return (CPUIDSDK_fp_GetDisplayAdapterMemoryType(objptr, _adapter_index, _type) == 1)?TRUE:FALSE;
	}
	return FALSE;
}

BOOL CPUIDSDK::GetDisplayAdapterMemorySize(int _adapter_index, int *_size)
{
	if (CPUIDSDK_fp_GetDisplayAdapterMemorySize)
	{
		return (CPUIDSDK_fp_GetDisplayAdapterMemorySize(objptr, _adapter_index, _size) == 1)?TRUE:FALSE;
	}
	return FALSE;
}

BOOL CPUIDSDK::GetDisplayAdapterMemoryBusWidth(int _adapter_index, int *_bus_width)
{
	if (CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth)
	{
		return (CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth(objptr, _adapter_index, _bus_width) == 1)?TRUE:FALSE;
	}
	return FALSE;
}

BOOL CPUIDSDK::GetDisplayDriverVersion(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetDisplayDriverVersion)
	{
		BSTR szTmp = CPUIDSDK_fp_GetDisplayDriverVersion(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetDirectXVersion(char *_szBuffer)
{
	if (CPUIDSDK_fp_GetDirectXVersion)
	{
		BSTR szTmp = CPUIDSDK_fp_GetDirectXVersion(objptr);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetDisplayAdapterBusInfos(int _adapter_index, int *_bus_type, int *_multi_vpu)
{
	if (CPUIDSDK_fp_GetDisplayAdapterBusInfos)
	{
		return (CPUIDSDK_fp_GetDisplayAdapterBusInfos(objptr, _adapter_index, _bus_type, _multi_vpu) == 1)?TRUE:FALSE;
	}
	return FALSE;
}

float CPUIDSDK::GetDisplayAdapterManufacturingProcess(int _adapter_index)
{
	if (CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess)
	{
		return CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess(objptr, _adapter_index);
	}
	return F_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetDisplayAdapterPCIID(int _adapter_index, int *_vendor_id, int *_device_id, int *_revision_id, int *_sub_vendor_id, int *_sub_model_id)
{
	if (CPUIDSDK_fp_GetDisplayAdapterPCIID)
	{
		if (CPUIDSDK_fp_GetDisplayAdapterPCIID(objptr, _adapter_index, _vendor_id, _device_id, _revision_id, _sub_vendor_id, _sub_model_id) == 1)
			return TRUE;
		else
			return FALSE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// HDD
///////////////////////////////////////////////////////////////////////////////////////////////////

int CPUIDSDK::GetNumberOfHDD()
{
	if (CPUIDSDK_fp_GetNumberOfHDD)
	{
		return CPUIDSDK_fp_GetNumberOfHDD(objptr);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetHDDName(int _hdd_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetHDDName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetHDDName(objptr, _hdd_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetHDDRevision(int _hdd_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetHDDRevision)
	{
		BSTR szTmp = CPUIDSDK_fp_GetHDDRevision(objptr, _hdd_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetHDDSerialNumber(int _hdd_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetHDDSerialNumber)
	{
		BSTR szTmp = CPUIDSDK_fp_GetHDDSerialNumber(objptr, _hdd_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

float CPUIDSDK::GetHDDTemperature(int _hdd_index, int _source)
{
	if (CPUIDSDK_fp_GetHDDTemperature)
	{
		return CPUIDSDK_fp_GetHDDTemperature(objptr, _hdd_index, _source);
	}
	return F_UNDEFINED_VALUE;
}

int CPUIDSDK::GetHDDNumberOfVolumes(int _hdd_index)
{
	if (CPUIDSDK_fp_GetHDDNumberOfVolumes)
	{
		return CPUIDSDK_fp_GetHDDNumberOfVolumes(objptr, _hdd_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetHDDVolumeLetter(int _hdd_index, int _volume_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetHDDVolumeLetter)
	{
		BSTR szTmp = CPUIDSDK_fp_GetHDDVolumeLetter(objptr, _hdd_index, _volume_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetHDDVolumeName(int _hdd_index, int _volume_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetHDDVolumeName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetHDDVolumeName(objptr, _hdd_index, _volume_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

float CPUIDSDK::GetHDDVolumeSize(int _hdd_index, int _volume_index)
{
	if (CPUIDSDK_fp_GetHDDVolumeSize)
	{
		return CPUIDSDK_fp_GetHDDVolumeSize(objptr, _hdd_index, _volume_index);
	}
	return F_UNDEFINED_VALUE;
}

unsigned int CPUIDSDK::GetHDDVolumeSerial(int _hdd_index, int _volume_index)
{
	if (CPUIDSDK_fp_GetHDDVolumeSerial)
	{
		return (unsigned int)CPUIDSDK_fp_GetHDDVolumeSerial(objptr, _hdd_index, _volume_index);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetHDDNumberOfAttributes(int _hdd_index)
{
	if (CPUIDSDK_fp_GetHDDNumberOfAttributes)
	{
		return (int)CPUIDSDK_fp_GetHDDNumberOfAttributes(objptr, _hdd_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetHDDAttribute(int _hdd_index, int _attrib_index, int *_id, int *_flags, int *_value, int *_worst, unsigned char *_data)
{
	if (CPUIDSDK_fp_GetHDDAttribute)
	{
		return (BOOL)CPUIDSDK_fp_GetHDDAttribute(objptr, _hdd_index, _attrib_index, _id, _flags, _value, _worst, _data);
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Monitoring
///////////////////////////////////////////////////////////////////////////////////////////////////

int CPUIDSDK::GetNumberOfDevices()
{
	if (CPUIDSDK_fp_GetNumberOfDevices)
	{
		return CPUIDSDK_fp_GetNumberOfDevices(objptr);
	}
	return I_UNDEFINED_VALUE;
}

int CPUIDSDK::GetDeviceClass(int _device_index)
{
	if (CPUIDSDK_fp_GetDeviceClass)
	{
		return CPUIDSDK_fp_GetDeviceClass(objptr, _device_index);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetDeviceName(int _device_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetDeviceName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetDeviceName(objptr, _device_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPUIDSDK::GetDeviceSerialNumber(int _device_index, char *_szBuffer)
{
	if (CPUIDSDK_fp_GetDeviceName)
	{
		BSTR szTmp = CPUIDSDK_fp_GetDeviceSerialNumber(objptr, _device_index);
		if (szTmp)
		{
			sprintf_s(_szBuffer, 512, (char *)szTmp);
			SysFreeString(szTmp);
			return TRUE;
		}
	}
	return FALSE;
}

int CPUIDSDK::GetNumberOfSensors(int _device_index, int _sensor_class)
{
	if (CPUIDSDK_fp_GetNumberOfSensors)
	{
		return CPUIDSDK_fp_GetNumberOfSensors(objptr, _device_index, (int)_sensor_class);
	}
	return I_UNDEFINED_VALUE;
}

BOOL CPUIDSDK::GetSensorInfos(int _device_index, int _sensor_index, unsigned int _sensor_class, unsigned int *_sensor_id, char *_szName, unsigned int *_raw_value, float *_value, float *_min_value, float *_max_value)
{
	BSTR szName;

	if (CPUIDSDK_fp_GetSensorInfos)
	{
		if (CPUIDSDK_fp_GetSensorInfos(objptr, _device_index, _sensor_index, (int)_sensor_class, (int *)_sensor_id, &szName, (int *)_raw_value, _value, _min_value, _max_value))
		{
			if (_szName)
			{
				sprintf_s(_szName, 128, (char *)szName);
				SysFreeString(szName);
			}
			return TRUE;
		}
	}
	return FALSE;
}

void CPUIDSDK::SensorClearMinMax(int _device_index, int _sensor_index, int _sensor_class)
{
	if (CPUIDSDK_fp_SensorClearMinMax)
	{
		CPUIDSDK_fp_SensorClearMinMax(objptr, _device_index, _sensor_index, (int)_sensor_class);
	}
}

float CPUIDSDK::GetSensorTypeValue(int _sensor_type, int *_device_index, int *_sensor_index)
{
	if (CPUIDSDK_fp_GetSensorTypeValue)
	{
		return CPUIDSDK_fp_GetSensorTypeValue(objptr, (int)_sensor_type, _device_index, _sensor_index);
	}
	return F_UNDEFINED_VALUE;
}
