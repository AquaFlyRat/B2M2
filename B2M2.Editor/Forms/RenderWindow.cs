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

namespace B2M2.Editor.Forms
{
    public partial class RenderWindow : Form
    {
        private RenderPanelWrapper _renderPanel;
        private Renderer2D _renderer;

        // tmp
        private Vector2 _rectPosition = new Vector2(100, 100);
        private Color _rectColor = new Color(1.0f, 0.0f, 1.0f, 1.0f);

        public RenderWindow()
        {
            System.Drawing.Size renderWindowSize = new System.Drawing.Size(800, 600);
            int refreshRateMs                    = 1000 / 60;

            MaximumSize                          = renderWindowSize;
            Size                                 = renderWindowSize;
            Text                                 = "Render Window";

            _renderPanel = new RenderPanelWrapper(
                renderWindowSize.Width, renderWindowSize.Height,
                GameWindowTick, refreshRateMs
            );
            Controls.Add(_renderPanel.Panel);

            _renderer = new Renderer2D();

            Matrix4 rendererProjection = Matrix4.Orthographic(
                renderWindowSize.Width, 0, 
                0, renderWindowSize.Height, 
                1, -1
            );
            _renderer.Initalize(rendererProjection);
            
            FormClosing += RenderWindow_FormClosing;
            Load        += RenderWindow_Load;
        }

        private void RenderWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            _renderer.Dispose();
        }
        
        private void GameWindowTick(Window window)
        {
            window.PollEvents();
            window.Clear();

            _renderer.Begin();
            {
                _renderer.FillRectangle(_rectPosition, 100, 100, _rectColor);
            }
            _renderer.End();
            _renderer.Present();

            window.SwapBuffers();
        }

        private void RenderWindow_Load(object sender, EventArgs e)
        {
            Win32.ShowWindow(_renderPanel.NativeWindow.GetHWND(), Win32.SW_SHOWNORMAL);
        }
    }
}
