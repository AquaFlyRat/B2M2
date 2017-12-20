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
        const int _arrowPadding = 6;
        private TriangleButton _expansionToggle = new TriangleButton();
        bool _isSectionExpanded = false;
        int _heightWhenLastExpanded = 0;

        [Category("Behaviour")]
        [Description("Does the section toggle button appear?")]
        public bool HasButton { get; set; } = false;

        public DarkCollapseSection()
        {
            Click += DarkCollapseSection_Click;
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);

            if (HasButton)
            {
                _expansionToggle = CreateToggleButton();
                Controls.Add(_expansionToggle);
            }
        }

        private int CalculateToggleButtonXPosition()
        {
            return Width - 20 - _arrowPadding;
        }

        private TriangleButton CreateToggleButton()
        {
            int w = 20, h = 10;
            TriangleButton toggleButton = new TriangleButton();
            toggleButton.Width = w;
            toggleButton.Height = h;

            toggleButton.Location = new Point(CalculateToggleButtonXPosition(), _arrowPadding);
            toggleButton.Anchor = AnchorStyles.Right | AnchorStyles.Top;
            toggleButton.MaximumSize = new Size(w, h);
            toggleButton.MinimumSize = new Size(w, h);
            toggleButton.Click += ToggleButtonClick;
            return toggleButton;
        }

        private void Redraw()
        {
            Invalidate();
            _expansionToggle.Invalidate();
        }

        private void DarkCollapseSection_Click(object sender, EventArgs e)
        {
            Focus();
            Redraw();
        }
        
        private void ToggleButtonClick(object sender, EventArgs e)
        {
            if (!HasButton) return;

            _isSectionExpanded = !_isSectionExpanded;

            if(_isSectionExpanded)
            {
                _expansionToggle.Direction = TriangleDirection.Downwards;
                _heightWhenLastExpanded = Size.Height;
                Height = 25;
            } else
            {
                _expansionToggle.Direction = TriangleDirection.Upwards;
                Height = _heightWhenLastExpanded;
            }

            Redraw();
            this.Parent.PerformLayout();
            foreach (Control child in Parent.Controls) child.Invalidate();
        }

        protected override void OnEnter(EventArgs e)
        {
            Focus();
            base.OnEnter(e);

            Redraw();
        }

        protected override void OnLeave(EventArgs e)
        {
            base.OnLeave(e);

            Redraw();
        }

        protected override void OnResize(EventArgs eventargs)
        {
            base.OnResize(eventargs);
            _expansionToggle.Location = new Point(CalculateToggleButtonXPosition(), _arrowPadding);

            Invalidate();
        }

        protected override void OnPaintBackground(PaintEventArgs e) { }

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

        [Category("Appearance")]
        [Description("The section header text associated with this control.")]
        public string SectionHeader
        {
            get
            {
                return _sectionHeader;
            }
            set
            {
                _sectionHeader = value;
                Invalidate();
            }
        }
    }
}
