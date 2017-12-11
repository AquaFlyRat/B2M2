using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DarkUI.Controls;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Collections.Specialized;
using System.Drawing;
using DarkUI.Config;

namespace Arch.Editor.Toolkit
{
    public class ListViewExtended : DarkScrollView
    {
        #region Event Region

        public event EventHandler SelectedIndicesChanged;

        #endregion

        #region Field Region

        private int _itemHeight = 20;
        private bool _multiSelect;

        private ObservableCollection<ListViewItemExtended> _items;
        private List<int> _selectedIndices;
        private int _anchoredItemStart = -1;
        private int _anchoredItemEnd = -1;
        private bool _labelEdit;
        private Timer _cursorFlash = new Timer();
        private Timer _waitingForStopTyping = new Timer();

        #endregion

        #region Property Region

        [Category("Behaviour")]
        [Description("Double clicking will enable edit mode on the selected item.")]
        [DefaultValue(false)]
        public bool LabelEdit
        {
            get { return _labelEdit;  }
            set { _labelEdit = value; }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ObservableCollection<ListViewItemExtended> Items
        {
            get { return _items; }
            set
            {
                if (_items != null)
                    _items.CollectionChanged -= Items_CollectionChanged;

                _items = value;

                _items.CollectionChanged += Items_CollectionChanged;

                UpdateListBox();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public List<int> SelectedIndices
        {
            get { return _selectedIndices; }
        }

        [Category("Appearance")]
        [Description("Determines the height of the individual list view items.")]
        [DefaultValue(20)]
        public int ItemHeight
        {
            get { return _itemHeight; }
            set
            {
                _itemHeight = value;
                UpdateListBox();
            }
        }

        [Category("Behaviour")]
        [Description("Determines whether multiple list view items can be selected at once.")]
        [DefaultValue(false)]
        public bool MultiSelect
        {
            get { return _multiSelect; }
            set { _multiSelect = value; }
        }

        #endregion

        #region Constructor Region

        private bool _cursorVisible = false;

        public ListViewExtended()
        {
            Items = new ObservableCollection<ListViewItemExtended>();
            _selectedIndices = new List<int>();
            _cursorFlash.Interval = 500;
            _cursorFlash.Tick += OnCursorFlash;

            _waitingForStopTyping.Interval = 300;
            _waitingForStopTyping.Tick += OnStopLabelTyping;
        }

        private void OnStopLabelTyping(object sender, EventArgs e)
        {
            _waitingForStopTyping.Stop();
            _cursorFlash.Start();
        }

        private void OnCursorFlash(object sender, EventArgs e)
        {
            _cursorVisible = !_cursorVisible;
            Invalidate();
        }

        #endregion

        #region Event Handler Region

        protected override void OnClick(EventArgs e)
        {
            
        }

        public event EventHandler<ListItemChangedEventArgs> CheckChanged;
        public event EventHandler<ListItemChangedEventArgs> ItemTextChanged;

        protected override void OnMouseClick(MouseEventArgs e)
        {
            var range = ItemIndexesInView().ToList();

            if (range.Count == 0)
                return;

            var top = range.Min();
            var bottom = range.Max();
            var pos = OffsetMousePosition;

            for (int i = 0; i <= Items.Count; i++)
            {
                Rectangle checkRect = new Rectangle(0, i * ItemHeight, Consts.CheckBoxSize+5, ItemHeight);
                if (checkRect.Contains(pos))
                {
                    Items[i].Checked = !Items[i].Checked;
                    CheckChanged?.Invoke(this, new ListItemChangedEventArgs(Items[i]));
                }
            }

            Invalidate();
            base.OnMouseClick(e);
        }

        private void Items_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                using (var g = CreateGraphics())
                {
                    // Set the area size of all new items
                    foreach (ListViewItemExtended item in e.NewItems)
                    {
                        item.TextChanged += Item_TextChanged;
                        UpdateItemSize(item, g);
                    }
                }

                // Find the starting index of the new item list and update anything past that
                if (e.NewStartingIndex < (Items.Count - 1))
                {
                    for (var i = e.NewStartingIndex; i <= Items.Count - 1; i++)
                    {
                        UpdateItemPosition(Items[i], i);
                    }
                }
            }

            if (e.OldItems != null)
            {
                foreach (ListViewItemExtended item in e.OldItems)
                    item.TextChanged -= Item_TextChanged;

                // Find the starting index of the old item list and update anything past that
                if (e.OldStartingIndex < (Items.Count - 1))
                {
                    for (var i = e.OldStartingIndex; i <= Items.Count - 1; i++)
                    {
                        UpdateItemPosition(Items[i], i);
                    }
                }
            }

            if (Items.Count == 0)
            {
                if (_selectedIndices.Count > 0)
                {
                    _selectedIndices.Clear();

                    if (SelectedIndicesChanged != null)
                        SelectedIndicesChanged(this, null);
                }
            }

            UpdateContentSize();
        }

        private void Item_TextChanged(object sender, EventArgs e)
        {
            var item = (ListViewItemExtended)sender;

            UpdateItemSize(item);
            UpdateContentSize(item);
            Invalidate();
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);

            if (Items.Count == 0)
                return;

            if (e.Button != MouseButtons.Left && e.Button != MouseButtons.Right)
                return;

            var pos = OffsetMousePosition;

            var range = ItemIndexesInView().ToList();

            var top = range.Min();
            var bottom = range.Max();
            var width = Math.Max(ContentSize.Width, Viewport.Width);
            bool foundItem = false;

            for (var i = top; i <= bottom; i++)
            {
                var rect = new Rectangle(0, i * ItemHeight, width, ItemHeight);

                if (rect.Contains(pos))
                {
                    if (MultiSelect && ModifierKeys == Keys.Shift)
                        SelectAnchoredRange(i);
                    else if (MultiSelect && ModifierKeys == Keys.Control)
                        ToggleItem(i);
                    else
                        SelectItem(i);
                }
            }

            if(!foundItem)
            {
                if(_editingIndex >= 0)
                {
                    StopEditing();
                }
            }
        }

        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            base.OnKeyPress(e);

