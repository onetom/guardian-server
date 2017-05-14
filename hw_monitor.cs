using System;
using System.IO;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Windows.Forms;

namespace guardian_server {

public class Monitor {
  Hardware hw;
  CPUID cpuid;

  public void update_sensors() {
    cpuid.update_sensors(hw.server.devices, hw.server.sensors);
  }

  public void update_devices() {
    cpuid.update_devices(hw.server.devices);
  }

  public Monitor(Hardware h) {
    hw = h;
    Program.log.add("Monitor: ");
    cpuid = new CPUID();
    if (!cpuid.ok) {
      Application.Exit();
    }
    Program.log.add_line("ok");
  }
}

}
