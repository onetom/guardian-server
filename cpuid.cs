using System;
using System.Collections.Generic;

public class MB_report {
  public string name;
  public List<dynamic> fan_list;
  public List<dynamic> temp_list;
}

public class CPU_report {
  public string name;
  public List<dynamic> load_list;
  public List<dynamic> temp_list;
}

public class HDD_report {
  public string name;
  public List<dynamic> temp_list;
}

public class GPU_report {
  public string name;
  public List<dynamic> fan_list;
  public List<dynamic> load_list;
  public List<dynamic> temp_list;
}

public class Monitor_report {
  public List<MB_report> mb_list;
  public List<CPU_report> cpu_list;
  public List<HDD_report> hdd_list;
  public List<GPU_report> gpu_list;
}

public class SMART_report {
  public string name;
  public List<List<dynamic>> attr_list;
}

class CPUID {
  CPUIDSDK pSDK;
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

  public List<dynamic> get_sensor_list(int device_index, int sensor_class) {
    int sensor_index;
    int NbSensors;
    bool result;
    int sensor_id = 0;
    string sensorname = "";
    int iValue = 0;
    float fValue = 0;
    float fMinValue = 0;
    float fMaxValue = 0;
    var sensors = new List<dynamic>();
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
        sensors.Add(new List<dynamic> { sensorname, Math.Round(fValue, 2) });
      }
    }
    return sensors;
  }

  public Monitor_report get_monitor_report() {
    int NbDevices;
    int device_index;
    string devicename;
    int deviceclass;
    var report = new Monitor_report();
    report.mb_list = new List<MB_report>();
    report.cpu_list = new List<CPU_report>();
    report.hdd_list = new List<HDD_report>();
    report.gpu_list = new List<GPU_report>();
    pSDK.RefreshInformation();
    NbDevices = pSDK.GetNumberOfDevices();
    for (device_index = 0; device_index < NbDevices; device_index += 1) {
      devicename = pSDK.GetDeviceName(device_index);
      deviceclass = pSDK.GetDeviceClass(device_index);
      if (deviceclass == CPUIDSDK.CLASS_DEVICE_MAINBOARD) {
        var mb = new MB_report();
        mb.name = devicename;
        mb.fan_list = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_FAN);
        mb.temp_list = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
        report.mb_list.Add(mb);
      } else if (deviceclass == CPUIDSDK.CLASS_DEVICE_PROCESSOR) {
        var cpu = new CPU_report();
        cpu.name = devicename;
        cpu.load_list = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_UTILIZATION);
        cpu.temp_list = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
        report.cpu_list.Add(cpu);
      } else if (deviceclass == CPUIDSDK.CLASS_DEVICE_DRIVE) {
        var hdd = new HDD_report();
        hdd.name = devicename;
        hdd.temp_list = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
        report.hdd_list.Add(hdd);
      } else if (deviceclass == CPUIDSDK.CLASS_DEVICE_DISPLAY_ADAPTER) {
        var gpu = new GPU_report();
        gpu.name = devicename;
        gpu.fan_list = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_FAN);
        gpu.load_list = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_UTILIZATION);
        gpu.temp_list = get_sensor_list(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
        report.gpu_list.Add(gpu);
      }
    }
    return report;
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
      smart.name = pSDK.GetHDDName(hdd_index);
      smart.attr_list = new List<List<dynamic>>();
      for (int attrib_index = 0; attrib_index < pSDK.GetHDDNumberOfAttributes(hdd_index); attrib_index += 1) {
        bool res = pSDK.GetHDDAttribute(hdd_index, attrib_index, ref id, ref flags, ref value, ref worst, data);
        if (res && smart_names.ContainsKey(attrib_index)) {
          smart.attr_list.Add(new List<dynamic> { smart_names[attrib_index], id, flags, value, worst });
        }
      }
      smart_list.Add(smart);
    }
    return smart_list;
  }

  ~CPUID() {
    pSDK.Close();
    pSDK.DestroyInstance();
  }
}
