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
                if (_data != null)
                    _data.X = value;
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
                if (_data != null)
                    _data.Y = value;
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

        private bool _updateOnDataChange = true;

        private void TxtX_TextChanged(object sender, EventArgs e)
        {
            HandleTextBoxTextChanges(ref txtX, ref _x);

            if (_data != null)
            {
                _updateOnDataChange = false;
                _data.X = _x;
                _updateOnDataChange = true;
            }
        }

        private void TxtY_TextChanged(object sender, EventArgs e)
        {
            HandleTextBoxTextChanges(ref txtY, ref _y);
            if (_data != null)
            {
                _updateOnDataChange = false;
                _data.Y = _y;
                _updateOnDataChange = true;
            }
        }

        private CharlieEngine.Vector2 _data;

        private void EngineValueChanged(object sender, PropertyChangedEventArgs e)
        {
            if (!_updateOnDataChange)
                return;

            if (e.PropertyName == "X")
            {
                X = _data.X;
            }
            else if (e.PropertyName == "Y")
            {
                Y = _data.Y;
            }
        }

        public void BindToVector2(CharlieEngine.Vector2 vec2)
        {
            _data = vec2;
            X = vec2.X;
            Y = vec2.Y;

            vec2.PropertyChanged += EngineValueChanged;
        }

        public void RemoveBindings()
        {
            if (_data != null)
            {
                _data.PropertyChanged -= EngineValueChanged;
                _data = null;
            }
            X = 0;
            Y = 0;
        }
    }
}
