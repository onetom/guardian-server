﻿using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace guardian_server {

class Settings {
  public string server_name { get; set; }
  public string browser_path { get; set; }
  public string ui_path { get; set; }
  public List<string> plugins { get; set; }
  public int port { get; set; }
  public int monitor_interval { get; set; }
}

class Program {
  public static bool is_running;
  public static Logger log;
  public static Settings settings;
  static NotifyIcon ni;
  static Server server;

  static void add_to_tray() {
    ContextMenuStrip CMS = new ContextMenuStrip();
    CMS.Items.Add("Exit", null, exit_click);
    ni = new NotifyIcon();
    ni.ContextMenuStrip = CMS;
    ni.DoubleClick += new System.EventHandler(ui_click);
    ni.Icon = new Icon("tray_icon.ico");
    ni.Visible = true;
    ni.Text = settings.server_name;
  }

  static void ui_click(object sender, EventArgs e) {
    string path = Tools.get_program_path() + "/";
    Tools.run_process(path + settings.browser_path, path + settings.ui_path);
  }

  static void exit_click(object sender, EventArgs e) {
    is_running = false;
    Application.Exit();
  }

  static void Main(string[] args) {
    is_running = true;
    log = new Logger("log.txt");
    log.add("server started\n");
    log.add("is_only_instance: ");
    if (!Tools.is_only_instance()) {
      MessageBox.Show("An instance of the server is already running");
      return;
    }
    log.add("ok\n");
    log.add("settings.json: ");
    settings = JsonConvert.DeserializeObject<Settings>(File.ReadAllText("settings.json"));
    Console.WriteLine(settings.port);
    log.add("ok\n");
    log.add("add_to_tray: ");
    add_to_tray();
    log.add("ok\n");
    server = new Server();
    Task task = Task.Factory.StartNew(() => {
      server.run();
    });
    Application.Run();
    log.add("server stopped");
  }
}

}
