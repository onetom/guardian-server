using System;
using System.Windows.Forms;
using System.IO;
using System.Net;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public class SSE {
  string server_name = "GUARDIAN_SERVER";
  string event_name = "RGB_ZONE_";
  string address;
  System.Timers.Timer timer;

  class coreProps {
    public string address { get; set; }
  }

  void get_address() {
    string name = Environment.GetEnvironmentVariable("PROGRAMDATA");
    name += "/SteelSeries/SteelSeries Engine 3/coreProps.json";
    if (File.Exists(name)) {
      address = JsonConvert.DeserializeObject<coreProps>(File.ReadAllText(name)).address;
    } else {
      MessageBox.Show("SteelSeries Engine not found");
      Application.Exit();
    }
  }

  string http_post_raw(string command, string data) {
    string url = "http://" + address + command;
    try {
      var client = new WebClient();
      client.Headers.Add("Content-Type", "application/json"); 
      return client.UploadString(url, data);
    } catch (WebException ex) {
      return new StreamReader(ex.Response.GetResponseStream()).ReadToEnd();
    }
  }

  void http_post(string command, string data) {
    Console.WriteLine("command: " + command + "\n");
    Console.WriteLine("data: " + data + "\n");
    Console.WriteLine("SSE answer:");
    Console.WriteLine(http_post_raw(command, data));
  }

  void remove_game() {
    var j = new JObject();
    j.Add("game", server_name);
    http_post("/remove_game", j.ToString());
  }

  void register_game() {
    var j = new JObject();
    j.Add("game", server_name);
    j.Add("game_display_name", server_name);
    j.Add("icon_color_id", 0);
    http_post("/game_metadata", j.ToString());
  }

  JObject json_color(int r, int g, int b) {
    JObject j = new JObject();
    j.Add("red", r);
    j.Add("green", g);
    j.Add("blue", b);
    return j;
  }

  JObject json_gradient(int r, int g, int b, int r1, int g1, int b1) {
    JObject color = new JObject();
    JObject gradient = new JObject();
    gradient.Add("zero", json_color(r, g, b));
    gradient.Add("hundred", json_color(r1, g1, b1));
    color.Add("gradient", gradient);
    return color;
  }

  JObject json_range(int low, int high, JObject color) {
    JObject j = new JObject();
    j.Add("low", low);
    j.Add("high", high);
    j.Add("color", color);
    return j;
  }

  void bind_event(string name, string zone, dynamic color) {
    var j = new JObject();
    var handlers = new JArray();
    var handler = new JObject();
    j.Add("game", server_name);
    j.Add("event", name);
    j.Add("min_value", 0);
    j.Add("max_value", 511);
    j.Add("icon_id", 0);
    handler.Add("device-type", "rgb-3-zone");
    handler.Add("zone", zone);
    handler.Add("mode", "color");
    handler.Add("color", color);
    handlers.Add(handler);
    j.Add("handlers", handlers);  
    http_post("/bind_game_event", j.ToString());
  }

  public void set_rgb_zone(int i, string zone) {
    var j = new JArray();
    int index = 0;
    for (int b = 0; b < 8; b += 1) {
      for (int g = 0; g < 8; g += 1) {
        for (int r = 0; r < 8; r += 1) {
          j.Add(json_range(index, index, json_color(r << 5, g << 5, b << 5)));
          index += 1;
        }
      }
    }
    bind_event(event_name + i, zone, j);
  }

  public void send_event(string name, int value) {
    var j = new JObject();
    var data = new JObject();
    j.Add("game", server_name);
    j.Add("event", name);
    data.Add("value", value);
    j.Add("data", data);
    http_post("/game_event", j.ToString());
  }

  public void set_zone_color(int zone, int r, int g, int b) {
    zone = Math.Min(zone, 2);
    r >>= 5;
    g >>= 5;
    b >>= 5;
    send_event(event_name + zone, r | (g << 3) | (b << 6));
  }

  public void send_ping() {
    var j = new JObject();
    j.Add("game", server_name);
    http_post("/game_heartbeat", j.ToString());
  }

  public void timer_event(Object source, System.Timers.ElapsedEventArgs e) {
    send_ping();
  }

  public void set_timer() {
    timer = new System.Timers.Timer();
    timer.Interval = 10000;
    timer.Elapsed += timer_event;
    timer.AutoReset = true;
    timer.Enabled = true;
  }

  public SSE() {
    get_address();
    remove_game();
    register_game();
    set_rgb_zone(0, "one");
    set_rgb_zone(1, "two");
    set_rgb_zone(2, "three");
    set_timer();
  }
}
