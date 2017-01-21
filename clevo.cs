using Microsoft.Win32;
using System;
using System.Windows.Forms;
using System.Diagnostics;
using System.ServiceProcess;
using System.Threading;

public class Clevo
{
  private EventLog eventLog1 = new EventLog();
  private EventLog outlog = new EventLog();
  private ServiceController serviceController1 = new ServiceController();
  private bool bIsNew = true;
  private bool bEnableSave;

  public Clevo()
  {
    this.serviceController1.ServiceName = "PowerBiosServer";
    this.eventLog1.Source = "PowerBiosServerSource";
    this.eventLog1.Log = "PowerBiosServerLog";
    this.outlog.Source = "PowerBIOSServer_Out";
    this.outlog.Log = "OutLog";
    if (this.serviceController1.Status != ServiceControllerStatus.Running || !EventLog.Exists(this.eventLog1.Log)) {
      MessageBox.Show("CLEVO HotKey driver not found");
      Application.Exit();
    }
    this.bEnableSave = true;
  }

  public void set_zone_color(int zone, int r, int g, int b) {
    zone = (int) Tools.clamp(zone, 0, 3);
    SetColor(r, g, b, zone + 1);
  }

  public void SetColor(int _iR, int _iG, int _iB, int iKbPart)
  {
    if (!this.bEnableSave)
      return;
    long data = (long) ((_iB << 16) + _iG + (_iR << 8));
    if (iKbPart == 1)
      data |= 4026531840L;
    else if (iKbPart == 2)
      data |= 4043309056L;
    else if (iKbPart == 3)
      data |= 4060086272L;
    else if (iKbPart == 4)
      data |= 4076863488L;
    if (this.bIsNew)
    {
      this.SetWmi(103, data);
      if (iKbPart == 4 && _iR == 0 && (_iG == 0 && _iB == 0))
      {
        this.SetLEDKBOnOff(true);
      }
      else
      {
        if (iKbPart != 4 || (_iR == 0 || _iG == 0) && _iB == 0)
          return;
        this.SetLEDKBOnOff(false);
      }
    }
    else
    {
      this.eventLog1.WriteEntry(Convert.ToString(data));
      Thread.Sleep(50);
      this.serviceController1.ExecuteCommand(231);
      Thread.Sleep(100);
    }
  }

