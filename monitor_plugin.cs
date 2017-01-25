using System;
using System.IO;
using System.Collections.Generic;
using System.Threading;
using WebSocketSharp;
using WebSocketSharp.Server;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public class Message {
  public string tag { get; set; }
  public dynamic data { get; set; }
}

public class Effect {
  public string name;
  public string zone;
  public List<int> color;
  public List<int> end_color;
  public int is_on;
}

class Program {
  static bool is_running = true;
  static WebSocket ws;
  static public Dictionary<string, dynamic> sensors;
  static public Dictionary<string, Effect> zones;

  static void send_message(string tag, dynamic data) {
    var message = new Message();
    message.tag = tag;
    message.data = data;
    ws.Send(JsonConvert.SerializeObject(message));
  }

  static void on_message(object sender, MessageEventArgs e) {
    var message = JsonConvert.DeserializeObject<Message>(e.Data);
    if (message.tag == "sensors") {
      sensors = message.data.ToObject<Dictionary<string, dynamic>>();
    } else if (message.tag == "reset_keyboard_effect") {
      string zone = message.data.zone;
      zones[zone] = new Effect();
      zones[zone].is_on = 0;
    } else if (message.tag == "set_keyboard_effect") {
      string name = message.data.name;
      if (name == "cpu_temp" || name == "cpu_load" || name == "gpu_temp" || name == "gpu_load") {
        Effect data = message.data.ToObject<Effect>();
        zones[data.zone] = data;
        zones[data.zone].is_on = 1;
      }
    }
  }

  static void update_monitor(Effect e, float x) {
    int r = (int) Tools.lerp(e.color[0], e.end_color[0], x);
    int g = (int) Tools.lerp(e.color[1], e.end_color[1], x);
    int b = (int) Tools.lerp(e.color[2], e.end_color[2], x);
    var j = new JObject();
    var color = new JArray();
    j.Add("name", "static_color_from_plugin");
    j.Add("zone", e.zone);
    color.Add(r);
    color.Add(g);
    color.Add(b);
    j.Add("color", color);
    send_message("set_keyboard_zones", j);
  }

  static float get_sensor_by_path(string section, string sensor_type, string sensor_name) {
    List<dynamic> section_list = sensors[section].ToObject<List<dynamic>>();
    if (section_list.Count == 0) {
      return 0;
    }
    List<dynamic> sensor_list = section_list[0][sensor_type].ToObject<List<dynamic>>();
    if (sensor_list.Count == 0) {
      return 0;
    }
    foreach (var x in sensor_list) {
      if (x["name"] == sensor_name) {
        return x["value"];
      }
    }
    return sensor_list[0]["value"];
  }

  static float get_sensor(Effect e) {
    float x = 0;
    if (e.name == "cpu_temp") {
      x = get_sensor_by_path("cpus", "temps", "Package");
      x = Tools.remap(x, 40, 70, 0, 1);
    } else if (e.name == "cpu_load") {
      x = get_sensor_by_path("cpus", "loads", "UC");
      x = Tools.remap(x, 0, 100, 0, 1);
    } else if (e.name == "gpu_temp") {
      x = get_sensor_by_path("gpus", "temps", "Package");
      x = Tools.remap(x, 40, 70, 0, 1);
    } else if (e.name == "gpu_load") {
      x = get_sensor_by_path("gpus", "loads", "UC");
      x = Tools.remap(x, 0, 100, 0, 1);
    }
    return x;
  }

  static void do_monitoring() {
    foreach (var effect in zones.Values) {
      if (effect.is_on != 0) {
        update_monitor(effect, get_sensor(effect));
      }
    }
  }

  static void Main(string[] args) {
    zones = new Dictionary<string, Effect>();
    ws = new WebSocket("ws://127.0.0.1:8000");
    ws.OnMessage += on_message;
    ws.OnError += (sender, e) => is_running = false;
    ws.OnClose += (sender, e) => is_running = false;
    ws.Connect();
    send_message("get_sensors", 0);
    while (is_running) {
      if (sensors != null) {
        do_monitoring();
      }
      send_message("get_sensors", 0);
      Thread.Sleep(1000);
    }
  }
}
