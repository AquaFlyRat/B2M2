using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace arch.Editor.Forms.Controls.Native
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

        [DllImport("user32.dll")]
        public static extern IntPtr GetActiveWindow();

        [DllImport("user32.dll")]
        public static extern int UpdateWindow(IntPtr hwnd);

        [DllImport("user32.dll")]
        public static extern long GetWindowLong(IntPtr hwnd, int index);

        [DllImport("user32.dll")]
        public static extern int SetWindowLong(IntPtr hwnd, int index, uint newLong);


        // Win32 constants

        public const int SW_SHOWNORMAL = 1;

        public const int SWP_SHOWWINDOW = 0x0040;
        public const int SWP_NOSIZE = 0x0001;

        public const int GWL_STYLE = -16;
        public const int GWL_EXSTYLE = -20;

        [DllImport("user32.dll")]
        public static extern int SetWindowRgn(IntPtr hWnd, IntPtr hRgn, bool bRedraw);
        [DllImport("gdi32.dll")]

        public static extern IntPtr CreateRoundRectRgn(int x1, int y1, int x2, int y2, int cx, int cy);

        public const long WS_CAPTION = 0x00800000L;
        public const long WS_THICKFRAME = 0x00040000L;
        public const long WS_MINIMIZE = 0x20000000L;
        public const long WS_MAXIMIZE = 0x01000000L;
        public const long WS_SYSMENU = 0x00080000L;
        public const long WS_POPUP = 0x80000000L;
        public const long WS_EX_DLGMODALFRAME = 0x00000001L;
        public const long WS_EX_CLIENTEDGE = 0x00000200L;
        public const long WS_EX_STATICEDGE = 0x00020000L;
        public const long WS_CHILD = 0x40000000L;
    }
}
