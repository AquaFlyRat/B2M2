using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CharlieEngine;
using System.Windows.Forms;

namespace Arch.Editor.View.Native
{
    class CharlieWindow
    {
        public Window NativeWindow;
        public Panel Panel;

        private Action<Window, Renderer2D> _onDrawAction;
        private Renderer2D _renderer;

        public CharlieWindow(int width, int height, Action<Window, Renderer2D> onDraw)
        {
            _onDrawAction = onDraw;

            Panel = new Panel();
            Panel.Width    = width;
            Panel.Height   = height;
            Panel.Dock     = DockStyle.Fill;
            Panel.BackColor = System.Drawing.Color.Black;
            Panel.Location = new System.Drawing.Point(0, 0);
            Panel.Click    += (object o, EventArgs e) => { Panel.Parent.Select(); };

            var screenDimensions = Screen.FromControl(Panel).Bounds;

            WindowConfig config = new WindowConfig(screenDimensions.Width,screenDimensions.Height, "", WindowFlags.Borderless | WindowFlags.PositionOrigin); 

            NativeWindow = new Window(config);
            NativeWindow.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);

            Timer timer = new Timer();
            timer.Interval = 1000 / 120;

            _renderer = new Renderer2D();
            _renderer.Initalize(Matrix4.Orthographic(screenDimensions.Width, 0, 0, screenDimensions.Height, 1, -1));

            Font font = new Font("Assets/WendyOne-Regular.ttf", 38);
            timer.Tick += (object o, EventArgs e) => {
                NativeWindow.PollEvents();
                NativeWindow.Clear();
                _renderer.Begin();
                _onDrawAction(NativeWindow, _renderer);
                _renderer.End();
                _renderer.Present();
                NativeWindow.SwapBuffers();
            };

            Panel.Disposed += (object o, EventArgs e) => { _renderer.Dispose(); };

            timer.Start();
            
            Win32.SetWindowPos(NativeWindow.GetHWND(), IntPtr.Zero, 0, 0, 0, 0, Win32.SWP_NOSIZE);
            Win32.SetParent(NativeWindow.GetHWND(), Panel.Handle);
            Win32.SetWindowLong(NativeWindow.GetHWND(), Win32.GWL_STYLE, (uint)Win32.WS_CHILD);
        }

        public Renderer2D GetRenderer()
        {
            return _renderer;
        }

        public void Show()
        {
            Win32.ShowWindow(NativeWindow.GetHWND(), Win32.SW_SHOWNORMAL);
        }
    }
}
