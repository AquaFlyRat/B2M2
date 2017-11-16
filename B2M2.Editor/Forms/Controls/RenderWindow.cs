using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DarkUI.Docking;
using B2M2.Editor.Forms.Controls.Native;

using CharlieEngine.Editor.Classes.Engine;

namespace CharlieEngine.Editor.Forms.Controls
{
    public partial class RenderWindow : DarkDocument
    {
        public static Scene CurrentScene = new Scene();
        private Font _wendyOne;

        public RenderWindow()
        {
            InitializeComponent();

            DockText = "Render Window";
            CharlieWindow window = new CharlieWindow(Width, Height, OnCharlieDraw);
            _wendyOne = new Font("Assets/WendyOne-Regular.ttf", 48);
            window.Panel.MouseClick += (object o, MouseEventArgs e) => {
                if (e.Button == MouseButtons.Right)
                {
                    _contextMenu.Show(Parent.PointToScreen(e.Location));
                }
            };
            window.Show();

            // Apparantly we need both for this to work correctly...
            // Please don't touch or all hell starts to break loose.
            Win32.SetParent(window.NativeWindow.GetHWND(), Handle);
            Controls.Add(window.Panel);
        }

        private void OnCharlieDraw(Window window, Renderer2D renderer)
        {
            var cursorPos = PointToClient(Cursor.Position);
            
            foreach(GameObject obj in CurrentScene.Objects)
            {
                if(cursorPos.X > obj.Position.X && cursorPos.X < obj.Position.X + obj.Width)
                {
                    if (cursorPos.Y > obj.Position.Y && cursorPos.Y < obj.Position.Y + obj.Height)
                    {
                        renderer.DrawRectangle(obj.Position, obj.Width, obj.Height, new Color(0.4f, 0.4f, 0.7f, 1.0f));
                    }
                }
                renderer.DrawString("Testing", _wendyOne, obj.Position, new Color(0.4f, 0.7f, 0.3f, 1.0f));
            }
        }

        private void _insertGameObject_Click(object sender, EventArgs e)
        {
            Point clientTerms = PointToClient(Cursor.Position);

            GameObject obj = new GameObject();
            obj.Position = new Vector2(clientTerms.X, clientTerms.Y);
            Vector2 size = _wendyOne.MeasureString("Testing");
            obj.Width = (int)size.X;
            obj.Height = (int) size.Y;
            CurrentScene.Objects.Add(obj);
        }
    }
}
 