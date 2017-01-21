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

public class RGB {
  public int r;
  public int g;
  public int b;
}

public class Monitor {
  public int is_on;
  public string sensor_type;
  public float start_value;
  public float end_value;
  public RGB start_color;
  public RGB end_color;
}

class Program {
  static bool is_running = true;
  static WebSocket ws;
  static public Dictionary<string, dynamic> sensors;
  static public Dictionary<string, dynamic> devices;
  static Monitor monitor;
  static int zone;

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
    } else if (message.tag == "devices") {
      devices = message.data.ToObject<Dictionary<string, dynamic>>();
    } else if (message.tag == "set_plugin_effect") {
      string name = message.data.name;
      dynamic data = message.data.data;
      if (name == "monitor_0") {
        zone = 0;
        monitor = data.ToObject<Monitor>();
      } else if (name == "monitor_1") {
        zone = 1;
        monitor = data.ToObject<Monitor>();
      } else if (name == "monitor_2") {
        zone = 2;
        monitor = data.ToObject<Monitor>();
      } else if (name == "monitor_3") {
        zone = 3;
        monitor = data.ToObject<Monitor>();
      }
    }
  }

  static void monitor_effect() {
    float value = 0;
    if (monitor.sensor_type == "cpu_temp") {
      value = sensors["cpus"][0]["temps"][0]["value"];
    } else if (monitor.sensor_type == "cpu_load") {
      value = sensors["cpus"][0]["loads"][0]["value"];
    }
    value = Tools.clamp(value, monitor.start_value, monitor.end_value);
    value = Tools.remap(value, monitor.start_value, monitor.end_value, 0, 1);
    int r = (int) Tools.lerp(monitor.start_color.r, monitor.end_color.r, value);
    int g = (int) Tools.lerp(monitor.start_color.g, monitor.end_color.g, value);
    int b = (int) Tools.lerp(monitor.start_color.b, monitor.end_color.b, value);
    var j = new JObject();
    j.Add("zone", zone);
    j.Add("r", r);
    j.Add("g", g);
    j.Add("b", b);
    send_message("set_keyboard_color", j);
  }

  static void Main(string[] args) {
    ws = new WebSocket("ws://127.0.0.1:8000");
    ws.OnMessage += on_message;
    ws.OnError += (sender, e) => is_running = false;
    ws.OnClose += (sender, e) => is_running = false;
    ws.Connect();
    send_message("get_devices", 0);
    while (is_running) {
      if (sensors != null && monitor != null && monitor.is_on != 0) {
        monitor_effect();
      }
      send_message("get_sensors", 0);
      Thread.Sleep(1000);
    }
  }
}
