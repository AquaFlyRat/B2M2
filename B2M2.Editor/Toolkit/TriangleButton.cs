using DarkUI.Config;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Arch.Editor.Toolkit
{
    enum TriangleDirection
    {
        Upwards, Downwards
    }

    class TriangleButton : Button
    {
        public TriangleDirection Direction = TriangleDirection.Upwards;
        public bool DrawFocusedBackground = false;

        protected override void OnLeave(System.EventArgs e)
        {
            base.OnLeave(e);
            Invalidate();
        }

        private void FillTriangle(Graphics g, Point pos, Size size, SolidBrush color)
        {
            Point[] point = new Point[3];
            switch(Direction)
            {
                case TriangleDirection.Downwards:
                    point[0] = pos;
                    point[1] = new Point(pos.X + (size.Width / 2), pos.Y + size.Height);
                    point[2] = new Point(pos.X + size.Width, pos.Y);
                    break;
                case TriangleDirection.Upwards:
                    point[0] = new Point(pos.X + (size.Width / 2), pos.Y);
                    point[1] = new Point(pos.X, pos.Y + size.Height);
                    point[2] = new Point(pos.X + size.Width, pos.Y + size.Height);
                    break;
            }

            g.FillPolygon(color, point);
        }
        
        protected override void OnPaint(PaintEventArgs pevent)
        {
            var rect = ClientRectangle;
            var bgColor = Parent.ContainsFocus ? Colors.BlueBackground : Colors.HeaderBackground;
            
            using (var b = new SolidBrush(bgColor))
            {
                pevent.Graphics.FillRectangle(b, rect);
            }
            pevent.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            using (var p = new SolidBrush(Colors.GreyHighlight))
            {
                FillTriangle(pevent.Graphics, rect.Location, new Size(Width, Height), p);
            }
        }

        public void Draw()
        {
            Refresh();
        }
    }
}
