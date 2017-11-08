using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace B2M2.Editor.Forms.Native
{
    class Win32
    {
        // Win32 windowing functions

        [DllImport("User32.dll")]
        public static extern int SetParent(IntPtr child, IntPtr parent);

        [DllImport("user32.dll")]
        public static extern IntPtr SetWindowPos(
            IntPtr handle,
            IntPtr handleAfter,
            int x,
            int y,
            int cx,
            int cy,
            uint flags
        );

        [DllImport("user32.dll")]
        public static extern IntPtr ShowWindow(IntPtr handle, int command);


        // Win32 constants

        public const int SW_SHOWNORMAL = 1;

        public const int SWP_SHOWWINDOW = 0x0040;
        public const int SWP_NOSIZE = 0x0001;
    }
}
