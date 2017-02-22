using System;
using System.IO;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using WebSocketSharp;
using WebSocketSharp.Server;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace guardian_server {

class Settings {
  public string server_name { get; set; }
  public string browser_path { get; set; }
  public string ui_path { get; set; }
  public List<string> plugins { get; set; }
  public int port { get; set; }
  public int sensors_interval { get; set; }
  public int devices_interval { get; set; }
  public string led_keyboard { get; set; }
}

public class Message {
  public string tag { get; set; }
  public dynamic data { get; set; }
}

public class Service : WebSocketBehavior {
  Server server;

  void send_message(string tag, dynamic data) {
    Send(server.make_message(tag, data));
  }

  protected override void OnOpen() {
    Program.log.add("connection: " + Context.UserEndPoint + "\n");
  }

  protected override void OnMessage(MessageEventArgs e) {
    Message message;
    if (!e.IsText) {
      return;
    }
    Program.log.add(e.Data + "\n");
    try {
      message = JsonConvert.DeserializeObject<Message>(e.Data);
    } catch {
      return;
    }
    if (message.tag == "get_devices") {
      send_message("devices", server.devices);
    } else if (server.fifo_in.Count < 1024) {
      server.fifo_in.Enqueue(message);
    }
  }

  public Service(Server s) {
    server = s;
  }
}

public class Server {
  CPUID cpuid;
  public Dictionary<string, dynamic> sensors;
  public Dictionary<string, dynamic> devices;
  Stopwatch sensors_timer;
  Stopwatch devices_timer;
  public Hardware hw;
  WebSocketServer wssv { get; set; }
  public ConcurrentQueue<Message> fifo_in;
  public ConcurrentQueue<string> fifo_out;

  public string make_message(string tag, dynamic data) {
    var message = new Message();
    message.tag = tag;
    message.data = data;
    return JsonConvert.SerializeObject(message);
  }

  void update() {
    if (sensors_timer.ElapsedMilliseconds > Program.settings.sensors_interval) {
      sensors_timer.Restart();
      update_sensors();
      wssv.WebSocketServices["/"].Sessions.Broadcast(make_message("sensors", sensors));
    }
    if (devices_timer.ElapsedMilliseconds > (1000 * 60 * Program.settings.devices_interval)) {
      devices_timer.Restart();
      update_devices();
    }
  }

  void start_plugins() {
    foreach (string file in Program.settings.plugins) {
      Program.log.add("plugin: " + file + "\n");
      Tools.run_process(file, "");
    }
    while (wssv.WebSocketServices["/"].Sessions.Count < Program.settings.plugins.Count) {
      Thread.Sleep(10);
    }
  }

  public void send_plugin_message(string tag, dynamic data) {
    fifo_out.Enqueue(make_message(tag, data));
  }

  void process_messages() {
    Message msg_in;
    string msg_out;
    while (fifo_in.TryDequeue(out msg_in)) {
      if (msg_in.tag == "set_keyboard_zones") {
        hw.led_keyboard.set_keyboard_zones(msg_in.data);
      }
    }
    while (fifo_out.TryDequeue(out msg_out)) {
      wssv.WebSocketServices["/"].Sessions.Broadcast(msg_out);
    }
  }

  public void run() {
    wssv.AddWebSocketService<Service>("/", () => new Service(this));
    wssv.Start();
    start_plugins();
    while (Program.is_running) {
      update();
      process_messages();
      Thread.Sleep(10);
    }
    wssv.Stop();
  }

  void update_sensors() {
    cpuid.update_sensors(devices, sensors);
    hw.update_sensors(sensors);
  }

  void update_devices() {
    cpuid.update_devices(devices);
    hw.update_devices(devices);
  }

  void on_exit(object sender, EventArgs e) {
    hw.save();
  }

  public Server() {
    Application.ApplicationExit += new EventHandler(this.on_exit);
    fifo_in = new ConcurrentQueue<Message>();
    fifo_out = new ConcurrentQueue<string>();
    sensors = new Dictionary<string, dynamic>();
    devices = new Dictionary<string, dynamic>();
    Program.log.add("CPUID: ");
    cpuid = new CPUID();
    if (!cpuid.ok) {
      Application.Exit();
    }
    Program.log.add("ok\n");
    hw = new Hardware(this);
    update_devices();
    update_sensors();
    sensors_timer = Stopwatch.StartNew();
    devices_timer = Stopwatch.StartNew();
    wssv = new WebSocketServer(Program.settings.port);
  }
}

}
