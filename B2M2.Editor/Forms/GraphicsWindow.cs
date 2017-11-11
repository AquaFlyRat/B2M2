using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;

using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using b2m2;
using B2M2.Editor.Forms.Native;
using System.Drawing;

namespace B2M2.Editor.Forms
{

    public partial class GraphicsWindow
    {
        public Window NativeWindow { get; private set; }

        private Timer _timer;
        
        public GraphicsWindow(Size size, Action<Window> onTick, int refreshRate)
        {
            WindowConfig config = new WindowConfig(
                size.Width, size.Height,
                string.Empty, WindowFlags.PositionOrigin
            );

            NativeWindow = new Window(config);
            NativeWindow.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);

            Win32.SetWindowPos(NativeWindow.GetHWND(), IntPtr.Zero, 300, 100, 0, 0, Win32.SWP_NOSIZE);

            _timer = new Timer();

            _timer.Enabled = true;
            _timer.Interval = refreshRate;

            _timer.Tick += (object o, EventArgs e) => {
                if (onTick != null)
                    onTick(NativeWindow);
            };

            _timer.Start();
        }

        public void SetParent(Form form)
        {
            Win32.SetParent(NativeWindow.GetHWND(), form.Handle);
        }

        public void Show()
        {
            Win32.ShowWindow(NativeWindow.GetHWND(), 1);
        }
    }
}
