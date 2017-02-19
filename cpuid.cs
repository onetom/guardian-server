using System;
using System.IO;
using System.Collections.Generic;

public class Sensor {
  public string name;
  public double value;
}

public class MB_sensors {
  public string name;
  public List<Sensor> fans;
  public List<Sensor> temps;
  public List<Sensor> volts;
}

public class CPU_sensors {
  public string name;
  public List<Sensor> loads;
  public List<Sensor> temps;
  public List<Sensor> volts;
  public List<Sensor> clocks;
  public List<Sensor> watts;
}

public class HDD_sensors {
  public string name;
  public List<Sensor> loads;
  public List<Sensor> temps;
}

public class GPU_sensors {
  public string name;
  public List<Sensor> fans;
  public List<Sensor> loads;
  public List<Sensor> temps;
}

public class Memory_sensors {
  public string name;
  public double free;
  public double total;
}

public class CPU_info {
  public string name;
  public string code_name;
  public double tdp;
  public double stock_clock;
}

public class MB_info {
  public string vendor;
  public string name;
  public string nb;
  public string sb;
  public string bios_version;
  public string bios_date;
}

public class HDD_info {
  public double total;
  public double free;
  public string fs;
  public string letter;
  public string volume;
}

public class GPU_info {
  public string name;
  public string code_name;
  public double clock;
  public double stock_clock;
  public double memory_size;
}

public class SPD_module {
  public string name;
  public int size;
  public string part;
}

public class Memory_info {
  public string type;
  public double size;
  public double clock;
  public List<SPD_module> spd;
}

public class Attribute {
  public string name;
  public int id;
  public int flags;
  public int value;
  public int worst;
}

public class SMART_report {
  public string name;
  public List<Attribute> attributes;
}

class CPUID {
  public CPUIDSDK pSDK;
  public bool ok = false;

  public Dictionary<int, string> smart_names = new Dictionary<int, string>() {
    {0x00, "Invalid"},
    {0x01, "Raw read error rate"},
    {0x02, "Throughput performance"},
    {0x03, "Spinup time"},
    {0x04, "Start/Stop count"},
    {0x05, "Reallocated sector count"},
    {0x06, "Read channel margin"},
    {0x07, "Seek error rate"},
    {0x08, "Seek timer performance"},
    {0x09, "Power-on hours count"},
    {0x0A, "Spinup retry count"},
    {0x0B, "Calibration retry count"},
    {0x0C, "Power cycle count"},
    {0x0D, "Soft read error rate"},
    {0x16, "Current Helium Level"},
    {0xAA, "Available Reserved Space"},
    {0xAB, "SSD Program Fail Count"},
    {0xAC, "SSD Erase Fail Count"},
    {0xAD, "SSD Wear Leveling Count"},
    {0xAE, "Unexpected power loss count"},
    {0xAF, "Power Loss Protection Failure"},
    {0xB0, "Erase Fail Count (chip)"},
    {0xB1, "Wear Range Delta"},
    {0xB3, "Used Reserved Block Count Total"},
    {0xB4, "Unused Reserved Block Count Total"},
    {0xB5, "Program Fail Count Total or Non-4K Aligned Access Count"},
    {0xB6, "Erase Fail Count"},
    {0xB7, "SATA Downshift Error Count or Runtime Bad Block"},
    {0xB8, "End-to-End error"},
    {0xB9, "Head Stability"},
    {0xBA, "Induced Op-Vibration Detection"},
    {0xBB, "Reported Uncorrectable Errors"},
    {0xBC, "Command Timeout"},
    {0xBD, "High Fly Writes"},
    {0xBE, "Airflow Temperature"},
    {0xBF, "G-sense error rate"},
    {0xC0, "Power-off retract count"},
    {0xC1, "Load/Unload cycle count"},
    {0xC2, "HDD temperature"},
    {0xC3, "Hardware ECC recovered"},
    {0xC4, "Reallocation count"},
    {0xC5, "Current pending sector count"},
    {0xC6, "Offline scan uncorrectable count"},
    {0xC7, "UDMA CRC error rate"},
    {0xC8, "Write error rate"},
    {0xC9, "Soft read error rate"},
    {0xCA, "Data Address Mark errors"},
    {0xCB, "Run out cancel"},
    {0xCC, "Soft ECC correction"},
    {0xCD, "Thermal asperity rate (TAR)"},
    {0xCE, "Flying height"},
    {0xCF, "Spin high current"},
    {0xD0, "Spin buzz"},
    {0xD1, "Offline seek performance"},
    {0xD2, "Vibration During Write"},
    {0xD3, "Vibration During Write"},
    {0xD4, "Shock During Write"},
    {0xDC, "Disk shift"},
    {0xDD, "G-sense error rate"},
    {0xDE, "Loaded hours"},
    {0xDF, "Load/unload retry count"},
    {0xE0, "Load friction"},
    {0xE1, "Load/Unload cycle count"},
    {0xE2, "Load-in time"},
    {0xE3, "Torque amplification count"},
    {0xE4, "Power-off retract count"},
    {0xE6, "GMR head amplitude"},
    {0xE7, "Temperature"},
    {0xE8, "Endurance Remaining or Available Reserved Space"},
    {0xE9, "Power-On Hours or Media Wearout Indicator"},
    {0xEA, "Average erase count AND Maximum Erase Count"},
    {0xEB, "Good Block Count AND System(Free) Block Count"},
    {0xF0, "Head flying hours"},
    {0xF1, "Total LBAs Written"},
    {0xF2, "Total LBAs Read"},
    {0xF3, "Total LBAs Written Expanded"},
    {0xF4, "Total LBAs Read Expanded"},
    {0xF9, "NAND_Writes_1GiB"},
    {0xFA, "Read error retry rate"},
    {0xFB, "Minimum Spares Remaining"},
    {0xFC, "Newly Added Bad Flash Block"},
    {0xFE, "Free Fall Protection"}
  };

