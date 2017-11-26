using System;
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
        private float _x, _y;

        public float X
        {
            get
            {
                return _x;
            }

            set
            {
                _x = value;
                txtX.Text = value.ToString();
            }
        }

        public float Y
        {
            get
            {
                return _y;
            }

            set
            {
                _y = value;
                txtY.Text = value.ToString();
            }
        }

        public Vector2()
        {
            InitializeComponent();
        }
    }
}
