using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using b2m2;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using WeifenLuo.WinFormsUI.Docking;

using B2M2.Editor.Classes.Native;

namespace B2M2.Editor.Forms
{
    using WinForms = System.Drawing;

    class GameWindow : DockContent {
        Timer _timer = new Timer();
        public Window _window;
        Renderer2D _renderer;
        Panel _viewport;
        Texture2D _texture;
        Font _font;

        public GameWindow()
        {
            Size = new WinForms.Size(800, 600);
            Text = "Render Window";
            _viewport = new Panel();
            _viewport.Location = new WinForms.Point(0, 0);
            _viewport.Dock = DockStyle.Fill;
            Controls.Add(_viewport);

            FormClosed += GameWindow_FormClosed;

            WindowConfig config = new WindowConfig(800, 600, ".NET Demo", false);
            _window = new Window(config);

            _window.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            _renderer = new Renderer2D();
            _renderer.Initalize(Matrix4.Orthographic(800, 0, 0, 600, 1.0f, -1.0f));

            _texture = new Texture2D("Assets/spr_basicfall.png", TextureFiltering.Nearest);
            _font = new Font("Assets/WendyOne-Regular.ttf", 32);
            MaximumSize = new WinForms.Size(800, 600);
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
        
        private void _timer_Tick(object sender, EventArgs e)
        {
            _window.Clear();
            _renderer.Begin();
            _renderer.FillRectangle(new Vector2(500, 200), 100, 100, new b2m2.Color(1.0f, 0.0f, 1.0f, 1.0f));
            _renderer.PushTransform(Matrix4.Scale(4f));
            _renderer.DrawTexture(_texture, new Vector2(10, 10));
            _renderer.PopTransform();
            _renderer.DrawString("Hello World!", _font, new Vector2(100, 300), new Color(0.3f, 0.4f, 0.5f, 1.0f));

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
            Size = new WinForms.Size(1280, 720);
            _window = new GameWindow();
            _window.MdiParent = this;
            _window.Show();
        }
    }
    
    class Entry
    {
        [STAThread]
        public static void Main(string [] args)
        {
            Application.Run(new Editor());
        }
    }
}
