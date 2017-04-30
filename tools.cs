using System;
using System.IO;
using System.Diagnostics;

public class Logger {
  public string log_file;

  public void add(string text) {
    File.AppendAllText(log_file, text);
  }

  public void add_line(string line) {
    File.AppendAllText(log_file, line + "\r\n");
  }

  public Logger(string file) {
    log_file = file;
    File.WriteAllText(log_file, "");
  }
}

public static class Tools {
  public static float lerp(float v0, float v1, float t) {
    return (1 - t) * v0 + t * v1;
  }

  public static float clamp(float x, float x_min, float x_max) {
    if (x < x_min) {
      return x_min;
    }
    if (x > x_max) {
      return x_max;
    }
    return x;
  }

  public static float remap(float x, float x_min, float x_max, float y_min, float y_max) {
    x = clamp(x, x_min, x_max);
    return y_min + (y_max - y_min) * ((x - x_min) / (x_max - x_min));
  }

  public static bool one_instance() {
    return Process.GetProcessesByName(
      Path.GetFileNameWithoutExtension(System.Reflection.Assembly.GetEntryAssembly().Location)
    ).Length == 1;
  }

  public static string get_program_path() {
    return Path.GetDirectoryName(Process.GetCurrentProcess().MainModule.FileName);
  }

  public static void run_process(string name, string args) {
    ProcessStartInfo startInfo = new ProcessStartInfo();        
    startInfo.FileName = name;
    startInfo.Arguments = args;
    Process.Start(startInfo);
  }
}
