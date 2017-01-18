using System;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace guardian_server {

public class RGB {
  public int r = 0;
  public int g = 0;
  public int b = 0;
}

public class Keyboard {
  public string name = "none";
  public RGB[] zones = new RGB[4];
  public Keyboard() {
    for (int i = 0; i < zones.Length; i += 1) {
      zones[i] = new RGB();
    }
  }
}

public class Hardware_state {
  public Keyboard keyboard;
}

public class Hardware {
  public dynamic keyboard;
  public Hardware_state state;

  public void set_keyboard_color(dynamic data) {
    int zone = data.zone;
    int r = data.r;
    int g = data.g;
    int b = data.b;
    state.keyboard.zones[zone].r = r;
    state.keyboard.zones[zone].g = g;
    state.keyboard.zones[zone].b = b;
    keyboard.set_zone_color(zone, r, g, b);
  }

  public void save_state() {
    File.WriteAllText("hardware.json", JsonConvert.SerializeObject(state));
  }

  public Hardware() {    
    state = new Hardware_state();
    Program.log.add("hardware.json: ");
    state = JsonConvert.DeserializeObject<Hardware_state>(File.ReadAllText("hardware.json"));
    Program.log.add("ok\n");
    Program.log.add("keyboard: ");
    if (Program.settings.keyboard == "SSE") {
      keyboard = new SSE();
      state.keyboard.name = "SSE";
    }
    Program.log.add(state.keyboard.name + "\n");
  }
}

}
