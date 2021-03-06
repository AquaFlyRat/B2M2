﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Forms;
using System.Runtime.InteropServices;

using System.Diagnostics;
using DarkUI.Win32;
using Arch.Editor.View.Native;
using System.Drawing;

namespace Arch.Editor.View
{
    partial class Editor : Form
    {
        private RenderWindow _renderWindow;
        private static Properties _properties;
        private static Layers _layers;

        public Editor()
        {
            InitializeComponent();

            WindowState = FormWindowState.Maximized;
            
            _layers = new Layers();
            _properties = new Properties();
            _renderWindow = new RenderWindow();

            Application.AddMessageFilter(new ControlScrollFilter());
            Application.AddMessageFilter(_dockPanel.DockContentDragFilter);
            Application.AddMessageFilter(_dockPanel.DockResizeFilter);
            
            _dockPanel.AddContent(_properties);
            _properties.DockRegion.Width = 383;

            _dockPanel.AddContent(_renderWindow);
            _dockPanel.AddContent(new ProjectExplorer());
            _dockPanel.AddContent(new OutputWindow());
            _dockPanel.AddContent(_layers);
        }

        public static Properties GetPropertiesWindow()
        {
            return _properties;
        }

        public static Layers GetLayersWindow()
        {
            return _layers;
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
