﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Arch.Editor.Toolkit
{
    public partial class Vector2 : DarkUserControl
    {
        private CharlieEngine.Vector2 _value = new CharlieEngine.Vector2();
        public Vector2()
        {
            InitializeComponent();
        }
    }
}
