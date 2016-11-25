#ifndef _CPUIDSDK_H_
#define _CPUIDSDK_H_

///////////////////////////////////////////////////////////////////////////
//	MACROS
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//	Fields validity
///////////////////////////////////////////////////////////////////////////

#define		I_UNDEFINED_VALUE					-1
#define		F_UNDEFINED_VALUE					-1.0f

template <class TYPE>
BOOL IS_I_DEFINED(TYPE T)
{
	return (T != (TYPE)I_UNDEFINED_VALUE);
}

#define		IS_F_DEFINED(a)						((a)>0.0f)

#define		MAX_INTEGER							0xFFFFFFFF
#define		MAX_FLOAT							(float)MAX_INTEGER

///////////////////////////////////////////////////////////////////////////
//	Error codes
///////////////////////////////////////////////////////////////////////////

#define		CPUIDSDK_ERROR_NO_ERROR				0x00000000

#define		CPUIDSDK_ERROR_EVALUATION			0x00000001
#define		CPUIDSDK_ERROR_DRIVER				0x00000002
#define		CPUIDSDK_ERROR_VM_RUNNING			0x00000004
#define		CPUIDSDK_ERROR_LOCKED				0x00000008
#define		CPUIDSDK_ERROR_INVALID_DLL			0x00000010

#define		CPUIDSDK_EXT_ERROR_EVAL_1			0x00000001
#define		CPUIDSDK_EXT_ERROR_EVAL_2			0x00000002

///////////////////////////////////////////////////////////////////////////
//	Configuration flags
///////////////////////////////////////////////////////////////////////////

#define		CPUIDSDK_CONFIG_USE_SOFTWARE		0x00000002
#define		CPUIDSDK_CONFIG_USE_DMI				0x00000004
#define		CPUIDSDK_CONFIG_USE_PCI				0x00000008
#define		CPUIDSDK_CONFIG_USE_ACPI			0x00000010
#define		CPUIDSDK_CONFIG_USE_CHIPSET			0x00000020
#define		CPUIDSDK_CONFIG_USE_SMBUS			0x00000040
#define		CPUIDSDK_CONFIG_USE_SPD				0x00000080
#define		CPUIDSDK_CONFIG_USE_STORAGE			0x00000100
#define		CPUIDSDK_CONFIG_USE_GRAPHICS		0x00000200
#define		CPUIDSDK_CONFIG_USE_HWMONITORING	0x00000400
#define		CPUIDSDK_CONFIG_USE_PROCESSOR		0x00000800
#define		CPUIDSDK_CONFIG_USE_DISPLAY_API		0x00001000

#define		CPUIDSDK_CONFIG_USE_ACPI_TIMER		0x00004000

#define		CPUIDSDK_CONFIG_CHECK_VM			0x01000000
#define		CPUIDSDK_CONFIG_WAKEUP_HDD			0x02000000

#define		CPUIDSDK_CONFIG_SERVER_SAFE			0x80000000

#define		CPUIDSDK_CONFIG_USE_EVERYTHING		0x7FFFFFFF

///////////////////////////////////////////////////////////////////////////
//	Cache descriptors
///////////////////////////////////////////////////////////////////////////

#define		CACHE_TYPE_DATA						0x1
#define		CACHE_TYPE_INSTRUCTION				0x2
#define		CACHE_TYPE_UNIFIED					0x3
#define		CACHE_TYPE_TRACE_CACHE				0x4

#define		CACHE_ASSOCIATIVITY_DIRECT_MAPPED	0x1
#define		CACHE_ASSOCIATIVITY_FULLY			0xFF

///////////////////////////////////////////////////////////////////////////
//	Instructions sets
///////////////////////////////////////////////////////////////////////////

#define		ISET_MMX							0x1
#define		ISET_EXTENDED_MMX					0x2
#define		ISET_3DNOW							0x3
#define		ISET_EXTENDED_3DNOW					0x4
#define		ISET_SSE							0x5
#define		ISET_SSE2							0x6
#define		ISET_SSE3							0x7
#define		ISET_SSSE3							0x8
#define		ISET_SSE4_1							0x9
#define		ISET_SSE4_2							0xC
#define		ISET_SSE4A							0xD
#define		ISET_XOP							0xE
#define		ISET_X86_64							0x10
#define		ISET_NX								0x11
#define		ISET_VMX							0x12
#define		ISET_AES							0x13
#define		ISET_AVX							0x14
#define		ISET_AVX2							0x15
#define		ISET_FMA3							0x16
#define		ISET_FMA4							0x17
#define		ISET_RTM							0x18
#define		ISET_HLE							0x19
#define		ISET_AVX512F						0x1A

///////////////////////////////////////////////////////////////////////////
// CPU manufacturers, archis & models
///////////////////////////////////////////////////////////////////////////

#define		CPU_MANUFACTURER_MASK					0xFF000000
#define		CPU_FAMILY_MASK							0xFFFFFF00
#define		CPU_MODEL_MASK							0xFFFFFFFF

// Manufacturers
#define		CPU_UNKNOWN								0x00000000
#define		CPU_INTEL								0x01000000
#define		CPU_AMD									0x02000000
#define		CPU_CYRIX								0x04000000
#define		CPU_VIA									0x08000000
#define		CPU_TRANSMETA							0x10000000
#define		CPU_DMP									0x20000000

// Intel families
#define		CPU_INTEL_386							(CPU_INTEL + 0x000100)
#define		CPU_INTEL_486							(CPU_INTEL + 0x000200)
#define		CPU_INTEL_P5							(CPU_INTEL + 0x000400)
#define		CPU_INTEL_P6							(CPU_INTEL + 0x000800)
#define		CPU_INTEL_NETBURST						(CPU_INTEL + 0x001000)
#define		CPU_INTEL_MOBILE						(CPU_INTEL + 0x002000)
#define		CPU_INTEL_CORE							(CPU_INTEL + 0x004000)
#define		CPU_INTEL_CORE_2						(CPU_INTEL + 0x008000)
#define		CPU_INTEL_BONNELL						(CPU_INTEL + 0x010000)
#define		CPU_INTEL_SALTWELL						(CPU_INTEL + 0x010100)
#define		CPU_INTEL_SILVERMONT					(CPU_INTEL + 0x010200)
#define		CPU_INTEL_GOLDMONT						(CPU_INTEL + 0x010400)
#define		CPU_INTEL_NEHALEM						(CPU_INTEL + 0x020000)
#define		CPU_INTEL_SANDY_BRIDGE					(CPU_INTEL + 0x020100)
#define		CPU_INTEL_HASWELL						(CPU_INTEL + 0x020200)
#define		CPU_INTEL_SKYLAKE						(CPU_INTEL + 0x040000)
#define		CPU_INTEL_ITANIUM						(CPU_INTEL + 0x100000)
#define		CPU_INTEL_ITANIUM_2						(CPU_INTEL + 0x100100)
#define		CPU_INTEL_MIC							(CPU_INTEL + 0x200000)

// Intel models
// P5
#define		CPU_PENTIUM								(CPU_INTEL_P5 + 0x01)
#define		CPU_PENTIUM_MMX							(CPU_INTEL_P5 + 0x02)

// P6
#define		CPU_PENTIUM_PRO							(CPU_INTEL_P6 + 0x01)
#define		CPU_PENTIUM_2							(CPU_INTEL_P6 + 0x02)
#define		CPU_PENTIUM_2_M							(CPU_INTEL_P6 + 0x03)
#define		CPU_CELERON_P2							(CPU_INTEL_P6 + 0x04)
#define		CPU_XEON_P2								(CPU_INTEL_P6 + 0x05)
#define		CPU_PENTIUM_3							(CPU_INTEL_P6 + 0x06)
#define		CPU_PENTIUM_3_M							(CPU_INTEL_P6 + 0x07)
#define		CPU_PENTIUM_3_S							(CPU_INTEL_P6 + 0x08)
#define		CPU_CELERON_P3							(CPU_INTEL_P6 + 0x09)
#define		CPU_XEON_P3								(CPU_INTEL_P6 + 0x0A)

// Netburst
#define		CPU_PENTIUM_4							(CPU_INTEL_NETBURST + 0x01)
#define		CPU_PENTIUM_4_M							(CPU_INTEL_NETBURST + 0x02)
#define		CPU_PENTIUM_4_HT						(CPU_INTEL_NETBURST + 0x03)
#define		CPU_PENTIUM_4_EE						(CPU_INTEL_NETBURST + 0x04)
#define		CPU_CELERON_P4							(CPU_INTEL_NETBURST + 0x05)
#define		CPU_CELERON_D							(CPU_INTEL_NETBURST + 0x06)
#define		CPU_XEON_P4								(CPU_INTEL_NETBURST + 0x07)
#define		CPU_PENTIUM_D							(CPU_INTEL_NETBURST + 0x08)
#define		CPU_PENTIUM_XE							(CPU_INTEL_NETBURST + 0x09)

// Mobile
#define		CPU_PENTIUM_M							(CPU_INTEL_MOBILE + 0x01)
#define		CPU_CELERON_M							(CPU_INTEL_MOBILE + 0x02)

