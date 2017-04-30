using System;
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
    string path = Tools.get_program_path();
    string browser_path = "\"" + path + "\\" + settings.browser_path + "\"";
    string ui_path = "\"" + path + "\\" + settings.ui_path + "\"";
    Tools.run_process(browser_path, ui_path);
  }

  static void exit_click(object sender, EventArgs e) {
    is_running = false;
    Application.Exit();
  }

  static void Main(string[] args) {
    is_running = true;
    Directory.SetCurrentDirectory(Tools.get_program_path());
    log = new Logger("log.txt");
    log.add("one_instance: ");
    if (!Tools.one_instance()) {
      MessageBox.Show("An instance of the server is already running");
      return;
    }
    log.add_line("ok");
    log.add("settings.json: ");
    settings = JsonConvert.DeserializeObject<Settings>(File.ReadAllText("settings.json"));
    log.add_line("ok");
    log.add("add_to_tray: ");
    add_to_tray();
    log.add_line("ok");
    server = new Server();
    Task task = Task.Factory.StartNew(() => {
      server.run();
    });
    Application.Run();
    log.add("server stopped");
  }
}

}
