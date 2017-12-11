using Arch.Editor.Model;
using Arch.Editor.View.Interfaces;
using CharlieEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace Arch.Editor.Presenters
{
    class MapEditorPresenter
    {
        private IMapEditorView _view;
        
        private Font _viewportFont;
        private Vector2 _lastMousePosition;

        private GameObject _currentGameObject = new GameObject(new Vector2(), string.Empty);
        public GameObject CurrentGameObject
        {
            get
            {
                return _currentGameObject;
            }
            private set
            {
                View.Properties props = View.Editor.GetPropertiesWindow();
                props.Position.RemoveBindings();
                props.ObjectScale.RemoveBindings();
                _currentGameObject = value;

                if (_currentGameObject != null)
                {
                    props.Position.BindToVector2(_currentGameObject.Position);
                    props.ObjectScale.BindToVector2(_currentGameObject.Scale);
                    props.ObjectName.Text = _currentGameObject.Name;
                } else
                {
                    props.ObjectName.Text = string.Empty;
                }
            }
        }
        
        public MapEditorPresenter(IMapEditorView view, Scene scene)
        {
            _view = view;
            
            _view.OnObjectCreated += OnObjectCreated;
            _view.OnViewportDraw += OnViewportDraw;
            _view.OnCameraScroll += OnCameraScroll;
            _view.OnCameraScrollStop += OnCameraScrollStop;
            _view.OnLeftClick += OnViewportLeftClick;

            View.Properties props = View.Editor.GetPropertiesWindow();
            props.Position.BindToVector2(CurrentGameObject.Position);
            props.ObjectScale.BindToVector2(CurrentGameObject.Scale);
            
            props.ObjectName.TextChanged += ObjectName_TextChanged;
            _viewportFont = new Font("Assets/WendyOne-Regular.ttf", 38);

            View.Layers layers = View.Editor.GetLayersWindow();
            layers.GetLayersList().CheckChanged += MapEditorPresenter_CheckChanged;
        }

        private void MapEditorPresenter_CheckChanged(object sender, Toolkit.ListItemChangedEventArgs e)
        {
            Layer layer = Scene.Current.Layers.Where(a => a.ID == ((Layer)(e.Affected.Tag)).ID).FirstOrDefault();
            layer.Visible = e.Affected.Checked;
            CurrentGameObject = null;
        }

        private void ObjectName_TextChanged(object sender, EventArgs e)
        {
            View.Properties props = View.Editor.GetPropertiesWindow();

            if(_currentGameObject != null)
            {
                _currentGameObject.Name = props.ObjectName.Text;
                Vector2 stringSize = _viewportFont.MeasureString(_currentGameObject.Name);
                _currentGameObject.Width = (int)stringSize.X;
                _currentGameObject.Height = (int)stringSize.Y;
            }
        }
        
        private void OnViewportLeftClick(object sender, LeftClickArgs e)
        {
            Vector2 worldPos = _view.Renderer.UnProject(_view.ViewportWidth, _view.ViewportHeight, e.ClickedPoint);

            bool found = false;
            foreach (Layer layer in Scene.Current.GetVisible())
            {
                foreach (GameObject obj in layer.Objects)
                {
                    if (Classes.Collisions.ABBCheckInside(worldPos.X, worldPos.Y, obj))
                    {
                        CurrentGameObject = obj;
                        found = true;
                    }
                }
            }
            
            if(!found)
            {
                CurrentGameObject = null;
            }
        }

        private void OnCameraScrollStop(object sender, EventArgs e)
        {
            _lastMousePosition = null;
        }

        private void OnCameraScroll(object sender, CameraScrollArgs args)
        {
            if(_lastMousePosition == null)
            {
                _lastMousePosition = args.NewCursorPosition;
            }

            Vector2 offset = new Vector2(args.NewCursorPosition.X - _lastMousePosition.X,
                                         args.NewCursorPosition.Y - _lastMousePosition.Y);

            offset.X = -offset.X*0.75f;
            offset.Y = -offset.Y*0.75f;

            _view.Renderer.MoveCamera(offset);

            _lastMousePosition = args.NewCursorPosition;
        }

        private void OnViewportDraw(object sender, ViewportDrawArgs args)
        {
            Renderer2D renderer = args.Renderer;
            Color objColor = new Color(0.6f, 0.4f, 0.9f, 1.0f);

            foreach (Layer layer in Scene.Current.GetVisible())
            {
                foreach (GameObject obj in layer.Objects)
                {
                    renderer.DrawString(obj.Name, _viewportFont, obj.Position, objColor, obj.Scale);
                }
            }

            if(CurrentGameObject != null)
                renderer.DrawRectangle(CurrentGameObject.Position, CurrentGameObject.Width, CurrentGameObject.Height, new Color(1.0f, 1.0f, 1.0f, 1.0f));
        }

        private void OnObjectCreated(object sender, GameObjectCreatedArgs args)
        {
            Renderer2D renderer = _view.Renderer;
            Vector2 worldCoordinates = renderer.UnProject(_view.ViewportWidth, _view.ViewportHeight, args.CreatedAt);

            GameObject gameObject = new GameObject(worldCoordinates, "Alan!");

            Vector2 stringSize = _viewportFont.MeasureString(gameObject.Name);
            gameObject.Width  = (int)stringSize.X;
            gameObject.Height = (int)stringSize.Y;
            CurrentGameObject = gameObject;
            Scene.Current.Layers[0].Objects.Add(gameObject);
        }
    }
}