// Core 1
#define		CPU_CORE_SOLO							(CPU_INTEL_CORE + 0x01)
#define		CPU_CORE_DUO							(CPU_INTEL_CORE + 0x02)
#define		CPU_CORE_CELERON_M						(CPU_INTEL_CORE + 0x03)
#define		CPU_CORE_CELERON						(CPU_INTEL_CORE + 0x04)

// Core 2
#define		CPU_CORE_2_DUO							(CPU_INTEL_CORE_2 + 0x01)
#define		CPU_CORE_2_EE							(CPU_INTEL_CORE_2 + 0x02)
#define		CPU_CORE_2_XEON							(CPU_INTEL_CORE_2 + 0x03)
#define		CPU_CORE_2_CELERON						(CPU_INTEL_CORE_2 + 0x04)
#define		CPU_CORE_2_QUAD							(CPU_INTEL_CORE_2 + 0x05)
#define		CPU_CORE_2_PENTIUM						(CPU_INTEL_CORE_2 + 0x06)
#define		CPU_CORE_2_CELERON_DC					(CPU_INTEL_CORE_2 + 0x07)
#define		CPU_CORE_2_SOLO							(CPU_INTEL_CORE_2 + 0x08)

// Bonnell
#define		CPU_BONNELL_ATOM						(CPU_INTEL_BONNELL + 0x01)

// Saltwell
#define		CPU_SALTWELL_ATOM						(CPU_INTEL_SALTWELL + 0x01)

// Silvermont
#define		CPU_SILVERMONT_ATOM						(CPU_INTEL_SILVERMONT + 0x01)
#define		CPU_SILVERMONT_CELERON					(CPU_INTEL_SILVERMONT + 0x02)
#define		CPU_SILVERMONT_PENTIUM					(CPU_INTEL_SILVERMONT + 0x03)
#define		CPU_SILVERMONT_ATOM_X7					(CPU_INTEL_SILVERMONT + 0x04)
#define		CPU_SILVERMONT_ATOM_X5					(CPU_INTEL_SILVERMONT + 0x05)
#define		CPU_SILVERMONT_ATOM_X3					(CPU_INTEL_SILVERMONT + 0x06)

// Nehalem
#define		CPU_NEHALEM_CORE_I7						(CPU_INTEL_NEHALEM + 0x01)
#define		CPU_NEHALEM_CORE_I7E					(CPU_INTEL_NEHALEM + 0x02)
#define		CPU_NEHALEM_XEON						(CPU_INTEL_NEHALEM + 0x03)
#define		CPU_NEHALEM_CORE_I3						(CPU_INTEL_NEHALEM + 0x04)
#define		CPU_NEHALEM_CORE_I5						(CPU_INTEL_NEHALEM + 0x05)
#define		CPU_NEHALEM_PENTIUM						(CPU_INTEL_NEHALEM + 0x07)
#define		CPU_NEHALEM_CELERON						(CPU_INTEL_NEHALEM + 0x08)

// Sandy Bridge
#define		CPU_SANDY_BRIDGE_CORE_I7				(CPU_INTEL_SANDY_BRIDGE + 0x01)
#define		CPU_SANDY_BRIDGE_CORE_I7E				(CPU_INTEL_SANDY_BRIDGE + 0x02)
#define		CPU_SANDY_BRIDGE_XEON					(CPU_INTEL_SANDY_BRIDGE + 0x03)
#define		CPU_SANDY_BRIDGE_CORE_I3				(CPU_INTEL_SANDY_BRIDGE + 0x04)
#define		CPU_SANDY_BRIDGE_CORE_I5				(CPU_INTEL_SANDY_BRIDGE + 0x05)
#define		CPU_SANDY_BRIDGE_PENTIUM				(CPU_INTEL_SANDY_BRIDGE + 0x07)
#define		CPU_SANDY_BRIDGE_CELERON				(CPU_INTEL_SANDY_BRIDGE + 0x08)

// Haswell
#define		CPU_HASWELL_CORE_I7						(CPU_INTEL_HASWELL + 0x01)
#define		CPU_HASWELL_CORE_I7E					(CPU_INTEL_HASWELL + 0x02)
#define		CPU_HASWELL_XEON						(CPU_INTEL_HASWELL + 0x03)
#define		CPU_HASWELL_CORE_I3						(CPU_INTEL_HASWELL + 0x04)
#define		CPU_HASWELL_CORE_I5						(CPU_INTEL_HASWELL + 0x05)
#define		CPU_HASWELL_PENTIUM						(CPU_INTEL_HASWELL + 0x07)
#define		CPU_HASWELL_CELERON						(CPU_INTEL_HASWELL + 0x08)
#define		CPU_HASWELL_CORE_M						(CPU_INTEL_HASWELL + 0x09)

// Skylake
#define		CPU_SKYLAKE_XEON						(CPU_INTEL_SKYLAKE + 0x01)
#define		CPU_SKYLAKE_CORE_I7						(CPU_INTEL_SKYLAKE + 0x02)
#define		CPU_SKYLAKE_CORE_I5						(CPU_INTEL_SKYLAKE + 0x03)
#define		CPU_SKYLAKE_CORE_I3						(CPU_INTEL_SKYLAKE + 0x04)
#define		CPU_SKYLAKE_PENTIUM						(CPU_INTEL_SKYLAKE + 0x05)
#define		CPU_SKYLAKE_CELERON						(CPU_INTEL_SKYLAKE + 0x06)
#define		CPU_SKYLAKE_CORE_M7						(CPU_INTEL_SKYLAKE + 0x07)
#define		CPU_SKYLAKE_CORE_M5						(CPU_INTEL_SKYLAKE + 0x08)
#define		CPU_SKYLAKE_CORE_M3						(CPU_INTEL_SKYLAKE + 0x09)

// AMD families
#define		CPU_AMD_386								(CPU_AMD + 0x000100)
#define		CPU_AMD_486								(CPU_AMD + 0x000200)
#define		CPU_AMD_K5								(CPU_AMD + 0x000400)
#define		CPU_AMD_K6								(CPU_AMD + 0x000800)
#define		CPU_AMD_K7								(CPU_AMD + 0x001000)
#define		CPU_AMD_K8								(CPU_AMD + 0x002000)
#define		CPU_AMD_K10								(CPU_AMD + 0x004000)
#define		CPU_AMD_K12								(CPU_AMD + 0x010000)
#define		CPU_AMD_K14								(CPU_AMD + 0x020000)
#define		CPU_AMD_K15								(CPU_AMD + 0x040000)
#define		CPU_AMD_K16								(CPU_AMD + 0x080000)
#define		CPU_AMD_K17								(CPU_AMD + 0x100000)

// AMD models
// K5
#define		CPU_K5									(CPU_AMD_K5 + 0x01)
#define		CPU_K5_GEODE							(CPU_AMD_K5 + 0x02)

// K6
#define		CPU_K6									(CPU_AMD_K6 + 0x01)
#define		CPU_K6_2								(CPU_AMD_K6 + 0x02)
#define		CPU_K6_3								(CPU_AMD_K6 + 0x03)

// K7
#define		CPU_K7_ATHLON							(CPU_AMD_K7 + 0x01)
#define		CPU_K7_ATHLON_XP						(CPU_AMD_K7 + 0x02)
#define		CPU_K7_ATHLON_MP						(CPU_AMD_K7 + 0x03)
#define		CPU_K7_DURON							(CPU_AMD_K7 + 0x04)
#define		CPU_K7_SEMPRON							(CPU_AMD_K7 + 0x05)
#define		CPU_K7_SEMPRON_M						(CPU_AMD_K7 + 0x06)

// K8
#define		CPU_K8_ATHLON_64						(CPU_AMD_K8 + 0x01)
#define		CPU_K8_ATHLON_64_M						(CPU_AMD_K8 + 0x02)
#define		CPU_K8_ATHLON_64_FX						(CPU_AMD_K8 + 0x03)
#define		CPU_K8_OPTERON							(CPU_AMD_K8 + 0x04)
#define		CPU_K8_TURION_64						(CPU_AMD_K8 + 0x05)
#define		CPU_K8_SEMPRON							(CPU_AMD_K8 + 0x06)
#define		CPU_K8_SEMPRON_M						(CPU_AMD_K8 + 0x07)
#define		CPU_K8_ATHLON_64_X2						(CPU_AMD_K8 + 0x08)
#define		CPU_K8_TURION_64_X2						(CPU_AMD_K8 + 0x09)
#define		CPU_K8_ATHLON_NEO						(CPU_AMD_K8 + 0x0A)