            if(_editingIndex >= 0)
            {
                if(e.KeyChar == (char)Keys.Back)
                {
                    string text = Items[_editingIndex].Text;
                    if (text.Length > 0)
                    {
                        Items[_editingIndex].Text = text.Remove(text.Length - 1);
                    }
                } else
                {
                    Items[_editingIndex].Text += e.KeyChar;
                }
                ItemTextChanged?.Invoke(this, new ListItemChangedEventArgs(Items[_editingIndex]));
                _waitingForStopTyping.Start();
                _cursorVisible = true;
                _cursorFlash.Stop();

                Invalidate();
                Update();
            }
        }

        protected override void OnLostFocus(EventArgs e)
        {
            base.OnLostFocus(e);
            StopEditing();
        }

        private void StopEditing()
        {
            _editingIndex = -1;
            _cursorFlash.Stop();
        }

        private int _editingIndex = -1;

        protected override void OnMouseDoubleClick(MouseEventArgs e)
        {
            base.OnMouseDoubleClick(e);

            if (Items.Count == 0)
                return;

            if (e.Button != MouseButtons.Left)
                return;

            var pos = OffsetMousePosition;

            var range = ItemIndexesInView().ToList();

            var top = range.Min();
            var bottom = range.Max();
            var width = Math.Max(ContentSize.Width, Viewport.Width);

            for (var i = top; i <= bottom; i++)
            {
                var rect = new Rectangle(0, i * ItemHeight, width, ItemHeight);

                if (rect.Contains(pos))
                {
                    _editingIndex = i;
                    _cursorFlash.Start();
                }
            }
            Invalidate();
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);

            if (Items.Count == 0)
                return;

            if (_editingIndex >= 0)
            {
                if (e.KeyCode == Keys.Enter || e.KeyCode == Keys.Escape)
                {
                    StopEditing();
                    Invalidate();
                    return;
                }
            }

            if (e.KeyCode != Keys.Down && e.KeyCode != Keys.Up)
                return;


            if (MultiSelect && ModifierKeys == Keys.Shift)
            {
                if (e.KeyCode == Keys.Up)
                {
                    if (_anchoredItemEnd - 1 >= 0)
                    {
                        SelectAnchoredRange(_anchoredItemEnd - 1);
                        EnsureVisible();
                    }
                }
                else if (e.KeyCode == Keys.Down)
                {
                    if (_anchoredItemEnd + 1 <= Items.Count - 1)
                    {
                        SelectAnchoredRange(_anchoredItemEnd + 1);
                    }
                }
            }
            else
            {
                if (e.KeyCode == Keys.Up)
                {
                    if (_anchoredItemEnd - 1 >= 0)
                        SelectItem(_anchoredItemEnd - 1);
                }
                else if (e.KeyCode == Keys.Down)
                {
                    if (_anchoredItemEnd + 1 <= Items.Count - 1)
                        SelectItem(_anchoredItemEnd + 1);
                }
            }

