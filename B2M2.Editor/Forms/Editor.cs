using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Forms;
using System.Runtime.InteropServices;

using System.Diagnostics;
using DarkUI.Win32;
using arch.Editor.Forms.Controls.Native;
using System.Drawing;

namespace CharlieEngine.Editor.Forms
{
    partial class Editor : Form
    {
        private Controls.RenderWindow _renderWindow = new Controls.RenderWindow();
        private static Controls.Properties _properties;
        public Editor()
        {
            InitializeComponent();

            WindowState = FormWindowState.Maximized;

            _properties = new Controls.Properties();

            Application.AddMessageFilter(new ControlScrollFilter());
            Application.AddMessageFilter(_dockPanel.DockContentDragFilter);
            Application.AddMessageFilter(_dockPanel.DockResizeFilter);
            
            _dockPanel.AddContent(_renderWindow);
            _dockPanel.AddContent(new Controls.ProjectExplorer());
            _dockPanel.AddContent(new Controls.Console());
            _dockPanel.AddContent(_properties);
        }

        public static Controls.Properties GetPropertiesWindow()
        {
            return _properties;
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnSubmitBug_Click(object sender, EventArgs e)
        {
            Process.Start("https://github.com/AquaFlyRat/arch/issues/new");
        }
    }
}