  public CPUID() {
    int error_code = 0;
    int extended_error_code = 0;
    pSDK = new CPUIDSDK();
    pSDK.CreateInstance();
    ok = pSDK.Init(CPUIDSDK.szDllPath,
      CPUIDSDK.szDllFilename,
      CPUIDSDK.CPUIDSDK_CONFIG_USE_EVERYTHING,
      ref error_code,
      ref extended_error_code);
  }

  public string get_drive_letter(string s) {
    return Char.ToUpper(s[Math.Max(s.IndexOf(":") - 1, 0)]) + ":";
  }

  public List<Sensor> get_sensor_list(int device_index, int sensor_class) {
    int sensor_index;
    int NbSensors;
    bool result;
    int sensor_id = 0;
    string sensorname = "";
    int iValue = 0;
    float fValue = 0;
    float fMinValue = 0;
    float fMaxValue = 0;
    var sensors = new List<Sensor>();
    NbSensors = pSDK.GetNumberOfSensors(device_index, sensor_class);
    for (sensor_index = 0; sensor_index < NbSensors; sensor_index += 1) {
      result = pSDK.GetSensorInfos(device_index,
        sensor_index,
        sensor_class,
        ref sensor_id,
        ref sensorname,
        ref iValue,
        ref fValue,
        ref fMinValue,
        ref fMaxValue);
      if (result == true) {
        var data = new Sensor();
        data.name = sensorname;
        data.value = Math.Round(fValue, 2);
        sensors.Add(data);
      }
    }
    return sensors;
  }

  public Memory_sensors get_memory_usage() {
    var memory = new Memory_sensors();
    var info = new Microsoft.VisualBasic.Devices.ComputerInfo();
    memory.name = "Physical Memory";
    memory.total = info.TotalPhysicalMemory;
    memory.free = info.AvailablePhysicalMemory;
    return memory;
  }

