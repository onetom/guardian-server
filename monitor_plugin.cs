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

class Program {
  static bool is_running = true;
  static WebSocket ws;
  static public Dictionary<string, dynamic> sensors;
  static public Dictionary<string, dynamic> devices;
  static RGB start_color;
  static RGB stop_color;
  static float start_temp;
  static float stop_temp;
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
    }
  }

  static void Main(string[] args) {
    ws = new WebSocket("ws://127.0.0.1:8000");
    ws.OnMessage += on_message;
    ws.OnError += (sender, e) => is_running = false;
    ws.OnClose += (sender, e) => is_running = false;
    ws.Connect();
    send_message("get_devices", 0);
    start_color = new RGB { r = 0, g = 255, b = 0 };
    stop_color = new RGB { r = 255, g = 0, b = 0 };
    start_temp = 40;
    stop_temp = 60;
    zone = 0;
    while (is_running) {
      if (sensors != null) {
        float temp = sensors["cpus"][0]["temps"]["Package"];
        temp = Tools.clamp(temp, start_temp, stop_temp);
        temp = Tools.remap(temp, start_temp, stop_temp, 0, 1);
        int r = (int) Tools.lerp(start_color.r, stop_color.r, temp);
        int g = (int) Tools.lerp(start_color.g, stop_color.g, temp);
        int b = (int) Tools.lerp(start_color.b, stop_color.b, temp);
        var j = new JObject();
        j.Add("zone", zone);
        j.Add("r", r);
        j.Add("g", g);
        j.Add("b", b);
        send_message("set_keyboard_color", j);
      }
      send_message("get_sensors", 0);
      Thread.Sleep(1000);
    }
  }
}
