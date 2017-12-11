using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Model
{
    public class Layer
    {
        public List<GameObject> Objects = new List<GameObject>();

        public string Name;
        public bool Visible = true;

        public Layer(string name)
        {
            Name = name;
        }
    }
}
