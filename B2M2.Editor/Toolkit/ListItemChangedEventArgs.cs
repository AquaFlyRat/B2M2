using Arch.Editor.Engine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Toolkit
{
    public class ListItemChangedEventArgs : EventArgs
    {
        public ListViewItemExtended Affected { get; private set; }

        public ListItemChangedEventArgs(ListViewItemExtended layer)
        {
            Affected = layer;
        }
    }
}
