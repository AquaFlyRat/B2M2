using b2m2;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace B2M2.Editor.Forms.Native
{
    class RenderPanelWrapper
    {
        public Panel Panel { get; private set; }
        public Window NativeWindow { get; private set; }

        private Timer _timer;

        public RenderPanelWrapper(int width, int height, Action<Window> onTick, int refreshRate)
        {
            Panel = new Panel();
            Panel.Width = width;
            Panel.Height = height;
            Panel.Dock = DockStyle.Fill;
            Panel.Location = new System.Drawing.Point(0, 0);

            WindowConfig config = new WindowConfig(
                width, height, 
                string.Empty, false
            );

            NativeWindow = new Window(config);
            NativeWindow.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);

            RegisterNativeFunctions();

            _timer = new Timer();

            _timer.Enabled = true;
            _timer.Interval = refreshRate;

            _timer.Tick += (object o, EventArgs e) => {
                onTick(NativeWindow);
            };

            _timer.Start();
        }

        private void RegisterNativeFunctions()
        {
            IntPtr nativeSDLWindowHwnd = NativeWindow.GetHWND();
            Win32.SetWindowPos(
                nativeSDLWindowHwnd,
                Panel.Handle,
                0, 0, 0, 0,
                Win32.SWP_SHOWWINDOW | Win32.SWP_NOSIZE
            );

            Win32.SetParent(nativeSDLWindowHwnd, Panel.Handle);
        }
    }
}
