using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arch.Editor.Toolkit
{
    public class ListViewItemExtended
    {
        public event EventHandler TextChanged;
        
        private string _text;

        public string Text
        {
            get { return _text; }
            set
            {
                _text = value;

                TextChanged?.Invoke(this, new EventArgs());
            }
        }

        public Rectangle Area { get; set; }

        public Color TextColor { get; set; }

        public FontStyle FontStyle { get; set; }

        public object Tag { get; set; }

        public bool Checked = false;

        public ListViewItemExtended()
        {
            TextColor = DarkUI.Config.Colors.LightText;
            FontStyle = FontStyle.Regular;
        }

        public ListViewItemExtended(string text)
            : this()
        {
            Text = text;
        }
    }
}
