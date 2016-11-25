using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CPUInfos
{
    public partial class Form1 : Form
    {
        int proc_index = 0;
        int core_index = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string s;
            float fValue;
            int iValue;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            // TAB 1
            //////////////////////////////////////////////////////////////////////////////////////////////////////

            //  Processor name
            CPUName.Text = Program.pSDK.GetProcessorName(proc_index);

            //  Codename
            CPUCodeName.Text = Program.pSDK.GetProcessorCodeName(proc_index);

            //  Process
            fValue = Program.pSDK.GetProcessorManufacturingProcess(proc_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                if (fValue < 0.10f)
                {
                    float fVal = fValue * 1000.0f;
                    s = Convert.ToString((int)(fVal + 0.5f)) + " nm";
                }
                else
                {
                    s = Convert.ToString(fValue) + " um";
                }
                CPUProcess.Text = s;
            }

            // VID
            fValue = Program.pSDK.GetProcessorVoltageID(proc_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                fValue = (float)((int)(fValue * 100.0 + 0.5)) / 100.0f;
                s = Convert.ToString(fValue) + " V";
                CPUVID.Text = s;
            }

            // TDP
            fValue = Program.pSDK.GetProcessorTDP(proc_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(fValue) + " W";
                CPUTDP.Text = s;
            }

            //  Specification
            CPUSpecs.Text = Program.pSDK.GetProcessorSpecification(proc_index);

            //  Package
            CPUPackage.Text = Program.pSDK.GetProcessorPackage(proc_index);

            //  Revision
            CPURevision.Text = Program.pSDK.GetProcessorStepping(proc_index);

            //  Instruction set
            s = "";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_MMX)) s += "MMX ";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_EXTENDED_MMX)) s += "(+)";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_3DNOW)) s += ", 3DNow!";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_EXTENDED_3DNOW)) s += "(+)";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_SSE)) s += ", SSE";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_SSE2)) s += ", SSE2";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_SSE3)) s += ", SSE3";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_SSSE3)) s += ", SSSE3";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_SSE4_1)) s += ", SSE4.1";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_SSE4_2)) s += ", SSE4.2";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_SSE4A)) s += ", SSE4A";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_XOP)) s += ", XOP";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_X86_64)) s += ", x86-64";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_NX)) s += ", NX";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_VMX)) s += ", VMX";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_AES)) s += ", AES";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_AVX)) s += ", AVX";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_AVX2)) s += ", AVX2";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_FMA3)) s += ", FMA3";
            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_FMA4)) s += ", FMA4";

            if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_RTM) &&
                Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_HLE))
            {
                s += ", TSX";
            }
            else if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_RTM))
            {
                s += ", RTM";
            }
            else if (Program.pSDK.IsProcessorInstructionSetAvailable(proc_index, CPUIDSDK.ISET_HLE))
            {
                s += ", HLE";
            }

            CPUIset.Text = s;

            //  Clocks
            fValue = Program.pSDK.GetProcessorStockClockFrequency(proc_index);
            fValue = Program.pSDK.GetProcessorStockBusFrequency(proc_index);

            fValue = Program.pSDK.GetProcessorCoreClockFrequency(proc_index, core_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                CPUFreq.Text = s + " MHz";
            }

            fValue = Program.pSDK.GetProcessorCoreClockMultiplier(proc_index, core_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(fValue);
                CPUMultiplier.Text = "x " + s;
            }

            fValue = Program.pSDK.GetBusFrequency();
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                BusFreq.Text = s + " MHz";
            }

            fValue = Program.pSDK.GetProcessorRatedBusFrequency(proc_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                RBusFreq.Text = s + " MHz";
            }

            //  Caches
            int max_level = Program.pSDK.GetProcessorMaxCacheLevel(proc_index);
            int nbcaches = 0, cachesize = 0;
            if (max_level >= 1)
            {
                //  L1 Data
                Program.pSDK.GetProcessorCacheParameters(proc_index, 1, CPUIDSDK.CACHE_TYPE_DATA, ref nbcaches, ref cachesize);
                if (cachesize > 0)
                {
                    if (nbcaches > 1)
                        s = Convert.ToString(nbcaches) + " x " + Convert.ToString(cachesize) + " KBytes";
                    else
                        s = Convert.ToString(cachesize) + " KBytes";

                    L1D.Text = s;
                }

                //  L1 instructions
                Program.pSDK.GetProcessorCacheParameters(proc_index, 1, CPUIDSDK.CACHE_TYPE_INSTRUCTION, ref nbcaches, ref cachesize);
                if (cachesize > 0)
                {
                    if (nbcaches > 1)
                        s = Convert.ToString(nbcaches) + " x " + Convert.ToString(cachesize) + " KBytes";
                    else
                        s = Convert.ToString(cachesize) + " KBytes";

                    L1ILabel.Text = "L1 Inst.";
                    L1I.Text = s;
                }

                //  L1 Trace cache
                Program.pSDK.GetProcessorCacheParameters(proc_index, 1, CPUIDSDK.CACHE_TYPE_TRACE_CACHE, ref nbcaches, ref cachesize);
                if (cachesize > 0)
                {
                    if (nbcaches > 1)
                        s = Convert.ToString(nbcaches) + " x " + Convert.ToString(cachesize) + " Kuops";
                    else
                        s = Convert.ToString(cachesize) + " Kuops";

                    L1ILabel.Text = "L1 TC";
                    L1I.Text = s;
                }
            }
            if (max_level >= 2)
            {
                //  L2
                Program.pSDK.GetProcessorCacheParameters(proc_index, 2, CPUIDSDK.CACHE_TYPE_UNIFIED, ref nbcaches, ref cachesize);
                if (cachesize > 0)
                {
                    if (nbcaches > 1)
                        s = Convert.ToString(nbcaches) + " x " + Convert.ToString(cachesize) + " KBytes";
                    else
                        s = Convert.ToString(cachesize) + " KBytes";

                    L2.Text = s;
                }
            }
            if (max_level >= 3)
            {
                //  L3
                Program.pSDK.GetProcessorCacheParameters(proc_index, 3, CPUIDSDK.CACHE_TYPE_UNIFIED, ref nbcaches, ref cachesize);
                if (cachesize > 0)
                {
                    if (nbcaches > 1)
                        s = Convert.ToString(nbcaches) + " x " + Convert.ToString(cachesize) + " KBytes";
                    else
                        s = Convert.ToString(cachesize) + " KBytes";

                    L3.Text = s;
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            // TAB 2
            //////////////////////////////////////////////////////////////////////////////////////////////////////

            s = Program.pSDK.GetNorthBridgeVendor();
            s = s + " ";
            s = s + Program.pSDK.GetNorthBridgeModel();
            HostbridgeName.Text = s;
            HBRev.Text = Program.pSDK.GetNorthBridgeRevision();

            s = Program.pSDK.GetSouthBridgeVendor();
            s = s + " ";
            s = s + Program.pSDK.GetSouthBridgeModel();
            LPCName.Text = s;
            LPCRev.Text = Program.pSDK.GetSouthBridgeRevision();

            s = Program.pSDK.GetBIOSVendor();
            s = Program.pSDK.GetBIOSVersion();
            s = Program.pSDK.GetBIOSDate();

            s = Program.pSDK.GetMainboardVendor();
            s = Program.pSDK.GetMainboardModel();
            s = Program.pSDK.GetMainboardRevision();
            s = Program.pSDK.GetMainboardSerialNumber();

            s = Program.pSDK.GetSystemManufacturer();
            s = Program.pSDK.GetSystemProductName();
            s = Program.pSDK.GetSystemVersion();
            s = Program.pSDK.GetSystemSerialNumber();
            s = Program.pSDK.GetSystemUUID();

            int nbslots = 0, nbusedslots = 0, slotmap = 0, maxmodulesize = 0;
            Program.pSDK.GetMemorySlotsConfig(ref nbslots, ref nbusedslots, ref slotmap, ref maxmodulesize);

            iValue = Program.pSDK.GetMemoryType();
            switch (iValue)
            {
                case CPUIDSDK.MEMORY_TYPE_SPM_RAM: s = "SPM"; break;
                case CPUIDSDK.MEMORY_TYPE_RDRAM: s = "RDRAM"; break;
                case CPUIDSDK.MEMORY_TYPE_EDO_RAM: s = "EDO"; break;
                case CPUIDSDK.MEMORY_TYPE_FPM_RAM: s = "FPM"; break;
                case CPUIDSDK.MEMORY_TYPE_SDRAM: s = "SDRAM"; break;
                case CPUIDSDK.MEMORY_TYPE_DDR_SDRAM: s = "DDR"; break;
                case CPUIDSDK.MEMORY_TYPE_DDR2_SDRAM: s = "DDR2"; break;
                case CPUIDSDK.MEMORY_TYPE_DDR2_SDRAM_FB: s = "FB-DDR2"; break;
                case CPUIDSDK.MEMORY_TYPE_DDR3_SDRAM: s = "DDR3"; break;
                case CPUIDSDK.MEMORY_TYPE_DDR4_SDRAM: s = "DDR4"; break;
                default: s = ""; break;
            }
            RAMType.Text = s;

            iValue = Program.pSDK.GetMemorySize();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMSize.Text = s + " MBytes";
            }

            fValue = Program.pSDK.GetMemoryClockFrequency();
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                RAMFreq.Text = s + " MHz";
            }

            fValue = Program.pSDK.GetMemoryCASLatency();
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                RAMCASLatency.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryRAStoCASDelay();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMRAStoCAS.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryRASPrecharge();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMRASPrecharge.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryTRAS();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMTRAS.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryTRC();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMTRC.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryCommandRate();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMCommandRate.Text = s + " clocks";
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            // TAB 3 : SPD
            //////////////////////////////////////////////////////////////////////////////////////////////////////

            int NbSPDModules;
            int spd_index;

            NbSPDModules = Program.pSDK.GetNumberOfSPDModules();
            for (spd_index = 0; spd_index < NbSPDModules; spd_index++)
            {
                s = "Module " + Convert.ToString(spd_index + 1);
                ComboBox1.Items.Add(s);
            }

            if (ComboBox1.Items.Count > 0)
            {
                ComboBox1.SelectedIndex = 0;
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            // TAB 4 : GRAPHICS
            //////////////////////////////////////////////////////////////////////////////////////////////////////

            for (int adapter_index = 0; adapter_index < Program.pSDK.GetNumberOfDisplayAdapter(); adapter_index++)
            {
                string adapter_name = Program.pSDK.GetDisplayAdapterName(adapter_index);
                comboBox2.Items.Add(adapter_name);
            }
            if (comboBox2.Items.Count > 0)
            {
                comboBox2.SelectedIndex = 0;
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Closing form
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            string s;
            float fValue;
            int iValue;

        //  CPU
            fValue = Program.pSDK.GetProcessorCoreClockFrequency(proc_index, core_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                CPUFreq.Text = s + " MHz";
            }

            fValue = Program.pSDK.GetProcessorCoreClockMultiplier(proc_index, core_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(fValue);
                CPUMultiplier.Text = "x " + s;
            }

            fValue = Program.pSDK.GetBusFrequency();
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                BusFreq.Text = s + " MHz";
            }

            fValue = Program.pSDK.GetProcessorRatedBusFrequency(proc_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                RBusFreq.Text = s + " MHz";
            }

        //  Memory
            fValue = Program.pSDK.GetMemoryClockFrequency();
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                RAMFreq.Text = s + " MHz";
            }

            fValue = Program.pSDK.GetMemoryCASLatency();
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                s = Convert.ToString(Math.Round(fValue, 1));
                RAMCASLatency.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryRAStoCASDelay();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMRAStoCAS.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryRASPrecharge();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMRASPrecharge.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryTRAS();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMTRAS.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryTRC();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMTRC.Text = s + " clocks";
            }

            iValue = Program.pSDK.GetMemoryCommandRate();
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                RAMCommandRate.Text = s + " clocks";
            }

        //  Graphics
            s = "";
            int adapter_index = comboBox2.SelectedIndex;
            int perf_level = comboBox3.SelectedIndex;

            float fClockGPU = Program.pSDK.GetDisplayAdapterClock(adapter_index, perf_level, CPUIDSDK.DISPLAY_CLOCK_DOMAIN_GPU);
            if (Program.pSDK.IS_F_DEFINED(fClockGPU))
            {
                s = Convert.ToString(Math.Round(fClockGPU, 1));
                GPUClock.Text = s + " MHz";
            }
            else
                GPUClock.Text = "";

            float fClockMemory = Program.pSDK.GetDisplayAdapterClock(adapter_index, perf_level, CPUIDSDK.DISPLAY_CLOCK_DOMAIN_MEMORY);
            if (Program.pSDK.IS_F_DEFINED(fClockMemory))
            {
                s = Convert.ToString(Math.Round(fClockMemory, 1));
                MemoryClock.Text = s + " MHz";
            }
            else
                MemoryClock.Text = "";

            float fClockShaders = Program.pSDK.GetDisplayAdapterClock(adapter_index, perf_level, CPUIDSDK.DISPLAY_CLOCK_DOMAIN_SHADER);
            if (Program.pSDK.IS_F_DEFINED(fClockShaders))
            {
                s = Convert.ToString(Math.Round(fClockShaders, 1));
                ShadersClock.Text = s + " MHz";
            }
            else
                ShadersClock.Text = "";
        }

        private void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string s;
            int iValue, NbProfiles;
            int spd_index = ComboBox1.SelectedIndex;
            int profile_index, tab_index, i, j;
            int epp_revision, xmp_revision, amp_revision;
            int tRCD, tRP, tRAS, tRC;
            float frequency, CL, nominal_voltage, minTRCD, minTRP, minTRAS, minTRC;

            tRC0.Text = tRC1.Text = tRC2.Text = tRC3.Text = "";

            iValue = Program.pSDK.GetSPDModuleSize(spd_index);
            if (Program.pSDK.IS_I_DEFINED(iValue))
            {
                s = Convert.ToString(iValue);
                SPDSize.Text = s + " MBytes";
            }

            s = Program.pSDK.GetSPDModuleManufacturer(spd_index);
            SPDManufacturer.Text = s;

            s = Program.pSDK.GetSPDModuleSpecification(spd_index);
            SPDSpec.Text = s;

            s = Program.pSDK.GetSPDModulePartNumber(spd_index);
            SPDPartNumber.Text = s;

            // Timings in ns
            minTRCD = Program.pSDK.GetSPDModuleMinTRCD(spd_index);
            minTRP = Program.pSDK.GetSPDModuleMinTRP(spd_index);
            minTRAS = Program.pSDK.GetSPDModuleMinTRAS(spd_index);
            minTRC = Program.pSDK.GetSPDModuleMinTRC(spd_index);

            tab_index = 0;
            profile_index = 0;

        //  AMP
            amp_revision = 0;
            NbProfiles = Program.pSDK.GetSPDModuleNumberOfAMPProfiles(spd_index, ref amp_revision);
            if (NbProfiles > 0)
            {
                float profileRCD, profileRAS, profileRP, profileRC, minCycleTime;
                int freq;

                profile_index += NbProfiles;
                tab_index = 4 - profile_index;
                if (tab_index < 0) tab_index = 0;

                freq = (int)CPUIDSDK.I_UNDEFINED_VALUE;
                CL = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRCD = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRAS = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRP = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRC = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                minCycleTime = (float)CPUIDSDK.F_UNDEFINED_VALUE;

                for (i = 0; i < NbProfiles; i++, tab_index++)
                {
                    Program.pSDK.GetSPDModuleAMPProfileInfos(spd_index, i, ref freq, ref minCycleTime, ref CL, ref profileRCD, ref profileRAS, ref profileRP, ref profileRC);

                    if (Program.pSDK.IS_I_DEFINED(freq))
                    {
                        switch (tab_index)
                        {
                            case 0: Prof0.Text = "AMP #" + (i + 1); break;
                            case 1: Prof1.Text = "AMP #" + (i + 1); break;
                            case 2: Prof2.Text = "AMP #" + (i + 1); break;
                            case 3: Prof3.Text = "AMP #" + (i + 1); break;
                            default: break;
                        }

                        s = Convert.ToString(freq);
                        switch (tab_index)
                        {
                            case 0: Freq0.Text = s + " MHz"; break;
                            case 1: Freq1.Text = s + " MHz"; break;
                            case 2: Freq2.Text = s + " MHz"; break;
                            case 3: Freq3.Text = s + " MHz"; break;
                            default: break;
                        }

                        s = Convert.ToString(CL);
                        switch (tab_index)
                        {
                            case 0: CL0.Text = s; break;
                            case 1: CL1.Text = s; break;
                            case 2: CL2.Text = s; break;
                            case 3: CL3.Text = s; break;
                            default: break;
                        }

                        tRCD = (int)(profileRCD * (1000.0f / minCycleTime) / 1000.0F);
                        s = Convert.ToString(tRCD);
                        switch (tab_index)
                        {
                            case 0: tRCD0.Text = s; break;
                            case 1: tRCD1.Text = s; break;
                            case 2: tRCD2.Text = s; break;
                            case 3: tRCD3.Text = s; break;
                            default: break;
                        }

                        tRP = (int)(profileRP * (1000.0f / minCycleTime) / 1000.0F);
                        s = Convert.ToString(tRP);
                        switch (tab_index)
                        {
                            case 0: tRP0.Text = s; break;
                            case 1: tRP1.Text = s; break;
                            case 2: tRP2.Text = s; break;
                            case 3: tRP3.Text = s; break;
                            default: break;
                        }

                        tRAS = (int)(profileRAS * (1000.0f / minCycleTime) / 1000.0F);
                        s = Convert.ToString(tRAS);
                        switch (tab_index)
                        {
                            case 0: tRAS0.Text = s; break;
                            case 1: tRAS1.Text = s; break;
                            case 2: tRAS2.Text = s; break;
                            case 3: tRAS3.Text = s; break;
                            default: break;
                        }

                        tRC = (int)(profileRC * (1000.0f / minCycleTime) / 1000.0F);
                        s = Convert.ToString(tRC);
                        switch (tab_index)
                        {
                            case 0: tRC0.Text = s; break;
                            case 1: tRC1.Text = s; break;
                            case 2: tRC2.Text = s; break;
                            case 3: tRC3.Text = s; break;
                            default: break;
                        }
                    }
                }
            }

        //  XMP/EPP
            xmp_revision = 0;
            epp_revision = 0;
            NbProfiles = Program.pSDK.GetSPDModuleNumberOfXMPProfiles(spd_index, ref xmp_revision);
            if (NbProfiles > 0)
            {
                profile_index += NbProfiles;
                tab_index = 4 - profile_index;
                if (tab_index < 0) tab_index = 0;

                float profileRCD, profileRAS, profileRP, max_CL;
                int max_freq;

                max_freq = CPUIDSDK.I_UNDEFINED_VALUE;
                CL = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRCD = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRAS = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRP = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                max_CL = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                nominal_voltage = (float)CPUIDSDK.F_UNDEFINED_VALUE;

                for (i = 0; i < NbProfiles; i++, tab_index++)
                {
                    Program.pSDK.GetSPDModuleXMPProfileInfos(spd_index,
                                                               i,
                                                               ref profileRCD,
                                                               ref profileRAS,
                                                               ref profileRP,
                                                               ref nominal_voltage,
                                                               ref max_freq,
                                                               ref max_CL);

                    if (Program.pSDK.IS_F_DEFINED(max_freq))
                    {
                        switch (tab_index)
                        {
                            case 0: Prof0.Text = "XMP-" + (2 * max_freq); break;
                            case 1: Prof1.Text = "XMP-" + (2 * max_freq); break;
                            case 2: Prof2.Text = "XMP-" + (2 * max_freq); break;
                            case 3: Prof3.Text = "XMP-" + (2 * max_freq); break;
                            default: break;
                        }

                        s = Convert.ToString((int)max_freq);
                        switch (tab_index)
                        {
                            case 0: Freq0.Text = s + " MHz"; break;
                            case 1: Freq1.Text = s + " MHz"; break;
                            case 2: Freq2.Text = s + " MHz"; break;
                            case 3: Freq3.Text = s + " MHz"; break;
                            default: break;
                        }

                    //  Get profile with max CL
                        int nbCL = Program.pSDK.GetSPDModuleXMPProfileNumberOfCL(spd_index, i);
                        int mindelta = 999;
                        int cas_index = -1;

                        frequency = (float)CPUIDSDK.F_UNDEFINED_VALUE;

                        for (j = 0; j < nbCL; j++)
                        {
                            Program.pSDK.GetSPDModuleXMPProfileCLInfos(spd_index, i, j, ref frequency, ref CL);
                            if ((int)CL == (int)max_CL)
                            {
                                cas_index = j;
                                break;
                            }
                            else
                            {
                                int delta = (int)CL - (int)max_CL;
                                if (delta > 0)
                                {
                                    if (delta < mindelta)
                                    {
                                        mindelta = delta;
                                        cas_index = j;
                                    }
                                }
                            }
                        }
                        if (cas_index >= 0)
                        {
                            Program.pSDK.GetSPDModuleXMPProfileCLInfos(spd_index, i, cas_index, ref frequency, ref CL);

                            s = Convert.ToString(CL);
                            switch (tab_index)
                            {
                                case 0: CL0.Text = s; break;
                                case 1: CL1.Text = s; break;
                                case 2: CL2.Text = s; break;
                                case 3: CL3.Text = s; break;
                                default: break;
                            }

                            //	Convert timings from ns to clocks
                            tRCD = (int)Math.Ceiling(profileRCD * frequency / 1000.0F);
                            s = Convert.ToString(tRCD);
                            switch (tab_index)
                            {
                                case 0: tRCD0.Text = s; break;
                                case 1: tRCD1.Text = s; break;
                                case 2: tRCD2.Text = s; break;
                                case 3: tRCD3.Text = s; break;
                                default: break;
                            }

                            tRP = (int)Math.Ceiling(profileRP * frequency / 1000.0F);
                            s = Convert.ToString(tRP);
                            switch (tab_index)
                            {
                                case 0: tRP0.Text = s; break;
                                case 1: tRP1.Text = s; break;
                                case 2: tRP2.Text = s; break;
                                case 3: tRP3.Text = s; break;
                                default: break;
                            }

                            tRAS = (int)Math.Ceiling(profileRAS * frequency / 1000.0F);
                            s = Convert.ToString(tRAS);
                            switch (tab_index)
                            {
                                case 0: tRAS0.Text = s; break;
                                case 1: tRAS1.Text = s; break;
                                case 2: tRAS2.Text = s; break;
                                case 3: tRAS3.Text = s; break;
                                default: break;
                            }
                        }
                        else
                        {
                            s = Convert.ToString(max_CL);
                            switch (tab_index)
                            {
                                case 0: CL0.Text = s; break;
                                case 1: CL1.Text = s; break;
                                case 2: CL2.Text = s; break;
                                case 3: CL3.Text = s; break;
                                default: break;
                            }

                            //	Convert timings from ns to clocks
                            tRCD = (int)Math.Ceiling(profileRCD * max_freq / 1000.0F);
                            s = Convert.ToString(tRCD);
                            switch (tab_index)
                            {
                                case 0: tRCD0.Text = s; break;
                                case 1: tRCD1.Text = s; break;
                                case 2: tRCD2.Text = s; break;
                                case 3: tRCD3.Text = s; break;
                                default: break;
                            }

                            tRP = (int)Math.Ceiling(profileRP * max_freq / 1000.0F);
                            s = Convert.ToString(tRP);
                            switch (tab_index)
                            {
                                case 0: tRP0.Text = s; break;
                                case 1: tRP1.Text = s; break;
                                case 2: tRP2.Text = s; break;
                                case 3: tRP3.Text = s; break;
                                default: break;
                            }

                            tRAS = (int)Math.Ceiling(profileRAS * max_freq / 1000.0F);
                            s = Convert.ToString(tRAS);
                            switch (tab_index)
                            {
                                case 0: tRAS0.Text = s; break;
                                case 1: tRAS1.Text = s; break;
                                case 2: tRAS2.Text = s; break;
                                case 3: tRAS3.Text = s; break;
                                default: break;
                            }
                        }
                    }
                }
            }
            else if (Program.pSDK.GetSPDModuleNumberOfEPPProfiles(spd_index, ref epp_revision) > 0)
            {
                float profileRCD, profileRAS, profileRP, profileRC;

                profile_index += NbProfiles;
                tab_index = 4 - profile_index;
                if (tab_index < 0) tab_index = 0;

                NbProfiles = Program.pSDK.GetSPDModuleNumberOfEPPProfiles(spd_index, ref epp_revision);
                frequency = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                CL = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRCD = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRAS = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRP = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                profileRC = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                nominal_voltage = (float)CPUIDSDK.F_UNDEFINED_VALUE;
  
                for (i = 0; i < NbProfiles; i++, tab_index++)
                {
                    Program.pSDK.GetSPDModuleEPPProfileInfos(spd_index, i, ref frequency, ref CL, ref profileRCD, ref profileRAS, ref profileRP, ref profileRC, ref nominal_voltage);
                    if (Program.pSDK.IS_F_DEFINED(frequency))
                    {
                        switch (tab_index)
                        {
                            case 0: Prof0.Text = "EPP #" + (i + 1); break;
                            case 1: Prof1.Text = "EPP #" + (i + 1); break;
                            case 2: Prof2.Text = "EPP #" + (i + 1); break;
                            case 3: Prof3.Text = "EPP #" + (i + 1); break;
                            default: break;
                        }

                        s = Convert.ToString((int)frequency);
                        switch (tab_index)
                        {
                            case 0: Freq0.Text = s + " MHz"; break;
                            case 1: Freq1.Text = s + " MHz"; break;
                            case 2: Freq2.Text = s + " MHz"; break;
                            case 3: Freq3.Text = s + " MHz"; break;
                            default: break;
                        }

                        s = Convert.ToString(CL);
                        switch (tab_index)
                        {
                            case 0: CL0.Text = s; break;
                            case 1: CL1.Text = s; break;
                            case 2: CL2.Text = s; break;
                            case 3: CL3.Text = s; break;
                            default: break;
                        }

                        tRCD = (int)Math.Ceiling(profileRCD * frequency / 1000.0F);
                        s = Convert.ToString(tRCD);
                        switch (tab_index)
                        {
                            case 0: tRCD0.Text = s; break;
                            case 1: tRCD1.Text = s; break;
                            case 2: tRCD2.Text = s; break;
                            case 3: tRCD3.Text = s; break;
                            default: break;
                        }

                        tRP = (int)Math.Ceiling(profileRP * frequency / 1000.0F);
                        s = Convert.ToString(tRP);
                        switch (tab_index)
                        {
                            case 0: tRP0.Text = s; break;
                            case 1: tRP1.Text = s; break;
                            case 2: tRP2.Text = s; break;
                            case 3: tRP3.Text = s; break;
                            default: break;
                        }

                        tRAS = (int)Math.Ceiling(profileRAS * frequency / 1000.0F);
                        s = Convert.ToString(tRAS);
                        switch (tab_index)
                        {
                            case 0: tRAS0.Text = s; break;
                            case 1: tRAS1.Text = s; break;
                            case 2: tRAS2.Text = s; break;
                            case 3: tRAS3.Text = s; break;
                            default: break;
                        }

                        tRC = (int)Math.Ceiling(profileRC * frequency / 1000.0F);
                        s = Convert.ToString(tRC);
                        switch (tab_index)
                        {
                            case 0: tRC0.Text = s; break;
                            case 1: tRC1.Text = s; break;
                            case 2: tRC2.Text = s; break;
                            case 3: tRC3.Text = s; break;
                            default: break;
                        }
                    }
                }
            }

        //  Jedec
            NbProfiles = Program.pSDK.GetSPDModuleNumberOfProfiles(spd_index);
            if (NbProfiles > 0)
            {
                frequency = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                CL = (float)CPUIDSDK.F_UNDEFINED_VALUE;
                nominal_voltage = (float)CPUIDSDK.F_UNDEFINED_VALUE;
 
                for (i = NbProfiles - 1, tab_index = 4 - profile_index - 1;
                      i >= 0;
                      i--, tab_index--)
                { 
                    Program.pSDK.GetSPDModuleProfileInfos(spd_index, i, ref frequency, ref CL, ref nominal_voltage);
                    if (Program.pSDK.IS_F_DEFINED(frequency))
                    {
                        switch (tab_index)
                        {
                            case 0: Prof0.Text = "Jedec #" + (i + 1); break;
                            case 1: Prof1.Text = "Jedec #" + (i + 1); break;
                            case 2: Prof2.Text = "Jedec #" + (i + 1); break;
                            case 3: Prof3.Text = "Jedec #" + (i + 1); break;
                            default: break;
                        }

                        s = Convert.ToString((int)frequency);
                        switch (tab_index)
                        {
                            case 0: Freq0.Text = s + " MHz"; break;
                            case 1: Freq1.Text = s + " MHz"; break;
                            case 2: Freq2.Text = s + " MHz"; break;
                            case 3: Freq3.Text = s + " MHz"; break;
                            default: break;
                        }

                        s = Convert.ToString(CL);
                        switch (tab_index)
                        {
                            case 0: CL0.Text = s; break;
                            case 1: CL1.Text = s; break;
                            case 2: CL2.Text = s; break;
                            case 3: CL3.Text = s; break;
                            default: break;
                        }

                        tRCD = (int)Math.Ceiling(minTRCD * frequency / 1000.0F);
                        s = Convert.ToString(tRCD);
                        switch (tab_index)
                        {
                            case 0: tRCD0.Text = s; break;
                            case 1: tRCD1.Text = s; break;
                            case 2: tRCD2.Text = s; break;
                            case 3: tRCD3.Text = s; break;
                            default: break;
                        }

                        tRP = (int)Math.Ceiling(minTRP * frequency / 1000.0F);
                        s = Convert.ToString(tRP);
                        switch (tab_index)
                        {
                            case 0: tRP0.Text = s; break;
                            case 1: tRP1.Text = s; break;
                            case 2: tRP2.Text = s; break;
                            case 3: tRP3.Text = s; break;
                            default: break;
                        }

                        tRAS = (int)Math.Ceiling(minTRAS * frequency / 1000.0F);
                        s = Convert.ToString(tRAS);
                        switch (tab_index)
                        {
                            case 0: tRAS0.Text = s; break;
                            case 1: tRAS1.Text = s; break;
                            case 2: tRAS2.Text = s; break;
                            case 3: tRAS3.Text = s; break;
                            default: break;
                        }

                        tRC = (int)Math.Ceiling(minTRC * frequency / 1000.0F);
                        s = Convert.ToString(tRC);
                        switch (tab_index)
                        {
                            case 0: tRC0.Text = s; break;
                            case 1: tRC1.Text = s; break;
                            case 2: tRC2.Text = s; break;
                            case 3: tRC3.Text = s; break;
                            default: break;
                        }
                    }
                }
            }
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string s = "";
            int adapter_index = comboBox2.SelectedIndex;
            int perf_level = 0;
            float fValue;

            comboBox3.Items.Clear();

            for (perf_level = 0; perf_level < Program.pSDK.GetDisplayAdapterNumberOfPerformanceLevels(adapter_index); perf_level++)
            {
                string perf_level_name = Program.pSDK.GetDisplayAdapterPerformanceLevelName(adapter_index, perf_level);
                comboBox3.Items.Add(perf_level_name);
            }
            if (comboBox3.Items.Count > 0)
            {
                comboBox3.SelectedIndex = 0;
            }

            string adapter_codename = Program.pSDK.GetDisplayAdapterCodeName(adapter_index);
            GPUCodename.Text = adapter_codename;

            //  GPU Process
            fValue = Program.pSDK.GetDisplayAdapterManufacturingProcess(adapter_index);
            if (Program.pSDK.IS_F_DEFINED(fValue))
            {
                if (fValue < 0.10f)
                {
                    float fVal = fValue * 1000.0f;
                    s = Convert.ToString((int)(fVal + 0.5f)) + " nm";
                }
                else
                {
                    s = Convert.ToString(fValue) + " um";
                }
                GPUProcess.Text = s;
            }

            // Memory size
            int size = -1;
            if (Program.pSDK.GetDisplayAdapterMemorySize(adapter_index, ref size))
            {
                if (Program.pSDK.IS_I_DEFINED(size))
                {
                    s = Convert.ToString(size);
                    VRAMSize.Text = s + " MBytes";
                }
            }

            // Memory type
            int type = -1;
            if (Program.pSDK.GetDisplayAdapterMemoryType(adapter_index, ref type))
            {
                switch (type)
                {
                    case CPUIDSDK.MEMORY_TYPE_DDR: s = "DDR"; break;
                    case CPUIDSDK.MEMORY_TYPE_DDR2: s = "DDR2"; break;
                    case CPUIDSDK.MEMORY_TYPE_DDR3: s = "DDR3"; break;
                    case CPUIDSDK.MEMORY_TYPE_GDDR3: s = "GDDR3"; break;
                    case CPUIDSDK.MEMORY_TYPE_GDDR4: s = "GDDR4"; break;
                    case CPUIDSDK.MEMORY_TYPE_GDDR5: s = "GDDR5"; break;
                    default: s = ""; break;
                }
                VRAMType.Text = s;
            }

            // Memory bus width
            int bus_width = -1;
            if (Program.pSDK.GetDisplayAdapterMemoryBusWidth(adapter_index, ref bus_width))
            {
                if (Program.pSDK.IS_I_DEFINED(bus_width))
                {
                    s = Convert.ToString(bus_width);
                    VRAMBusWidth.Text = s + " bits";
                }
            }
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            string s = "";
            int adapter_index = comboBox2.SelectedIndex;
            int perf_level = comboBox3.SelectedIndex;

            float fClockGPU = Program.pSDK.GetDisplayAdapterClock(adapter_index, perf_level, CPUIDSDK.DISPLAY_CLOCK_DOMAIN_GPU);
            if (Program.pSDK.IS_F_DEFINED(fClockGPU))
            {
                s = Convert.ToString(Math.Round(fClockGPU, 1));
                GPUClock.Text = s + " MHz";
            }

            float fClockMemory = Program.pSDK.GetDisplayAdapterClock(adapter_index, perf_level, CPUIDSDK.DISPLAY_CLOCK_DOMAIN_MEMORY);
            if (Program.pSDK.IS_F_DEFINED(fClockMemory))
            {
                s = Convert.ToString(Math.Round(fClockMemory, 1));
                MemoryClock.Text = s + " MHz";
            }

            float fClockShaders = Program.pSDK.GetDisplayAdapterClock(adapter_index, perf_level, CPUIDSDK.DISPLAY_CLOCK_DOMAIN_SHADER);
            if (Program.pSDK.IS_F_DEFINED(fClockShaders))
            {
                s = Convert.ToString(Math.Round(fClockShaders, 1));
                ShadersClock.Text = s + " MHz";
            }
        }
    }
}