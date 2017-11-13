using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CharlieEngine;
using System.Windows.Forms;

namespace B2M2.Editor.Forms.Controls.Native
{
    class CharlieWindow
    {
        public Window NativeWindow;
        public Panel Panel;

        public CharlieWindow()
        {
            Panel = new Panel();
            Panel.Width    = 800;
            Panel.Height   = 600;
            Panel.Dock     = DockStyle.Fill;
            Panel.Location = new System.Drawing.Point(0, 0);
            Panel.Click    += (object o, EventArgs e) => { Panel.Parent.Select(); };
            WindowConfig config = new WindowConfig(800, 600, "", WindowFlags.Borderless | WindowFlags.PositionOrigin); 

            NativeWindow = new Window(config);
            NativeWindow.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);

            Timer timer = new Timer();
            timer.Interval = 1000 / 60;

            Renderer2D renderer = new Renderer2D();
            renderer.Initalize(Matrix4.Orthographic(800, 0, 0, 600, 1, -1));

            timer.Tick += (object o, EventArgs e) => {
                NativeWindow.PollEvents();
                NativeWindow.Clear();
                renderer.Begin();
                renderer.FillRectangle(new Vector2(100, 100), 100, 100, new Color(0.1f, 0.7f, 0.3f, 1.0f));
                renderer.End();
                renderer.Present();
                NativeWindow.SwapBuffers();
            };

            Panel.Disposed += (object o, EventArgs e) => { renderer.Dispose(); };

            timer.Start();
            
            Win32.SetWindowPos(NativeWindow.GetHWND(), IntPtr.Zero, 0, 0, 0, 0, Win32.SWP_NOSIZE);
            Win32.SetParent(NativeWindow.GetHWND(), Panel.Handle);
            Win32.SetWindowLong(NativeWindow.GetHWND(), Win32.GWL_STYLE, (uint)Win32.WS_CHILD);
        }

        public void Show()
        {
            Win32.ShowWindow(NativeWindow.GetHWND(), Win32.SW_SHOWNORMAL);
        }
    }
}
