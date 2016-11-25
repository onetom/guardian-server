using System;
using System.Runtime.InteropServices;

public class CPUIDSDK
{
///////////////////////////////////////////////////////////////////////////
//	Error codes
///////////////////////////////////////////////////////////////////////////

    public const uint CPUIDSDK_ERROR_NO_ERROR =	0x00000000;

    public const uint CPUIDSDK_ERROR_EVALUATION	= 0x00000001;
    public const uint CPUIDSDK_ERROR_DRIVER	= 0x00000002;
    public const uint CPUIDSDK_ERROR_VM_RUNNING	= 0x00000004;
    public const uint CPUIDSDK_ERROR_LOCKED	= 0x00000008;
    public const uint CPUIDSDK_ERROR_INVALID_DLL = 0x00000010;

    public const uint CPUIDSDK_EXT_ERROR_EVAL_1	= 0x00000001;
    public const uint CPUIDSDK_EXT_ERROR_EVAL_2 = 0x00000002;

///////////////////////////////////////////////////////////////////////////
//	Configuration flags
///////////////////////////////////////////////////////////////////////////

    public const uint CPUIDSDK_CONFIG_USE_SOFTWARE = 0x00000002;
    public const uint CPUIDSDK_CONFIG_USE_DMI =	0x00000004;
    public const uint CPUIDSDK_CONFIG_USE_PCI =	0x00000008;
    public const uint CPUIDSDK_CONFIG_USE_ACPI = 0x00000010;
    public const uint CPUIDSDK_CONFIG_USE_CHIPSET = 0x00000020;
    public const uint CPUIDSDK_CONFIG_USE_SMBUS = 0x00000040;
    public const uint CPUIDSDK_CONFIG_USE_SPD = 0x00000080;
    public const uint CPUIDSDK_CONFIG_USE_STORAGE = 0x00000100;
    public const uint CPUIDSDK_CONFIG_USE_GRAPHICS = 0x00000200;
    public const uint CPUIDSDK_CONFIG_USE_HWMONITORING = 0x00000400;
    public const uint CPUIDSDK_CONFIG_USE_PROCESSOR = 0x00000800;
    public const uint CPUIDSDK_CONFIG_USE_DISPLAY_API = 0x00001000;
    public const uint CPUIDSDK_CONFIG_USE_ACPI_TIMER = 0x00004000;

    public const uint CPUIDSDK_CONFIG_CHECK_VM = 0x01000000;
    public const uint CPUIDSDK_CONFIG_WAKEUP_HDD = 0x02000000;

    public const uint CPUIDSDK_CONFIG_SERVER_SAFE = 0x80000000;

    public const uint CPUIDSDK_CONFIG_USE_EVERYTHING = 0x7FFFFFFF;
    
///////////////////////////////////////////////////////////////////////////
//	Constants
///////////////////////////////////////////////////////////////////////////

    public static int I_UNDEFINED_VALUE = -1;
    public static float F_UNDEFINED_VALUE = -1.0f;

    public static uint MAX_INTEGER = 0xFFFFFFFF;
    public static float MAX_FLOAT = (float)MAX_INTEGER;

    public bool IS_F_DEFINED(float _f) { return (_f > 0.0f) ? true : false; }
    public bool IS_F_DEFINED(double _f) { return (_f > 0.0) ? true : false; }
    public bool IS_I_DEFINED(int _i) { return (_i == I_UNDEFINED_VALUE) ? false : true; }
    public bool IS_I_DEFINED(uint _i) { return (_i == (uint)I_UNDEFINED_VALUE) ? false : true; }
    public bool IS_I_DEFINED(short _i) { return (_i == (short)I_UNDEFINED_VALUE) ? false : true; }
    public bool IS_I_DEFINED(ushort _i) { return (_i == (ushort)I_UNDEFINED_VALUE) ? false : true; }
    public bool IS_I_DEFINED(sbyte _i) { return (_i == (sbyte)I_UNDEFINED_VALUE) ? false : true; }
    public bool IS_I_DEFINED(byte _i) { return (_i == (byte)I_UNDEFINED_VALUE) ? false : true; }


///////////////////////////////////////////////////////////////////////////
//	Devices classes
///////////////////////////////////////////////////////////////////////////

    public const uint CLASS_DEVICE_UNKNOWN = 0x00000000;
    public const uint CLASS_DEVICE_PCI = 0x00000001;
    public const uint CLASS_DEVICE_SMBUS = 0x00000002;
    public const uint CLASS_DEVICE_PROCESSOR = 0x00000004;
    public const uint CLASS_DEVICE_LPCIO = 0x00000008;
    public const uint CLASS_DEVICE_DRIVE = 0x00000010;
    public const uint CLASS_DEVICE_DISPLAY_ADAPTER = 0x00000020;
    public const uint CLASS_DEVICE_HID = 0x00000040;
    public const uint CLASS_DEVICE_BATTERY = 0x00000080;
    public const uint CLASS_DEVICE_EVBOT = 0x00000100;
    public const uint CLASS_DEVICE_NETWORK = 0x00000200;
    public const uint CLASS_DEVICE_MAINBOARD = 0x00000400;
    public const uint CLASS_DEVICE_MEMORY_MODULE = 0x00000800;
    public const uint CLASS_DEVICE_PSU = 0x00001000;

    public const uint CLASS_DEVICE_TYPE_MASK = 0x7FFFFFFF;
    public const uint CLASS_DEVICE_COMPOSITE = 0x80000000;

///////////////////////////////////////////////////////////////////////////
//	CPU manufacturers, archis & models
///////////////////////////////////////////////////////////////////////////

    public const uint CPU_MANUFACTURER_MASK = 0xFF000000;
    public const uint CPU_FAMILY_MASK = 0xFFFFFF00;
    public const uint CPU_MODEL_MASK = 0xFFFFFFFF;

    // Manufacturers
    public const uint CPU_UNKNOWN = 0x0;
    public const uint CPU_INTEL = 0x1000000;
    public const uint CPU_AMD = 0x2000000;
    public const uint CPU_CYRIX = 0x4000000;
    public const uint CPU_VIA = 0x8000000;
    public const uint CPU_TRANSMETA = 0x10000000;

    // Intel families
    public const uint CPU_INTEL_386 = CPU_INTEL + 0x100;
    public const uint CPU_INTEL_486 = CPU_INTEL + 0x200;
    public const uint CPU_INTEL_P5 = CPU_INTEL + 0x400;
    public const uint CPU_INTEL_P6 = CPU_INTEL + 0x800;
    public const uint CPU_INTEL_NETBURST = CPU_INTEL + 0x1000;
    public const uint CPU_INTEL_MOBILE = CPU_INTEL + 0x2000;
    public const uint CPU_INTEL_CORE = CPU_INTEL + 0x4000;
    public const uint CPU_INTEL_CORE_2 = CPU_INTEL + 0x8000;
    public const uint CPU_INTEL_BONNELL	= CPU_INTEL + 0x010000;
    public const uint CPU_INTEL_SALTWELL = CPU_INTEL + 0x010100;
    public const uint CPU_INTEL_SILVERMONT = CPU_INTEL + 0x010200;
    public const uint CPU_INTEL_AIRMONT = CPU_INTEL + 0x010400;
    public const uint CPU_INTEL_NEHALEM = CPU_INTEL + 0x20000;
    public const uint CPU_INTEL_SANDY_BRIDGE = CPU_INTEL + 0x020100;
    public const uint CPU_INTEL_HASWELL = CPU_INTEL + 0x020200;
    public const uint CPU_INTEL_SKYLAKE = CPU_INTEL + 0x040000;
    public const uint CPU_INTEL_ITANIUM = CPU_INTEL + 0x100000;
    public const uint CPU_INTEL_ITANIUM_2 = CPU_INTEL + 0x100100;
    public const uint CPU_INTEL_MIC = CPU_INTEL + 0x200000;

    // Intel models
    // P5
    public const uint CPU_PENTIUM = CPU_INTEL_P5 + 0x1;
    public const uint CPU_PENTIUM_MMX = CPU_INTEL_P5 + 0x2;

    // P6
    public const uint CPU_PENTIUM_PRO = CPU_INTEL_P6 + 0x1;
    public const uint CPU_PENTIUM_2 = CPU_INTEL_P6 + 0x2;
    public const uint CPU_PENTIUM_2_M = CPU_INTEL_P6 + 0x3;
    public const uint CPU_CELERON_P2 = CPU_INTEL_P6 + 0x4;
    public const uint CPU_XEON_P2 = CPU_INTEL_P6 + 0x5;
    public const uint CPU_PENTIUM_3 = CPU_INTEL_P6 + 0x6;
    public const uint CPU_PENTIUM_3_M = CPU_INTEL_P6 + 0x7;
    public const uint CPU_PENTIUM_3_S = CPU_INTEL_P6 + 0x8;
    public const uint CPU_CELERON_P3 = CPU_INTEL_P6 + 0x9;
    public const uint CPU_XEON_P3 = CPU_INTEL_P6 + 0xA;

    // Netburst
    public const uint CPU_PENTIUM_4 = CPU_INTEL_NETBURST + 0x1;
    public const uint CPU_PENTIUM_4_M = CPU_INTEL_NETBURST + 0x2;
    public const uint CPU_PENTIUM_4_HT = CPU_INTEL_NETBURST + 0x3;
    public const uint CPU_PENTIUM_4_EE = CPU_INTEL_NETBURST + 0x4;
    public const uint CPU_CELERON_P4 = CPU_INTEL_NETBURST + 0x5;
    public const uint CPU_CELERON_D = CPU_INTEL_NETBURST + 0x6;
    public const uint CPU_XEON_P4 = CPU_INTEL_NETBURST + 0x7;
    public const uint CPU_PENTIUM_D = CPU_INTEL_NETBURST + 0x8;
    public const uint CPU_PENTIUM_XE = CPU_INTEL_NETBURST + 0x9;

    // Mobile
    public const uint CPU_PENTIUM_M = CPU_INTEL_MOBILE + 0x1;
    public const uint CPU_CELERON_M = CPU_INTEL_MOBILE + 0x2;

    // Core 1
    public const uint CPU_CORE_SOLO = CPU_INTEL_CORE + 0x1;
    public const uint CPU_CORE_DUO = CPU_INTEL_CORE + 0x2;
    public const uint CPU_CORE_CELERON_M = CPU_INTEL_CORE + 0x3;
    public const uint CPU_CORE_CELERON = CPU_INTEL_CORE + 0x4;

