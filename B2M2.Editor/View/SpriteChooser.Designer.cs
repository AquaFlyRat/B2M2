namespace Arch.Editor.View
{
    partial class SpriteChooser
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lstSprites = new DarkUI.Controls.DarkListView();
            this.darkToolStrip1 = new DarkUI.Controls.DarkToolStrip();
            this.btnChoose = new System.Windows.Forms.ToolStripButton();
            this.btnCancel = new System.Windows.Forms.ToolStripButton();
            this.darkToolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lstSprites
            // 
            this.lstSprites.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstSprites.Location = new System.Drawing.Point(0, 28);
            this.lstSprites.Name = "lstSprites";
            this.lstSprites.Size = new System.Drawing.Size(256, 334);
            this.lstSprites.TabIndex = 0;
            this.lstSprites.Text = "s";
            // 
            // darkToolStrip1
            // 
            this.darkToolStrip1.AutoSize = false;
            this.darkToolStrip1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.darkToolStrip1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkToolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.btnChoose,
            this.btnCancel});
            this.darkToolStrip1.Location = new System.Drawing.Point(0, 0);
            this.darkToolStrip1.Name = "darkToolStrip1";
            this.darkToolStrip1.Padding = new System.Windows.Forms.Padding(5, 0, 1, 0);
            this.darkToolStrip1.Size = new System.Drawing.Size(256, 28);
            this.darkToolStrip1.TabIndex = 1;
            this.darkToolStrip1.Text = "darkToolStrip1";
            // 
            // btnChoose
            // 
            this.btnChoose.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btnChoose.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.btnChoose.Image = global::Arch.Editor.Properties.Resources.ok;
            this.btnChoose.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnChoose.Name = "btnChoose";
            this.btnChoose.Size = new System.Drawing.Size(23, 25);
            this.btnChoose.Text = "toolStripButton1";
            // 
            // btnCancel
            // 
            this.btnCancel.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btnCancel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.btnCancel.Image = global::Arch.Editor.Properties.Resources.cancel;
            this.btnCancel.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(23, 25);
            this.btnCancel.Text = "toolStripButton2";
            // 
            // SpriteChooser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(256, 362);
            this.Controls.Add(this.lstSprites);
            this.Controls.Add(this.darkToolStrip1);
            this.Name = "SpriteChooser";
            this.Text = "SpriteChooser";
            this.darkToolStrip1.ResumeLayout(false);
            this.darkToolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private DarkUI.Controls.DarkListView lstSprites;
        private DarkUI.Controls.DarkToolStrip darkToolStrip1;
        private System.Windows.Forms.ToolStripButton btnChoose;
        private System.Windows.Forms.ToolStripButton btnCancel;
    }
}