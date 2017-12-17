using CharlieEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Classes
{
    class MatrixUtils
    {
        public static Matrix4 RotateAroundPoint(Vector2 point, float angle)
        {
            Vector2 negative = new Vector2(point.X, point.Y);
            negative.X = -negative.X;
            negative.Y = -negative.Y;

            return Matrix4.Translate(point).Multiply(Matrix4.RotateZ(angle)).Multiply(Matrix4.Translate(negative));

        }
    }
}
