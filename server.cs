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
    } else if (message.tag == "get_hardware_data") {
      send_message("hardware_data", server.hardware_data);
    } else if (message.tag == "get_smart_data") {
      send_message("smart_data", server.smart_data);
    } else {
      server.fifo.Enqueue(message);
    }
  }

  public Service(Server s) {
    server = s;
  }
}

public class Server {
  CPUID cpuid;
  public Monitor_report hardware_data;
  public List<SMART_report> smart_data;
  Stopwatch monitor_timer;
  Stopwatch smart_timer;
  public dynamic client_data;
  WebSocketServer wssv { get; set; }
  public ConcurrentQueue<Message> fifo;

  void update_hardware_data() {
    if (monitor_timer.ElapsedMilliseconds > Program.settings.monitor_interval) {
      hardware_data = cpuid.get_monitor_report();
      monitor_timer.Restart();
    }
    if (smart_timer.ElapsedMilliseconds > (1000 * 60 * 60)) {
      smart_data = cpuid.get_smart_report();
      smart_timer.Restart();
    }
  }

  void run_plugins() {
    foreach (string file in Program.settings.plugins) {
      Program.log.add("plugin: " + file);
      Tools.run_process(file, "");
    }
  }

  void process_messages() {
    Message message;
    while (fifo.TryDequeue(out message)) {
      if (message.tag == "set_client_data") {
        client_data = message.data;
        File.WriteAllText("client_data.json", JsonConvert.SerializeObject(client_data));
      }
    }
  }

  public void run() {
    wssv.AddWebSocketService<Service>("/", () => new Service(this));
    wssv.Start();
    run_plugins();
    while (Program.is_running) {
      update_hardware_data();
      process_messages();
      Thread.Sleep(100);
    }
    wssv.Stop();
  }

  public Server() {
    Program.log.add("client_data.json: ");
    client_data = JsonConvert.DeserializeObject(File.ReadAllText("client_data.json"));
    Program.log.add("ok\n");
    cpuid = new CPUID();
    Program.log.add("CPUID: ");
    if (!cpuid.ok) {
      Application.Exit();
    }
    Program.log.add("ok\n");
    monitor_timer = Stopwatch.StartNew();
    smart_timer = Stopwatch.StartNew();
    hardware_data = cpuid.get_monitor_report();
    smart_data = cpuid.get_smart_report();
    fifo = new ConcurrentQueue<Message>();
    wssv = new WebSocketServer(Program.settings.port);
  }
}

}
