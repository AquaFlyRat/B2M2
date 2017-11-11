using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using b2m2;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using WeifenLuo.WinFormsUI.Docking;

using B2M2.Editor.Forms.Native;
using System.Diagnostics;

namespace B2M2.Editor.Forms
{
    class Editor : Form
    {
        private MenuStrip menuStrip1;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem viewToolStripMenuItem;
        private ToolStripMenuItem helpToolStripMenuItem;
        private ToolStrip toolStrip1;
        private TreeView treeView1;
        Renderer2D _renderer = new Renderer2D();
        Font _wendyOne;
        
        public Editor()
        {
            RenderPanelWrapper wrapper = new RenderPanelWrapper(800, 600, Tick, 1000 / 60);
            _renderer.Initalize(Matrix4.Orthographic(800, 0, 0, 600, 1, -1));
            _wendyOne =  new Font("Assets/WendyOne-Regular.ttf", 38); ;
            Win32.SetParent(wrapper.NativeWindow.GetHWND(), Handle);
            Win32.ShowWindow(wrapper.NativeWindow.GetHWND(), 1);

            FormClosing += (object o, FormClosingEventArgs e) => { _renderer.Dispose(); };

            InitializeComponent();
        }

        private void Tick(Window window)
        {
            window.PollEvents();
            window.Clear();
            _renderer.Begin();
            _renderer.FillRectangle(new Vector2(100, 100), 100, 100, new Color(1, 0, 1, 1));
            _renderer.DrawString("Hello World!", _wendyOne, new Vector2(25, 300), new Color(1, 1, 1, 1));
            _renderer.End();
            _renderer.Present();
            window.SwapBuffers();
        }

        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(822, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.viewToolStripMenuItem.Text = "View";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // toolStrip1
            // 
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(822, 25);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Left;
            this.treeView1.Location = new System.Drawing.Point(0, 49);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(222, 428);
            this.treeView1.TabIndex = 2;
            // 
            // Editor
            // 
            this.ClientSize = new System.Drawing.Size(822, 477);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Editor";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
    }

    class Entry
    {
        [STAThread]
        public static void Main(string [] args)
        {
            Application.Run(new Editor());
        }
    }
}
