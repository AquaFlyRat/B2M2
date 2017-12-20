using DarkUI.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Arch.Editor.View
{
    public partial class SpriteChooser : DarkForm
    {
        public SpriteChooser()
        {
            InitializeComponent();

            lstSprites.Items.Add(new DarkUI.Controls.DarkListItem("spr_dave"));
            lstSprites.Items.Add(new DarkUI.Controls.DarkListItem("spr_bob"));
            lstSprites.Items.Add(new DarkUI.Controls.DarkListItem("spr_harry"));

        }
    }
}
