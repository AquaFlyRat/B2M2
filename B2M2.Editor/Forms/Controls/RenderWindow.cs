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
using B2M2.Editor.Forms.Controls.Native;

namespace B2M2.Editor.Forms.Controls
{
    public partial class RenderWindow : DarkDocument
    {
        public RenderWindow()
        {
            InitializeComponent();

            DockText = "Render Window";
            Native.CharlieWindow window = new Native.CharlieWindow();
            window.Show();

            // Apparantly we need both for this to work correctly...
            // Please don't touch or all hell starts to break loose.
            Win32.SetParent(window.NativeWindow.GetHWND(), Handle);
            Controls.Add(window.Panel);
        }
    }
}
