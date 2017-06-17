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
  public string keyboard { get; set; }
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
    Program.log.add_line("connection: " + Context.UserEndPoint);
  }

  protected override void OnMessage(MessageEventArgs e) {
    Message message;
    if (!e.IsText) {
      return;
    }
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
  public Dictionary<string, dynamic> sensors;
  public Dictionary<string, dynamic> devices;
  Stopwatch sensors_timer;
  Stopwatch devices_timer;
  public Hardware hw;
  WebSocketServer wssv { get; set; }
  public ConcurrentQueue<Message> fifo_in;
  public ConcurrentQueue<string> fifo_out;
  bool send_sensors_now = false;

  public string make_message(string tag, dynamic data) {
    var message = new Message();
    message.tag = tag;
    message.data = data;
    return JsonConvert.SerializeObject(message);
  }

  void update() {
    if (sensors_timer.ElapsedMilliseconds > Program.settings.sensors_interval) {
      sensors_timer.Restart();
      hw.update_sensors();
      send_sensors_now = true;
    }
    if (devices_timer.ElapsedMilliseconds > (1000 * 60 * Program.settings.devices_interval)) {
      devices_timer.Restart();
      hw.update_devices();
    }
  }

  void start_plugins() {
    foreach (string file in Program.settings.plugins) {
      Program.log.add_line("plugin: " + file);
      Tools.run_process(file, "");
    }
    while (wssv.WebSocketServices["/"].Sessions.Count < Program.settings.plugins.Count) {
      Thread.Sleep(10);
    }
  }

  public void send_plugin_message(string tag, dynamic data) {
    fifo_out.Enqueue(make_message(tag, data));
  }

  void send_sensors() {
    if (send_sensors_now) {
      sensors["time"] = DateTime.UtcNow;
      wssv.WebSocketServices["/"].Sessions.Broadcast(make_message("sensors", sensors));
      send_sensors_now = false;
    }
  }

  void process_messages() {
    Message msg_in;
    string msg_out;
    while (fifo_in.TryDequeue(out msg_in)) {
      hw.get_message(msg_in.tag, msg_in.data);
      send_sensors_now = true;
    }
    while (fifo_out.TryDequeue(out msg_out)) {
      wssv.WebSocketServices["/"].Sessions.Broadcast(msg_out);
    }
    send_sensors();
  }

  public void run() {
    wssv.AddWebSocketService<Service>("/", () => new Service(this));
    wssv.Start();
    start_plugins();
    while (Program.is_running) {    
      update();
      process_messages();
      Thread.Sleep(100);
    }
    wssv.Stop();
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
    hw = new Hardware(this);
    hw.update_devices();
    hw.update_sensors();
    sensors_timer = Stopwatch.StartNew();
    devices_timer = Stopwatch.StartNew();
    wssv = new WebSocketServer(Program.settings.port);
  }
}

}
