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

            txtX.TextChanged += TxtX_TextChanged;
            txtY.TextChanged += TxtY_TextChanged;
        }

        private static Color InvalidValueForeColor = Color.IndianRed;
        private static Color DefaultLightForeColor = DarkUI.Config.Colors.LightText;

        private void HandleTextBoxTextChanges(ref DarkUI.Controls.DarkTextBox textBox, ref float element)
        {
            float newValue;
            bool validFloat = Single.TryParse(textBox.Text, out newValue);

            if(validFloat)
            {
                textBox.ForeColor = DefaultLightForeColor;
                element = newValue;
            } else
            {
                textBox.ForeColor = InvalidValueForeColor;
            }
        }

        private void TxtX_TextChanged(object sender, EventArgs e)
        {
            HandleTextBoxTextChanges(ref txtX, ref _x);
        }

        private void TxtY_TextChanged(object sender, EventArgs e)
        {
            HandleTextBoxTextChanges(ref txtY, ref _y);
        }

        public void BindToVector2(CharlieEngine.Vector2 vec2)
        {
            X = vec2.X;
            Y = vec2.Y;

            vec2.PropertyChanged += (object sender, PropertyChangedEventArgs e) =>
            {
                if(e.PropertyName == "X")
                {
                    X = vec2.X;
                } else if(e.PropertyName == "Y")
                {
                    Y = vec2.Y;
                }
            };
        }
    }
}
