using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using b2m2;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using B2M2.Editor.Forms.Native;
using System.Diagnostics;

namespace B2M2.Editor.Forms
{
    using FormSize = System.Drawing.Size;

    partial class Editor : Form
    {
        Renderer2D _renderer = new Renderer2D();
        Font _wendyOne;
        
        public Editor()
        {
            FormSize windowSize = new FormSize(800, 600);

            GraphicsWindow graphicsWindow  = new GraphicsWindow(windowSize, Tick, 1000 / 60);
            graphicsWindow.SetParent(this);
            graphicsWindow.Show();

            _renderer.Initalize(Matrix4.Orthographic(windowSize.Width, 0, 0, windowSize.Height, 1, -1));
            _wendyOne =  new Font("Assets/WendyOne-Regular.ttf", 38); ;
            
            FormClosing += (object o, FormClosingEventArgs e) => { _renderer.Dispose(); };

            InitializeComponent();
        }

        private void Tick(Window window)
        {
            window.PollEvents();
            window.Clear();
            _renderer.Begin();
            _renderer.FillRectangle(new Vector2(100, 100), 100, 100, new Color(1, 0, 1, 1));
            _renderer.DrawString("Hello World!", _wendyOne, new Vector2(25, 300), new Color(1, 1, 1, 1));
            _renderer.End();
            _renderer.Present();
            window.SwapBuffers();
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