    // Core 2
    public const uint CPU_CORE_2_DUO = CPU_INTEL_CORE_2 + 0x1;
    public const uint CPU_CORE_2_EE = CPU_INTEL_CORE_2 + 0x2;
    public const uint CPU_CORE_2_XEON = CPU_INTEL_CORE_2 + 0x3;
    public const uint CPU_CORE_2_CELERON = CPU_INTEL_CORE_2 + 0x4;
    public const uint CPU_CORE_2_QUAD = CPU_INTEL_CORE_2 + 0x5;
    public const uint CPU_CORE_2_PENTIUM = CPU_INTEL_CORE_2 + 0x6;
    public const uint CPU_CORE_2_CELERON_DC = CPU_INTEL_CORE_2 + 0x7;
    public const uint CPU_CORE_2_SOLO = CPU_INTEL_CORE_2 + 0x8;

    // Bonnell
    public const uint CPU_BONNELL_ATOM = CPU_INTEL_BONNELL + 0x01;

    // Saltwell
    public const uint CPU_SALTWELL_ATOM = CPU_INTEL_SALTWELL + 0x01;

    // Silvermont
    public const uint CPU_SILVERMONT_ATOM =	CPU_INTEL_SILVERMONT + 0x01;
    public const uint CPU_SILVERMONT_CELERON = CPU_INTEL_SILVERMONT + 0x02;
    public const uint CPU_SILVERMONT_PENTIUM = CPU_INTEL_SILVERMONT + 0x03;
    public const uint CPU_SILVERMONT_ATOM_X7 = CPU_INTEL_SILVERMONT + 0x04;
    public const uint CPU_SILVERMONT_ATOM_X5 = CPU_INTEL_SILVERMONT + 0x05;
    public const uint CPU_SILVERMONT_ATOM_X3 = CPU_INTEL_SILVERMONT + 0x06;

    // Nehalem
    public const uint CPU_NEHALEM_CORE_I7 = CPU_INTEL_NEHALEM + 0x1;
    public const uint CPU_NEHALEM_CORE_I7E = CPU_INTEL_NEHALEM + 0x2;
    public const uint CPU_NEHALEM_XEON = CPU_INTEL_NEHALEM + 0x3;
    public const uint CPU_NEHALEM_CORE_I3 = CPU_INTEL_NEHALEM + 0x4;
    public const uint CPU_NEHALEM_CORE_I5 = CPU_INTEL_NEHALEM + 0x5;
    public const uint CPU_NEHALEM_PENTIUM = CPU_INTEL_NEHALEM + 0x7;
    public const uint CPU_NEHALEM_CELERON = CPU_INTEL_NEHALEM + 0x8;

    // Sandybridge
    public const uint CPU_SANDY_BRIDGE_CORE_I7 = CPU_INTEL_SANDY_BRIDGE + 0x01;
    public const uint CPU_SANDY_BRIDGE_CORE_I7E = CPU_INTEL_SANDY_BRIDGE + 0x02;
    public const uint CPU_SANDY_BRIDGE_XEON	= CPU_INTEL_SANDY_BRIDGE + 0x03;
    public const uint CPU_SANDY_BRIDGE_CORE_I3 = CPU_INTEL_SANDY_BRIDGE + 0x04;
    public const uint CPU_SANDY_BRIDGE_CORE_I5 = CPU_INTEL_SANDY_BRIDGE + 0x05;
    public const uint CPU_SANDY_BRIDGE_PENTIUM = CPU_INTEL_SANDY_BRIDGE + 0x07;
    public const uint CPU_SANDY_BRIDGE_CELERON = CPU_INTEL_SANDY_BRIDGE + 0x08;

    // Haswell
    public const uint CPU_HASWELL_CORE_I7 = CPU_INTEL_HASWELL + 0x01;
    public const uint CPU_HASWELL_CORE_I7E = CPU_INTEL_HASWELL + 0x02;
    public const uint CPU_HASWELL_XEON = CPU_INTEL_HASWELL + 0x03;
    public const uint CPU_HASWELL_CORE_I3 = CPU_INTEL_HASWELL + 0x04;
    public const uint CPU_HASWELL_CORE_I5 = CPU_INTEL_HASWELL + 0x05;
    public const uint CPU_HASWELL_PENTIUM = CPU_INTEL_HASWELL + 0x07;
    public const uint CPU_HASWELL_CELERON = CPU_INTEL_HASWELL + 0x08;
    public const uint CPU_HASWELL_CORE_M = CPU_INTEL_HASWELL + 0x09;

    // Skylake
    public const uint CPU_SKYLAKE_XEON = CPU_INTEL_SKYLAKE + 0x01;
    public const uint CPU_SKYLAKE_CORE_I7 = CPU_INTEL_SKYLAKE + 0x02;
    public const uint CPU_SKYLAKE_CORE_I5 = CPU_INTEL_SKYLAKE + 0x03;
    public const uint CPU_SKYLAKE_CORE_I3 = CPU_INTEL_SKYLAKE + 0x04;
    public const uint CPU_SKYLAKE_PENTIUM = CPU_INTEL_SKYLAKE + 0x05;
    public const uint CPU_SKYLAKE_CELERON = CPU_INTEL_SKYLAKE + 0x06;
    public const uint CPU_SKYLAKE_CORE_M7 = CPU_INTEL_SKYLAKE + 0x07;
    public const uint CPU_SKYLAKE_CORE_M5 = CPU_INTEL_SKYLAKE + 0x08;
    public const uint CPU_SKYLAKE_CORE_M3 = CPU_INTEL_SKYLAKE + 0x09;

    // AMD families
    public const uint CPU_AMD_386 = CPU_AMD + 0x000100;
    public const uint CPU_AMD_486 = CPU_AMD + 0x000200;
    public const uint CPU_AMD_K5 = CPU_AMD + 0x000400;
    public const uint CPU_AMD_K6 = CPU_AMD + 0x000800;
    public const uint CPU_AMD_K7 = CPU_AMD + 0x001000;
    public const uint CPU_AMD_K8 = CPU_AMD + 0x002000;
    public const uint CPU_AMD_K10 = CPU_AMD + 0x004000;
    public const uint CPU_AMD_K12 = CPU_AMD + 0x010000;
    public const uint CPU_AMD_K14 = CPU_AMD + 0x020000;
    public const uint CPU_AMD_K15 = CPU_AMD + 0x040000;
    public const uint CPU_AMD_K16 = CPU_AMD + 0x080000;
    public const uint CPU_AMD_K17 = CPU_AMD + 0x100000;

    // AMD models
    // K5
    public const uint CPU_K5 = CPU_AMD_K5 + 0x01;
    public const uint CPU_K5_GEODE = CPU_AMD_K5 + 0x02;

    // K6
    public const uint CPU_K6 = CPU_AMD_K6 + 0x01;
    public const uint CPU_K6_2 = CPU_AMD_K6 + 0x02;
    public const uint CPU_K6_3 = CPU_AMD_K6 + 0x03;

    // K7
    public const uint CPU_K7_ATHLON = CPU_AMD_K7 + 0x01;
    public const uint CPU_K7_ATHLON_XP = CPU_AMD_K7 + 0x02;
    public const uint CPU_K7_ATHLON_MP = CPU_AMD_K7 + 0x03;
    public const uint CPU_K7_DURON = CPU_AMD_K7 + 0x04;
    public const uint CPU_K7_SEMPRON = CPU_AMD_K7 + 0x05;
    public const uint CPU_K7_SEMPRON_M = CPU_AMD_K7 + 0x06;

    // K8
    public const uint CPU_K8_ATHLON_64 = CPU_AMD_K8 + 0x01;
    public const uint CPU_K8_ATHLON_64_M = CPU_AMD_K8 + 0x02;
    public const uint CPU_K8_ATHLON_64_FX = CPU_AMD_K8 + 0x03;
    public const uint CPU_K8_OPTERON = CPU_AMD_K8 + 0x04;
    public const uint CPU_K8_TURION_64 = CPU_AMD_K8 + 0x05;
    public const uint CPU_K8_SEMPRON = CPU_AMD_K8 + 0x06;
    public const uint CPU_K8_SEMPRON_M = CPU_AMD_K8 + 0x07;
    public const uint CPU_K8_ATHLON_64_X2 = CPU_AMD_K8 + 0x08;
    public const uint CPU_K8_TURION_64_X2 = CPU_AMD_K8 + 0x09;
    public const uint CPU_K8_ATHLON_NEO = CPU_AMD_K8 + 0x0A;

    // K10
    public const uint CPU_K10_PHENOM = CPU_AMD_K10 + 0x01;
    public const uint CPU_K10_PHENOM_X3 = CPU_AMD_K10 + 0x02;
    public const uint CPU_K10_PHENOM_FX = CPU_AMD_K10 + 0x03;
    public const uint CPU_K10_OPTERON = CPU_AMD_K10 + 0x04;
    public const uint CPU_K10_TURION_64 = CPU_AMD_K10 + 0x05;
    public const uint CPU_K10_TURION_64_ULTRA = CPU_AMD_K10 + 0x06;
    public const uint CPU_K10_ATHLON_64 = CPU_AMD_K10 + 0x07;
    public const uint CPU_K10_SEMPRON = CPU_AMD_K10 + 0x08;
    public const uint CPU_K10_ATHLON_2 = CPU_AMD_K10 + 0x11;
    public const uint CPU_K10_ATHLON_2_X2 = CPU_AMD_K10 + 0x0B;
    public const uint CPU_K10_ATHLON_2_X3 = CPU_AMD_K10 + 0x0D;
    public const uint CPU_K10_ATHLON_2_X4 = CPU_AMD_K10 + 0x0C;
    public const uint CPU_K10_PHENOM_II = CPU_AMD_K10 + 0x09;
    public const uint CPU_K10_PHENOM_II_X2 = CPU_AMD_K10 + 0x0A;
    public const uint CPU_K10_PHENOM_II_X3 = CPU_AMD_K10 + 0x0E;
    public const uint CPU_K10_PHENOM_II_X4 = CPU_AMD_K10 + 0x0F;
    public const uint CPU_K10_PHENOM_II_X6 = CPU_AMD_K10 + 0x10;

