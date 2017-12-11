using Arch.Editor.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Toolkit
{
    public class ListItemCheckChangedEventArgs : EventArgs
    {
        public ListViewItemExtended Affected { get; private set; }

        public ListItemCheckChangedEventArgs(ListViewItemExtended layer)
        {
            Affected = layer;
        }
    }
}
