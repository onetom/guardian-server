using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;

namespace CPUInfos
{
    static class Program
    {
        public static CPUIDSDK pSDK;

        private static volatile bool _shouldStop = false;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Thread UpdateThread;
            bool res;
            int dll_version = 0;
            int error_code = 0, extended_error_code = 0;
            string error_message;

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            pSDK = new CPUIDSDK();
            res = pSDK.CreateInstance();

            res = pSDK.Init(CPUIDSDK.szDllPath,
                            CPUIDSDK.szDllFilename,
                            CPUIDSDK.CPUIDSDK_CONFIG_USE_EVERYTHING,
                            ref error_code,
                            ref extended_error_code);

            if (error_code != CPUIDSDK.CPUIDSDK_ERROR_NO_ERROR)
            {
                //	Init failed, check errorcode
                switch ((uint)error_code)
                {
                    case CPUIDSDK.CPUIDSDK_ERROR_EVALUATION:
                        {
                            switch ((uint)extended_error_code)
                            {
                                case CPUIDSDK.CPUIDSDK_EXT_ERROR_EVAL_1:
                                    error_message = "You are running a trial version of the DLL SDK. In order to make it work, please run CPU-Z at the same time.";
                                    break;

                                case CPUIDSDK.CPUIDSDK_EXT_ERROR_EVAL_2:
                                    error_message = "Evaluation version has expired.";
                                    break;

                                default:
                                    error_message = "Eval version error " + extended_error_code;
                                    break;
                            }
                        }
                        break;

                    case CPUIDSDK.CPUIDSDK_ERROR_DRIVER:
                        error_message = "Driver error " + extended_error_code;
                        break;

                    case CPUIDSDK.CPUIDSDK_ERROR_VM_RUNNING:
                        error_message = "Virtual machine detected.";
                        break;

                    case CPUIDSDK.CPUIDSDK_ERROR_LOCKED:
                        {
                            switch ((uint)extended_error_code)
                            {
                                case 6: // ERROR_INVALID_HANDLE:
                                    error_message = "SDK mutex not created.";
                                    break;

                                default:
                                    error_message = "SDK mutex locked.";
                                    break;
                            }
                        }
                        break;

                    default:
                        error_message = "Error code " + error_code;
                        break;
                }
                MessageBox.Show(error_message, "CPUID SDK Error");
            }

            if (res)
            {

                pSDK.GetDllVersion(ref dll_version);

                UpdateThread = new Thread(new ThreadStart(ThreadLoop));
                UpdateThread.Start();

                Application.Run(new Form1());

                _shouldStop = true;
                UpdateThread.Join();
            }

            pSDK.Close();
            pSDK.DestroyInstance();
        }

        public static void ThreadLoop()
        {
            //while ((Thread.CurrentThread.IsAlive) && (!_shouldStop))
            while (!_shouldStop)
            {
                pSDK.RefreshInformation();
                Thread.Sleep(1000);
            }
        }
    }
}