    // K15
    public const uint CPU_K15_FXB = CPU_AMD_K15 + 0x01;
    public const uint CPU_K15_OPTERON = CPU_AMD_K15 + 0x02;
    public const uint CPU_K15_A10T = CPU_AMD_K15 + 0x03;
    public const uint CPU_K15_A8T = CPU_AMD_K15 + 0x04;
    public const uint CPU_K15_A6T = CPU_AMD_K15 + 0x05;
    public const uint CPU_K15_A4T = CPU_AMD_K15 + 0x06;
    public const uint CPU_K15_ATHLON_X4 = CPU_AMD_K15 + 0x07;
    public const uint CPU_K15_FXV = CPU_AMD_K15 + 0x08;
    public const uint CPU_K15_A10R = CPU_AMD_K15 + 0x09;
    public const uint CPU_K15_A8R = CPU_AMD_K15 + 0x0A;
    public const uint CPU_K15_A6R = CPU_AMD_K15 + 0x0B;
    public const uint CPU_K15_A4R = CPU_AMD_K15 + 0x0C;
    public const uint CPU_K15_SEMPRON = CPU_AMD_K15 + 0x0D;
    public const uint CPU_K15_ATHLON_X2	= CPU_AMD_K15 + 0x0E;
    public const uint CPU_K15_FXC = CPU_AMD_K15 + 0x0F;
    public const uint CPU_K15_A10C = CPU_AMD_K15 + 0x10;
    public const uint CPU_K15_A8C = CPU_AMD_K15 + 0x11;
    public const uint CPU_K15_A6C = CPU_AMD_K15 + 0x12;
    public const uint CPU_K15_A4C = CPU_AMD_K15 + 0x13;
    public const uint CPU_K15_A12 = CPU_AMD_K15 + 0x14;

    // K16
    public const uint CPU_K16_A6 = CPU_AMD_K16 + 0x01;
    public const uint CPU_K16_A4 = CPU_AMD_K16 + 0x02;
    public const uint CPU_K16_OPTERON =	CPU_AMD_K16 + 0x05;
    public const uint CPU_K16_ATHLON = CPU_AMD_K16 + 0x06;
    public const uint CPU_K16_SEMPRON = CPU_AMD_K16 + 0x07;
    public const uint CPU_K16_E1 = CPU_AMD_K16 + 0x08;
    public const uint CPU_K16_E2 = CPU_AMD_K16 + 0x09;
    public const uint CPU_K16_A8 = CPU_AMD_K16 + 0x0A;
    public const uint CPU_K16_A10 = CPU_AMD_K16 + 0x0B;

    // VIA families
    public const uint CPU_VIA_WINCHIP = CPU_VIA + 0x000400;
    public const uint CPU_VIA_C3 = CPU_VIA + 0x000800;
    public const uint CPU_VIA_C7 = CPU_VIA + 0x001000;
    public const uint CPU_VIA_NANO = CPU_VIA + 0x002000;

    // VIA models
    // C3
    public const uint CPU_C3 = CPU_VIA_C3 + 0x01;

    // C7
    public const uint CPU_C7 = CPU_VIA_C7 + 0x01;
    public const uint CPU_C7_M = CPU_VIA_C7 + 0x02;
    public const uint CPU_EDEN = CPU_VIA_C7 + 0x03;
    public const uint CPU_C7_D = CPU_VIA_C7 + 0x04;

    // Nano
    public const uint CPU_NANO_X2 = CPU_VIA_NANO + 0x01;
    public const uint CPU_EDEN_X2 = CPU_VIA_NANO + 0x02;
    public const uint CPU_NANO_X3 = CPU_VIA_NANO + 0x03;
    public const uint CPU_EDEN_X4 = CPU_VIA_NANO + 0x04;
    public const uint CPU_QUADCORE = CPU_VIA_NANO + 0x05;

    // Cyrix
    public const uint CPU_CYRIX_6X86 = CPU_CYRIX + 0x02;

    // Transmeta
    public const uint CPU_CRUSOE = CPU_TRANSMETA + 0x01;
    public const uint CPU_EFFICEON = CPU_TRANSMETA + 0x02;

///////////////////////////////////////////////////////////////////////////
//	Cache descriptors
///////////////////////////////////////////////////////////////////////////

    public const int CACHE_TYPE_DATA = 0x1;             // Data cache
    public const int CACHE_TYPE_INSTRUCTION = 0x2;      // Instruction cache
    public const int CACHE_TYPE_UNIFIED = 0x3;          // Unified cache
    public const int CACHE_TYPE_TRACE_CACHE = 0x4;      // Trace cache

///////////////////////////////////////////////////////////////////////////
//	Instructions sets
///////////////////////////////////////////////////////////////////////////

    public const int ISET_MMX = 0x01;
    public const int ISET_EXTENDED_MMX = 0x02;
    public const int ISET_3DNOW = 0x03;
    public const int ISET_EXTENDED_3DNOW = 0x04;
    public const int ISET_SSE = 0x05;
    public const int ISET_SSE2 = 0x06;
    public const int ISET_SSE3 = 0x07;
    public const int ISET_SSSE3 = 0x08;
    public const int ISET_SSE4_1 = 0x09;
    public const int ISET_SSE4_2 = 0x0C;
    public const int ISET_SSE4A = 0x0D;
    public const int ISET_XOP = 0x0E;
    public const int ISET_X86_64 = 0x10;
    public const int ISET_NX = 0x11;
    public const int ISET_VMX = 0x12;
    public const int ISET_AES  = 0x13;
    public const int ISET_AVX  = 0x14;
    public const int ISET_AVX2 = 0x15;
    public const int ISET_FMA3 = 0x16;
    public const int ISET_FMA4 = 0x17;
    public const int ISET_RTM = 0x18;
    public const int ISET_HLE = 0x19;
    public const int ISET_AVX512F = 0x1A;


///////////////////////////////////////////////////////////////////////////
//	Monitoring
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//	Hardware Monitor IDs
///////////////////////////////////////////////////////////////////////////

    public const int HWM_CLASS_LPC = 0x00000001;
    public const int HWM_CLASS_CPU = 0x00000002;
    public const int HWM_CLASS_HDD = 0x00000004;
    public const int HWM_CLASS_DISPLAYADAPTER = 0x00000008;
    public const int HWM_CLASS_PSU = 0x00000010;
    public const int HWM_CLASS_ACPI = 0x00000020;
    public const int HWM_CLASS_RAM = 0x00000040;
    public const int HWM_CLASS_CHASSIS = 0x00000080;
    public const int HWM_CLASS_WATERCOOLER = 0x00000100;
    public const int HWM_CLASS_BATTERY = 0x00000200;

///////////////////////////////////////////////////////////////////////////
//	Sensors classes & predefined types
///////////////////////////////////////////////////////////////////////////

    public const int SENSOR_CLASS_VOLTAGE = 0x100;
    public const int SENSOR_CLASS_TEMPERATURE = 0x200;
    public const int SENSOR_CLASS_FAN = 0x400;
    public const int SENSOR_CLASS_CURRENT = 0x800;
    public const int SENSOR_CLASS_POWER = 0x1000;
    public const int SENSOR_CLASS_FAN_PWM = 0x2000;
    public const int SENSOR_CLASS_PUMP_PWM = 0x4000;
    public const int SENSOR_CLASS_WATER_LEVEL = 0x8000;
    public const int SENSOR_CLASS_POSITION = 0x10000;
    public const int SENSOR_CLASS_CAPACITY = 0x20000;
    public const int SENSOR_CLASS_CASEOPEN = 0x40000;
    public const int SENSOR_CLASS_LEVEL = 0x80000;
    public const int SENSOR_CLASS_COUNTER = 0x100000;
    public const int SENSOR_CLASS_UTILIZATION = 0x200000;
    public const int SENSOR_CLASS_CLOCK_SPEED = 0x400000;

    public const int SENSOR_VOLTAGE_VCORE = 0x1000000 + SENSOR_CLASS_VOLTAGE;
    public const int SENSOR_VOLTAGE_3V3 = 0x2000000 + SENSOR_CLASS_VOLTAGE;      // +3.3V
    public const int SENSOR_VOLTAGE_P5V = 0x3000000 + SENSOR_CLASS_VOLTAGE;      // +5V
    public const int SENSOR_VOLTAGE_P12V = 0x4000000 + SENSOR_CLASS_VOLTAGE;     // +12V
    public const int SENSOR_VOLTAGE_M5V = 0x5000000 + SENSOR_CLASS_VOLTAGE;      // -5V
    public const int SENSOR_VOLTAGE_M12V = 0x6000000 + SENSOR_CLASS_VOLTAGE;     // -12V
    public const int SENSOR_VOLTAGE_5VSB = 0x7000000 + SENSOR_CLASS_VOLTAGE;     // +5V standby
    public const int SENSOR_VOLTAGE_DRAM = 0x8000000 + SENSOR_CLASS_VOLTAGE;

    public const int SENSOR_TEMPERATURE_CPU = 0x1000000 + SENSOR_CLASS_TEMPERATURE;

    public const int SENSOR_FAN_CPU = 0x1000000 + SENSOR_CLASS_FAN;

    public const int SENSOR_MODE_AUTO = 0x1;
    public const int SENSOR_MODE_MANUAL = 0x2;

///////////////////////////////////////////////////////////////////////////
//	Memory types
///////////////////////////////////////////////////////////////////////////

    public const int MEMORY_TYPE_SPM_RAM = 0x1;
    public const int MEMORY_TYPE_RDRAM = 0x2;
    public const int MEMORY_TYPE_EDO_RAM = 0x3;
    public const int MEMORY_TYPE_FPM_RAM = 0x4;
    public const int MEMORY_TYPE_SDRAM = 0x5;
    public const int MEMORY_TYPE_DDR_SDRAM = 0x6;
    public const int MEMORY_TYPE_DDR2_SDRAM = 0x7;
    public const int MEMORY_TYPE_DDR2_SDRAM_FB = 0x8;
    public const int MEMORY_TYPE_DDR3_SDRAM = 0x9;
    public const int MEMORY_TYPE_DDR4_SDRAM = 0xA;

///////////////////////////////////////////////////////////////////////////
//	Display Adapter infos source
///////////////////////////////////////////////////////////////////////////

