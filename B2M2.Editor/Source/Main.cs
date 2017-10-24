using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using b2m2;

namespace B2M2.Editor.Source
{
    class cMain
    {
        public static void Main(string [] args)
        {
            WindowConfig config = new WindowConfig(800, 600, "Hello Dave, Feck off!");

            Window window = new Window(config);
            while(window.IsRunning)
            {
                window.PollEvents();
            }
        }
    }
}
