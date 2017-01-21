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
    var message = new Message();
    message.tag = tag;
    message.data = data;
    Send(JsonConvert.SerializeObject(message));
  }

  protected override void OnOpen() {
    Program.log.add("connection: " + Context.UserEndPoint + "\n");
  }

  protected override void OnMessage(MessageEventArgs e) {
    var message = JsonConvert.DeserializeObject<Message>(e.Data);
    if (message.tag == "get_sensors") {
      send_message("sensors", server.sensors);
    } else if (message.tag == "get_devices") {
      send_message("devices", server.devices);
    } else if (message.tag == "set_plugin_effect") {
      Sessions.Broadcast(e.Data);
      server.hw.set_plugin_effect(message.data);
    } else if (server.fifo.Count < 1024) {
      server.fifo.Enqueue(message);
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
  public ConcurrentQueue<Message> fifo;

  void update() {
    if (sensors_timer.ElapsedMilliseconds > Program.settings.sensors_interval) {
      update_sensors();
      sensors_timer.Restart();
    }
    if (devices_timer.ElapsedMilliseconds > (1000 * 60 * Program.settings.devices_interval)) {
      update_devices();
      devices_timer.Restart();
    }
  }

  void run_plugins() {
    foreach (string file in Program.settings.plugins) {
      Program.log.add("plugin: " + file + "\n");
      Tools.run_process(file, "");
    }
  }

  void process_messages() {
    Message message;
    while (fifo.TryDequeue(out message)) {
      if (message.tag == "set_keyboard_color" && Program.settings.led_keyboard != "none") {
        hw.set_keyboard_color(message.data);
      }
    }
  }

  public void run() {
    wssv.AddWebSocketService<Service>("/", () => new Service(this));
    wssv.Start();
    run_plugins();
    while (Program.is_running) {
      update();
      process_messages();
      Thread.Sleep(100);
    }
    wssv.Stop();
  }

  private void on_exit(object sender, EventArgs e) {
    hw.save();
  }

  void update_sensors() {
    cpuid.update_sensors(sensors);
  }

  void update_devices() {
    cpuid.update_devices(devices);
    hw.update(devices);
  }

  public Server() {
    Application.ApplicationExit += new EventHandler(this.on_exit);
    sensors = new Dictionary<string, dynamic>();
    devices = new Dictionary<string, dynamic>();
    Program.log.add("CPUID: ");
    cpuid = new CPUID();
    if (!cpuid.ok) {
      Application.Exit();
    }
    Program.log.add("ok\n");
    hw = new Hardware();
    update_sensors();
    update_devices();
    sensors_timer = Stopwatch.StartNew();
    devices_timer = Stopwatch.StartNew();
    fifo = new ConcurrentQueue<Message>();
    wssv = new WebSocketServer(Program.settings.port);
  }
}

}