// K10
#define		CPU_K10_PHENOM							(CPU_AMD_K10 + 0x01)
#define		CPU_K10_PHENOM_X3						(CPU_AMD_K10 + 0x02)
#define		CPU_K10_PHENOM_FX						(CPU_AMD_K10 + 0x03)
#define		CPU_K10_OPTERON							(CPU_AMD_K10 + 0x04)
#define		CPU_K10_TURION_64						(CPU_AMD_K10 + 0x05)
#define		CPU_K10_TURION_64_ULTRA					(CPU_AMD_K10 + 0x06)
#define		CPU_K10_ATHLON_64						(CPU_AMD_K10 + 0x07)
#define		CPU_K10_SEMPRON							(CPU_AMD_K10 + 0x08)
#define		CPU_K10_ATHLON_2						(CPU_AMD_K10 + 0x11)
#define		CPU_K10_ATHLON_2_X2						(CPU_AMD_K10 + 0x0B)
#define		CPU_K10_ATHLON_2_X3						(CPU_AMD_K10 + 0x0D)
#define		CPU_K10_ATHLON_2_X4						(CPU_AMD_K10 + 0x0C)
#define		CPU_K10_PHENOM_II						(CPU_AMD_K10 + 0x09)
#define		CPU_K10_PHENOM_II_X2					(CPU_AMD_K10 + 0x0A)
#define		CPU_K10_PHENOM_II_X3					(CPU_AMD_K10 + 0x0E)
#define		CPU_K10_PHENOM_II_X4					(CPU_AMD_K10 + 0x0F)
#define		CPU_K10_PHENOM_II_X6					(CPU_AMD_K10 + 0x10)

// K15
#define		CPU_K15_FXB								(CPU_AMD_K15 + 0x01)
#define		CPU_K15_OPTERON							(CPU_AMD_K15 + 0x02)
#define		CPU_K15_A10T							(CPU_AMD_K15 + 0x03)
#define		CPU_K15_A8T								(CPU_AMD_K15 + 0x04)
#define		CPU_K15_A6T								(CPU_AMD_K15 + 0x05)
#define		CPU_K15_A4T								(CPU_AMD_K15 + 0x06)
#define		CPU_K15_ATHLON_X4						(CPU_AMD_K15 + 0x07)
#define		CPU_K15_FXV								(CPU_AMD_K15 + 0x08)
#define		CPU_K15_A10R							(CPU_AMD_K15 + 0x09)
#define		CPU_K15_A8R								(CPU_AMD_K15 + 0x0A)
#define		CPU_K15_A6R								(CPU_AMD_K15 + 0x0B)
#define		CPU_K15_A4R								(CPU_AMD_K15 + 0x0C)
#define		CPU_K15_SEMPRON							(CPU_AMD_K15 + 0x0D)
#define		CPU_K15_ATHLON_X2						(CPU_AMD_K15 + 0x0E)
#define		CPU_K15_FXC								(CPU_AMD_K15 + 0x0F)
#define		CPU_K15_A10C							(CPU_AMD_K15 + 0x10)
#define		CPU_K15_A8C								(CPU_AMD_K15 + 0x11)
#define		CPU_K15_A6C								(CPU_AMD_K15 + 0x12)
#define		CPU_K15_A4C								(CPU_AMD_K15 + 0x13)
#define		CPU_K15_A12								(CPU_AMD_K15 + 0x14)

// K16
#define		CPU_K16_A6								(CPU_AMD_K16 + 0x01)
#define		CPU_K16_A4								(CPU_AMD_K16 + 0x02)
#define		CPU_K16_OPTERON							(CPU_AMD_K16 + 0x05)
#define		CPU_K16_ATHLON							(CPU_AMD_K16 + 0x06)
#define		CPU_K16_SEMPRON							(CPU_AMD_K16 + 0x07)
#define		CPU_K16_E1								(CPU_AMD_K16 + 0x08)
#define		CPU_K16_E2								(CPU_AMD_K16 + 0x09)
#define		CPU_K16_A8								(CPU_AMD_K16 + 0x0A)
#define		CPU_K16_A10								(CPU_AMD_K16 + 0x0B)

// VIA families
#define		CPU_VIA_WINCHIP							(CPU_VIA + 0x000400)
#define		CPU_VIA_C3								(CPU_VIA + 0x000800)
#define		CPU_VIA_C7								(CPU_VIA + 0x001000)
#define		CPU_VIA_NANO							(CPU_VIA + 0x002000)

// VIA models
// C3
#define		CPU_C3									(CPU_VIA_C3 + 0x01)

// C7
#define		CPU_C7									(CPU_VIA_C7 + 0x01)
#define		CPU_C7_M								(CPU_VIA_C7 + 0x02)
#define		CPU_EDEN								(CPU_VIA_C7 + 0x03)
#define		CPU_C7_D								(CPU_VIA_C7 + 0x04)

// Nano
#define		CPU_NANO_X2								(CPU_VIA_NANO + 0x01)
#define		CPU_EDEN_X2								(CPU_VIA_NANO + 0x02)
#define		CPU_NANO_X3								(CPU_VIA_NANO + 0x03)
#define		CPU_EDEN_X4								(CPU_VIA_NANO + 0x04)
#define		CPU_QUADCORE							(CPU_VIA_NANO + 0x05)

// Cyrix
#define		CPU_CYRIX_6X86							(CPU_CYRIX + 0x02)

// Transmeta
#define		CPU_CRUSOE								(CPU_TRANSMETA + 0x01)
#define		CPU_EFFICEON							(CPU_TRANSMETA + 0x02)


///////////////////////////////////////////////////////////////////////////
//	Memory types
///////////////////////////////////////////////////////////////////////////

#define		SPM_RAM							0x1
#define		RDRAM							0x2
#define		EDO_RAM							0x3
#define		FPM_RAM							0x4
#define		SDRAM							0x5
#define		DDR_SDRAM						0x6
#define		DDR2_SDRAM						0x7
#define		DDR2_SDRAM_FB					0x8
#define		DDR3_SDRAM						0x9
#define		DDR4_SDRAM						0xA

///////////////////////////////////////////////////////////////////////////
//	Memory correction
///////////////////////////////////////////////////////////////////////////

#define		SPD_CORRECTION_NONE				0x0
#define		SPD_CORRECTION_PARITY			0x1
#define		SPD_CORRECTION_ECC				0x2


///////////////////////////////////////////////////////////////////////////
//	Display Adapter infos source
///////////////////////////////////////////////////////////////////////////

#define		DISPLAY_CLOCK_DOMAIN_GRAPHICS	0
#define 	DISPLAY_CLOCK_DOMAIN_MEMORY		4
#define 	DISPLAY_CLOCK_DOMAIN_PROCESSOR	7

#define		DISPLAY_VOLTAGE_DOMAIN_VCORE	0

#define		MEMORY_TYPE_SDR					1
#define		MEMORY_TYPE_DDR					2
#define		MEMORY_TYPE_LPDDR2				9
#define		MEMORY_TYPE_DDR2				3
#define		MEMORY_TYPE_DDR3				7
#define		MEMORY_TYPE_GDDR2				4
#define		MEMORY_TYPE_GDDR3				5
#define		MEMORY_TYPE_GDDR4				6
#define		MEMORY_TYPE_GDDR5				8
#define		MEMORY_TYPE_GDDR5X				10
#define		MEMORY_TYPE_HBM2				11


///////////////////////////////////////////////////////////////////////////
//	Monitoring
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//	Devices Classes
///////////////////////////////////////////////////////////////////////////

#define 	CLASS_DEVICE_UNKNOWN			0x00000000
#define 	CLASS_DEVICE_PCI				0x00000001
#define 	CLASS_DEVICE_SMBUS				0x00000002
#define 	CLASS_DEVICE_PROCESSOR			0x00000004
#define 	CLASS_DEVICE_LPCIO				0x00000008
#define 	CLASS_DEVICE_DRIVE				0x00000010
#define 	CLASS_DEVICE_DISPLAY_ADAPTER	0x00000020
#define 	CLASS_DEVICE_HID				0x00000040
#define 	CLASS_DEVICE_BATTERY			0x00000080
#define 	CLASS_DEVICE_MAINBOARD			0x00000400
#define 	CLASS_DEVICE_MEMORY_MODULE		0x00000800
#define 	CLASS_DEVICE_PSU				0x00001000
#define 	CLASS_DEVICE_WATERCOOLER		0x00004000

///////////////////////////////////////////////////////////////////////////
//	Hardware Monitor Classes
///////////////////////////////////////////////////////////////////////////

#define		HWM_CLASS_LPC					0x00000001
#define		HWM_CLASS_CPU					0x00000002
#define		HWM_CLASS_HDD					0x00000004
#define		HWM_CLASS_DISPLAYADAPTER		0x00000008
#define		HWM_CLASS_PSU					0x00000010
#define		HWM_CLASS_ACPI					0x00000020
#define		HWM_CLASS_RAM					0x00000040
#define		HWM_CLASS_CHASSIS				0x00000080
#define		HWM_CLASS_WATERCOOLER			0x00000100
#define		HWM_CLASS_BATTERY				0x00000200

///////////////////////////////////////////////////////////////////////////
//	Sensors classes & predefined types
///////////////////////////////////////////////////////////////////////////

// Masks
#define		SENSOR_CPU_SHIFT			30
#define		SENSOR_CPU_MASK				(0x3 << SENSOR_CPU_SHIFT)

#define		SENSOR_TYPE_SHIFT			24
#define		SENSOR_TYPE_MASK			(0xFF << SENSOR_TYPE_SHIFT)

