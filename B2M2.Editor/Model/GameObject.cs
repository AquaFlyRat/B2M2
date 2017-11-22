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
        public int Width, Height;
        public Vector2 Position;

        public string Name;

        public GameObject(Vector2 position, int width, int height, string name)
        {
            Position = position;
            Width = width;
            Height = height;
            Name = name;
        }

        public GameObject(Vector2 position, string name)
        {
            Position = position;
            Name = name;
        }
    }
}
