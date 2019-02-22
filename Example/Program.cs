using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Runtime.InteropServices;


namespace RyzenAdjDLLTest
{
    unsafe class Program
    {
        [DllImport("RyzenAdjAPI.dll")]
        public static extern bool init_ryzenadj_library();

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_stapm_limit(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_fast_limit(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_slow_limit(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_slow_time(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_stapm_time(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_tctl_temp(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_vrm_current(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_vrmsoc_current(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_vrmmax_current(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_vrmsocmax_current(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_psi0_current(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern int set_psi0soc_current(uint value);

        [DllImport("RyzenAdjAPI.dll")]
        public static extern void cleanup_ryzenadj_library();


        static void Main(string[] args)
        {
            Console.WriteLine("Ryzen Adjustment Interoperability Example for C#.");

            // Initialise the RyzenAdj library.
            Console.WriteLine(init_ryzenadj_library());

            // Set the STAPM Limit to 15000 (25 Watts).
            Console.WriteLine(set_stapm_limit(25000));

            // Set the PPT Fast Limit to 25000 (25 Watts).
            Console.WriteLine(set_fast_limit(25000));

            // Set the PPT Slow Limit to 20000 (25 Watts).
            Console.WriteLine(set_slow_limit(25000));

            // Cleanup the RyzenAdj library after use.
            cleanup_ryzenadj_library();

            Console.WriteLine("Set new values.");
            Console.ReadLine();
        }
    }
}
