using System;
using System.IO;
using System.Diagnostics;

public class Logger {
  public string log_file;

  public void add(string line) {
    File.AppendAllText(log_file, line);
  }

  public Logger(string file) {
    log_file = file;
    File.WriteAllText(log_file, "");
  }
}

public static class Tools {
  public static bool is_only_instance() {
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
