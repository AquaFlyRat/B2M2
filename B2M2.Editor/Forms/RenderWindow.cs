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
        private Font _wendyOne;
        // tmp
        private Vector2 _rectPosition = new Vector2(100, 100);
        private Color _rectColor = new Color(1.0f, 0.0f, 1.0f, 1.0f);

        public RenderWindow()
        {
            System.Drawing.Size renderWindowSize = new System.Drawing.Size(800, 600);
            int refreshRateMs                    = 1000 / 1000;

            MaximumSize                          = renderWindowSize;
            Size                                 = renderWindowSize;
            Text                                 = "Render Window";
            FormBorderStyle                      = FormBorderStyle.FixedToolWindow;

            _renderPanel = new RenderPanelWrapper(
                renderWindowSize.Width, renderWindowSize.Height,
                GameWindowTick, refreshRateMs
            );
            
            Controls.Add(_renderPanel.Panel);

            _renderer = new Renderer2D();
            _wendyOne = new Font("Assets/WendyOne-Regular.ttf", 48);

            Matrix4 rendererProjection = Matrix4.Orthographic(
                renderWindowSize.Width, 0, 
                0, renderWindowSize.Height, 
                1, -1
            );
            _renderer.Initalize(rendererProjection);

            FormClosing += RenderWindow_FormClosing;
            Load        += RenderWindow_Load;
            KeyPress += RenderWindow_KeyPress;
        }

        public IntPtr GetNativeHandle()
        {
            return _renderPanel.NativeWindow.GetHWND();
        }

        public Window GetNativeWindow()
        {
            return _renderPanel.NativeWindow;
        } 

        string _text = "";

        private void RenderWindow_KeyPress(object sender, KeyPressEventArgs e)
        {
            _text += e.KeyChar;
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
                System.Drawing.Point cursorPos = Cursor.Position;
                cursorPos = PointToClient(cursorPos);
                _renderer.DrawString(cursorPos.X + ", " + cursorPos.Y, _wendyOne, new Vector2(100, 100), new Color(1.0f, 0.5f, 1.0f, 1.0f));
                _renderer.DrawString(_text, _wendyOne, new Vector2(100, 300), new Color(1.0f, 0.5f, 1.0f, 1.0f));
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
