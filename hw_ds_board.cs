using System;
using System.IO;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace guardian_server {

public class DS_Board {
  Hardware hw;
  Dictionary<string, dynamic> state;

  public void update_sensors() {
    hw.server.sensors["fans"] = state["fans"];
    hw.server.sensors["strips"] = state["strips"];
    hw.server.sensors["uv_strips"] = state["uv_strips"];
  }

  public Dictionary<string, dynamic> save() {
    return state;
  }

  public List<double?> default_color() {
    return new List<double?> { 0, 1, 0.5 };
  }

  public List<double?> default_beg_color() {
    return new List<double?> { 240, 1, 0.5 };
  }

  public List<double?> default_end_color() {
    return new List<double?> { 0, 1, 0.5 };
  }

  public dynamic as_fan_color(dynamic color) {
    color[1] = null;
    color[2] = null;
    return color;
  }

  public dynamic as_uv_color(dynamic color) {
    color[0] = null;
    color[2] = null;
    return color;
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
      fan["color"] = as_fan_color(default_color());
      fan["beg_color"] = as_fan_color(default_beg_color());
      fan["end_color"] = as_fan_color(default_end_color());
      fan["pwm"] = 0;
      fan["rpm"] = 0;
      fan["auto"] = 0;
      fan["temp"] = 40;
      state["fans"].Add(fan);
    }
    for (i = 0; i < 4; i += 1) {
      var strip = new Dictionary<string, dynamic>();
      strip["name"] = "Strip " + (i + 1);
      strip["effect"] = "none";
      strip["color"] = default_color();
      strip["beg_color"] = default_beg_color();
      strip["end_color"] = default_end_color();
      state["strips"].Add(strip);
    }
    for (i = 0; i < 2; i += 1) {
      var uv = new Dictionary<string, dynamic>();
      uv["name"] = "UV Strip " + (i + 1);
      uv["effect"] = "none";
      uv["color"] = as_uv_color(default_color());
      uv["beg_color"] = as_uv_color(default_beg_color());
      uv["end_color"] = as_uv_color(default_end_color());
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
      var x = state["fans"][i];
      if (fan["name"] == x["name"]) {
        update_obj(fan, x);
        as_fan_color(x["color"]);
        as_fan_color(x["beg_color"]);
        as_fan_color(x["end_color"]);
      }
    }
  }

  public void update_strip(dynamic strip) {
    int i;
    for (i = 0; i < state["strips"].Count; i += 1) {
      var x = state["strips"][i];
      if (strip["name"] == x["name"]) {
        update_obj(strip, x);
      }
    }
  }

  public void update_uv_strip(dynamic uv_strip) {
    int i;
    for (i = 0; i < state["uv_strips"].Count; i += 1) {
      var x = state["uv_strips"][i];
      if (uv_strip["name"] == x["name"]) {
        update_obj(uv_strip, x);
        as_uv_color(x["color"]);
        as_uv_color(x["beg_color"]);
        as_uv_color(x["end_color"]);
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
