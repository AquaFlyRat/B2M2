using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Arch.Editor.Model;
using Arch.Editor.Toolkit;

namespace Arch.Editor.View
{
    public partial class Layers : DarkUI.Docking.DarkToolWindow
    {
        public Layers()
        {
            InitializeComponent();

            DockArea = DarkUI.Docking.DarkDockArea.Right;
            DockText = "Layers";

            Scene currentScene = Scene.Current;
            foreach(Layer layer in currentScene.Layers)
            {
                ListViewItemExtended item = new ListViewItemExtended();
                item.Tag = layer;
                item.Text = layer.Name;
                item.Checked = true;
                listViewExtended1.Items.Add(item);
            }

            listViewExtended1.SelectedIndices.Add(0);
        }

        public ListViewExtended GetLayersList()
        {
            return listViewExtended1;
        }

        private void btnAddNewLayer_Click(object sender, EventArgs e)
        {
            listViewExtended1.Items.Add(new Toolkit.ListViewItemExtended("Hello World!"));
        }

        private void btnRemoveLayer_Click(object sender, EventArgs e)
        {
            foreach (int index in listViewExtended1.SelectedIndices.ToList())
            {
                if (index < listViewExtended1.Items.Count && index >= 0)
                {
                    listViewExtended1.Items.RemoveAt(index);
                }
            }
        }
    }
}
