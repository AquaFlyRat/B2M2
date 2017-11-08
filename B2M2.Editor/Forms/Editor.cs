using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using b2m2;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using WeifenLuo.WinFormsUI.Docking;

using B2M2.Editor.Forms.Native;

namespace B2M2.Editor.Forms
{
    class Editor : Form
    {
        private RenderWindow _window;

        public Editor()
        {
            IsMdiContainer = true;
            Size = new System.Drawing.Size(1280, 720);
            _window = new RenderWindow();
            _window.MdiParent = this;
            _window.Show();
        }
    }
    
    class Entry
    {
        [STAThread]
        public static void Main(string [] args)
        {
            Application.EnableVisualStyles();
            Application.Run(new Editor());
        }
    }
}
