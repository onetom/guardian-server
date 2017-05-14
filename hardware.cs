using System;
using System.IO;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace guardian_server {

public class Hardware {
  public Server server;
  public Dictionary<string, dynamic> state;
  public Monitor mon;
  public Keyboard kb;
  public DS_Board ds;

  public void save() {
    state["led_keyboard"] = kb.save();
    state["ds_board"] = ds.save();
    File.WriteAllText("hardware.json", JsonConvert.SerializeObject(state));
  }

  public void update_sensors() {
    mon.update_sensors();
    kb.update_sensors();
    ds.update_sensors();
  }

  public void update_devices() {
    mon.update_devices();
    kb.update_devices();
  }

  public void get_message(string tag, dynamic data) {
    Console.WriteLine(String.Format("tag: {0}\ndata: {1}\n", tag, Newtonsoft.Json.JsonConvert.SerializeObject(data)));
    if (tag == "set_keyboard_zones") {
      kb.set_keyboard_zones(data);
    } else if (tag == "fans") {
      ds.update_fan(data);
    } else if (tag == "strips") {
      ds.update_strip(data);
    } else if (tag == "uv_strips") {
      ds.update_uv_strip(data);
    }
  }

  public Hardware(Server s) {
    server = s;
    state = new Dictionary<string, dynamic>();
    Program.log.add("hardware.json: ");
    state = JsonConvert.DeserializeObject<Dictionary<string, dynamic>>(File.ReadAllText("hardware.json"));
    Program.log.add_line("ok");
    mon = new Monitor(this);
    kb = new Keyboard(this);
    ds = new DS_Board(this);
  }
}

}
