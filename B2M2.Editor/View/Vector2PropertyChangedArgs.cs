using CharlieEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.View
{
    public class Vector2PropertyChangedArgs : EventArgs
    {
        public Vector2 NewValue { get; }

        public Vector2PropertyChangedArgs(Vector2 newValue)
        {
            NewValue = newValue;
        }
    }

}