  public void SetLEDKBOn()
  {
    int num1 = 1;
    int num2 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "LedVolStatus", (object) "1"));
    int num3 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "KbLeftStatus", (object) "1"));
    int num4 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "KbMidStatus", (object) "1"));
    int num5 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "KbRightStatus", (object) "1"));
    int num6 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "KbTpStatus", (object) "1"));
    uint num7 = 3758096384;
    uint num8 = 7;
    uint num9 = 0;
    uint num10 = 0;
    uint num11 = 0;
    uint num12 = 1;
    uint num13 = 1;
    if (num1 == 1)
      num7 = (uint) (((int) num7 | (int) num10 | (int) num11 | (int) num8 | (int) num9) + ((int) num12 << 12) + ((int) num13 << 13) + (num2 << 14) + (num6 << 15) + (num3 << 16) + (num4 << 17) + (num5 << 18));
    this.SetWmi(103, (long) num7);
  }

  public void SetLEDKBOnOff(bool bIsBlack)
  {
    int num1 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "KbTpStatus", (object) "1"));
    if (num1 == 0 && !bIsBlack)
      return;
    uint num2 = 3758096384;
    uint num3 = 1;
    uint num4 = 0;
    uint num5 = 0;
    uint num6 = 0;
    uint num7 = 1;
    uint num8 = 1;
    int num9 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "LEDKB_Status", (object) "1"));
    int num10 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "LedVolStatus", (object) "1"));
    int num11 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "KbLeftStatus", (object) "1"));
    int num12 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "KbMidStatus", (object) "1"));
    int num13 = (int) Convert.ToInt16(Registry.GetValue("HKEY_CURRENT_USER\\Software\\hotkey\\LEDKB", "KbRightStatus", (object) "1"));
    if (bIsBlack)
      num3 = 7U;
    uint num14;
    if (num9 == 1)
    {
      uint num15 = 0;
      uint num16 = 0;
      num14 = (uint) (((int) num2 | (int) num15 | (int) num16 | (int) num3 | (int) num4) + ((int) num7 << 12) + ((int) num8 << 13) + (num10 << 14) + (num1 << 15) + (num11 << 16) + (num12 << 17) + (num13 << 18));
    }
    else
      num14 = (uint) (((int) num2 | (int) num5 | (int) num6 | (int) num3 | (int) num4) + ((int) num7 << 12) + ((int) num8 << 13));
    this.SetWmi(103, (long) num14);
  }

  public void DisKbMode(int mode)
  {
    if (!this.bEnableSave || mode == 9)
      return;
    if (this.bIsNew)
    {
      this.SetWmi(103, 268435456L);
    }
    else
    {
      this.eventLog1.WriteEntry(Convert.ToString(268435456));
      Thread.Sleep(50);
      this.serviceController1.ExecuteCommand(231);
      Thread.Sleep(100);
    }
  }

  public void SetKbMode(int mode)
  {
    if (!this.bEnableSave)
      return;
    switch (mode)
    {
      case 0:
        if (this.bIsNew)
        {
          this.SetWmi(103, 1879048192L);
          break;
        }
        this.eventLog1.WriteEntry(Convert.ToString(1879048192));
        Thread.Sleep(100);
        this.serviceController1.ExecuteCommand(231);
        break;
      case 2:
        int num1 = 0 | 40960 | (2 << 16 | 268435456);
        if (this.bIsNew)
        {
          this.SetWmi(103, (long) num1);
          break;
        }
        this.eventLog1.WriteEntry(Convert.ToString(num1));
        Thread.Sleep(100);
        this.serviceController1.ExecuteCommand(231);
        break;
      case 3:
        int num2 = 1 << 16 | 3 << 24 | 805306368;
        if (this.bIsNew)
        {
          this.SetWmi(103, (long) num2);
          break;
        }
        this.eventLog1.WriteEntry(Convert.ToString(num2));
        Thread.Sleep(100);
        this.serviceController1.ExecuteCommand(231);
        break;
      case 4:
        if (this.bIsNew)
        {
          this.SetWmi(103, 2952790016L);
          break;
        }
        this.eventLog1.WriteEntry(Convert.ToString(2952790016U));
        Thread.Sleep(100);
        this.serviceController1.ExecuteCommand(231);
        break;
      case 5:
        if (this.bIsNew)
        {
          this.SetWmi(103, 2147483648L);
          break;
        }
        this.eventLog1.WriteEntry(Convert.ToString(2147483648U));
        Thread.Sleep(100);
        this.serviceController1.ExecuteCommand(231);
        break;
      case 6:
        if (this.bIsNew)
        {
          this.SetWmi(103, 2415919104L);
          break;
        }
        this.eventLog1.WriteEntry(Convert.ToString(2415919104U));
        Thread.Sleep(100);
        this.serviceController1.ExecuteCommand(231);
        break;
      case 7:
        if (this.bIsNew)
        {
          this.SetWmi(103, 2684354560L);
          break;
        }
        this.eventLog1.WriteEntry(Convert.ToString(2684354560U));
        Thread.Sleep(100);
        this.serviceController1.ExecuteCommand(231);
        break;
    }
  }

  public void SetColorAll(long _iR, long _iG, long _iB)
  {
    if (!this.bEnableSave)
      return;
    long data1 = (long) ((_iB << 16) + _iG + (_iR << 8)) | 4026531840L;
    if (this.bIsNew)
    {
      this.SetWmi(103, data1);
    }
    else
    {
      this.eventLog1.WriteEntry(Convert.ToString(data1));
      Thread.Sleep(50);
      this.serviceController1.ExecuteCommand(231);
      Thread.Sleep(100);
    }
    long data2 = (long) ((_iB << 16) + _iG + (_iR << 8)) | 4043309056L;
    if (this.bIsNew)
    {
      this.SetWmi(103, data2);
    }
    else
    {
      this.eventLog1.WriteEntry(Convert.ToString(data2));
      Thread.Sleep(50);
      this.serviceController1.ExecuteCommand(231);
      Thread.Sleep(100);
    }
    long data3 = (long) ((_iB << 16) + _iG + (_iR << 8)) | 4060086272L;
    if (this.bIsNew)
    {
      this.SetWmi(103, data3);
    }
    else
    {
      this.eventLog1.WriteEntry(Convert.ToString(data3));
      Thread.Sleep(50);
      this.serviceController1.ExecuteCommand(231);
      Thread.Sleep(100);
    }
  }

  public void SetKbBrightness(int index)
  {
    long num;
    switch (index)
    {
      case 0:
        num = 63;
        break;
      case 1:
        num = 126;
        break;
      case 2:
        num = 189;
        break;
      case 3:
        num = 252;
        break;
      default:
        num = 1;
        break;
    }
    long data = (long) num | 4093640704L;
    if (this.bIsNew)
    {
      this.SetWmi(103, data);
    }
    else
    {
      this.eventLog1.WriteEntry(Convert.ToString(data));
      Thread.Sleep(50);
      this.serviceController1.ExecuteCommand(231);
      Thread.Sleep(100);
    }
  }

  public bool SetWmi(int arg, long data)
  {
    try
    {
      this.eventLog1.WriteEntry(("w_arg" + arg.ToString() + "^" + data.ToString()).ToLower());
      Thread.Sleep(100);
      return true;
    }
    catch
    {
      return false;
    }
  }

  public bool Notice_KbClose()
  {
    try
    {
      this.outlog.WriteEntry("Arg888^0");
      Thread.Sleep(100);
      return true;
    }
    catch
    {
      return false;
    }
  }

  public bool Notice_KbLedChange()
  {
    try
    {
      this.outlog.WriteEntry("Arg888^103");
      Thread.Sleep(100);
      return true;
    }
    catch
    {
      return false;
    }
  }

  private enum KbPart
  {
    all,
    left,
    mid,
    right,
    touchpad,
    none,
  }
}