  public void update_sensors(Dictionary<string, dynamic> sensors) {
    int NbDevices;
    int device_index;
    string devicename;
    int deviceclass;  
    var mb = new MB_sensors();
    var cpus = new List<CPU_sensors>();
    var hdds = new List<HDD_sensors>();
    var gpus = new List<GPU_sensors>();
    pSDK.RefreshInformation();
    NbDevices = pSDK.GetNumberOfDevices();
    for (device_index = 0; device_index < NbDevices; device_index += 1) {
      devicename = pSDK.GetDeviceName(device_index);
      deviceclass = pSDK.GetDeviceClass(device_index);
      if (deviceclass == CPUIDSDK.CLASS_DEVICE_MAINBOARD) {
        mb.name = devicename;
        mb.fans = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_FAN);
        mb.temps = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
        mb.volts = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_VOLTAGE);
      } else if (deviceclass == CPUIDSDK.CLASS_DEVICE_PROCESSOR) {
        var cpu = new CPU_sensors();
        cpu.name = devicename;
        cpu.loads = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_UTILIZATION);
        cpu.temps = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
        cpu.volts = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_VOLTAGE);
        cpu.clocks = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_CLOCK_SPEED);
        cpu.watts = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_POWER);
        cpus.Add(cpu);
      } else if (deviceclass == CPUIDSDK.CLASS_DEVICE_DRIVE) {
        var hdd = new HDD_sensors();
        hdd.name = devicename.Trim();
        hdd.loads = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_UTILIZATION);
        foreach (var x in hdd.loads) {
          x.name = get_drive_letter(x.name);
        }
        hdd.temps = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
        hdds.Add(hdd);
      } else if (deviceclass == CPUIDSDK.CLASS_DEVICE_DISPLAY_ADAPTER) {
        var gpu = new GPU_sensors();
        gpu.name = devicename;
        gpu.fans = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_FAN);
        gpu.loads = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_UTILIZATION);
        gpu.temps = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
        gpus.Add(gpu);
      }
    }
    sensors["mb"] = mb;
    sensors["cpus"] = cpus;
    sensors["hdds"] = hdds;
    sensors["gpus"] = gpus;
    sensors["memory"] = get_memory_usage();
  }

  public List<SMART_report> get_smart_report() {
    int id = 0;
    int flags = 0;
    int value = 0;
    int worst = 0;
    var data = new byte[6];
    var smart_list = new List<SMART_report>();
    for (int hdd_index = 0; hdd_index < pSDK.GetNumberOfHDD(); hdd_index += 1) {
      var smart = new SMART_report();
      smart.name = pSDK.GetHDDName(hdd_index).Trim();
      smart.attributes = new List<Attribute>();
      for (int attrib_index = 0; attrib_index < pSDK.GetHDDNumberOfAttributes(hdd_index); attrib_index += 1) {
        bool res = pSDK.GetHDDAttribute(hdd_index, attrib_index, ref id, ref flags, ref value, ref worst, data);
        if (res && smart_names.ContainsKey(attrib_index)) {
          var attribute = new Attribute();
          attribute.name = smart_names[attrib_index];
          attribute.id = id;
          attribute.flags = flags;
          attribute.value = value;
          attribute.worst = worst;
          smart.attributes.Add(attribute);
        }
      }
      smart_list.Add(smart);
    }
    return smart_list;
  }

  public List<HDD_info> get_hdd_info_list() {
    var hdd_list = new List<HDD_info>();
    var allDrives = DriveInfo.GetDrives();
    foreach (DriveInfo d in allDrives) {
      if (d.IsReady) {
        var hdd = new HDD_info();
        hdd.fs = d.DriveFormat;
        hdd.letter = get_drive_letter(d.Name);
        hdd.free = d.TotalFreeSpace;
        hdd.total = d.TotalSize;
        hdd.volume = d.VolumeLabel;
        hdd_list.Add(hdd);
      }
    }
    return hdd_list;
  }

  public List<CPU_info> get_cpu_info_list() {
    var cpu_list = new List<CPU_info>();
    for (int cpu_index = 0; cpu_index < pSDK.GetNumberOfProcessors(); cpu_index += 1) {
      var cpu = new CPU_info();
      cpu.name = pSDK.GetProcessorName(cpu_index);
      cpu.code_name = pSDK.GetProcessorCodeName(cpu_index);
      cpu.tdp = pSDK.GetProcessorTDP(cpu_index);
      cpu.stock_clock = pSDK.GetProcessorStockClockFrequency(cpu_index);
      cpu_list.Add(cpu);
    }
    return cpu_list;
  }

  public MB_info get_mb_info() {
    var mb = new MB_info();
    mb.vendor = pSDK.GetMainboardVendor();
    mb.name = pSDK.GetMainboardModel();
    mb.nb = pSDK.GetNorthBridgeModel();
    mb.sb = pSDK.GetSouthBridgeModel();
    mb.bios_version = pSDK.GetBIOSVersion();
    mb.bios_date = pSDK.GetBIOSDate();
    return mb;
  }

  public List<GPU_info> get_gpu_info_list() {
    int size = 0;
    var gpu_list = new List<GPU_info>();
    for (int gpu_index = 0; gpu_index < pSDK.GetNumberOfDisplayAdapter(); gpu_index += 1) {
      var gpu = new GPU_info();
      var perf_level = pSDK.GetDisplayAdapterCurrentPerformanceLevel(gpu_index);
      gpu.name = pSDK.GetDisplayAdapterName(gpu_index);
      gpu.code_name = pSDK.GetDisplayAdapterCodeName(gpu_index);
      gpu.clock = pSDK.GetDisplayAdapterClock(gpu_index, perf_level, CPUIDSDK.DISPLAY_CLOCK_DOMAIN_GRAPHICS);
      gpu.stock_clock = pSDK.GetDisplayAdapterStockClock(gpu_index, perf_level, CPUIDSDK.DISPLAY_CLOCK_DOMAIN_GRAPHICS);
      pSDK.GetDisplayAdapterMemorySize(gpu_index, ref size);
      gpu.memory_size = size;
      gpu_list.Add(gpu);
    }
    return gpu_list;
  }

  public Memory_info get_memory_info() {
    string s;
    var memory = new Memory_info();
    switch (pSDK.GetMemoryType()) {
      case CPUIDSDK.MEMORY_TYPE_SPM_RAM: s = "SPM"; break;
      case CPUIDSDK.MEMORY_TYPE_RDRAM: s = "RDRAM"; break;
      case CPUIDSDK.MEMORY_TYPE_EDO_RAM: s = "EDO"; break;
      case CPUIDSDK.MEMORY_TYPE_FPM_RAM: s = "FPM"; break;
      case CPUIDSDK.MEMORY_TYPE_SDRAM: s = "SDRAM"; break;
      case CPUIDSDK.MEMORY_TYPE_DDR_SDRAM: s = "DDR"; break;
      case CPUIDSDK.MEMORY_TYPE_DDR2_SDRAM: s = "DDR2"; break;
      case CPUIDSDK.MEMORY_TYPE_DDR2_SDRAM_FB: s = "FB-DDR2"; break;
      case CPUIDSDK.MEMORY_TYPE_DDR3_SDRAM: s = "DDR3"; break;
      case CPUIDSDK.MEMORY_TYPE_DDR4_SDRAM: s = "DDR4"; break;
      default: s = ""; break;
    }
    memory.type = s;
    memory.size = pSDK.GetMemorySize();
    memory.clock = pSDK.GetMemoryClockFrequency();
    memory.spd = new List<SPD_module>();
    int spd_modules = pSDK.GetNumberOfSPDModules();
    for (int spd_index = 0; spd_index < spd_modules; spd_index += 1) {
      var spd_module = new SPD_module();
      string format = pSDK.GetSPDModuleFormat(spd_index).Trim();
      spd_module.size = pSDK.GetSPDModuleSize(spd_index);
      string name = pSDK.GetSPDModuleManufacturer(spd_index).Trim();
      string spec = pSDK.GetSPDModuleSpecification(spd_index).Trim();
      spd_module.name = format + " " + name + " " + spec;      
      spd_module.part = pSDK.GetSPDModulePartNumber(spd_index).Trim();
      memory.spd.Add(spd_module);
    }
    return memory;
  }

  public void update_devices(Dictionary<string, dynamic> devices) {
    devices["mb"] = get_mb_info();
    devices["cpus"] = get_cpu_info_list();
    devices["hdds"] = get_hdd_info_list();
    devices["smart"] = get_smart_report();
    devices["gpus"] = get_gpu_info_list();
    devices["memory"] = get_memory_info();
  }

  ~CPUID() {
    pSDK.Close();
    pSDK.DestroyInstance();
  }
}