#define		SENSOR_CLASS_SHIFT			8
#define		SENSOR_CLASS_MASK			(0xFFFF << SENSOR_CLASS_SHIFT)

#define		SENSOR_ID_SHIFT				0
#define		SENSOR_ID_MASK				(0xFF << SENSOR_ID_SHIFT)


// Sensor classes
#define		SENSOR_CLASS_VOLTAGE			(0x0001	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_TEMPERATURE		(0x0002	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_FAN				(0x0004	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_CURRENT			(0x0008	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_POWER				(0x0010	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_FAN_PWM			(0x0020	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_PUMP_PWM			(0x0040	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_WATER_LEVEL		(0x0080	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_POSITION			(0x0100	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_CAPACITY			(0x0200	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_CASEOPEN			(0x0400	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_LEVEL				(0x0800	<< SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_COUNTER			(0x1000 << SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_UTILIZATION		(0x2000 << SENSOR_CLASS_SHIFT)
#define		SENSOR_CLASS_CLOCK_SPEED		(0x4000 << SENSOR_CLASS_SHIFT)

// Sensor types
#define		SENSOR_CPU0						(0x0 << SENSOR_CPU_SHIFT)
#define		SENSOR_CPU1						(0x1 << SENSOR_CPU_SHIFT)

#define		SENSOR_VOLTAGE_VCORE			((0x1 << 24) + SENSOR_CLASS_VOLTAGE)
#define		SENSOR_VOLTAGE_3V3				((0x2 << 24) + SENSOR_CLASS_VOLTAGE)	// +3.3V
#define		SENSOR_VOLTAGE_P5V				((0x3 << 24) + SENSOR_CLASS_VOLTAGE)	// +5V
#define		SENSOR_VOLTAGE_P12V				((0x4 << 24) + SENSOR_CLASS_VOLTAGE)	// +12V
#define		SENSOR_VOLTAGE_M5V				((0x5 << 24) + SENSOR_CLASS_VOLTAGE)	// -5V
#define		SENSOR_VOLTAGE_M12V				((0x6 << 24) + SENSOR_CLASS_VOLTAGE)	// -12V
#define		SENSOR_VOLTAGE_5VSB				((0x7 << 24) + SENSOR_CLASS_VOLTAGE)	// +5V standby
#define		SENSOR_VOLTAGE_DRAM				((0x8 << 24) + SENSOR_CLASS_VOLTAGE)

#define		SENSOR_TEMPERATURE_CPU			((0x1 << 24) + SENSOR_CLASS_TEMPERATURE)

#define		SENSOR_FAN_CPU					((0x1 << 24) + SENSOR_CLASS_FAN)

// Macros
#define		SENSOR_VOLTAGE_VCORE_CPU0		(SENSOR_CPU0 | SENSOR_VOLTAGE_VCORE)
#define		SENSOR_VOLTAGE_VCORE_CPU1		(SENSOR_CPU1 | SENSOR_VOLTAGE_VCORE)

#define		SENSOR_TEMPERATURE_CPU0			(SENSOR_CPU0 | SENSOR_TEMPERATURE_CPU)
#define		SENSOR_TEMPERATURE_CPU1			(SENSOR_CPU1 | SENSOR_TEMPERATURE_CPU)

#define		SENSOR_FAN_CPU0					(SENSOR_CPU0 | SENSOR_FAN_CPU)
#define		SENSOR_FAN_CPU1					(SENSOR_CPU1 | SENSOR_FAN_CPU)


///////////////////////////////////////////////////////////////////////////
//	DLL functions
///////////////////////////////////////////////////////////////////////////

// DLL management
typedef void* (__stdcall *TCPUIDSDK_fp_CreateInstance)();
typedef void (__stdcall *TCPUIDSDK_fp_DestroyInstance)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_Init)(void *objptr, BSTR _szDllPath, BSTR _szDllName, int _config_flag, int *_errorcode, int *_extended_errorcode);
typedef void (__stdcall *TCPUIDSDK_fp_Close)(void *objptr);
typedef void (__stdcall *TCPUIDSDK_fp_RefreshInformation)(void *objptr);
typedef void (__stdcall *TCPUIDSDK_fp_GetDLLVersion)(void *objptr, int *_version);

// Processor
typedef int (__stdcall *TCPUIDSDK_fp_GetNbProcessors)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorFamily)(void *pbjptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorExtendedFamily)(void *pbjptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorModel)(void *pbjptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorExtendedModel)(void *pbjptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorSteppingID)(void *pbjptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorCoreCount)(void *pbjptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorThreadCount)(void *objptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorCoreThreadCount)(void *objptr, int _proc_index, int _core_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorThreadAPICID)(void *objptr, int _proc_index, int _core_index, int _thread_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetProcessorName)(void *objptr, int _proc_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetProcessorCodeName)(void *objptr, int _proc_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetProcessorSpecification)(void *objptr, int _proc_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetProcessorPackage)(void *objptr, int _proc_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetProcessorStepping)(void *objptr, int _proc_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetProcessorTDP)(void *objptr, int _proc_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetProcessorManufacturingProcess)(void *objptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_IsProcessorInstructionSetAvailable)(void *objptr, int _proc_index, int _iset);
typedef float (__stdcall *TCPUIDSDK_fp_GetProcessorCoreClockFrequency)(void *objptr, int _proc_index, int _core_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetProcessorCoreClockMultiplier)(void *objptr, int _proc_index, int _core_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetProcessorCoreTemperature)(void *objptr, int _proc_index, int _core_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetBusFrequency)(void *objptr);
typedef float (__stdcall *TCPUIDSDK_fp_GetProcessorRatedBusFrequency)(void *objptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorStockClockFrequency)(void *objptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorStockBusFrequency)(void *objptr, int _proc_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorMaxCacheLevel)(void *objptr, int _proc_index);
typedef void (__stdcall *TCPUIDSDK_fp_GetProcessorCacheParameters)(void *objptr, int _proc_index, int _cache_level, int _cache_type, int *_NbCaches, int *_size);
typedef void (__stdcall *TCPUIDSDK_fp_GetProcessorExtendedCacheParameters)(void *objptr, int _proc_index, int _cache_level, int _cache_type, int *_associativity, int *_linesize);
typedef int (__stdcall *TCPUIDSDK_fp_GetHyperThreadingStatus)(void *objptr, int _proc_index, int *_supported, int *_enabled);
typedef int (__stdcall *TCPUIDSDK_fp_GetVirtualTechnologyStatus)(void *objptr, int _proc_index, int *_supported, int *_enabled);
typedef int (__stdcall *TCPUIDSDK_fp_GetProcessorID)(void *objptr, int _proc_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetProcessorVoltageID)(void *objptr, int _proc_index);

// Memory
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryType)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemorySize)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryNumberOfChannels)(void *objptr);
typedef float (__stdcall *TCPUIDSDK_fp_GetMemoryClockFrequency)(void *objptr);
typedef float (__stdcall *TCPUIDSDK_fp_GetMemoryCASLatency)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryRAStoCASDelay)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryRASPrecharge)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryTRAS)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryTRC)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryCommandRate)(void *objptr);
typedef float (__stdcall *TCPUIDSDK_fp_ComputeMemoryFrequency)(void *objptr, float _fsb, float _cpu_clock_multiplier);
typedef void (__stdcall *TCPUIDSDK_fp_GetMemorySlotsConfig)(void *objptr, int *_nbslots, int *_nbusedslots, int *_slotmap, int *_maxmodulesize);

// Chipset
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetNorthBridgeVendor)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetNorthBridgeModel)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetNorthBridgeRevision)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSouthBridgeVendor)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSouthBridgeModel)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSouthBridgeRevision)(void *objptr);

// BIOS & mainboard
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetBIOSVendor)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetBIOSVersion)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetBIOSDate)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetBIOSType)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetBIOSROMSize)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetMainboardVendor)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetMainboardModel)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetMainboardRevision)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetMainboardSerialNumber)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSystemManufacturer)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSystemProductName)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSystemVersion)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSystemSerialNumber)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSystemUUID)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetChassisManufacturer)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetChassisType)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetChassisSerialNumber)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryInfosExt)(void *objptr, BSTR *_szLocation, BSTR *_szUsage, BSTR *_szCorrection);
typedef int (__stdcall *TCPUIDSDK_fp_GetNumberOfMemoryDevices)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryDeviceInfos)(void *objptr, int _device_index, int *_size, BSTR *_szFormat);
typedef int (__stdcall *TCPUIDSDK_fp_GetMemoryDeviceInfosExt)(void *objptr, int _device_index, BSTR *_szDesignation, BSTR *_szType, int *_total_width, int *_data_width, int *_speed);

