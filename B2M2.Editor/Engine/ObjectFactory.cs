using CharlieEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Engine
{
    class ObjectFactory
    {
        public const int DefaultWidth = 64;
        public const int DefaultHeight = 64;

        public GameObject CreateDefaultGameObject(Vector2 position)
        {
            GameObject obj = new GameObject(position, "New Game Object");
            obj.Width = DefaultWidth;
            obj.Height = DefaultHeight;
            obj.Scale = new Vector2(1, 1);
            obj.Rotation = 0.0f;

            return obj;
        }
    }
}
