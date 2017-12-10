namespace Arch.Editor.View
{
    partial class Layers
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.listViewExtended1 = new Arch.Editor.Toolkit.ListViewExtended();
            this.darkToolStrip1 = new DarkUI.Controls.DarkToolStrip();
            this.btnAddNewLayer = new System.Windows.Forms.ToolStripButton();
            this.darkToolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // listViewExtended1
            // 
            this.listViewExtended1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listViewExtended1.Location = new System.Drawing.Point(0, 53);
            this.listViewExtended1.Name = "listViewExtended1";
            this.listViewExtended1.Size = new System.Drawing.Size(309, 138);
            this.listViewExtended1.TabIndex = 0;
            this.listViewExtended1.Text = "listViewExtended1";
            // 
            // darkToolStrip1
            // 
            this.darkToolStrip1.AutoSize = false;
            this.darkToolStrip1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.darkToolStrip1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkToolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.btnAddNewLayer});
            this.darkToolStrip1.Location = new System.Drawing.Point(0, 25);
            this.darkToolStrip1.Name = "darkToolStrip1";
            this.darkToolStrip1.Padding = new System.Windows.Forms.Padding(5, 0, 1, 0);
            this.darkToolStrip1.Size = new System.Drawing.Size(309, 28);
            this.darkToolStrip1.TabIndex = 1;
            this.darkToolStrip1.Text = "darkToolStrip1";
            // 
            // btnAddNewLayer
            // 
            this.btnAddNewLayer.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btnAddNewLayer.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.btnAddNewLayer.Image = global::Arch.Editor.Properties.Resources.edit_tool;
            this.btnAddNewLayer.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnAddNewLayer.Name = "btnAddNewLayer";
            this.btnAddNewLayer.Size = new System.Drawing.Size(24, 24);
            this.btnAddNewLayer.Text = "toolStripButton1";
            this.btnAddNewLayer.Click += new System.EventHandler(this.btnAddNewLayer_Click);
            // 
            // Layers
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.listViewExtended1);
            this.Controls.Add(this.darkToolStrip1);
            this.Name = "Layers";
            this.Size = new System.Drawing.Size(309, 191);
            this.darkToolStrip1.ResumeLayout(false);
            this.darkToolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private Toolkit.ListViewExtended listViewExtended1;
        private DarkUI.Controls.DarkToolStrip darkToolStrip1;
        private System.Windows.Forms.ToolStripButton btnAddNewLayer;
    }
}