// SPD
typedef int (__stdcall *TCPUIDSDK_fp_GetNumberOfSPDModules)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleAddress)(void *objptr, int _spd_index, int *_host_index, int *_channel, int *_address);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleType)(void *objptr, int _spd_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleSize)(void *objptr, int _spd_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSPDModuleFormat)(void *objptr, int _spd_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSPDModuleManufacturer)(void *objptr, int _spd_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleManufacturerID)(void *objptr, int _spd_index, unsigned char *_id);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleMaxFrequency)(void *objptr, int _spd_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSPDModuleSpecification)(void *objptr, int _spd_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSPDModulePartNumber)(void *objptr, int _spd_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetSPDModuleSerialNumber)(void *objptr, int _spd_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetSPDModuleMinTRCD)(void *objptr, int _spd_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetSPDModuleMinTRP)(void *objptr, int _spd_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetSPDModuleMinTRAS)(void *objptr, int _spd_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetSPDModuleMinTRC)(void *objptr, int _spd_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleManufacturingDate)(void *objptr, int _spd_index, int *_year, int *_week);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleNumberOfBanks)(void *objptr, int _spd_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleDataWidth)(void *objptr, int _spd_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleNumberOfProfiles)(void *objptr, int _spd_index);
typedef void (__stdcall *TCPUIDSDK_fp_GetSPDModuleProfileInfos)(void *objptr, int _spd_index, int _profile_index, float *_frequency, float *_tCL, float *_nominal_vdd);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles)(void *objptr, int _spd_index, int *_epp_revision);
typedef void (__stdcall *TCPUIDSDK_fp_GetSPDModuleEPPProfileInfos)(void *objptr, int _spd_index, int _profile_index, float *_frequency, float *_tCL, float *_tRCD, float *_tRAS, float *_tRP, float *_tRC, float *_nominal_vdd);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles)(void *objptr, int _spd_index, int *_xmp_revision);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL)(void *objptr, int _spd_index, int _profile_index);
typedef void (__stdcall *TCPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos)(void *objptr, int _spd_index, int _profile_index, int _cl_index, float *_frequency, float *_CL);
typedef void (__stdcall *TCPUIDSDK_fp_GetSPDModuleXMPProfileInfos)(void *objptr, int _spd_index, int _profile_index, float *_tRCD, float *_tRAS, float *_tRP, float *_nominal_vdd, int *_max_freq, float *_max_CL);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles)(void *objptr, int _spd_index, int *_amp_revision);
typedef void (__stdcall *TCPUIDSDK_fp_GetSPDModuleAMPProfileInfos)(void *objptr, int _spd_index, int _profile_index, int *_frequency, float *_fMinCycleTime, float *_tCL, float *_tRCD, float *_tRAS, float *_tRP, float *_tRC);
typedef int (__stdcall *TCPUIDSDK_fp_GetSPDModuleRawData)(void *objptr, int _spd_index, int _offset);

// Hardware monitor
typedef int (__stdcall *TCPUIDSDK_fp_GetNumberOfDevices)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetDeviceClass)(void *objptr, int _device_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetDeviceName)(void *objptr, int _device_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetDeviceSerialNumber)(void *objptr, int _device_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetNumberOfSensors)(void *objptr, int _device_index, int _sensor_class);
typedef int (__stdcall *TCPUIDSDK_fp_GetSensorInfos)(void *objptr, int _device_index, int _sensor_index, int _sensor_class, int *_sensor_id, BSTR *_szName, int *_raw_value, float *_value, float *_min_value, float *_max_value);
typedef void (__stdcall *TCPUIDSDK_fp_SensorClearMinMax)(void *objptr, int _device_index, int _sensor_index, int _sensor_class);
typedef float (__stdcall *TCPUIDSDK_fp_GetSensorTypeValue)(void *objptr, int _sensor_type, int *_device_index, int *_sensor_index);

// Display
typedef int (__stdcall *TCPUIDSDK_fp_GetNumberOfDisplayAdapter)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterID)(void *objptr, int _adapter_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterName)(void *objptr, int _adapter_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterCodeName)(void *objptr, int _adapter_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels)(void *objptr, int _adapter_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel)(void *objptr, int _adapter_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName)(void *objptr, int _adapter_index, int _perf_level);
typedef float (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterClock)(void *objptr, int _adapter_index, int _perf_level, int _domain);
typedef float (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterStockClock)(void *objptr, int _adapter_index, int _perf_level, int _domain);
typedef float (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterTemperature)(void *objptr, int _adapter_index, int _domain);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterFanSpeed)(void *objptr, int _adapter_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterFanPWM)(void *objptr, int _adapter_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterMemoryType)(void *objptr, int _adapter_index, int *_type);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterMemorySize)(void *objptr, int _adapter_index, int *_size);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth)(void *objptr, int _adapter_index, int *_bus_width);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetDisplayDriverVersion)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetDirectXVersion)(void *objptr);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterBusInfos)(void *objptr, int _adapter_index, int *_bus_type, int *_multi_vpu);
typedef float (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterManufacturingProcess)(void *objptr, int _adapter_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetDisplayAdapterPCIID)(void *objptr, int _adapter_index, int *_vendor_id, int *_device_id, int *_revision_id, int *_sub_vendor_id, int *_sub_model_id);

// HDD
typedef int (__stdcall *TCPUIDSDK_fp_GetNumberOfHDD)(void *objptr);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetHDDName)(void *objptr, int _hdd_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetHDDRevision)(void *objptr, int _hdd_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetHDDSerialNumber)(void *objptr, int _hdd_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetHDDTemperature)(void *objptr, int _hdd_index, int _source);
typedef int (__stdcall *TCPUIDSDK_fp_GetHDDNumberOfVolumes)(void *objptr, int _hdd_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetHDDVolumeLetter)(void *objptr, int _hdd_index, int _volume_index);
typedef BSTR (__stdcall *TCPUIDSDK_fp_GetHDDVolumeName)(void *objptr, int _hdd_index, int _volume_index);
typedef float (__stdcall *TCPUIDSDK_fp_GetHDDVolumeSize)(void *objptr, int _hdd_index, int _volume_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetHDDVolumeSerial)(void *objptr, int _hdd_index, int _volume_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetHDDNumberOfAttributes)(void *objptr, int _hdd_index);
typedef int (__stdcall *TCPUIDSDK_fp_GetHDDAttribute)(void *objptr, int _hdd_index, int _attrib_index, int *_id, int *_flags, int *_value, int *_worst, unsigned char *_data);


