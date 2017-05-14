using System;
using System.IO;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace guardian_server {

public class DS_Board {
  Hardware hw;
  Dictionary<string, dynamic> state = null;

  public void update_sensors() {
    hw.server.sensors["fans"] = state["fans"];
    hw.server.sensors["strips"] = state["strips"];
    hw.server.sensors["uv_strips"] = state["uv_strips"];
  }

  public Dictionary<string, dynamic> save() {
    return state;
  }

  public void set_default_state() {
    int i;
    state = new Dictionary<string, dynamic>();
    state["fans"] = new List<Dictionary<string, dynamic>>();
    state["strips"] = new List<Dictionary<string, dynamic>>();
    state["uv_strips"] = new List<Dictionary<string, dynamic>>();
    for (i = 0; i < 7; i += 1) {
      var fan = new Dictionary<string, dynamic>();
      fan["name"] = "Fan " + (i + 1);
      fan["effect"] = "none";
      fan["color"] = new List<int> { 0, 0, 0 };
      fan["beg_color"] = new List<int> { 0, 0, 0 };
      fan["end_color"] = new List<int> { 0, 0, 0 };
      fan["pwm"] = 0;
      fan["tach"] = 0;
      fan["auto"] = 0;
      state["fans"].Add(fan);
    }
    for (i = 0; i < 4; i += 1) {
      var strip = new Dictionary<string, dynamic>();
      strip["name"] = "Strip " + (i + 1);
      strip["effect"] = "none";
      strip["color"] = new List<int> { 0, 0, 0 };
      strip["beg_color"] = new List<int> { 0, 0, 0 };
      strip["end_color"] = new List<int> { 0, 0, 0 };
      state["strips"].Add(strip);
    }
    for (i = 0; i < 2; i += 1) {
      var uv = new Dictionary<string, dynamic>();
      uv["name"] = "UV Strip " + (i + 1);
      uv["effect"] = "none";
      uv["color"] = new List<int> { 0, 0, 0 };
      uv["beg_color"] = new List<int> { 0, 0, 0 };
      uv["end_color"] = new List<int> { 0, 0, 0 };
      state["uv_strips"].Add(uv);
    }
  }

  void update_obj(dynamic from, dynamic to) {
    foreach (JProperty x in from) {
      to[x.Name] = x.Value;
    }
  }

  public void update_fan(dynamic fan) {
    int i;
    for (i = 0; i < state["fans"].Count; i += 1) {
      if (fan.name == state["fans"][i].name) {
        update_obj(fan, state["fans"][i]);
      }
    }
  }

  public void update_strip(dynamic strip) {
    int i;
    for (i = 0; i < state["strips"].Count; i += 1) {
      if (strip.name == state["strips"][i].name) {
        update_obj(strip, state["strips"][i]);
      }
    }
  }

  public void update_uv_strip(dynamic uv_strip) {
    int i;
    for (i = 0; i < state["uv_strips"].Count; i += 1) {
      if (uv_strip.name == state["uv_strips"][i].name) {
        update_obj(uv_strip, state["uv_strips"][i]);
      }
    }
  }

  public DS_Board(Hardware h) {
    Program.log.add("DS_Board: ");
    hw = h;
    set_default_state();
    if (hw.state["ds_board"] != null) {
      update_obj(hw.state["ds_board"], state);
    }
    Program.log.add_line("ok");
  }
}

}
