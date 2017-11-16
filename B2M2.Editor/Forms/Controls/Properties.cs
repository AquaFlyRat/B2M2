using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DarkUI.Docking;

namespace CharlieEngine.Editor.Forms.Controls
{
    public partial class Properties : DarkToolWindow
    {
        public Properties()
        {
            InitializeComponent();

            DockText = "Properties";
        }
    }
}
