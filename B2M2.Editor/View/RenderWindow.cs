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

using Arch.Editor.View.Native;
using Arch.Editor.Model;

using CharlieEngine;
using Arch.Editor.View.Interfaces;

namespace Arch.Editor.View
{
    public partial class RenderWindow : DarkDocument, IMapEditorView
    {
        public Scene CurrentScene = new Scene();
        private CharlieWindow _window = null;
        
        public event EventHandler<GameObjectCreatedArgs> OnObjectCreated;
        public event EventHandler<LeftClickArgs> OnLeftClick;
        public event EventHandler<CameraScrollArgs> OnCameraScroll;
        public event EventHandler<ViewportDrawArgs> OnViewportDraw;
        public event EventHandler OnCameraScrollStop;

        public GameObject SelectedObject { get; }
        public int ViewportWidth { get { return Width; } }
        public int ViewportHeight { get { return Height; } }
        public Renderer2D Renderer { get { return _window.GetRenderer(); } }

        public RenderWindow()
        {
            InitializeComponent();
            
            DockText = "Render Window";
            _window = new CharlieWindow(Width, Height, OnCharlieDraw);

            _window.Panel.MouseClick += Panel_MouseClick;
            _window.Panel.MouseUp += Panel_MouseUp;
            _window.Panel.MouseMove += Panel_MouseMove;
            _window.Panel.Resize += Panel_Resize;            


            _window.Show();

            // Apparantly we need both for this to work correctly... (by both I mean SetParent & Controls.Add)
            // Please don't touch or all hell starts to break loose.
            Win32.SetParent(_window.NativeWindow.GetHWND(), Handle);
            Controls.Add(_window.Panel);

            new Presenters.MapEditorPresenter(this, CurrentScene);
        }

        private void Panel_Resize(object sender, EventArgs e)
        {
            _window.NativeWindow.SetViewportSize(Width, Height);
            _window.GetRenderer().SetProjection(Matrix4.Orthographic(Width, 0, 0, Height, 1.0f, -1.0f));
        }

        private void Panel_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Middle)
            {
                OnCameraScroll?.Invoke(this, new CameraScrollArgs(new Vector2(e.Location.X, e.Location.Y)));
            }
        }

        private void Panel_MouseClick(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    Vector2 clickedPos = PointToClient(Cursor.Position).ToVector2();
                    OnLeftClick?.Invoke(this, new LeftClickArgs(clickedPos));
                    break;

                case MouseButtons.Right:
                    _contextMenu.Show(Parent.PointToScreen(e.Location));
                    break;
            };
        }

        private void Panel_MouseUp(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Middle)
            {
                OnCameraScrollStop?.Invoke(this, new EventArgs());
            }
        }

        private void OnCharlieDraw(Window window, Renderer2D renderer)
        {
            OnViewportDraw?.Invoke(this, new ViewportDrawArgs(renderer));
        }

        private void _insertGameObject_Click(object sender, EventArgs e)
        {
            Point cursorPosition = PointToClient(Cursor.Position);
            OnObjectCreated?.Invoke(this, new GameObjectCreatedArgs(cursorPosition.ToVector2()));
        }
    }
}
 