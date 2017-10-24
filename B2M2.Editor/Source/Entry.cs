using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using b2m2;

namespace B2M2.Editor.Source
{
    class Entry
    {
        public static void Main(string [] args)
        {
            WindowConfig config = new WindowConfig(800, 600, "B2M2 Engine!");

            Window window = new Window(config);
            Console.WriteLine(window.GLMajor + ", " + window.GLMinor);

            while(window.IsRunning)
            {
                window.PollEvents();
            }
        }
    }
}