    public const int DISPLAY_CLOCK_DOMAIN_GRAPHICS = 0x0;
    public const int DISPLAY_CLOCK_DOMAIN_MEMORY = 0x4;
    public const int DISPLAY_CLOCK_DOMAIN_PROCESSOR = 0x7;

    public const int MEMORY_TYPE_SDR = 1;
    public const int MEMORY_TYPE_DDR = 2;
    public const int MEMORY_TYPE_LPDDR2 = 9;
    public const int MEMORY_TYPE_DDR2 = 3;
    public const int MEMORY_TYPE_DDR3 = 7;
    public const int MEMORY_TYPE_GDDR2 = 4;
    public const int MEMORY_TYPE_GDDR3 = 5;
    public const int MEMORY_TYPE_GDDR4 = 6;
    public const int MEMORY_TYPE_GDDR5 = 8;
    public const int MEMORY_TYPE_GDDR5X = 10;
    public const int MEMORY_TYPE_HBM2 = 11;


///////////////////////////////////////////////////////////////////////////
//	DLL name & path
///////////////////////////////////////////////////////////////////////////

#if _X64_
#if DEBUG
    public const string szDllPath = "..\\..\\..\\..\\..\\..\\bin\\";
#else
    public const string szDllPath = "";
#endif
    public const string szDllFilename = "cpuidsdk64.dll";    
#else   // _X64_
#if DEBUG
    public const string szDllPath = "..\\..\\..\\..\\..\\bin\\";
#else
    public const string szDllPath = "";
#endif
    public const string szDllFilename = "cpuidsdk.dll";
#endif  // _X64_

    protected const string szDllName = szDllPath + szDllFilename;

///////////////////////////////////////////////////////////////////////////
//	DLL functions
///////////////////////////////////////////////////////////////////////////    

