using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Forms;
using System.Runtime.InteropServices;

using System.Diagnostics;
using DarkUI.Win32;
using B2M2.Editor.Forms.Controls.Native;
using System.Drawing;

namespace B2M2.Editor.Forms
{
    partial class Editor : Form
    {
        private Controls.RenderWindow _renderWindow = new Controls.RenderWindow();

        public Editor()
        {
            InitializeComponent();

            WindowState = FormWindowState.Maximized;

            Application.AddMessageFilter(new ControlScrollFilter());
            Application.AddMessageFilter(_dockPanel.DockContentDragFilter);
            Application.AddMessageFilter(_dockPanel.DockResizeFilter);
            
            _dockPanel.AddContent(_renderWindow);
            _dockPanel.AddContent(new Controls.ProjectExplorer());
            _dockPanel.AddContent(new Controls.Console());
        }
    }
}
