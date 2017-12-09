﻿using Arch.Editor.Model;
using Arch.Editor.View.Interfaces;
using CharlieEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Presenters
{
    class MapEditorPresenter
    {
        private IMapEditorView _view;
        private Scene _scene;

        private Font _viewportFont;

        private Vector2 _lastMousePosition;
        private GameObject _currentGameObject = null;

        public MapEditorPresenter(IMapEditorView view, Scene scene)
        {
            _view = view;
            _scene = scene;

            _view.OnObjectCreated += OnObjectCreated;
            _view.OnViewportDraw += OnViewportDraw;
            _view.OnCameraScroll += OnCameraScroll;
            _view.OnCameraScrollStop += OnCameraScrollStop;

            _viewportFont = new Font("Assets/WendyOne-Regular.ttf", 38);
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

            offset.X = -offset.X;
            offset.Y = -offset.Y;

            _view.Renderer.MoveCamera(offset);

            _lastMousePosition = args.NewCursorPosition;
        }

        private void OnViewportDraw(object sender, ViewportDrawArgs args)
        {
            Renderer2D renderer = args.Renderer;
            Color objColor = new Color(0.6f, 0.4f, 0.9f, 1.0f);

            foreach(GameObject obj in _scene.Objects) 
            {
                renderer.DrawString(obj.Name, _viewportFont, obj.Position, objColor);
            }
        }

        private void OnObjectCreated(object sender, GameObjectCreatedArgs args)
        {
            if(_currentGameObject != null)
            {
                _currentGameObject.Position.X += 20;
                _currentGameObject.Position.Y += 20;
                return;
            }

            Renderer2D renderer = _view.Renderer;
            Vector2 worldCoordinates = renderer.UnProject(_view.ViewportWidth, _view.ViewportHeight, args.CreatedAt);

            GameObject gameObject = new GameObject(worldCoordinates, "Alan!");

            Vector2 stringSize = _viewportFont.MeasureString(gameObject.Name);
            gameObject.Width  = (int)stringSize.X;
            gameObject.Height = (int)stringSize.Y;

            View.Properties props = View.Editor.GetPropertiesWindow();
            props.Position.BindToVector2(gameObject.Position);
            _currentGameObject = gameObject;
        
            _scene.Objects.Add(gameObject);
        }
    }
}
