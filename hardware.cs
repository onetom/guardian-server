using System;
using System.IO;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace guardian_server {

public class Keyboard_info {
  public string name;
  public int number_of_zones;
}

public class Led_keyboard {
  Hardware hw;
  dynamic kb_server;
  public Dictionary<string, dynamic> zones;
  public Keyboard_info kb_info;

  void set_zone_color(string zone, dynamic effect) {
    if (kb_server == null) {
      return;
    }
    int z = int.Parse(zone);
    int r = effect["color"][0];
    int g = effect["color"][1];
    int b = effect["color"][2];
    if (z > kb_server.get_number_of_zones()) {
      return;
    }
    kb_server.set_zone_color(z - 1, r, g, b);
  }

  void set_static_color(dynamic effect) {
    string zone = effect["zone"];
    if (zone == "all") {
      for (int z = 1; z <= kb_info.number_of_zones; z += 1) {
        set_zone_color(z.ToString(), effect);
      }
    } else {
      set_zone_color(zone, effect);
    }
  }

  public void reset_zone(string zone) {
    hw.server.send_plugin_message("reset_keyboard_effect", zones[zone]);
    if (zone == "all") {
      set_default_effects();
    }
    set_static_color(zones[zone]);
  }

  public void set_keyboard_zones(dynamic effect) {
    if (zones == null) {
      return;
    }
    string name = effect["name"];
    string zone = effect["zone"];
    if (name == "static_color_from_plugin") {
      if (zones[zone]["name"] != "static_color") {
        set_static_color(effect);
      }
      return;
    }
    if (name == "off" || zones[zone]["name"] != "static_color") {
      reset_zone(zone);
    }
    if (name == "static_color") {
      set_static_color(effect);
    } else if (name != "off") {
      hw.server.send_plugin_message("set_keyboard_effect", effect);
    }
    zones[zone] = effect;
  }

  public void update_sensors(Dictionary<string, dynamic> sensors) {
    sensors["led_keyboard"] = zones;
  }

  public void update_devices(Dictionary<string, dynamic> devices) {
    devices["led_keyboard"] = kb_info;
  }

  public void set_default_effect(string zone) {
    var effect = new Dictionary<string, dynamic>();
    effect["name"] = "static_color";
    effect["zone"] = zone;
    effect["color"] = new List<int> { 0, 0, 0 };
    effect["beg_color"] = new List<int> { 0, 0, 0 };
    effect["end_color"] = new List<int> { 0, 0, 0 };
    zones[zone] = effect;
  }

  public void set_default_effects() {
    for (int z = 1; z <= kb_info.number_of_zones; z += 1) {
      set_default_effect(z.ToString());
    }
    set_default_effect("all");
    zones["all"]["name"] = "off";
  }

  public void restore() {
    if (zones["all"]["name"] != "off") {
      set_keyboard_zones(zones["all"]);
      return;
    }
    for (int z = 1; z <= kb_info.number_of_zones; z += 1) {
      set_keyboard_zones(zones[z.ToString()]);
    }
  }

  public Dictionary<string, dynamic> save() {
    return zones;
  }

  public Led_keyboard(Hardware h) {
    Program.log.add("led_keyboard: ");
    hw = h;
    kb_info = new Keyboard_info();
    kb_info.name = Program.settings.led_keyboard;
    if (kb_info.name == "SSE3") {
      kb_server = new SSE(3);
    } else if (kb_info.name == "SSE4") {
      kb_server = new SSE(4);
    } else if (kb_info.name == "SSE5") {
      kb_server = new SSE(5);
    } else if (kb_info.name == "Clevo") {
      kb_server = new Clevo();
    } else {
      Program.log.add_line(kb_info.name);
      return;
    }
    kb_info.number_of_zones = kb_server.get_number_of_zones();
    zones = new Dictionary<string, dynamic>();
    set_default_effects();
    if (hw.state["led_keyboard"] != null) {
      foreach (JProperty x in hw.state["led_keyboard"]) {
        zones[x.Name] = x.Value;
      }
    }
    restore();
    Program.log.add_line(kb_info.name);
  }
}

public class Digital_storm {
  Hardware hw;
  Dictionary<string, dynamic> state = null;

  public void update_sensors(Dictionary<string, dynamic> sensors) {
    sensors["fans"] = state["fans"];
    sensors["strips"] = state["strips"];
    sensors["uv_strips"] = state["uv_strips"];
  }

  public Dictionary<string, dynamic> save() {
    return state;
  }

  public void set_default_state() {
    int i;
    state = new Dictionary<string, dynamic>();
    state["fans"] = new List<Dictionary<string, dynamic>>();
    state["strips"] = new List<Dictionary<string, dynamic>>();
    state["uv_strips"] = new List<Dictionary<string, dynamic>>();
    for (i = 0; i < 7; i += 1) {
      var fan = new Dictionary<string, dynamic>();
      fan["name"] = "Fan " + i;
      fan["effect"] = "none";
      fan["color"] = new List<int> { 0, 0, 0 };
      fan["beg_color"] = new List<int> { 0, 0, 0 };
      fan["end_color"] = new List<int> { 0, 0, 0 };
      fan["pwm"] = 0;
      fan["tach"] = 0;
      state["fans"].Add(fan);
    }
    for (i = 0; i < 4; i += 1) {
      var strip = new Dictionary<string, dynamic>();
      strip["name"] = "Strip " + i;
      strip["effect"] = "none";
      strip["color"] = new List<int> { 0, 0, 0 };
      strip["beg_color"] = new List<int> { 0, 0, 0 };
      strip["end_color"] = new List<int> { 0, 0, 0 };
      state["strips"].Add(strip);
    }
    for (i = 0; i < 2; i += 1) {
      var uv = new Dictionary<string, dynamic>();
      uv["name"] = "UV Strip " + i;
      uv["effect"] = "none";
      uv["color"] = new List<int> { 0, 0, 0 };
      uv["beg_color"] = new List<int> { 0, 0, 0 };
      uv["end_color"] = new List<int> { 0, 0, 0 };
      state["uv_strips"].Add(uv);
    }
  }

  public void update_state(dynamic s) {
    foreach (JProperty x in s) {
      state[x.Name] = x.Value;
    }
  }

  public Digital_storm(Hardware h) {
    Program.log.add("Digital_storm: ");
    hw = h;
    set_default_state();
    if (hw.state["digital_storm"] != null) {
      foreach (JProperty x in hw.state["digital_storm"]) {
        state[x.Name] = x.Value;
      }
    }
    Program.log.add_line("ok");
  }
}

public class Hardware {
  public Server server;
  public Dictionary<string, dynamic> state;
  public Led_keyboard lk;
  public Digital_storm ds;

  public void save() {
    state["led_keyboard"] = lk.save();
    state["digital_storm"] = ds.save();
    File.WriteAllText("hardware.json", JsonConvert.SerializeObject(state));
  }

  public void update_sensors(Dictionary<string, dynamic> sensors) {
    lk.update_sensors(sensors);
    ds.update_sensors(sensors);
  }

  public void update_devices(Dictionary<string, dynamic> devices) {
    lk.update_devices(devices);
  }

  public Hardware(Server s) {
    server = s;
    state = new Dictionary<string, dynamic>();
    Program.log.add("hardware.json: ");
    state = JsonConvert.DeserializeObject<Dictionary<string, dynamic>>(File.ReadAllText("hardware.json"));
    Program.log.add_line("ok");
    lk = new Led_keyboard(this);
    ds = new Digital_storm(this);
  }
}

}
