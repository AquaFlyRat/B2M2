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

using CharlieEngine;

namespace Arch.Editor.View
{
    public partial class Properties : DarkToolWindow
    {
        public Properties()
        {
            InitializeComponent();

            DockText = "Properties";
        }

        private void darkTextBox1_Click(object sender, EventArgs e)
        {
            darkSectionPanel1.Select();
            darkTextBox1.Select();
        }
    }
}
