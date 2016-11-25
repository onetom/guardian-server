using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace HWMonitor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            System.Windows.Forms.ListViewItem ItemListView;
            string s;
            float fValue;
            int dummy = 0;

            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_VCORE, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                ItemListView = ListView4.Items.Add("VCORE");
                ItemListView.SubItems.Add(s);
            }
            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_DRAM, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                ItemListView = ListView4.Items.Add("DRAM Voltage");
                ItemListView.SubItems.Add(s);
            }

            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_3V3, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                ItemListView = ListView4.Items.Add("ATX +3.3V");
                ItemListView.SubItems.Add(s);
            }

            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_P5V, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                ItemListView = ListView4.Items.Add("ATX +5V");
                ItemListView.SubItems.Add(s);
            }

            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_P12V, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                ItemListView = ListView4.Items.Add("ATX +12V");
                ItemListView.SubItems.Add(s);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            System.Windows.Forms.ListViewItem ItemListView;
            string devicename = "";
            string sensorname = "";
            string s = "";            
            float fValue, fMinValue, fMaxValue;
            int NbSensors, NbDevices, device_index, sensor_index, sensor_id, iValue, dummy;
            int index, index1, index2, index3, index4, index5, index6;
            bool result;
 
            dummy = 0;
            iValue = 0;
            fMinValue = 0.0f;
            fMaxValue = 0.0f;
            index = 0;
            sensor_id = 0;

            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_VCORE, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                if (ListView4.Items.Count > index)
                {
                    ItemListView = ListView4.Items[index];
                    ItemListView.SubItems[1].Text = s;
                    index++;
                }
            }
            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_DRAM, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                if (ListView4.Items.Count > index)
                {
                    ItemListView = ListView4.Items[index];
                    ItemListView.SubItems[1].Text = s;
                    index++;
                }
            }
            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_3V3, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                if (ListView4.Items.Count > index)
                {
                    ItemListView = ListView4.Items[index];
                    ItemListView.SubItems[1].Text = s;
                    index++;
                }
            }
            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_P5V, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                if (ListView4.Items.Count > index)
                {
                    ItemListView = ListView4.Items[index];
                    ItemListView.SubItems[1].Text = s;
                    index++;
                }
            }
            fValue = Program.pSDK.GetSensorTypeValue(CPUIDSDK.SENSOR_VOLTAGE_P12V, ref dummy, ref dummy);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 2));
                s = s + "  V";
                if (ListView4.Items.Count > index)
                {
                    ItemListView = ListView4.Items[index];
                    ItemListView.SubItems[1].Text = s;
                    index++;
                }
            }

        //  Check for sensors count
            NbSensors = Program.pSDK.GetNumberOfSensors(-1, CPUIDSDK.SENSOR_CLASS_VOLTAGE);
            if (NbSensors != ListView1.Items.Count)
            {
                ListView1.Items.Clear();
            }
            NbSensors = Program.pSDK.GetNumberOfSensors(-1, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
            if (NbSensors != ListView2.Items.Count)
            {
                ListView2.Items.Clear();
            }
            NbSensors = Program.pSDK.GetNumberOfSensors(-1, CPUIDSDK.SENSOR_CLASS_FAN);
            if (NbSensors != ListView3.Items.Count)
            {
                ListView3.Items.Clear();
            }
            NbSensors = Program.pSDK.GetNumberOfSensors(-1, CPUIDSDK.SENSOR_CLASS_CLOCK_SPEED);
            if (NbSensors != ListView6.Items.Count)
            {
                ListView6.Items.Clear();
            }
            NbSensors = Program.pSDK.GetNumberOfSensors(-1, CPUIDSDK.SENSOR_CLASS_UTILIZATION);
            if (NbSensors != ListView7.Items.Count)
            {
                ListView7.Items.Clear();
            }

            index1 = index2 = index3 = index4 = index5 = index6 = 0;
            NbDevices = Program.pSDK.GetNumberOfDevices();
            for (device_index = 0; device_index < NbDevices; device_index++)
            {
                devicename = Program.pSDK.GetDeviceName(device_index);

                // Voltage listview
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_VOLTAGE);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_VOLTAGE, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if ((result == true) && (fValue > -CPUIDSDK.MAX_FLOAT))
                    {
                        s = Convert.ToString(Math.Round(fValue, 2));
                        s = s + "  V";
                        if (ListView1.Items.Count <= index1)
                        {
                            ItemListView = ListView1.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView1.Items[index1];
                            ItemListView.SubItems[2].Text = s;                            
                        }
                        index1++;
                    }
                }

                // Temperature listview
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_TEMPERATURE, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if ((result == true) && Program.pSDK.IS_F_DEFINED(fValue))
                    {
                        s = Convert.ToString(Math.Round(fValue, 0));
                        s = s + "  °C";
                        if (ListView2.Items.Count <= index2)
                        {
                            ItemListView = ListView2.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView2.Items[index2];
                            ItemListView.SubItems[2].Text = s;                            
                        }
                        index2++;
                    }
                }

                // Fan listview
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_FAN);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_FAN, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if ((result == true) && (Math.Round(fValue, 0) >= 0))
                    {
                        s = Convert.ToString(Math.Round(fValue, 0));
                        s = s + "  RPM";
                        if (ListView3.Items.Count <= index3)
                        {
                            ItemListView = ListView3.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView3.Items[index3];
                            ItemListView.SubItems[2].Text = s;
                            
                        }
                        index3++;
                    }
                }

                // Clocks listview
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_CLOCK_SPEED);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_CLOCK_SPEED, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if ((result == true) && (fValue > 0.0F))
                    {
                        s = Convert.ToString(Math.Round(fValue, 1));
                        s = s + "  MHz";
                        if (ListView6.Items.Count <= index4)
                        {
                            ItemListView = ListView6.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView6.Items[index4];
                            ItemListView.SubItems[2].Text = s;
                        }
                        index4++;
                    }
                }

                // Utilizations listview
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_UTILIZATION);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_UTILIZATION, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if ((result == true) && (Math.Round(fValue, 0) >= 0))
                    {
                        s = Convert.ToString(Math.Round(fValue, 0));
                        s = s + "  %";
                        if (ListView7.Items.Count <= index6)
                        {
                            ItemListView = ListView7.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView7.Items[index6];
                            ItemListView.SubItems[2].Text = s;                            
                        }
                        index6++;
                    }
                }

                // "Other" listview
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_CURRENT);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_CURRENT, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if ((result == true) && (fValue > 0.0F))
                    {
                        s = Convert.ToString(Math.Round(fValue, 1));
                        s = s + "  Amps";
                        if (ListView5.Items.Count <= index5)
                        {
                            ItemListView = ListView5.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView5.Items[index5];
                            ItemListView.SubItems[2].Text = s;                            
                        }
                        index5++;
                    }
                }
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_POWER);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_POWER, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if ((result == true) && (fValue > 0.0F))
                    {
                        s = Convert.ToString(Math.Round(fValue, 1));
                        s = s + "  Watts";
                        if (ListView5.Items.Count <= index5)
                        {
                            ItemListView = ListView5.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView5.Items[index5];
                            ItemListView.SubItems[2].Text = s;                            
                        }
                        index5++;
                    }
                }
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_FAN_PWM);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_FAN_PWM, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if (result == true)
                    {
                        s = Convert.ToString(Math.Round(fValue, 0));
                        s = s + "  %";
                        if (ListView5.Items.Count <= index5)
                        {
                            ItemListView = ListView5.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView5.Items[index5];
                            ItemListView.SubItems[2].Text = s;
                        }
                        index5++;
                    }
                }
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_CAPACITY);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_CAPACITY, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if ((result == true) && (fValue > 0.0F))
                    {
                        s = Convert.ToString(Math.Round(fValue, 0));
                        s = s + "  mWh";
                        if (ListView5.Items.Count <= index5)
                        {
                            ItemListView = ListView5.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView5.Items[index5];
                            ItemListView.SubItems[2].Text = s;
                        }
                        index5++;
                    }
                }
                NbSensors = Program.pSDK.GetNumberOfSensors(device_index, CPUIDSDK.SENSOR_CLASS_LEVEL);
                for (sensor_index = 0; sensor_index < NbSensors; sensor_index++)
                {
                    result = Program.pSDK.GetSensorInfos(device_index, sensor_index, CPUIDSDK.SENSOR_CLASS_LEVEL, ref sensor_id, ref sensorname, ref iValue, ref fValue, ref fMinValue, ref fMaxValue);
                    if (result == true)
                    {
                        s = Convert.ToString(Math.Round(fValue, 0));
                        s = s + "  %";
                        if (ListView5.Items.Count <= index5)
                        {
                            ItemListView = ListView5.Items.Add(devicename);
                            ItemListView.SubItems.Add(sensorname);
                            ItemListView.SubItems.Add(s);
                        }
                        else
                        {
                            ItemListView = ListView5.Items[index5];
                            ItemListView.SubItems[2].Text = s;
                        }
                        index5++;
                    }
                }
            }
        }
    }
}