class CPUIDSDK
{
protected:
	void *objptr;

protected:
	TCPUIDSDK_fp_CreateInstance									CPUIDSDK_fp_CreateInstance;
	TCPUIDSDK_fp_DestroyInstance								CPUIDSDK_fp_DestroyInstance;
	TCPUIDSDK_fp_Init											CPUIDSDK_fp_Init;
	TCPUIDSDK_fp_Close											CPUIDSDK_fp_Close;
	TCPUIDSDK_fp_RefreshInformation								CPUIDSDK_fp_RefreshInformation;
	TCPUIDSDK_fp_GetDLLVersion									CPUIDSDK_fp_GetDLLVersion;
	
//	CPU
	TCPUIDSDK_fp_GetNbProcessors								CPUIDSDK_fp_GetNbProcessors;
	TCPUIDSDK_fp_GetProcessorFamily								CPUIDSDK_fp_GetProcessorFamily;
	TCPUIDSDK_fp_GetProcessorExtendedFamily						CPUIDSDK_fp_GetProcessorExtendedFamily;
	TCPUIDSDK_fp_GetProcessorModel								CPUIDSDK_fp_GetProcessorModel;
	TCPUIDSDK_fp_GetProcessorExtendedModel						CPUIDSDK_fp_GetProcessorExtendedModel;
	TCPUIDSDK_fp_GetProcessorSteppingID							CPUIDSDK_fp_GetProcessorSteppingID;
	TCPUIDSDK_fp_GetProcessorTDP								CPUIDSDK_fp_GetProcessorTDP;
	TCPUIDSDK_fp_GetProcessorCoreCount							CPUIDSDK_fp_GetProcessorCoreCount;
	TCPUIDSDK_fp_GetProcessorThreadCount						CPUIDSDK_fp_GetProcessorThreadCount;
	TCPUIDSDK_fp_GetProcessorCoreThreadCount					CPUIDSDK_fp_GetProcessorCoreThreadCount;
	TCPUIDSDK_fp_GetProcessorThreadAPICID						CPUIDSDK_fp_GetProcessorThreadAPICID;
	TCPUIDSDK_fp_GetProcessorName								CPUIDSDK_fp_GetProcessorName;
	TCPUIDSDK_fp_GetProcessorCodeName							CPUIDSDK_fp_GetProcessorCodeName;
	TCPUIDSDK_fp_GetProcessorSpecification						CPUIDSDK_fp_GetProcessorSpecification;
	TCPUIDSDK_fp_GetProcessorPackage							CPUIDSDK_fp_GetProcessorPackage;
	TCPUIDSDK_fp_GetProcessorStepping							CPUIDSDK_fp_GetProcessorStepping;
	TCPUIDSDK_fp_GetProcessorManufacturingProcess				CPUIDSDK_fp_GetProcessorManufacturingProcess;
	TCPUIDSDK_fp_IsProcessorInstructionSetAvailable				CPUIDSDK_fp_IsProcessorInstructionSetAvailable;
	TCPUIDSDK_fp_GetProcessorCoreClockFrequency					CPUIDSDK_fp_GetProcessorCoreClockFrequency;
	TCPUIDSDK_fp_GetProcessorCoreClockMultiplier				CPUIDSDK_fp_GetProcessorCoreClockMultiplier;
	TCPUIDSDK_fp_GetProcessorCoreTemperature					CPUIDSDK_fp_GetProcessorCoreTemperature;
	TCPUIDSDK_fp_GetBusFrequency								CPUIDSDK_fp_GetBusFrequency;
	TCPUIDSDK_fp_GetProcessorRatedBusFrequency					CPUIDSDK_fp_GetProcessorRatedBusFrequency;	
	TCPUIDSDK_fp_GetProcessorStockClockFrequency				CPUIDSDK_fp_GetProcessorStockClockFrequency;
	TCPUIDSDK_fp_GetProcessorStockBusFrequency					CPUIDSDK_fp_GetProcessorStockBusFrequency;
	TCPUIDSDK_fp_GetProcessorMaxCacheLevel						CPUIDSDK_fp_GetProcessorMaxCacheLevel;
	TCPUIDSDK_fp_GetProcessorCacheParameters					CPUIDSDK_fp_GetProcessorCacheParameters;
	TCPUIDSDK_fp_GetProcessorExtendedCacheParameters			CPUIDSDK_fp_GetProcessorExtendedCacheParameters;
	TCPUIDSDK_fp_GetHyperThreadingStatus						CPUIDSDK_fp_GetHyperThreadingStatus;
	TCPUIDSDK_fp_GetVirtualTechnologyStatus						CPUIDSDK_fp_GetVirtualTechnologyStatus;
	TCPUIDSDK_fp_GetProcessorID									CPUIDSDK_fp_GetProcessorID;
	TCPUIDSDK_fp_GetProcessorVoltageID							CPUIDSDK_fp_GetProcessorVoltageID;

//	chipset & memory
	TCPUIDSDK_fp_GetMemoryType									CPUIDSDK_fp_GetMemoryType;
	TCPUIDSDK_fp_GetMemorySize									CPUIDSDK_fp_GetMemorySize;
	TCPUIDSDK_fp_GetMemoryNumberOfChannels						CPUIDSDK_fp_GetMemoryNumberOfChannels;
	TCPUIDSDK_fp_GetMemoryClockFrequency						CPUIDSDK_fp_GetMemoryClockFrequency;
	TCPUIDSDK_fp_GetMemoryCASLatency							CPUIDSDK_fp_GetMemoryCASLatency;
	TCPUIDSDK_fp_GetMemoryRAStoCASDelay							CPUIDSDK_fp_GetMemoryRAStoCASDelay;
	TCPUIDSDK_fp_GetMemoryRASPrecharge							CPUIDSDK_fp_GetMemoryRASPrecharge;
	TCPUIDSDK_fp_GetMemoryTRAS									CPUIDSDK_fp_GetMemoryTRAS;
	TCPUIDSDK_fp_GetMemoryTRC									CPUIDSDK_fp_GetMemoryTRC;
	TCPUIDSDK_fp_GetMemoryCommandRate							CPUIDSDK_fp_GetMemoryCommandRate;
	TCPUIDSDK_fp_ComputeMemoryFrequency							CPUIDSDK_fp_ComputeMemoryFrequency;
	TCPUIDSDK_fp_GetMemorySlotsConfig							CPUIDSDK_fp_GetMemorySlotsConfig;

	TCPUIDSDK_fp_GetNorthBridgeVendor							CPUIDSDK_fp_GetNorthBridgeVendor;
	TCPUIDSDK_fp_GetNorthBridgeModel							CPUIDSDK_fp_GetNorthBridgeModel;
	TCPUIDSDK_fp_GetNorthBridgeRevision							CPUIDSDK_fp_GetNorthBridgeRevision;
	TCPUIDSDK_fp_GetSouthBridgeVendor							CPUIDSDK_fp_GetSouthBridgeVendor;
	TCPUIDSDK_fp_GetSouthBridgeModel							CPUIDSDK_fp_GetSouthBridgeModel;
	TCPUIDSDK_fp_GetSouthBridgeRevision							CPUIDSDK_fp_GetSouthBridgeRevision;

