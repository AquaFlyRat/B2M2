﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DarkUI.Docking;

namespace Arch.Editor.View
{
    public partial class ProjectExplorer : DarkToolWindow
    {
        public ProjectExplorer()
        {
            InitializeComponent();

            DockText = "Project Explorer";
            DefaultDockArea = DarkDockArea.Left;

        }
    }
}