    [DllImport(szDllName, EntryPoint = "QueryInterface")]
    protected static extern IntPtr CPUIDSDK_fp_QueryInterface(uint _code);

//  Instance management
    private delegate IntPtr CPUIDSDK_fp_CreateInstance();
    private delegate void CPUIDSDK_fp_DestroyInstance(IntPtr objptr);
    private delegate int CPUIDSDK_fp_Init(IntPtr objptr, string _szDllPath, string _szDllFilename, int _config_flag, ref int _errorcode, ref int _extended_errorcode);
    private delegate void CPUIDSDK_fp_Close(IntPtr objptr);
    private delegate void CPUIDSDK_fp_RefreshInformation(IntPtr objptr);
    private delegate void CPUIDSDK_fp_GetDllVersion(IntPtr objptr, ref int _version);

//  CPU
    private delegate int CPUIDSDK_fp_GetNbProcessors(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetProcessorFamily(IntPtr objptr, int _proc_index);
    private delegate int CPUIDSDK_fp_GetProcessorCoreCount(IntPtr objptr, int _proc_index);
    private delegate int CPUIDSDK_fp_GetProcessorThreadCount(IntPtr objptr, int _proc_index);
    private delegate int CPUIDSDK_fp_GetProcessorCoreThreadCount(IntPtr objptr, int _proc_index, int _core_index);
    private delegate int CPUIDSDK_fp_GetProcessorThreadAPICID(IntPtr objptr, int _proc_index, int _core_index, int _thread_index);
    private delegate IntPtr CPUIDSDK_fp_GetProcessorName(IntPtr objptr, int _proc_index);
    private delegate IntPtr CPUIDSDK_fp_GetProcessorCodeName(IntPtr objptr, int _proc_index);
    private delegate IntPtr CPUIDSDK_fp_GetProcessorSpecification(IntPtr objptr, int _proc_index);
    private delegate IntPtr CPUIDSDK_fp_GetProcessorPackage(IntPtr objptr, int _proc_index);
    private delegate IntPtr CPUIDSDK_fp_GetProcessorStepping(IntPtr objptr, int _proc_index);
    private delegate float CPUIDSDK_fp_GetProcessorTDP(IntPtr objptr, int _proc_index);
    private delegate float CPUIDSDK_fp_GetProcessorManufacturingProcess(IntPtr objptr, int _proc_index);
    private delegate int CPUIDSDK_fp_IsProcessorInstructionSetAvailable(IntPtr objptr, int _proc_index, int _iset);
    private delegate float CPUIDSDK_fp_GetProcessorCoreClockFrequency(IntPtr objptr, int _proc_index, int _core_index);
    private delegate float CPUIDSDK_fp_GetProcessorCoreClockMultiplier(IntPtr objptr, int _proc_index, int _core_index);
    private delegate float CPUIDSDK_fp_GetProcessorCoreTemperature(IntPtr objptr, int _proc_index, int _core_index);
    private delegate float CPUIDSDK_fp_GetBusFrequency(IntPtr objptr);
    private delegate float CPUIDSDK_fp_GetProcessorRatedBusFrequency(IntPtr objptr, int _proc_index);
    private delegate int CPUIDSDK_fp_GetProcessorStockClockFrequency(IntPtr objptr, int _proc_index);
    private delegate int CPUIDSDK_fp_GetProcessorStockBusFrequency(IntPtr objptr, int _proc_index);
    private delegate int CPUIDSDK_fp_GetProcessorMaxCacheLevel(IntPtr objptr, int _proc_index);
    private delegate void CPUIDSDK_fp_GetProcessorCacheParameters(IntPtr objptr, int _proc_index, int _cache_level, int _cache_type, ref int _NbCaches, ref int _size);
    private delegate int CPUIDSDK_fp_GetProcessorID(IntPtr objptr, int _proc_index);
    private delegate float CPUIDSDK_fp_GetProcessorVoltageID(IntPtr objptr, int _proc_index);
 
//  Memory
    private delegate int CPUIDSDK_fp_GetMemoryType(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemorySize(IntPtr objptr);
    private delegate float CPUIDSDK_fp_GetMemoryClockFrequency(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemoryNumberOfChannels(IntPtr objptr);
    private delegate float CPUIDSDK_fp_GetMemoryCASLatency(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemoryRAStoCASDelay(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemoryRASPrecharge(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemoryTRAS(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemoryTRC(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemoryCommandRate(IntPtr objptr);

//  NB & BIOS
    private delegate IntPtr CPUIDSDK_fp_GetNorthBridgeVendor(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetNorthBridgeModel(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetNorthBridgeRevision(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetSouthBridgeVendor(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetSouthBridgeModel(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetSouthBridgeRevision(IntPtr objptr);

    private delegate void CPUIDSDK_fp_GetGraphicBusLinkParameters(IntPtr objptr, ref int _bus_type, ref int _link_width);
    private delegate void CPUIDSDK_fp_GetMemorySlotsConfig(IntPtr objptr, ref int _nbslots, ref int _nbusedslots, ref int _slotmap, ref int _maxmodulesize);

    private delegate IntPtr CPUIDSDK_fp_GetBIOSVendor(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetBIOSVersion(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetBIOSDate(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetMainboardVendor(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetMainboardModel(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetMainboardRevision(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetMainboardSerialNumber(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetSystemManufacturer(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetSystemProductName(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetSystemVersion(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetSystemSerialNumber(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetSystemUUID(IntPtr objptr);

    private delegate IntPtr CPUIDSDK_fp_GetChassisManufacturer(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetChassisType(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetChassisSerialNumber(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemoryInfosExt(IntPtr objptr, ref IntPtr _szLocation, ref IntPtr _szUsage, ref IntPtr _szCorrection);
    private delegate int CPUIDSDK_fp_GetNumberOfMemoryDevices(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetMemoryDeviceInfos(IntPtr objptr, int _device_index, ref int _size, ref IntPtr _szFormat);
    private delegate int CPUIDSDK_fp_GetMemoryDeviceInfosExt(IntPtr objptr, int _device_index, ref IntPtr _szDesignation, ref IntPtr _szType, ref int _total_width, ref int _data_width, ref int _speed);

//  SPD
    private delegate int CPUIDSDK_fp_GetNumberOfSPDModules(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetSPDModuleType(IntPtr objptr, int _spd_index);
    private delegate int CPUIDSDK_fp_GetSPDModuleSize(IntPtr objptr, int _spd_index);
    private delegate IntPtr CPUIDSDK_fp_GetSPDModuleFormat(IntPtr objptr, int _spd_index);
    private delegate IntPtr CPUIDSDK_fp_GetSPDModuleManufacturer(IntPtr objptr, int _spd_index);
    private delegate int CPUIDSDK_fp_GetSPDModuleManufacturerID(IntPtr objptr, int _spd_index, byte[] _id);
    private delegate int CPUIDSDK_fp_GetSPDModuleMaxFrequency(IntPtr objptr, int _spd_index);
    private delegate IntPtr CPUIDSDK_fp_GetSPDModuleSpecification(IntPtr objptr, int _spd_index);
    private delegate IntPtr CPUIDSDK_fp_GetSPDModulePartNumber(IntPtr objptr, int _spd_index);
    private delegate IntPtr CPUIDSDK_fp_GetSPDModuleSerialNumber(IntPtr objptr, int _spd_index);
    private delegate float CPUIDSDK_fp_GetSPDModuleMinTRCD(IntPtr objptr, int _spd_index);
    private delegate float CPUIDSDK_fp_GetSPDModuleMinTRP(IntPtr objptr, int _spd_index);
    private delegate float CPUIDSDK_fp_GetSPDModuleMinTRAS(IntPtr objptr, int _spd_index);
    private delegate float CPUIDSDK_fp_GetSPDModuleMinTRC(IntPtr objptr, int _spd_index);
    private delegate int CPUIDSDK_fp_GetSPDModuleManufacturingDate(IntPtr objptr, int _spd_index, ref int _year, ref int _week);
    private delegate int CPUIDSDK_fp_GetSPDModuleNumberOfBanks(IntPtr objptr, int _spd_index);
    private delegate int CPUIDSDK_fp_GetSPDModuleDataWidth(IntPtr objptr, int _spd_index);
    private delegate int CPUIDSDK_fp_GetSPDModuleNumberOfProfiles(IntPtr objptr, int _spd_index);
    private delegate void CPUIDSDK_fp_GetSPDModuleProfileInfos(IntPtr objptr, int _spd_index, int _profile_index, ref float _frequency, ref float _tCL, ref float _nominal_vdd);
    private delegate int CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles(IntPtr objptr, int _spd_index, ref int _epp_revision);
    private delegate void CPUIDSDK_fp_GetSPDModuleEPPProfileInfos(IntPtr objptr, int _spd_index, int _profile_index, ref float _frequency, ref float _tCL, ref float _tRCD, ref float _tRAS, ref float _tRP, ref float _tRC, ref float _nominal_vdd);
    private delegate int CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles(IntPtr objptr, int _spd_index, ref int _xmp_revision);
    private delegate int CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL(IntPtr objptr, int _spd_index, int _profile_index);
    private delegate void CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos(IntPtr objptr, int _spd_index, int _profile_index, int _cl_index, ref float _frequency, ref float _CL);
    private delegate void CPUIDSDK_fp_GetSPDModuleXMPProfileInfos(IntPtr objptr, int _spd_index, int _profile_index, ref float _tRCD, ref float _tRAS, ref float _tRP, ref float _nominal_vdd, ref int _max_freq, ref float _max_CL);
    private delegate int CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles(IntPtr objptr, int _spd_index, ref int _amp_revision);
    private delegate void CPUIDSDK_fp_GetSPDModuleAMPProfileInfos(IntPtr objptr, int _spd_index, int _profile_index, ref int _frequency, ref float _min_cycle_time, ref float _tCL, ref float _tRCD, ref float _tRAS, ref float _tRP, ref float _tRC);
    private delegate int CPUIDSDK_fp_GetSPDModuleRawData(IntPtr objptr, int _spd_index, int _offset);

//  Monitoring
    private delegate int CPUIDSDK_fp_GetNumberOfDevices(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetDeviceClass(IntPtr objptr, int _device_index);
    private delegate IntPtr CPUIDSDK_fp_GetDeviceName(IntPtr objptr, int _device_index);
    private delegate int CPUIDSDK_fp_GetNumberOfSensors(IntPtr objptr, int _device_index, int _sensor_class);
    private delegate int CPUIDSDK_fp_GetSensorInfos(IntPtr objptr, int _device_index, int _sensor_index, int _sensor_class, ref int _sensor_id, ref IntPtr _szNamePtr, ref int _raw_value, ref float _value, ref float _min_value, ref float _max_value);
    private delegate void CPUIDSDK_fp_SensorClearMinMax(IntPtr objptr, int _device_index, int _sensor_index, int _sensor_class);
    private delegate float CPUIDSDK_fp_GetSensorTypeValue(IntPtr objptr, int _sensor_type, ref int _device_index, ref int _sensor_index);

//  Display
    private delegate int CPUIDSDK_fp_GetNumberOfDisplayAdapter(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterID(IntPtr objptr, int _adapter_index);
    private delegate IntPtr CPUIDSDK_fp_GetDisplayAdapterName(IntPtr objptr, int _adapter_index);
    private delegate IntPtr CPUIDSDK_fp_GetDisplayAdapterCodeName(IntPtr objptr, int _adapter_index);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels(IntPtr objptr, int _adapter_index);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel(IntPtr objptr, int _adapter_index);
    private delegate IntPtr CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName(IntPtr objptr, int _adapter_index, int _perf_level);
    private delegate float CPUIDSDK_fp_GetDisplayAdapterClock(IntPtr objptr, int _perf_level, int _adapter_index, int _domain);
    private delegate float CPUIDSDK_fp_GetDisplayAdapterStockClock(IntPtr objptr, int _perf_level, int _adapter_index, int _domain);
    private delegate float CPUIDSDK_fp_GetDisplayAdapterTemperature(IntPtr objptr, int _adapter_index, int _domain);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterFanSpeed(IntPtr objptr, int _adapter_index);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterFanPWM(IntPtr objptr, int _adapter_index);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterMemoryType(IntPtr objptr, int _adapter_index, ref int _type);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterMemorySize(IntPtr objptr, int _adapter_index, ref int _size);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth(IntPtr objptr, int _adapter_index, ref int _bus_width);
    private delegate IntPtr CPUIDSDK_fp_GetDisplayDriverVersion(IntPtr objptr);
    private delegate IntPtr CPUIDSDK_fp_GetDirectXVersion(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetDisplayAdapterBusInfos(IntPtr objptr, int _adapter_index, ref int _bus_type, ref int _multi_vpu);
    private delegate float CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess(IntPtr objptr, int _adapter_index);

//  HDD
    private delegate int CPUIDSDK_fp_GetNumberOfHDD(IntPtr objptr);
    private delegate int CPUIDSDK_fp_GetHDDDeviceNumber(IntPtr objptr, int _hdd_index);
    private delegate IntPtr CPUIDSDK_fp_GetHDDName(IntPtr objptr, int _hdd_index);
    private delegate IntPtr CPUIDSDK_fp_GetHDDRevision(IntPtr objptr, int _hdd_index);
    private delegate IntPtr CPUIDSDK_fp_GetHDDSerialNumber(IntPtr objptr, int _hdd_index);
    private delegate int CPUIDSDK_fp_GetHDDFitnessPercent(IntPtr objptr, int _hdd_index);
    private delegate int CPUIDSDK_fp_GetHDDPerformancePercent(IntPtr objptr, int _hdd_index);
    private delegate int CPUIDSDK_fp_GetHDDNumberOfVolumes(IntPtr objptr, int _hdd_index);
    private delegate IntPtr CPUIDSDK_fp_GetHDDVolumeLetter(IntPtr objptr, int _hdd_index, int _volume_index);
    private delegate IntPtr CPUIDSDK_fp_GetHDDVolumeName(IntPtr objptr, int _hdd_index, int _volume_index);
    private delegate float CPUIDSDK_fp_GetHDDVolumeSize(IntPtr objptr, int _hdd_index, int _volume_index);
    private delegate int CPUIDSDK_fp_GetHDDVolumeSerial(IntPtr objptr, int _hdd_index, int _volume_index);
    private delegate int CPUIDSDK_fp_GetHDDNumberOfAttributes(IntPtr objptr, int _hdd_index);
    private delegate int CPUIDSDK_fp_GetHDDAttribute(IntPtr objptr, int _hdd_index, int _attrib_index, ref int _id, ref int _flags, ref int _value, ref int _worst, byte[] _data);


    protected IntPtr objptr = IntPtr.Zero;

//  Instance management
    public bool CreateInstance()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x21452459);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_CreateInstance msd = (CPUIDSDK_fp_CreateInstance)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_CreateInstance));
                objptr = msd();
                if (objptr != IntPtr.Zero)
                    return true;
                else
                    return false;
            }
            else
            {
                objptr = IntPtr.Zero;
                return false;
            }
        }
        catch (Exception e)
        {
            string message = e.Message;
            return false;
        }
    }
    public void DestroyInstance()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x30571113);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_DestroyInstance msd = (CPUIDSDK_fp_DestroyInstance)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_DestroyInstance));
                msd(objptr);
            }
        }
        catch
        {
        }
    }
    public bool Init(string _szDllPath, string _szDllFilename, uint _config_flag, ref int _errorcode, ref int _extended_errorcode)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x19937329);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_Init msd = (CPUIDSDK_fp_Init)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_Init));
                res = msd(objptr, _szDllPath, _szDllFilename, (int)_config_flag, ref _errorcode, ref _extended_errorcode);
                if (res == 1) return true;
                else return false;
            }
            else
            {
                _errorcode = (int)CPUIDSDK_ERROR_INVALID_DLL;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public void Close()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x14862213);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_Close msd = (CPUIDSDK_fp_Close)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_Close));
                msd(objptr);
            }
        }
        catch
        {
        }
    }
    public void RefreshInformation()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x75030260);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_RefreshInformation msd = (CPUIDSDK_fp_RefreshInformation)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_RefreshInformation));
                msd(objptr);
            }
        }
        catch
        {
        }
    }
    public void GetDllVersion(ref int _version)
    {
       try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x61956551);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDllVersion msd = (CPUIDSDK_fp_GetDllVersion)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDllVersion));
                msd(objptr, ref _version);
            }
        }
        catch
        {
        }
    }

//  Processor
    public int GetNumberOfProcessors()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x74126687);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNbProcessors msd = (CPUIDSDK_fp_GetNbProcessors)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNbProcessors));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetProcessorFamily(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x32350046);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorFamily msd = (CPUIDSDK_fp_GetProcessorFamily)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorFamily));
                return msd(objptr, _proc_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetProcessorCoreCount(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x70028077);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorCoreCount msd = (CPUIDSDK_fp_GetProcessorCoreCount)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorCoreCount));
                return msd(objptr, _proc_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetProcessorThreadCount(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x36189448);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorThreadCount msd = (CPUIDSDK_fp_GetProcessorThreadCount)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorThreadCount));
                return msd(objptr, _proc_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetProcessorCoreThreadCount(int _proc_index, int _core_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x63895059);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorCoreThreadCount msd = (CPUIDSDK_fp_GetProcessorCoreThreadCount)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorCoreThreadCount));
                return msd(objptr, _proc_index, _core_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetProcessorThreadAPICID(IntPtr objptr, int _proc_index, int _core_index, int _thread_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x5805773);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorThreadAPICID msd = (CPUIDSDK_fp_GetProcessorThreadAPICID)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorThreadAPICID));
                return msd(objptr, _proc_index, _core_index, _thread_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public string GetProcessorName(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x20310671);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorName msd = (CPUIDSDK_fp_GetProcessorName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorName));
                IntPtr pointer = msd(objptr, _proc_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetProcessorCodeName(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x49828055);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorCodeName msd = (CPUIDSDK_fp_GetProcessorCodeName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorCodeName));
                IntPtr pointer = msd(objptr, _proc_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetProcessorSpecification(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x40463981);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorSpecification msd = (CPUIDSDK_fp_GetProcessorSpecification)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorSpecification));
                IntPtr pointer = msd(objptr, _proc_index);
                return (Marshal.PtrToStringAnsi(pointer));
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetProcessorPackage(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x1341414);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorPackage msd = (CPUIDSDK_fp_GetProcessorPackage)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorPackage));
                IntPtr pointer = msd(objptr, _proc_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetProcessorStepping(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x28151889);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorStepping msd = (CPUIDSDK_fp_GetProcessorStepping)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorStepping));
                IntPtr pointer = msd(objptr, _proc_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public float GetProcessorTDP(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x79867689);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorTDP msd = (CPUIDSDK_fp_GetProcessorTDP)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorTDP));
                return msd(objptr, _proc_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetProcessorManufacturingProcess(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x23977925);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorManufacturingProcess msd = (CPUIDSDK_fp_GetProcessorManufacturingProcess)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorManufacturingProcess));
                return msd(objptr, _proc_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public bool IsProcessorInstructionSetAvailable(int _proc_index, int _iset)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x81550931);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_IsProcessorInstructionSetAvailable msd = (CPUIDSDK_fp_IsProcessorInstructionSetAvailable)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_IsProcessorInstructionSetAvailable));
                int res = msd(objptr, _proc_index, _iset);
                if (res == 1) return true;
                else return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public float GetProcessorCoreClockFrequency(int _proc_index, int _core_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x3472558);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorCoreClockFrequency msd = (CPUIDSDK_fp_GetProcessorCoreClockFrequency)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorCoreClockFrequency));
                return msd(objptr, _proc_index, _core_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetProcessorCoreClockMultiplier(int _proc_index, int _core_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x12802281);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorCoreClockMultiplier msd = (CPUIDSDK_fp_GetProcessorCoreClockMultiplier)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorCoreClockMultiplier));
                return msd(objptr, _proc_index, _core_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetProcessorCoreTemperature(int _proc_index, int _core_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x20560624);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorCoreTemperature msd = (CPUIDSDK_fp_GetProcessorCoreTemperature)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorCoreTemperature));
                return msd(objptr, _proc_index, _core_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetBusFrequency()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x9851369);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetBusFrequency msd = (CPUIDSDK_fp_GetBusFrequency)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetBusFrequency));
                return msd(objptr);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetProcessorRatedBusFrequency(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x33371080);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorRatedBusFrequency msd = (CPUIDSDK_fp_GetProcessorRatedBusFrequency)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorRatedBusFrequency));
                return msd(objptr, _proc_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetProcessorStockClockFrequency(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x09585365);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorStockClockFrequency msd = (CPUIDSDK_fp_GetProcessorStockClockFrequency)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorStockClockFrequency));
                return msd(objptr, _proc_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetProcessorStockBusFrequency(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x81130419);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorStockBusFrequency msd = (CPUIDSDK_fp_GetProcessorStockBusFrequency)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorStockBusFrequency));
                return msd(objptr, _proc_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public int GetProcessorMaxCacheLevel(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x11105429);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorMaxCacheLevel msd = (CPUIDSDK_fp_GetProcessorMaxCacheLevel)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorMaxCacheLevel));
                return msd(objptr, _proc_index);
            }
            return 0;
        }
        catch
        {
            return 0;
        }
    }
    public void GetProcessorCacheParameters(int _proc_index, int _cache_level, int _cache_type, ref int _NbCaches, ref int _size)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x34341922);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorCacheParameters msd = (CPUIDSDK_fp_GetProcessorCacheParameters)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorCacheParameters));
                msd(objptr, _proc_index, _cache_level, _cache_type, ref _NbCaches, ref _size);
            }
        }
        catch
        {
        }
    }
    public uint GetProcessorID(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x11017670);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorID msd = (CPUIDSDK_fp_GetProcessorID)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorID));
                return (uint)msd(objptr, _proc_index);
            }
            return 0;
        }
        catch
        {
            return 0;
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  FIV/VID
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    public float GetProcessorVoltageID(int _proc_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x12381437);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetProcessorVoltageID msd = (CPUIDSDK_fp_GetProcessorVoltageID)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetProcessorVoltageID));
                return msd(objptr, _proc_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Memory
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    public int GetMemoryType()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x29342710);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryType msd = (CPUIDSDK_fp_GetMemoryType)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryType));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetMemorySize()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x62110385);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemorySize msd = (CPUIDSDK_fp_GetMemorySize)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemorySize));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public float GetMemoryClockFrequency()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x90020894);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryClockFrequency msd = (CPUIDSDK_fp_GetMemoryClockFrequency)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryClockFrequency));
                return msd(objptr);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public int GetMemoryNumberOfChannels()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x85438592);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryNumberOfChannels msd = (CPUIDSDK_fp_GetMemoryNumberOfChannels)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryNumberOfChannels));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public float GetMemoryCASLatency()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x84046156);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryCASLatency msd = (CPUIDSDK_fp_GetMemoryCASLatency)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryCASLatency));
                return msd(objptr);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public int GetMemoryRAStoCASDelay()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x79190623);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryRAStoCASDelay msd = (CPUIDSDK_fp_GetMemoryRAStoCASDelay)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryRAStoCASDelay));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetMemoryRASPrecharge()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x39535851);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryRASPrecharge msd = (CPUIDSDK_fp_GetMemoryRASPrecharge)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryRASPrecharge));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetMemoryTRAS()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x71291988);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryTRAS msd = (CPUIDSDK_fp_GetMemoryTRAS)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryTRAS));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetMemoryTRC()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x55020883);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryTRC msd = (CPUIDSDK_fp_GetMemoryTRC)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryTRC));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetMemoryCommandRate()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x78298296);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemoryCommandRate msd = (CPUIDSDK_fp_GetMemoryCommandRate)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryCommandRate));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Chipset
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    public string GetNorthBridgeVendor()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x10414802);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNorthBridgeVendor msd = (CPUIDSDK_fp_GetNorthBridgeVendor)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNorthBridgeVendor));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetNorthBridgeModel()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x07726825);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNorthBridgeModel msd = (CPUIDSDK_fp_GetNorthBridgeModel)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNorthBridgeModel));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetNorthBridgeRevision()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x51134157);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNorthBridgeRevision msd = (CPUIDSDK_fp_GetNorthBridgeRevision)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNorthBridgeRevision));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSouthBridgeVendor()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x11173275);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSouthBridgeVendor msd = (CPUIDSDK_fp_GetSouthBridgeVendor)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSouthBridgeVendor));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSouthBridgeModel()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x86002729);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSouthBridgeModel msd = (CPUIDSDK_fp_GetSouthBridgeModel)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSouthBridgeModel));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSouthBridgeRevision()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x35194959);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSouthBridgeRevision msd = (CPUIDSDK_fp_GetSouthBridgeRevision)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSouthBridgeRevision));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public void GetGraphicBusLinkParameters(ref int _bus_type, ref int _link_width)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x00000000);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetGraphicBusLinkParameters msd = (CPUIDSDK_fp_GetGraphicBusLinkParameters)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetGraphicBusLinkParameters));
                msd(objptr, ref _bus_type, ref _link_width);
            }
        }
        catch
        {
        }
    }
    public void GetMemorySlotsConfig(ref int _nbslots, ref int _nbusedslots, ref int _slotmap, ref int _maxmodulesize)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x09748908);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMemorySlotsConfig msd = (CPUIDSDK_fp_GetMemorySlotsConfig)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemorySlotsConfig));
                msd(objptr, ref _nbslots, ref _nbusedslots, ref _slotmap, ref _maxmodulesize);
            }
        }
        catch
        {
        }
    }
    public string GetBIOSVendor()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x08870551);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetBIOSVendor msd = (CPUIDSDK_fp_GetBIOSVendor)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetBIOSVendor));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetBIOSVersion()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x75071585);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetBIOSVersion msd = (CPUIDSDK_fp_GetBIOSVersion)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetBIOSVersion));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetBIOSDate()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x17547205);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetBIOSDate msd = (CPUIDSDK_fp_GetBIOSDate)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetBIOSDate));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetMainboardVendor()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x59275458);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMainboardVendor msd = (CPUIDSDK_fp_GetMainboardVendor)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMainboardVendor));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetMainboardModel()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x52979740);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMainboardModel msd = (CPUIDSDK_fp_GetMainboardModel)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMainboardModel));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetMainboardRevision()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x88673334);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMainboardRevision msd = (CPUIDSDK_fp_GetMainboardRevision)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMainboardRevision));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetMainboardSerialNumber()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x34029267);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetMainboardSerialNumber msd = (CPUIDSDK_fp_GetMainboardSerialNumber)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMainboardSerialNumber));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSystemManufacturer()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x69289762);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSystemManufacturer msd = (CPUIDSDK_fp_GetSystemManufacturer)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSystemManufacturer));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSystemProductName()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x83146519);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSystemProductName msd = (CPUIDSDK_fp_GetSystemProductName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSystemProductName));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSystemVersion()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x90340390);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSystemVersion msd = (CPUIDSDK_fp_GetSystemVersion)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSystemVersion));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSystemSerialNumber()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x51914170);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSystemSerialNumber msd = (CPUIDSDK_fp_GetSystemSerialNumber)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSystemSerialNumber));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSystemUUID()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x59942501);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSystemUUID msd = (CPUIDSDK_fp_GetSystemUUID)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSystemUUID));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetChassisManufacturer()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x68873846);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetChassisManufacturer msd = (CPUIDSDK_fp_GetChassisManufacturer)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetChassisManufacturer));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetChassisType()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x71205454);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetChassisType msd = (CPUIDSDK_fp_GetChassisType)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetChassisType));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetChassisSerialNumber()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x14260747);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetChassisSerialNumber msd = (CPUIDSDK_fp_GetChassisSerialNumber)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetChassisSerialNumber));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public bool GetMemoryInfosExt(ref string _szLocation, ref string _szUsage, ref string _szCorrection)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x47918636);
            if (ptr != IntPtr.Zero)
            {
                IntPtr location = IntPtr.Zero;
                IntPtr usage = IntPtr.Zero;
                IntPtr correction = IntPtr.Zero;

                CPUIDSDK_fp_GetMemoryInfosExt msd = (CPUIDSDK_fp_GetMemoryInfosExt)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryInfosExt));
                res = msd(objptr, ref location, ref usage, ref correction);
                if (res == 1)
                {
                    _szLocation = Marshal.PtrToStringAnsi(location);
                    Marshal.FreeBSTR(location);
                    _szUsage = Marshal.PtrToStringAnsi(usage);
                    Marshal.FreeBSTR(usage);
                    _szCorrection = Marshal.PtrToStringAnsi(correction);
                    Marshal.FreeBSTR(correction);

                    return true;
                }
                return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public int GetNumberOfMemoryDevices()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x22697876);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNumberOfMemoryDevices msd = (CPUIDSDK_fp_GetNumberOfMemoryDevices)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNumberOfMemoryDevices));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public bool GetMemoryDeviceInfos(int _device_index, ref int _size, ref string _szFormat)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x92217148);
            if (ptr != IntPtr.Zero)
            {
                IntPtr format = IntPtr.Zero;

                CPUIDSDK_fp_GetMemoryDeviceInfos msd = (CPUIDSDK_fp_GetMemoryDeviceInfos)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryDeviceInfos));
                res = msd(objptr, _device_index, ref _size, ref format);
                if (res == 1)
                {
                    _szFormat = Marshal.PtrToStringAnsi(format);
                    Marshal.FreeBSTR(format);
                    return true;
                }
                return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public bool GetMemoryDeviceInfosExt(int _device_index, ref string _szDesignation, ref string _szType, ref int _total_width, ref int _data_width, ref int _speed)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x84480656);
            if (ptr != IntPtr.Zero)
            {
                IntPtr designation = IntPtr.Zero;
                IntPtr type = IntPtr.Zero;

                CPUIDSDK_fp_GetMemoryDeviceInfosExt msd = (CPUIDSDK_fp_GetMemoryDeviceInfosExt)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetMemoryDeviceInfosExt));
                res = msd(objptr, _device_index, ref designation, ref type, ref _total_width, ref _data_width, ref _speed);
                if (res == 1)
                {
                    _szDesignation = Marshal.PtrToStringAnsi(designation);
                    Marshal.FreeBSTR(designation);

                    _szType = Marshal.PtrToStringAnsi(type);
                    Marshal.FreeBSTR(type);

                    return true;
                }
                return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  SPD
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    public int GetNumberOfSPDModules()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x95984869);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNumberOfSPDModules msd = (CPUIDSDK_fp_GetNumberOfSPDModules)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNumberOfSPDModules));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetSPDModuleType(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x73560137);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleType msd = (CPUIDSDK_fp_GetSPDModuleType)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleType));
                return msd(objptr, _spd_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetSPDModuleSize(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x17926572);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleSize msd = (CPUIDSDK_fp_GetSPDModuleSize)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleSize));
                return msd(objptr, _spd_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public string GetSPDModuleFormat(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x43266541);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleFormat msd = (CPUIDSDK_fp_GetSPDModuleFormat)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleFormat));
                IntPtr pointer = msd(objptr, _spd_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSPDModuleManufacturer(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x20020212);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleManufacturer msd = (CPUIDSDK_fp_GetSPDModuleManufacturer)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleManufacturer));
                IntPtr pointer = msd(objptr, _spd_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public bool GetSPDModuleManufacturerID(int _spd_index, byte[] _id)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x05650041);
            if (ptr != IntPtr.Zero)
            {

                CPUIDSDK_fp_GetSPDModuleManufacturerID msd = (CPUIDSDK_fp_GetSPDModuleManufacturerID)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleManufacturerID));
                res = msd(objptr, _spd_index, _id);
                if (res == 1) return true;
                else return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public int GetSPDModuleMaxFrequency(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x61240771);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleMaxFrequency msd = (CPUIDSDK_fp_GetSPDModuleMaxFrequency)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleMaxFrequency));
                return msd(objptr, _spd_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public string GetSPDModuleSpecification(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x66920432);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleSpecification msd = (CPUIDSDK_fp_GetSPDModuleSpecification)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleSpecification));
                IntPtr pointer = msd(objptr, _spd_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSPDModulePartNumber(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x67418601);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModulePartNumber msd = (CPUIDSDK_fp_GetSPDModulePartNumber)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModulePartNumber));
                IntPtr pointer = msd(objptr, _spd_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetSPDModuleSerialNumber(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x88405126);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleSerialNumber msd = (CPUIDSDK_fp_GetSPDModuleSerialNumber)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleSerialNumber));
                IntPtr pointer = msd(objptr, _spd_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public float GetSPDModuleMinTRCD(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x03395383);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleMinTRCD msd = (CPUIDSDK_fp_GetSPDModuleMinTRCD)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleMinTRCD));
                return msd(objptr, _spd_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetSPDModuleMinTRP(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x42080663);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleMinTRP msd = (CPUIDSDK_fp_GetSPDModuleMinTRP)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleMinTRP));
                return msd(objptr, _spd_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetSPDModuleMinTRAS(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x28029203);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleMinTRAS msd = (CPUIDSDK_fp_GetSPDModuleMinTRAS)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleMinTRAS));
                return msd(objptr, _spd_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetSPDModuleMinTRC(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x86021092);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleMinTRC msd = (CPUIDSDK_fp_GetSPDModuleMinTRC)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleMinTRC));
                return msd(objptr, _spd_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public int GetSPDModuleManufacturingDate(int _spd_index, ref int _year, ref int _week)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x21472874);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleManufacturingDate msd = (CPUIDSDK_fp_GetSPDModuleManufacturingDate)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleManufacturingDate));
                return msd(objptr, _spd_index, ref _year, ref _week);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetSPDModuleNumberOfBanks(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x02931381);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleNumberOfBanks msd = (CPUIDSDK_fp_GetSPDModuleNumberOfBanks)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleNumberOfBanks));
                return msd(objptr, _spd_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetSPDModuleDataWidth(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x73627103);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleDataWidth msd = (CPUIDSDK_fp_GetSPDModuleDataWidth)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleDataWidth));
                return msd(objptr, _spd_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetSPDModuleNumberOfProfiles(int _spd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x61286404);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleNumberOfProfiles msd = (CPUIDSDK_fp_GetSPDModuleNumberOfProfiles)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleNumberOfProfiles));
                return msd(objptr, _spd_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public void GetSPDModuleProfileInfos(int _spd_index, int _profile_index, ref float _frequency, ref float _tCL, ref float _nominal_vdd)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x19109521);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleProfileInfos msd = (CPUIDSDK_fp_GetSPDModuleProfileInfos)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleProfileInfos));
                msd(objptr, _spd_index, _profile_index, ref _frequency, ref _tCL, ref _nominal_vdd);
            }
        }
        catch
        {
        }
    }
    public int GetSPDModuleNumberOfEPPProfiles(int _spd_index, ref int _epp_revision)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x71453072);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles msd = (CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles));
                return msd(objptr, _spd_index, ref _epp_revision);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public void GetSPDModuleEPPProfileInfos(int _spd_index, int _profile_index, ref float _frequency, ref float _tCL, ref float _tRCD, ref float _tRAS, ref float _tRP, ref float _tRC, ref float _nominal_vdd)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x49734767);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleEPPProfileInfos msd = (CPUIDSDK_fp_GetSPDModuleEPPProfileInfos)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleEPPProfileInfos));
                msd(objptr, _spd_index, _profile_index, ref _frequency, ref _tCL, ref _tRCD, ref _tRAS, ref _tRP, ref _tRC, ref _nominal_vdd);
            }
        }
        catch
        {
        }
    }
    public int GetSPDModuleNumberOfXMPProfiles(int _spd_index, ref int _xmp_revision)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x27872643);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles msd = (CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles));
                return msd(objptr, _spd_index, ref _xmp_revision);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetSPDModuleXMPProfileNumberOfCL(int _spd_index, int _profile_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x40772909);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL msd = (CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL));
                return msd(objptr, _spd_index, _profile_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public void GetSPDModuleXMPProfileCLInfos(int _spd_index, int _profile_index, int _cl_index, ref float _frequency, ref float _CL)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x19772059);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos msd = (CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos));
                msd(objptr, _spd_index, _profile_index, _cl_index, ref _frequency, ref _CL);
            }
        }
        catch
        {
        }
    }
    public void GetSPDModuleXMPProfileInfos(int _spd_index, int _profile_index, ref float _tRCD, ref float _tRAS, ref float _tRP, ref float _nominal_vdd, ref int _max_freq, ref float _max_CL)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x76279884);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleXMPProfileInfos msd = (CPUIDSDK_fp_GetSPDModuleXMPProfileInfos)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleXMPProfileInfos));
                msd(objptr, _spd_index, _profile_index, ref _tRCD, ref _tRAS, ref _tRP, ref _nominal_vdd, ref _max_freq, ref _max_CL);
            }
        }
        catch
        {
        }
    }
    public int GetSPDModuleNumberOfAMPProfiles(int _spd_index, ref int _amp_revision)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x57184768);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles msd = (CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles));
                return msd(objptr, _spd_index, ref _amp_revision);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public void GetSPDModuleAMPProfileInfos(int _spd_index, int _profile_index, ref int _frequency, ref float _min_cycle_time, ref float _tCL, ref float _tRCD, ref float _tRAS, ref float _tRP, ref float _tRC)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x73365255);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleAMPProfileInfos msd = (CPUIDSDK_fp_GetSPDModuleAMPProfileInfos)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleAMPProfileInfos));
                msd(objptr, _spd_index, _profile_index, ref _frequency, ref _min_cycle_time, ref _tCL, ref _tRCD, ref _tRAS, ref _tRP, ref _tRC);
            }
        }
        catch
        {
        }
    }
    public int GetSPDModuleRawData(int _spd_index, int _offset)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x85485813);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSPDModuleRawData msd = (CPUIDSDK_fp_GetSPDModuleRawData)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSPDModuleRawData));
                return msd(objptr, _spd_index, _offset);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Display
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    public int GetNumberOfDisplayAdapter()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x21249495);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNumberOfDisplayAdapter msd = (CPUIDSDK_fp_GetNumberOfDisplayAdapter)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNumberOfDisplayAdapter));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetDisplayAdapterID(int _adapter_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x10057658);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterID msd = (CPUIDSDK_fp_GetDisplayAdapterID)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterID));
                return msd(objptr, _adapter_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public string GetDisplayAdapterName(int _adapter_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x92905207);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterName msd = (CPUIDSDK_fp_GetDisplayAdapterName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterName));
                IntPtr pointer = msd(objptr, _adapter_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetDisplayAdapterCodeName(int _adapter_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x36601485);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterCodeName msd = (CPUIDSDK_fp_GetDisplayAdapterCodeName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterCodeName));
                IntPtr pointer = msd(objptr, _adapter_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }

    public int GetDisplayAdapterNumberOfPerformanceLevels(int _adapter_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x70614420);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels msd = (CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels));
                return msd(objptr, _adapter_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetDisplayAdapterCurrentPerformanceLevel(int _adapter_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x38305572);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel msd = (CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel));
                return msd(objptr, _adapter_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public string GetDisplayAdapterPerformanceLevelName(int _adapter_index, int _perf_level)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x74800436);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName msd = (CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName));
                IntPtr pointer = msd(objptr, _adapter_index, _perf_level);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public float GetDisplayAdapterClock(int _adapter_index, int _perf_level, int _domain)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x58160354);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterClock msd = (CPUIDSDK_fp_GetDisplayAdapterClock)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterClock));
                return msd(objptr, _adapter_index, _perf_level, _domain);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetDisplayAdapterStockClock(int _adapter_index, int _perf_level, int _domain)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x98839608);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterStockClock msd = (CPUIDSDK_fp_GetDisplayAdapterStockClock)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterStockClock));
                return msd(objptr, _adapter_index, _perf_level, _domain);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetDisplayAdapterManufacturingProcess(int _adapter_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x15062802);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess msd = (CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess));
                return msd(objptr, _adapter_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public float GetDisplayAdapterTemperature(int _adapter_index, int _domain)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x89591134);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterTemperature msd = (CPUIDSDK_fp_GetDisplayAdapterTemperature)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterTemperature));
                return msd(objptr, _adapter_index, _domain);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
    public int GetDisplayAdapterFanSpeed(int _adapter_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x47296089);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterFanSpeed msd = (CPUIDSDK_fp_GetDisplayAdapterFanSpeed)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterFanSpeed));
                return msd(objptr, _adapter_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetDisplayAdapterFanPWM(int _adapter_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x95172240);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterFanPWM msd = (CPUIDSDK_fp_GetDisplayAdapterFanPWM)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterFanPWM));
                return msd(objptr, _adapter_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public bool GetDisplayAdapterMemoryType(int _adapter_index, ref int _type)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x58437098);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterMemoryType msd = (CPUIDSDK_fp_GetDisplayAdapterMemoryType)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterMemoryType));
                res = msd(objptr, _adapter_index, ref _type);
                if (res == 1) return true;
                else return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public bool GetDisplayAdapterMemorySize(int _adapter_index, ref int _size)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x25764630);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterMemorySize msd = (CPUIDSDK_fp_GetDisplayAdapterMemorySize)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterMemorySize));
                res = msd(objptr, _adapter_index, ref _size);
                if (res == 1) return true;
                else return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public bool GetDisplayAdapterMemoryBusWidth(int _adapter_index, ref int _bus_width)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x62256484);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth msd = (CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth));
                res = msd(objptr, _adapter_index, ref _bus_width);
                if (res == 1) return true;
                else return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public string GetDisplayDriverVersion()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x40381382);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayDriverVersion msd = (CPUIDSDK_fp_GetDisplayDriverVersion)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayDriverVersion));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetDirectXVersion()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x04336787);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDirectXVersion msd = (CPUIDSDK_fp_GetDirectXVersion)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDirectXVersion));
                IntPtr pointer = msd(objptr);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public bool GetDisplayAdapterBusInfos(int _adapter_index, ref int _bus_type, ref int _multi_vpu)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x29194080);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDisplayAdapterBusInfos msd = (CPUIDSDK_fp_GetDisplayAdapterBusInfos)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDisplayAdapterBusInfos));
                res = msd(objptr, _adapter_index, ref _bus_type, ref _multi_vpu);
                if (res == 1) return true;
                else return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  HDD
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    public int GetNumberOfHDD()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x70194191);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNumberOfHDD msd = (CPUIDSDK_fp_GetNumberOfHDD)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNumberOfHDD));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetHDDDeviceNumber(int _hdd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x29681416);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDDeviceNumber msd = (CPUIDSDK_fp_GetHDDDeviceNumber)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDDeviceNumber));
                return msd(objptr, _hdd_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public string GetHDDName(int _hdd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x14281523);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDName msd = (CPUIDSDK_fp_GetHDDName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDName));
                IntPtr pointer = msd(objptr, _hdd_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetHDDRevision(int _hdd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x20439067);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDRevision msd = (CPUIDSDK_fp_GetHDDRevision)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDRevision));
                IntPtr pointer = msd(objptr, _hdd_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetHDDSerialNumber(int _hdd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x84456446);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDSerialNumber msd = (CPUIDSDK_fp_GetHDDSerialNumber)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDSerialNumber));
                IntPtr pointer = msd(objptr, _hdd_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public int GetHDDNumberOfVolumes(int _hdd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x03560569);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDNumberOfVolumes msd = (CPUIDSDK_fp_GetHDDNumberOfVolumes)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDNumberOfVolumes));
                return msd(objptr, _hdd_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public string GetHDDVolumeLetter(int _hdd_index, int _volume_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x33850175);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDVolumeLetter msd = (CPUIDSDK_fp_GetHDDVolumeLetter)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDVolumeLetter));
                IntPtr pointer = msd(objptr, _hdd_index, _volume_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public string GetHDDVolumeName(int _hdd_index, int _volume_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x32324888);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDVolumeName msd = (CPUIDSDK_fp_GetHDDVolumeName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDVolumeName));
                IntPtr pointer = msd(objptr, _hdd_index, _volume_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public float GetHDDVolumeSize(int _hdd_index, int _volume_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x49680854);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDVolumeSize msd = (CPUIDSDK_fp_GetHDDVolumeSize)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDVolumeSize));
                return (uint)msd(objptr, _hdd_index, _volume_index);
            }
            return F_UNDEFINED_VALUE;
        }
        catch
        {
            return F_UNDEFINED_VALUE;
        }
    }
    public uint GetHDDVolumeSerial(int _hdd_index, int _volume_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x83859347);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDVolumeSerial msd = (CPUIDSDK_fp_GetHDDVolumeSerial)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDVolumeSerial));
                return (uint)msd(objptr, _hdd_index, _volume_index);
            }
            return (uint)I_UNDEFINED_VALUE;
        }
        catch
        {
            return (uint)I_UNDEFINED_VALUE;
        }
    }

    public int GetHDDNumberOfAttributes(int _hdd_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x47656581);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDNumberOfAttributes msd = (CPUIDSDK_fp_GetHDDNumberOfAttributes)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDNumberOfAttributes));
                return (int)msd(objptr, _hdd_index);
            }
            return (int)I_UNDEFINED_VALUE;
        }
        catch
        {
            return (int)I_UNDEFINED_VALUE;
        }
    }
    public bool GetHDDAttribute(int _hdd_index, int _attrib_index, ref int _id, ref int _flags, ref int _value, ref int _worst, byte[] _data)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x34762833);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetHDDAttribute msd = (CPUIDSDK_fp_GetHDDAttribute)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetHDDAttribute));
                res = msd(objptr, _hdd_index, _attrib_index, ref _id, ref _flags, ref _value, ref _worst, _data);
                if (res == 1) return true;
                else return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Monitoring
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    public int GetNumberOfDevices()
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x25057433);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNumberOfDevices msd = (CPUIDSDK_fp_GetNumberOfDevices)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNumberOfDevices));
                return msd(objptr);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public int GetDeviceClass(int _device_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x36807526);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDeviceClass msd = (CPUIDSDK_fp_GetDeviceClass)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDeviceClass));
                return msd(objptr, _device_index);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public string GetDeviceName(int _device_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x39542713);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetDeviceName msd = (CPUIDSDK_fp_GetDeviceName)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetDeviceName));
                IntPtr pointer = msd(objptr, _device_index);
                string tmp = Marshal.PtrToStringAnsi(pointer);
                Marshal.FreeBSTR(pointer);
                return tmp;
            }
            return null;
        }
        catch
        {
            return null;
        }
    }
    public int GetNumberOfSensors(int _device_index, int _sensor_class)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x95629590);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetNumberOfSensors msd = (CPUIDSDK_fp_GetNumberOfSensors)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetNumberOfSensors));
                return msd(objptr, _device_index, _sensor_class);
            }
            return I_UNDEFINED_VALUE;
        }
        catch
        {
            return I_UNDEFINED_VALUE;
        }
    }
    public bool GetSensorInfos(int _device_index, int _sensor_index, int _sensor_class, ref int _sensor_id, ref string _szName, ref int _raw_value, ref float _value, ref float _min_value, ref float _max_value)
    {
        int res;
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x49543122);
            if (ptr != IntPtr.Zero)
            {
                IntPtr pointer = IntPtr.Zero;

                CPUIDSDK_fp_GetSensorInfos msd = (CPUIDSDK_fp_GetSensorInfos)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSensorInfos));
                res = msd(objptr, _device_index, _sensor_index, _sensor_class, ref _sensor_id, ref pointer, ref _raw_value, ref _value, ref _min_value, ref _max_value);
                if (res == 1)
                {
                    _szName = Marshal.PtrToStringAnsi(pointer);
                    Marshal.FreeBSTR(pointer);
                    return true;
                }
                return false;
            }
            return false;
        }
        catch
        {
            return false;
        }
    }
    public void SensorClearMinMax(int _device_index, int _sensor_index, int _sensor_class, ref int _sensor_id, ref string _szName, ref int _raw_value, ref float _value, ref float _min_value, ref float _max_value)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x33549146);
            if (ptr != IntPtr.Zero)
            {
                IntPtr pointer = IntPtr.Zero;

                CPUIDSDK_fp_SensorClearMinMax msd = (CPUIDSDK_fp_SensorClearMinMax)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_SensorClearMinMax));
                msd(objptr, _device_index, _sensor_index, _sensor_class);
            }
        }
        catch
        {
        }
    }
    public float GetSensorTypeValue(int _sensor_type, ref int _device_index, ref int _sensor_index)
    {
        try
        {
            IntPtr ptr = CPUIDSDK_fp_QueryInterface(0x12013410);
            if (ptr != IntPtr.Zero)
            {
                CPUIDSDK_fp_GetSensorTypeValue msd = (CPUIDSDK_fp_GetSensorTypeValue)Marshal.GetDelegateForFunctionPointer(ptr, typeof(CPUIDSDK_fp_GetSensorTypeValue));
                return msd(objptr, _sensor_type, ref _device_index, ref _sensor_index);
            }
            return (float)F_UNDEFINED_VALUE;
        }
        catch
        {
            return (float)F_UNDEFINED_VALUE;
        }
    }
}