	TCPUIDSDK_fp_GetBIOSVendor									CPUIDSDK_fp_GetBIOSVendor;
	TCPUIDSDK_fp_GetBIOSVersion									CPUIDSDK_fp_GetBIOSVersion;
	TCPUIDSDK_fp_GetBIOSDate									CPUIDSDK_fp_GetBIOSDate;
	TCPUIDSDK_fp_GetBIOSType									CPUIDSDK_fp_GetBIOSType;
	TCPUIDSDK_fp_GetBIOSROMSize									CPUIDSDK_fp_GetBIOSROMSize;
	TCPUIDSDK_fp_GetMainboardVendor								CPUIDSDK_fp_GetMainboardVendor;
	TCPUIDSDK_fp_GetMainboardModel								CPUIDSDK_fp_GetMainboardModel;
	TCPUIDSDK_fp_GetMainboardRevision							CPUIDSDK_fp_GetMainboardRevision;
	TCPUIDSDK_fp_GetMainboardSerialNumber						CPUIDSDK_fp_GetMainboardSerialNumber;
	TCPUIDSDK_fp_GetSystemManufacturer							CPUIDSDK_fp_GetSystemManufacturer;
	TCPUIDSDK_fp_GetSystemProductName							CPUIDSDK_fp_GetSystemProductName;
	TCPUIDSDK_fp_GetSystemVersion								CPUIDSDK_fp_GetSystemVersion;
	TCPUIDSDK_fp_GetSystemSerialNumber							CPUIDSDK_fp_GetSystemSerialNumber;
	TCPUIDSDK_fp_GetSystemUUID									CPUIDSDK_fp_GetSystemUUID;
	TCPUIDSDK_fp_GetChassisManufacturer							CPUIDSDK_fp_GetChassisManufacturer;
	TCPUIDSDK_fp_GetChassisType									CPUIDSDK_fp_GetChassisType;
	TCPUIDSDK_fp_GetChassisSerialNumber							CPUIDSDK_fp_GetChassisSerialNumber;
	TCPUIDSDK_fp_GetMemoryInfosExt								CPUIDSDK_fp_GetMemoryInfosExt;
	TCPUIDSDK_fp_GetNumberOfMemoryDevices						CPUIDSDK_fp_GetNumberOfMemoryDevices;
	TCPUIDSDK_fp_GetMemoryDeviceInfos							CPUIDSDK_fp_GetMemoryDeviceInfos;
	TCPUIDSDK_fp_GetMemoryDeviceInfosExt						CPUIDSDK_fp_GetMemoryDeviceInfosExt;

//	SPD
	TCPUIDSDK_fp_GetNumberOfSPDModules							CPUIDSDK_fp_GetNumberOfSPDModules;
	TCPUIDSDK_fp_GetSPDModuleAddress							CPUIDSDK_fp_GetSPDModuleAddress;
	TCPUIDSDK_fp_GetSPDModuleType								CPUIDSDK_fp_GetSPDModuleType;
	TCPUIDSDK_fp_GetSPDModuleSize								CPUIDSDK_fp_GetSPDModuleSize;
	TCPUIDSDK_fp_GetSPDModuleFormat								CPUIDSDK_fp_GetSPDModuleFormat;
	TCPUIDSDK_fp_GetSPDModuleManufacturer						CPUIDSDK_fp_GetSPDModuleManufacturer;
	TCPUIDSDK_fp_GetSPDModuleManufacturerID						CPUIDSDK_fp_GetSPDModuleManufacturerID;
	TCPUIDSDK_fp_GetSPDModuleMaxFrequency						CPUIDSDK_fp_GetSPDModuleMaxFrequency;
	TCPUIDSDK_fp_GetSPDModuleSpecification						CPUIDSDK_fp_GetSPDModuleSpecification;
	TCPUIDSDK_fp_GetSPDModulePartNumber							CPUIDSDK_fp_GetSPDModulePartNumber;
	TCPUIDSDK_fp_GetSPDModuleSerialNumber						CPUIDSDK_fp_GetSPDModuleSerialNumber;
	TCPUIDSDK_fp_GetSPDModuleMinTRCD							CPUIDSDK_fp_GetSPDModuleMinTRCD;
	TCPUIDSDK_fp_GetSPDModuleMinTRP								CPUIDSDK_fp_GetSPDModuleMinTRP;
	TCPUIDSDK_fp_GetSPDModuleMinTRAS							CPUIDSDK_fp_GetSPDModuleMinTRAS;
	TCPUIDSDK_fp_GetSPDModuleMinTRC								CPUIDSDK_fp_GetSPDModuleMinTRC;
	TCPUIDSDK_fp_GetSPDModuleManufacturingDate					CPUIDSDK_fp_GetSPDModuleManufacturingDate;
	TCPUIDSDK_fp_GetSPDModuleNumberOfBanks						CPUIDSDK_fp_GetSPDModuleNumberOfBanks;
	TCPUIDSDK_fp_GetSPDModuleDataWidth							CPUIDSDK_fp_GetSPDModuleDataWidth;
	TCPUIDSDK_fp_GetSPDModuleNumberOfProfiles					CPUIDSDK_fp_GetSPDModuleNumberOfProfiles;
	TCPUIDSDK_fp_GetSPDModuleProfileInfos						CPUIDSDK_fp_GetSPDModuleProfileInfos;
	TCPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles				CPUIDSDK_fp_GetSPDModuleNumberOfEPPProfiles;
	TCPUIDSDK_fp_GetSPDModuleEPPProfileInfos					CPUIDSDK_fp_GetSPDModuleEPPProfileInfos;
	TCPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles				CPUIDSDK_fp_GetSPDModuleNumberOfXMPProfiles;
	TCPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL				CPUIDSDK_fp_GetSPDModuleXMPProfileNumberOfCL;
	TCPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos					CPUIDSDK_fp_GetSPDModuleXMPProfileCLInfos;
	TCPUIDSDK_fp_GetSPDModuleXMPProfileInfos					CPUIDSDK_fp_GetSPDModuleXMPProfileInfos;
	TCPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles				CPUIDSDK_fp_GetSPDModuleNumberOfAMPProfiles;
	TCPUIDSDK_fp_GetSPDModuleAMPProfileInfos					CPUIDSDK_fp_GetSPDModuleAMPProfileInfos;
	TCPUIDSDK_fp_GetSPDModuleRawData							CPUIDSDK_fp_GetSPDModuleRawData;

//	HWM
	TCPUIDSDK_fp_GetNumberOfDevices								CPUIDSDK_fp_GetNumberOfDevices;
	TCPUIDSDK_fp_GetDeviceClass									CPUIDSDK_fp_GetDeviceClass;
	TCPUIDSDK_fp_GetDeviceName									CPUIDSDK_fp_GetDeviceName;
	TCPUIDSDK_fp_GetDeviceSerialNumber							CPUIDSDK_fp_GetDeviceSerialNumber;
	TCPUIDSDK_fp_GetNumberOfSensors								CPUIDSDK_fp_GetNumberOfSensors;
	TCPUIDSDK_fp_GetSensorInfos									CPUIDSDK_fp_GetSensorInfos;
	TCPUIDSDK_fp_SensorClearMinMax								CPUIDSDK_fp_SensorClearMinMax;
	TCPUIDSDK_fp_GetSensorTypeValue								CPUIDSDK_fp_GetSensorTypeValue;

//	Display
	TCPUIDSDK_fp_GetNumberOfDisplayAdapter						CPUIDSDK_fp_GetNumberOfDisplayAdapter;
	TCPUIDSDK_fp_GetDisplayAdapterName							CPUIDSDK_fp_GetDisplayAdapterName;
	TCPUIDSDK_fp_GetDisplayAdapterCodeName						CPUIDSDK_fp_GetDisplayAdapterCodeName;
	TCPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels		CPUIDSDK_fp_GetDisplayAdapterNumberOfPerformanceLevels;
	TCPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel		CPUIDSDK_fp_GetDisplayAdapterCurrentPerformanceLevel;
	TCPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName			CPUIDSDK_fp_GetDisplayAdapterPerformanceLevelName;
	TCPUIDSDK_fp_GetDisplayAdapterClock							CPUIDSDK_fp_GetDisplayAdapterClock;
	TCPUIDSDK_fp_GetDisplayAdapterStockClock					CPUIDSDK_fp_GetDisplayAdapterStockClock;
	TCPUIDSDK_fp_GetDisplayAdapterTemperature					CPUIDSDK_fp_GetDisplayAdapterTemperature;
	TCPUIDSDK_fp_GetDisplayAdapterFanSpeed						CPUIDSDK_fp_GetDisplayAdapterFanSpeed;
	TCPUIDSDK_fp_GetDisplayAdapterFanPWM						CPUIDSDK_fp_GetDisplayAdapterFanPWM;
	TCPUIDSDK_fp_GetDisplayAdapterMemoryType					CPUIDSDK_fp_GetDisplayAdapterMemoryType;
	TCPUIDSDK_fp_GetDisplayAdapterMemorySize					CPUIDSDK_fp_GetDisplayAdapterMemorySize;
	TCPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth				CPUIDSDK_fp_GetDisplayAdapterMemoryBusWidth;
	TCPUIDSDK_fp_GetDisplayDriverVersion						CPUIDSDK_fp_GetDisplayDriverVersion;
	TCPUIDSDK_fp_GetDirectXVersion								CPUIDSDK_fp_GetDirectXVersion;
	TCPUIDSDK_fp_GetDisplayAdapterBusInfos						CPUIDSDK_fp_GetDisplayAdapterBusInfos;
	TCPUIDSDK_fp_GetDisplayAdapterManufacturingProcess			CPUIDSDK_fp_GetDisplayAdapterManufacturingProcess;
	TCPUIDSDK_fp_GetDisplayAdapterPCIID							CPUIDSDK_fp_GetDisplayAdapterPCIID;

//	HDD
	TCPUIDSDK_fp_GetNumberOfHDD									CPUIDSDK_fp_GetNumberOfHDD;
	TCPUIDSDK_fp_GetHDDName										CPUIDSDK_fp_GetHDDName;
	TCPUIDSDK_fp_GetHDDRevision									CPUIDSDK_fp_GetHDDRevision;
	TCPUIDSDK_fp_GetHDDSerialNumber								CPUIDSDK_fp_GetHDDSerialNumber;
	TCPUIDSDK_fp_GetHDDTemperature								CPUIDSDK_fp_GetHDDTemperature;
	TCPUIDSDK_fp_GetHDDNumberOfVolumes							CPUIDSDK_fp_GetHDDNumberOfVolumes;
	TCPUIDSDK_fp_GetHDDVolumeLetter								CPUIDSDK_fp_GetHDDVolumeLetter;
	TCPUIDSDK_fp_GetHDDVolumeName								CPUIDSDK_fp_GetHDDVolumeName;
	TCPUIDSDK_fp_GetHDDVolumeSize								CPUIDSDK_fp_GetHDDVolumeSize;
	TCPUIDSDK_fp_GetHDDVolumeSerial								CPUIDSDK_fp_GetHDDVolumeSerial;
	TCPUIDSDK_fp_GetHDDNumberOfAttributes						CPUIDSDK_fp_GetHDDNumberOfAttributes;
	TCPUIDSDK_fp_GetHDDAttribute								CPUIDSDK_fp_GetHDDAttribute;

public:
	CPUIDSDK();
	virtual ~CPUIDSDK();

	BOOL InitDll(HMODULE _hDll);

//	Instance management
	BOOL CreateInstance();
	void DestroyInstance();
	BOOL Init(char *_szDllPath, char *_szDllFilename, int _config_flag, int *_errorcode, int *_extended_errorcode);
	void Close();
	void RefreshInformation();
	void GetDLLVersion(int *_version);

//	Processors
	int GetNumberOfProcessors();
	int GetProcessorFamily(int _proc_index);
	int GetProcessorExtendedFamily(int _proc_index);
	int GetProcessorModel(int _proc_index);
	int GetProcessorExtendedModel(int _proc_index);
	int GetProcessorSteppingID(int _proc_index);
	int GetProcessorCoreCount(int _proc_index);
	int GetProcessorThreadCount(int _proc_index);
	int GetProcessorCoreThreadCount(int _proc_index, int _core_index);
	int GetProcessorThreadAPICID(int _proc_index, int _core_index, int _thread_index);
	BOOL GetProcessorName(int _proc_index, char *_szBuffer);
	BOOL GetProcessorCodeName(int _proc_index, char *_szBuffer);
	BOOL GetProcessorPackage(int _proc_index, char *_szBuffer);
	BOOL GetProcessorSpecification(int _proc_index, char *_szBuffer);
	BOOL GetProcessorStepping(int _proc_index, char *_szBuffer);
	float GetProcessorTDP(int _proc_index);
	float GetProcessorManufacturingProcess(int _proc_index);
	BOOL IsProcessorInstructionSetAvailable(int _proc_index, int _iset);
	int GetProcessorStockClockFrequency(int _proc_index);
	int GetProcessorStockBusFrequency(int _proc_index);
	float GetProcessorCoreClockFrequency(int _proc_index, int _core_index);
	float GetProcessorCoreClockMultiplier(int _proc_index, int _core_index);
	float GetProcessorCoreTemperature(int _proc_index, int _core_index);
	float GetBusFrequency();
	float GetProcessorRatedBusFrequency(int _proc_index);
	int GetProcessorMaxCacheLevel(int _proc_index);
	void GetProcessorCacheParameters(int _proc_index, int _cache_level, int _cache_type, int *_NbCaches, int *_size);
	void GetProcessorExtendedCacheParameters(int _proc_index, int _cache_level, int _cache_type, int *_associativity, int *_line_size);
	BOOL GetHyperThreadingStatus(int _proc_index, int *_supported, int *_enabled);
	BOOL GetVirtualTechnologyStatus(int _proc_index, int *_supported, int *_enabled);
	unsigned int GetProcessorID(int _proc_index);

//	FID/VID
	float GetProcessorVoltageID(int _proc_index);

//	Memory and chipset
	BOOL GetNorthBridgeVendor(char *_szBuffer);
	BOOL GetNorthBridgeModel(char *_szBuffer);
	BOOL GetNorthBridgeRevision(char *_szBuffer);
	BOOL GetSouthBridgeVendor(char *_szBuffer);
	BOOL GetSouthBridgeModel(char *_szBuffer);
	BOOL GetSouthBridgeRevision(char *_szBuffer);

