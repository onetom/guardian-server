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
    string name = effect["name"];
    string zone = effect["zone"];
    if (name == "static_color_from_plugin" && zones[zone]["name"] != "static_color") {
      set_static_color(effect);
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

  public Led_keyboard(Hardware h) {
    Program.log.add("led_keyboard: ");
    hw = h;
    kb_info = new Keyboard_info();
    kb_info.name = Program.settings.led_keyboard;
    if (kb_info.name == "SSE") {
      kb_server = new SSE();
    } else if (kb_info.name == "Clevo") {
      kb_server = new Clevo();
    }
    kb_info.number_of_zones = kb_server.get_number_of_zones();
    zones = new Dictionary<string, dynamic>();
    set_default_effects();
    foreach (JProperty x in hw.state["led_keyboard"]) {
      zones[x.Name] = x.Value;
    }
    restore();
    Program.log.add(kb_info.name + "\n");
  }
}

public class Hardware {
  public Server server;
  public Dictionary<string, dynamic> state;
  public Led_keyboard led_keyboard;

  public void save() {
    state["led_keyboard"] = led_keyboard.zones;
    File.WriteAllText("hardware.json", JsonConvert.SerializeObject(state));
  }

  public void update_sensors(Dictionary<string, dynamic> sensors) {
    led_keyboard.update_sensors(sensors);
  }

  public void update_devices(Dictionary<string, dynamic> devices) {
    led_keyboard.update_devices(devices);
  }

  public Hardware(Server s) {
    server = s;
    state = new Dictionary<string, dynamic>();
    Program.log.add("hardware.json: ");
    state = JsonConvert.DeserializeObject<Dictionary<string, dynamic>>(File.ReadAllText("hardware.json"));
    Program.log.add("ok\n");
    led_keyboard = new Led_keyboard(this);
  }
}

}
