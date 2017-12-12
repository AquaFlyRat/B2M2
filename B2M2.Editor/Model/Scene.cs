using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Model
{
    public class Scene
    {
        public List<Layer> Layers = new List<Layer>();
        
        public Scene()
        {
            Layers.Add(new Layer("Default"));
            CurrentLayer = Layers[0];
       }

        public List<Layer> GetVisible()
        {
            return Layers.Where(a => a.Visible).ToList();
        }

        public static Scene Current = new Scene();

        public Layer CurrentLayer { get; set; }
    }
}
