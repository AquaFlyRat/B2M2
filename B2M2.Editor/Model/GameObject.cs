using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CharlieEngine;

namespace Arch.Editor.Model
{
    public class GameObject
    {
        private int _w, _h;

        public int Width
        {
            get
            {
                return (int)(_w * Scale.X);
            }
            set
            {
                _w = value;
            }
        }

        public int Height
        {
            get
            {
                return (int)(_h * Scale.Y);
            }
            set
            {
                _h = value;
            }
        }

        public Vector2 Position;
        public string Name;
        public Vector2 Scale;

        public float Rotation = 0.0f;

        public GameObject(Vector2 position, int width, int height, string name)
        {
            Position = position;
            Width = width;
            Height = height;
            Name = name;
            Scale = new Vector2(1, 1);
        }

        public GameObject(Vector2 position, string name)
        {
            Position = position;
            Name = name;
            Scale = new Vector2(1, 1);
        }
    }
}
