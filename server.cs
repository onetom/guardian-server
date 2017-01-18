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
    send_message("client_data", server.client_data);
    Program.log.add("connection: " + Context.UserEndPoint + "\n");
  }

  protected override void OnMessage(MessageEventArgs e) {
    var message = JsonConvert.DeserializeObject<Message>(e.Data);
    if (message.tag == "get_client_data") {
      send_message("client_data", server.client_data);
    } else if (message.tag == "get_monitor_data") {
      send_message("monitor_data", server.monitor_data);
    } else if (message.tag == "get_smart_data") {
      send_message("smart_data", server.smart_data);
    } else if (message.tag == "get_info_data") {
      send_message("info_data", server.info_data);
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
  public Info_report info_data;
  public List<SMART_report> smart_data;
  public Monitor_report monitor_data;
  Stopwatch monitor_timer;
  Stopwatch info_timer;
  public dynamic client_data;
  public Hardware hw;
  WebSocketServer wssv { get; set; }
  public ConcurrentQueue<Message> fifo;

  void update_sensors() {
    if (monitor_timer.ElapsedMilliseconds > Program.settings.monitor_interval) {
      monitor_data = cpuid.get_monitor_report();
      monitor_timer.Restart();
    }
    if (info_timer.ElapsedMilliseconds > (1000 * 60 * Program.settings.info_interval)) {
      smart_data = cpuid.get_smart_report();
      info_data = get_info_data();
      info_timer.Restart();
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
      if (message.tag == "set_client_data") {
        client_data = message.data;
        File.WriteAllText("client_data.json", JsonConvert.SerializeObject(client_data));
      } else if (message.tag == "set_keyboard_color" && Program.settings.keyboard != "none") {
        hw.set_keyboard_color(message.data);
      }
    }
  }

  public void run() {
    wssv.AddWebSocketService<Service>("/", () => new Service(this));
    wssv.Start();
    run_plugins();
    while (Program.is_running) {
      update_sensors();
      process_messages();
      Thread.Sleep(100);
    }
    wssv.Stop();
  }

  private void on_exit(object sender, EventArgs e) {
    hw.save_state();
  }

  Info_report get_info_data() {
    var info = cpuid.get_info_report();
    info.other = hw.state;
    return info;
  }

  public Server() {
    Program.log.add("client_data.json: ");
    client_data = JsonConvert.DeserializeObject(File.ReadAllText("client_data.json"));
    Program.log.add("ok\n");
    hw = new Hardware();
    cpuid = new CPUID();
    Program.log.add("CPUID: ");
    if (!cpuid.ok) {
      Application.Exit();
    }
    Program.log.add("ok\n");
    Application.ApplicationExit += new EventHandler(this.on_exit);
    monitor_data = cpuid.get_monitor_report();
    smart_data = cpuid.get_smart_report();
    info_data = get_info_data();
    monitor_timer = Stopwatch.StartNew();
    info_timer = Stopwatch.StartNew();
    fifo = new ConcurrentQueue<Message>();
    wssv = new WebSocketServer(Program.settings.port);
  }
}

}