	int GetMemoryType();
	int GetMemorySize();
	int GetMemoryNumberOfChannels();
	float GetMemoryClockFrequency();
	float GetMemoryCASLatency();
	int GetMemoryRAStoCASDelay();
	int GetMemoryRASPrecharge();
	int GetMemoryTRAS();
	int GetMemoryTRC();
	int GetMemoryCommandRate();
	float ComputeMemoryFrequency(float _fsb, float _cpu_clock_multiplier);

//	BIOS & Mainboard
	BOOL GetBIOSVendor(char *_szBuffer);
	BOOL GetBIOSVersion(char *_szBuffer);
	BOOL GetBIOSDate(char *_szBuffer);
	BOOL GetBIOSType(char *_szBuffer);
	int GetBIOSROMSize();
	BOOL GetMainboardVendor(char *_szBuffer);
	BOOL GetMainboardModel(char *_szBuffer);
	BOOL GetMainboardRevision(char *_szBuffer);
	BOOL GetMainboardSerialNumber(char *_szBuffer);
	BOOL GetSystemManufacturer(char *_szBuffer);
	BOOL GetSystemProductName(char *_szBuffer);
	BOOL GetSystemVersion(char *_szBuffer);
	BOOL GetSystemSerialNumber(char *_szBuffer);
	BOOL GetSystemUUID(char *_szBuffer);
	BOOL GetChassisManufacturer(char *_szBuffer);
	BOOL GetChassisType(char *_szBuffer);
	BOOL GetChassisSerialNumber(char *_szBuffer);
	BOOL GetMemoryInfosExt(char *_szLocation, char *_szUsage, char *_szCorrection);
	int GetNumberOfMemoryDevices();
	BOOL GetMemoryDeviceInfos(int _device_index, int *_size, char *_szFormat);
	BOOL GetMemoryDeviceInfosExt(int _device_index, char *_szDesignation, char *_szType, int *_total_width, int *_data_width, int *_speed);
	void GetMemorySlotsConfig(int *_nbslots, int *_nbusedslots, int *_slotmap, int *_maxmodulesize);

//	SPD
	int GetNumberOfSPDModules();
	BOOL GetSPDModuleAddress(int _spd_index, int *_host_index, int *_channel, int *_address);
	int GetSPDModuleType(int _spd_index);
	int GetSPDModuleSize(int _spd_index);
	BOOL GetSPDModuleFormat(int _spd_index, char *_szBuffer);
	BOOL GetSPDModuleManufacturingDate(int _spd_index, int *_year, int *_week);
	int GetSPDModuleNumberOfBanks(int _spd_index);
	int GetSPDModuleDataWidth(int _spd_index);
	BOOL GetSPDModuleManufacturer(int _spd_index, char *_szBuffer);
	BOOL GetSPDModuleManufacturerID(int _spd_index, unsigned char *_id);
	int GetSPDModuleMaxFrequency(int _spd_index);
	BOOL GetSPDModuleSpecification(int _spd_index, char *_szBuffer);
	BOOL GetSPDModulePartNumber(int _spd_index, char *_szBuffer);
	BOOL GetSPDModuleSerialNumber(int _spd_index, char *_szBuffer);
	float GetSPDModuleMinTRCD(int _spd_index);
	float GetSPDModuleMinTRP(int _spd_index);
	float GetSPDModuleMinTRAS(int _spd_index);
	float GetSPDModuleMinTRC(int _spd_index);
	int GetSPDModuleNumberOfProfiles(int _spd_index);
	void GetSPDModuleProfileInfos(int _spd_index, int _profile_index, float *_frequency, float *_tCL, float *_nominal_vdd);
	int GetSPDModuleNumberOfEPPProfiles(int _spd_index, int *_epp_revision);
	void GetSPDModuleEPPProfileInfos(int _spd_index, int _profile_index, float *_frequency, float *_tCL, float *_tRCD, float *_tRAS, float *_tRP, float *_tRC, float *_nominal_vdd);
	int GetSPDModuleNumberOfXMPProfiles(int _spd_index, int *_xmp_revision);
	int GetSPDModuleXMPProfileNumberOfCL(int _spd_index, int _profile_index);
	void GetSPDModuleXMPProfileCLInfos(int _spd_index, int _profile_index, int _cl_index, float *_frequency, float *_CL);
	void GetSPDModuleXMPProfileInfos(int _spd_index, int _profile_index, float *_tRCD, float *_tRAS, float *_tRP, float *_nominal_vdd, int *_max_freq, float *_max_CL);
	int GetSPDModuleNumberOfAMPProfiles(int _spd_index, int *_amp_revision);
	void GetSPDModuleAMPProfileInfos(int _spd_index, int _profile_index, int *_frequency, float *_fMinCycleTime, float *_tCL, float *_tRCD, float *_tRAS, float *_tRP, float *_tRC);
	int GetSPDModuleRawData(int _spd_index, int _offset);

//	Display
	int GetNumberOfDisplayAdapter();
	BOOL GetDisplayAdapterName(int _adapter_index, char *_szBuffer);
	BOOL GetDisplayAdapterCodeName(int _adapter_index, char *_szBuffer);
	int GetDisplayAdapterNumberOfPerformanceLevels(int _adapter_index);
	int GetDisplayAdapterCurrentPerformanceLevel(int _adapter_index);
	BOOL GetDisplayAdapterPerformanceLevelName(int _adapter_index, int _perf_level, char *_szBuffer);
	float GetDisplayAdapterClock(int _adapter_index, int _perf_level, int _domain);
	float GetDisplayAdapterStockClock(int _adapter_index, int _perf_level, int _domain);
	float GetDisplayAdapterTemperature(int _adapter_index, int _domain);
	int GetDisplayAdapterFanSpeed(int _adapter_index);
	int GetDisplayAdapterFanPWM(int _adapter_index);
	BOOL GetDisplayAdapterMemoryType(int _adapter_index, int *_type);
	BOOL GetDisplayAdapterMemorySize(int _adapter_index, int *_size);
	BOOL GetDisplayAdapterMemoryBusWidth(int _adapter_index, int *_bus_width);
	BOOL GetDisplayDriverVersion(char *_szBuffer);
	BOOL GetDirectXVersion(char *_szBuffer);
	BOOL GetDisplayAdapterBusInfos(int _adapter_index, int *_bus_type, int *_multi_vpu);
	float GetDisplayAdapterManufacturingProcess(int _adapter_index);
	BOOL GetDisplayAdapterPCIID(int _adapter_index, int *_vendor_id, int *_device_id, int *_revision_id, int *_sub_vendor_id, int *_sub_model_id);

//	HDD
	int GetNumberOfHDD();
	BOOL GetHDDName(int _hdd_index, char *_szBuffer);
	BOOL GetHDDRevision(int _hdd_index, char *_szBuffer);
	BOOL GetHDDSerialNumber(int _hdd_index, char *_szBuffer);
	float GetHDDTemperature(int _hdd_index, int _source);
	int GetHDDNumberOfVolumes(int _hdd_index);
	BOOL GetHDDVolumeLetter(int _hdd_index, int _volume_index, char *_szBuffer);
	BOOL GetHDDVolumeName(int _hdd_index, int _volume_index, char *_szBuffer);
	float GetHDDVolumeSize(int _hdd_index, int _volume_index);
	unsigned int GetHDDVolumeSerial(int _hdd_index, int _volume_index);
	int GetHDDNumberOfAttributes(int _hdd_index);
	BOOL GetHDDAttribute(int _hdd_index, int _attrib_index, int *_id, int *_flags, int *_value, int *_worst, unsigned char *_data);

//	Monitoring
	int GetNumberOfDevices();
	int GetDeviceClass(int _device_index);
	BOOL GetDeviceName(int _device_index, char *_szBuffer);
	BOOL GetDeviceSerialNumber(int _device_index, char *_szBuffer);
	int GetNumberOfSensors(int _device_index, int _sensor_class);
	BOOL GetSensorInfos(int _device_index, int _sensor_index, unsigned int _sensor_class, unsigned int *_sensor_id, char *_szName, unsigned int *_raw_value, float *_value, float *_min_value, float *_max_value);
	void SensorClearMinMax(int _device_index, int _sensor_index, int _sensor_class);
	float GetSensorTypeValue(int _sensor_type, int *_device_index, int *_sensor_index);
};

#endif //_CPUIDSDK_H_