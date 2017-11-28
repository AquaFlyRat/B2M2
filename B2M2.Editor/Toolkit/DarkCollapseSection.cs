using DarkUI.Config;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Arch.Editor.Toolkit
{
    public class DarkCollapseSection : Panel
    {
        private string _sectionHeader;

        [Category("Appearance")]
        [Description("The section header text associated with this control.")]
        public string SectionHeader
        {
            get { return _sectionHeader; }
            set
            {
                _sectionHeader = value;
                Invalidate();
            }
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            // Absorb event
        }

        int padding = 6;

        TriangleButton toggle = new TriangleButton();         
        public DarkCollapseSection()
        {
            Click += DarkCollapseSection_Click;
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            int w = 20, h = 10;
            toggle.Width = w;
            toggle.Height = h;
            
            toggle.Location = new Point(Width-20-padding, padding);
            toggle.Anchor = AnchorStyles.Right | AnchorStyles.Top;      
            toggle.MaximumSize = new Size(w, h);
            toggle.MinimumSize = new Size(w, h);
            toggle.Click += Toggle_Click;
            Controls.Add(toggle);
        }

        private void DarkCollapseSection_Click(object sender, EventArgs e)
        {
            Focus();
            Invalidate();
            toggle.Invalidate();
        }

        bool _isExpanded = false;
        int _lastHeight = 0;
        private void Toggle_Click(object sender, EventArgs e)
        {
            _isExpanded = !_isExpanded;

            if(_isExpanded)
            {
                toggle.Direction = TriangleDirection.Downwards;
                _lastHeight = Size.Height;
                Size = new Size(Width, 25);
            } else
            {
                toggle.Direction = TriangleDirection.Upwards;
                Height = _lastHeight;
            }
            toggle.Invalidate();
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            Focus();
        }

        protected override void OnEnter(System.EventArgs e)
        {
            Focus();
            base.OnEnter(e);

            Invalidate();
            toggle.Invalidate();
        }

        protected override void OnLeave(System.EventArgs e)
        {
            base.OnLeave(e);
            Invalidate();
            toggle.Invalidate();
        }

        protected override void OnResize(EventArgs eventargs)
        {
            toggle.Location = new Point(Width - 20-padding, padding);
            base.OnResize(eventargs);
            Invalidate();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            var g = e.Graphics;
            var rect = ClientRectangle;

            // Fill body
            using (var b = new SolidBrush(Colors.GreyBackground))
            {
                g.FillRectangle(b, rect);
            }

            // Draw header
            var bgColor = ContainsFocus ? Colors.BlueBackground : Colors.HeaderBackground;
            var darkColor = ContainsFocus ? Colors.DarkBlueBorder : Colors.DarkBorder;
            var lightColor = ContainsFocus ? Colors.LightBlueBorder : Colors.LightBorder;

            using (var b = new SolidBrush(bgColor))
            {
                var bgRect = new Rectangle(0, 0, rect.Width, 25);
                g.FillRectangle(b, bgRect);
            }

            using (var p = new Pen(darkColor))
            {
                g.DrawLine(p, rect.Left, 0, rect.Right, 0);
                g.DrawLine(p, rect.Left, 25 - 1, rect.Right, 25 - 1);
            }

            using (var p = new Pen(lightColor))
            {
                g.DrawLine(p, rect.Left, 1, rect.Right, 1);
            }
            
            var xOffset = 3;

            using (var b = new SolidBrush(Colors.LightText))
            {
                var textRect = new Rectangle(xOffset, 0, rect.Width - 4 - xOffset, 25);

                var format = new StringFormat
                {
                    Alignment = StringAlignment.Near,
                    LineAlignment = StringAlignment.Center,
                    FormatFlags = StringFormatFlags.NoWrap,
                    Trimming = StringTrimming.EllipsisCharacter
                };

                g.DrawString(SectionHeader, Font, b, textRect, format);
            }

            // Draw border
            using (var p = new Pen(Colors.DarkBorder, 1))
            {
                var modRect = new Rectangle(rect.Left, rect.Top, rect.Width - 1, rect.Height - 1);

                g.DrawRectangle(p, modRect);
            }

        }
    }
}