            EnsureVisible();
        }

        #endregion

        #region Method Region

        public int GetItemIndex(ListViewItemExtended item)
        {
            return Items.IndexOf(item);
        }

        public void SelectItem(int index)
        {
            if (index < 0 || index > Items.Count - 1)
                throw new IndexOutOfRangeException($"Value '{index}' is outside of valid range.");

            _selectedIndices.Clear();
            _selectedIndices.Add(index);

            if (SelectedIndicesChanged != null)
                SelectedIndicesChanged(this, null);

            _anchoredItemStart = index;
            _anchoredItemEnd = index;

            Invalidate();
        }

        public void SelectItems(IEnumerable<int> indexes)
        {
            _selectedIndices.Clear();

            var list = indexes.ToList();

            foreach (var index in list)
            {
                if (index < 0 || index > Items.Count - 1)
                    throw new IndexOutOfRangeException($"Value '{index}' is outside of valid range.");

                _selectedIndices.Add(index);
            }

            if (SelectedIndicesChanged != null)
                SelectedIndicesChanged(this, null);

            _anchoredItemStart = list[list.Count - 1];
            _anchoredItemEnd = list[list.Count - 1];

            Invalidate();
        }

        public void ToggleItem(int index)
        {
            if (_selectedIndices.Contains(index))
            {
                _selectedIndices.Remove(index);

                // If we just removed both the anchor start AND end then reset them
                if (_anchoredItemStart == index && _anchoredItemEnd == index)
                {
                    if (_selectedIndices.Count > 0)
                    {
                        _anchoredItemStart = _selectedIndices[0];
                        _anchoredItemEnd = _selectedIndices[0];
                    }
                    else
                    {
                        _anchoredItemStart = -1;
                        _anchoredItemEnd = -1;
                    }
                }

                // If we just removed the anchor start then update it accordingly
                if (_anchoredItemStart == index)
                {
                    if (_anchoredItemEnd < index)
                        _anchoredItemStart = index - 1;
                    else if (_anchoredItemEnd > index)
                        _anchoredItemStart = index + 1;
                    else
                        _anchoredItemStart = _anchoredItemEnd;
                }

                // If we just removed the anchor end then update it accordingly
                if (_anchoredItemEnd == index)
                {
                    if (_anchoredItemStart < index)
                        _anchoredItemEnd = index - 1;
                    else if (_anchoredItemStart > index)
                        _anchoredItemEnd = index + 1;
                    else
                        _anchoredItemEnd = _anchoredItemStart;
                }
            }
            else
            {
                _selectedIndices.Add(index);
                _anchoredItemStart = index;
                _anchoredItemEnd = index;
            }

            if (SelectedIndicesChanged != null)
                SelectedIndicesChanged(this, null);

            Invalidate();
        }

        public void SelectItems(int startRange, int endRange)
        {
            _selectedIndices.Clear();

            if (startRange == endRange)
                _selectedIndices.Add(startRange);

            if (startRange < endRange)
            {
                for (var i = startRange; i <= endRange; i++)
                    _selectedIndices.Add(i);
            }
            else if (startRange > endRange)
            {
                for (var i = startRange; i >= endRange; i--)
                    _selectedIndices.Add(i);
            }

            SelectedIndicesChanged?.Invoke(this, null);

            Invalidate();
        }

        private void SelectAnchoredRange(int index)
        {
            _anchoredItemEnd = index;
            SelectItems(_anchoredItemStart, index);
        }

        private void UpdateListBox()
        {
            using (var g = CreateGraphics())
            {
                for (var i = 0; i <= Items.Count - 1; i++)
                {
                    var item = Items[i];
                    UpdateItemSize(item, g);
                    UpdateItemPosition(item, i);
                }
            }

            UpdateContentSize();
        }

        private void UpdateItemSize(ListViewItemExtended item)
        {
            using (var g = CreateGraphics())
            {
                UpdateItemSize(item, g);
            }
        }

        private void UpdateItemSize(ListViewItemExtended item, Graphics g)
        {
            var size = g.MeasureString(item.Text, Font);
            size.Width++;

            item.Area = new Rectangle(item.Area.Left, item.Area.Top, (int)size.Width, item.Area.Height);
        }

        private void UpdateItemPosition(ListViewItemExtended item, int index)
        {
            item.Area = new Rectangle(2, (index * ItemHeight), item.Area.Width, ItemHeight);
        }

        private void UpdateContentSize()
        {
            var highestWidth = 0;

            foreach (var item in Items)
            {
                if (item.Area.Right + 1 > highestWidth)
                    highestWidth = item.Area.Right + 1;
            }

            var width = highestWidth;
            var height = Items.Count * ItemHeight;

            if (ContentSize.Width != width || ContentSize.Height != height)
            {
                ContentSize = new Size(width, height);
                Invalidate();
            }
        }

        private void UpdateContentSize(ListViewItemExtended item)
        {
            var itemWidth = item.Area.Right + 1;

            if (itemWidth == ContentSize.Width)
            {
                UpdateContentSize();
                return;
            }

            if (itemWidth > ContentSize.Width)
            {
                ContentSize = new Size(itemWidth, ContentSize.Height);
                Invalidate();
            }
        }

        public void EnsureVisible()
        {
            if (SelectedIndices.Count == 0)
                return;

            var itemTop = -1;

            if (!MultiSelect)
                itemTop = SelectedIndices[0] * ItemHeight;
            else
                itemTop = _anchoredItemEnd * ItemHeight;

            var itemBottom = itemTop + ItemHeight;

            if (itemTop < Viewport.Top)
                VScrollTo(itemTop);

            if (itemBottom > Viewport.Bottom)
                VScrollTo((itemBottom - Viewport.Height));
        }

        private IEnumerable<int> ItemIndexesInView()
        {
            var top = (Viewport.Top / ItemHeight) - 1;

            if (top < 0)
                top = 0;

            var bottom = ((Viewport.Top + Viewport.Height) / ItemHeight) + 1;

            if (bottom > Items.Count)
                bottom = Items.Count;

            var result = Enumerable.Range(top, bottom - top);
            return result;
        }

        private IEnumerable<ListViewItemExtended> ItemsInView()
        {
            var indexes = ItemIndexesInView();
            var result = indexes.Select(index => Items[index]).ToList();
            return result;
        }

        #endregion

        #region Paint Region
        
        protected override void PaintContent(Graphics g)
        {
            var range = ItemIndexesInView().ToList();

            if (range.Count == 0)
                return;

            var top = range.Min();
            var bottom = range.Max();

            for (var i = top; i <= bottom; i++)
            {
                var width = Math.Max(ContentSize.Width, Viewport.Width);
                var rect = new Rectangle(0, i * ItemHeight, width, ItemHeight);

                // Background
                var odd = i % 2 != 0;
                var bgColor = !odd ? Colors.HeaderBackground : Colors.GreyBackground;

                if (SelectedIndices.Count > 0 && SelectedIndices.Contains(i))
                    bgColor = Focused ? Colors.BlueSelection : Colors.GreySelection;

                using (var b = new SolidBrush(bgColor))
                {
                    g.FillRectangle(b, rect);
                }

                // DEBUG: Border
                /*using (var p = new Pen(Colors.DarkBorder))
                {
                    g.DrawLine(p, new Point(rect.Left, rect.Bottom - 1), new Point(rect.Right, rect.Bottom - 1));
                }*/

                // Text
                using (var b = new SolidBrush(Items[i].TextColor))
                {
                    var stringFormat = new StringFormat
                    {
                        Alignment = StringAlignment.Near,
                        LineAlignment = StringAlignment.Center
                    };

                    var modFont = new Font(Font, Items[i].FontStyle);
                    var modRect = new Rectangle(rect.Left + 10 + Consts.CheckBoxSize, rect.Top, rect.Width, rect.Height);

                    StringFormat f = new StringFormat(StringFormat.GenericTypographic)
                    { FormatFlags = StringFormatFlags.MeasureTrailingSpaces };
                    
                    int w = (int)g.MeasureString(Items[i].Text, modFont, 512, f).Width;
                    Rectangle editingRect = new Rectangle(modRect.Left, modRect.Top+2, w+7, rect.Height-5);

                    if(Items[i].Text.Length == 0)
                    {
                        editingRect.Height = modRect.Height-5;

                    }

                    bool inEditMode = (_editingIndex == i);

                    if (inEditMode)
                    {
                        using (var txtBack = new SolidBrush(Colors.LightBackground))
                        {
                            g.FillRectangle(txtBack, editingRect);
                        }
                    }

                    g.DrawString(Items[i].Text, modFont, b, modRect, stringFormat);

                    if (inEditMode)
                    {
                        using (var foreColor = new Pen(Colors.LightText))
                        {
                            g.DrawRectangle(foreColor, editingRect);
                            if (_cursorVisible)
                            {
                                
                                //int x = (editingRect.X + w);
                                //g.DrawLine(Pens.Red,x, editingRect.Top + 2, x, editingRect.Bottom - 2);
                            }
                        }
                    }
                }

                int checkX = 3;
                int checkY = 3;

                var borderColor = Colors.LightText;
                using (var p = new Pen(borderColor))
                {
                    var boxRect = new Rectangle(checkX, (i * ItemHeight)+ checkY, Consts.CheckBoxSize, Consts.CheckBoxSize);

                    g.DrawRectangle(p, boxRect);
                }

                var fillColor = Colors.LightestBackground;
                if (Items[i].Checked)
                {
                    using (var b = new SolidBrush(fillColor))
                    {
                        Rectangle boxRect = new Rectangle(2 + checkX, (i * ItemHeight) + 2 + checkY, Consts.CheckBoxSize - 3, Consts.CheckBoxSize - 3);
                        g.FillRectangle(b, boxRect);
                    }
                }
            }
        }

        #endregion
    }
}
