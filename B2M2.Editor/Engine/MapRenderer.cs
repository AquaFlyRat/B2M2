using CharlieEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Engine
{
    class MapRenderer
    {
        private Scene _scene;
        private Font _viewportFont;
        private GameObject _currentGameObject;

        public bool HighlightSelected = false;

        public Font CurrentFont
        {
            get
            {
                return _viewportFont;
            }
        }

        public GameObject SelectedGameObject
        {
            set
            {
                _currentGameObject = value;
            }
            get
            {
                return _currentGameObject;
            }
        }
        
        public MapRenderer(Scene scene, GameObject currentGameObject)
        {
            _viewportFont = new Font("Assets/WendyOne-Regular.ttf", 16);
            _currentGameObject = currentGameObject;
            _scene = scene;
        }

        private const float SelectionBoxThickness = 1.0f;

        public void Render(Renderer2D renderer)
        {
            Color objColor = new Color(0.6f, 0.4f, 0.9f, 1.0f);

            foreach (Layer layer in _scene.Layers)
            {
                foreach (GameObject obj in layer.Objects)
                {
                    Color col = new Color(0.5f, 0.5f, 0.5f, 1.0f);
                    if (SelectedGameObject == obj) col = new Color(0.9f, 0.9f, 0.9f, 1.0f);
                    renderer.DrawRectangle(
                        obj.Position,
                        obj.Width, obj.Height, 
                        col, new Vector2(1, 1), SelectionBoxThickness);
                    float strWidth = _viewportFont.MeasureString(obj.Name).X;
                    Vector2 namePos = new Vector2(obj.Position.X - strWidth, obj.Position.Y + obj.Height + 10);
                    namePos.X += (strWidth / 2) + (obj.Width / 2);
                    renderer.DrawString(obj.Name, _viewportFont, namePos, col);
                }
            }
         }
    }
}
