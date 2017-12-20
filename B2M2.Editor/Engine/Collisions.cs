using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Arch.Editor.Engine;

namespace Arch.Editor.Engine
{
    public class Collisions
    {
        public static bool ABBCheckInside(float x, float y, GameObject obj)
        {
            return x < obj.Position.X + obj.Width && x > obj.Position.X &&
                   y < obj.Position.Y + obj.Height && y > obj.Position.Y;
        }
    }
}
