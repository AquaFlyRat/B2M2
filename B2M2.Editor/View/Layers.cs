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
            listViewExtended1.ItemTextChanged += ListViewExtended1_ItemTextChanged;
            listViewExtended1.SelectedIndices.Add(0);
            listViewExtended1.SelectedIndicesChanged += ListViewExtended1_SelectedIndicesChanged;
        }

        private void ListViewExtended1_SelectedIndicesChanged(object sender, EventArgs e)
        {
            if (listViewExtended1.SelectedIndices.Count == 0)
                return;

            int selIndex = listViewExtended1.SelectedIndices[0];
            Scene.Current.CurrentLayer = Scene.Current.Layers.Where(a => a.ID == ((Layer)listViewExtended1.Items[selIndex].Tag).ID).FirstOrDefault();
        }

        private void ListViewExtended1_ItemTextChanged(object sender, ListItemChangedEventArgs e)
        {
            Scene currentScene = Scene.Current;
            foreach (Layer layer in currentScene.Layers)
            {
                if (layer.ID == ((Layer)e.Affected.Tag).ID)
                {
                    layer.Name = e.Affected.Text;
                }
            }
        }

        public ListViewExtended GetLayersList()
        {
            return listViewExtended1;
        }

        private void btnAddNewLayer_Click(object sender, EventArgs e)
        {
            string layerName = "New Layer";

            Layer backLayer = new Layer("Hello World!");
            
            ListViewItemExtended item = new ListViewItemExtended();
            item.Tag = backLayer;
            item.Text = layerName;
            item.Checked = true;
            listViewExtended1.Items.Add(item);

            Scene.Current.Layers.Add(backLayer);
        }

        private void btnRemoveLayer_Click(object sender, EventArgs e)
        {
            Layer atSelection = (Layer)listViewExtended1.Items[listViewExtended1.SelectedIndices[0]].Tag;

            if (Scene.Current.CurrentLayer == atSelection)
            {
                Scene.Current.CurrentLayer = null;
            }

            Scene.Current.Layers.Remove(atSelection);

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
