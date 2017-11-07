using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using b2m2;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing;
using WeifenLuo.WinFormsUI.Docking;

namespace B2M2.Editor.Source
{
    class Win32
    {
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
    }

    class GameWindow : DockContent {
        Timer _timer = new Timer();
        public Window _window;
        Renderer2D _renderer;
        Panel _viewport;

        public GameWindow()
        {
            Text = "Render Window";
            _viewport = new Panel();
            _viewport.Location = new Point(0, 0);
            _viewport.Dock = DockStyle.Fill;
            Controls.Add(_viewport);

            FormClosed += GameWindow_FormClosed;
            ResizeEnd += GameWindow_ResizeEnd;
            WindowConfig config = new WindowConfig(800, 600, ".NET Demo", false);
            _window = new Window(config);

            _window.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            _renderer = new Renderer2D();
            _renderer.Initalize(Matrix4.Orthographic(800, 0, 0, 600, 1.0f, -1.0f));
            
            Shown += GameWindow_Shown;

            MaximumSize = new Size(800, 600);
            IntPtr hwnd = _window.GetHWND();
            Win32.SetWindowPos(
            hwnd,
            _viewport.Handle,
             0,
            0,
            0,
            0,
            0x0401
           );

            Win32.SetParent(hwnd, _viewport.Handle);
            Win32.ShowWindow(hwnd, 1);
            _timer.Tick += _timer_Tick;
            _timer.Enabled = true;
            _timer.Interval = 1000 / 60;
            _timer.Start();
        }

        private void GameWindow_ResizeEnd(object sender, EventArgs e)
        {
            //_window.SetSize(Size.Width, Size.Height);

        }

        private void GameWindow_Shown(object sender, EventArgs e)
        {
            
        }
        float x = 100;
        private void _timer_Tick(object sender, EventArgs e)
        {
            _window.Clear();
            _renderer.Begin();
            _renderer.FillRectangle(new Vector2(x, 100), 100, 100, new b2m2.Color(1.0f, 0.0f, 1.0f, 1.0f));
            _renderer.End();
            _renderer.Present();

            _window.SwapBuffers();
        }

        private void GameWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            _renderer.Dispose();
        }
    }

    class Editor : Form {
        GameWindow _window;
        public Editor()
        {
            IsMdiContainer = true;
            
            DockPanel panel = new DockPanel();
            panel.Theme = new VS2015BlueTheme();

            panel.Dock = DockStyle.Fill;
            Controls.Add(panel);

            _window = new GameWindow();
            _window.Show(panel, DockState.Document);
            new DockContent().Show(panel, DockState.DockLeft);
            new DockContent().Show(panel, DockState.DockBottom);

            ResizeEnd += Editor_ResizeEnd;
        }

        private void Editor_ResizeEnd(object sender, EventArgs e)
        {
            _window._window.SetSize(_window.Size.Width, _window.Size.Height);
        }
    }


    class Entry
    {
        [STAThread]
        public static void Main(string [] args)
        {
            Application.Run(new Editor());

            /*WindowConfig config = new WindowConfig(800, 600, ".NET Demo");
            Window window = new Window(config);

            window.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);

            using (Renderer2D renderer = new Renderer2D())
            {
                Matrix4 mat4 = Matrix4.Orthographic(800, 0, 0, 600, 1.0f, -1.0f);
                float y = mat4.At(0, 0);
                renderer.Initalize(mat4);

                Vector2 pos = new Vector2(100, 100);
                Color color = new Color(66.0f / 255, 134.0f / 255, 244.0f / 255, 1.0f);

                while (window.IsRunning)
                {
                    window.PollEvents();
                    window.Clear();

                    renderer.Begin();
                    renderer.FillRectangle(pos, 100, 100, color);
                    renderer.End();
                    renderer.Present();

                    window.SwapBuffers();
                    window.Delay(1000 / 60);
                }
            }

            window.Destroy();*/
        }
    }
}
