using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Arch.Editor.View
{
    public partial class Layers : DarkUI.Docking.DarkToolWindow
    {
        public Layers()
        {
            InitializeComponent();

            DockArea = DarkUI.Docking.DarkDockArea.Right;
            DockText = "Layers";
            listViewExtended1.Items.Add(new Toolkit.ListViewItemExtended("Hello World!"));
            listViewExtended1.Items.Add(new Toolkit.ListViewItemExtended("Hello World!"));
            listViewExtended1.Items.Add(new Toolkit.ListViewItemExtended("Hello World!"));

        }

        private void btnAddNewLayer_Click(object sender, EventArgs e)
        {
            listViewExtended1.Items.Add(new Toolkit.ListViewItemExtended("Hello World!"));
        }
    }
}
