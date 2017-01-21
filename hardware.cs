using System;
using System.IO;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace guardian_server {

public class RGB {
  public int r = 0;
  public int g = 0;
  public int b = 0;
}

public class Led_keyboard {
  public string name = "none";
  public RGB[] zones = new RGB[4];
  public Led_keyboard() {
    for (int i = 0; i < zones.Length; i += 1) {
      zones[i] = new RGB();
    }
  }
}

public class Hardware_state {
  public Led_keyboard led_keyboard;
  public Dictionary<string, dynamic> plugin_effects;
}

public class Hardware {
  public dynamic led_keyboard;
  public Hardware_state state;

  public void set_keyboard_color(dynamic data) {
    int zone = data.zone;
    zone = (int) Tools.clamp(zone, 0, state.led_keyboard.zones.Length - 1);
    int r = data.r;
    int g = data.g;
    int b = data.b;
    state.led_keyboard.zones[zone].r = r;
    state.led_keyboard.zones[zone].g = g;
    state.led_keyboard.zones[zone].b = b;
    led_keyboard.set_zone_color(zone, r, g, b);
  }

  public void restore() {
    int r;
    int g;
    int b;
    for (int i = 0; i < state.led_keyboard.zones.Length - 1; i += 1) {
      r = state.led_keyboard.zones[i].r;
      g = state.led_keyboard.zones[i].g;
      b = state.led_keyboard.zones[i].b;
      led_keyboard.set_zone_color(i, r, g, b);
    }
  }

  public void save() {
    File.WriteAllText("hardware.json", JsonConvert.SerializeObject(state));
  }

  public void update(Dictionary<string, dynamic> devices) {
    devices["led_keyboard"] = state.led_keyboard;
    devices["plugin_effects"] = state.plugin_effects;
  }

  public void set_plugin_effect(dynamic data) {
    string name = data.name;
    state.plugin_effects[name] = data;
  }

  public Hardware() {    
    Program.log.add("hardware.json: ");
    state = JsonConvert.DeserializeObject<Hardware_state>(File.ReadAllText("hardware.json"));
    Program.log.add("ok\n");
    Program.log.add("led_keyboard: ");
    if (Program.settings.led_keyboard == "SSE") {
      led_keyboard = new SSE();     
    } else if (Program.settings.led_keyboard == "Clevo") {
      led_keyboard = new Clevo();
    }
    state.led_keyboard.name = Program.settings.led_keyboard;
    Program.log.add(state.led_keyboard.name + "\n");
    restore();
  }

}

}
