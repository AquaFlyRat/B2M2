using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Toolkit
{
    public class Vector2ChangedEventArgs : EventArgs
    {
        public float NewX { get; private set; }
        public float NewY { get; private set; }
        public bool InternalUpdate { get; private set; }
        public Vector2ChangedEventArgs(float x, float y, bool b)
        {
            NewX = x;
            NewY = y;
            InternalUpdate = b;
        }
    }
}
