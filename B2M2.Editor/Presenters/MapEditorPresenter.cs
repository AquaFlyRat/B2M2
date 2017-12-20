using Arch.Editor.Engine;
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
        
        private Vector2 _lastMousePosition;
        private MapRenderer _renderer;

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
                props.Rotation = 0.0f;

                _currentGameObject = value;

                if (_currentGameObject != null)
                {
                    props.Position.BindToVector2(_currentGameObject.Position);
                    props.ObjectScale.BindToVector2(_currentGameObject.Scale);
                    props.ObjectName.Text = _currentGameObject.Name;
                    props.Rotation = props.Rotation;
                }
                else
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
            props.txtAngle.TextChanged += TxtAngle_TextChanged;

            _renderer = new MapRenderer(Scene.Current, CurrentGameObject);

            View.Layers layers = View.Editor.GetLayersWindow();
            layers.GetLayersList().CheckChanged += MapEditorPresenter_CheckChanged;
        }

        private void TxtAngle_TextChanged(object sender, EventArgs e)
        {
            View.Properties props = View.Editor.GetPropertiesWindow();

            float newValue;
            if(Single.TryParse(props.txtAngle.Text, out newValue))
            {
                CurrentGameObject.Rotation = newValue;
            }
        }

        private void MapEditorPresenter_CheckChanged(object sender, Toolkit.ListItemChangedEventArgs e)
        {
            Layer layer = Scene.Current.Layers.Where(a => a.ID == ((Layer)(e.Affected.Tag)).ID).FirstOrDefault();
            layer.Visible = e.Affected.Checked;
            ClearSelectedObject();
        }

        private void ObjectName_TextChanged(object sender, EventArgs e)
        {
            View.Properties props = View.Editor.GetPropertiesWindow();

            if(_currentGameObject != null)
            {
                _currentGameObject.Name = props.ObjectName.Text;
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
                    if (Engine.Collisions.ABBCheckInside(worldPos.X, worldPos.Y, obj))
                    {
                        AssignSelectedObject(obj);
                        found = true;
                    }
                }
            }
            
            if(!found)
            {
                ClearSelectedObject();
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

        private void AssignSelectedObject(GameObject current)
        {
            _renderer.HighlightSelected = true;
            _renderer.SelectedGameObject = current;
            CurrentGameObject = current;
        }

        private void ClearSelectedObject()
        {
            _renderer.HighlightSelected = false;
            _renderer.SelectedGameObject = null;
            CurrentGameObject = null;
        }

        private void OnViewportDraw(object sender, ViewportDrawArgs args)
        {
            _renderer.Render(args.Renderer);
        }

        private void OnObjectCreated(object sender, GameObjectCreatedArgs args)
        {
            if (Scene.Current.CurrentLayer == null)
                return;
            Renderer2D renderer = _view.Renderer;

            Vector2 worldCoordinates = renderer.UnProject(_view.ViewportWidth, _view.ViewportHeight, args.CreatedAt);

            GameObject obj = new ObjectFactory().CreateDefaultGameObject(worldCoordinates);
            AssignSelectedObject(obj);
            Scene.Current.CurrentLayer.Objects.Add(obj);
        }
    }
}
