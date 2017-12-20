using CharlieEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Engine
{
    class MatrixUtils
    {
        public static Matrix4 RotateAroundPoint(Vector2 point, float angle)
        {
            Vector2 negative = new Vector2(point.X, point.Y);
            negative.X = -negative.X;
            negative.Y = -negative.Y;
            
            var a = Matrix4.RotateZ(angle).Multiply(Matrix4.Translate(point));
            return a.Multiply(Matrix4.Translate(negative));
        }
    }
}
