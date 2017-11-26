namespace Arch.Editor.View
{
    partial class Properties
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
            this.darkLabel1 = new DarkUI.Controls.DarkLabel();
            this.darkTextBox1 = new DarkUI.Controls.DarkTextBox();
            this.darkLabel2 = new DarkUI.Controls.DarkLabel();
            this.darkSectionPanel1 = new DarkUI.Controls.DarkSectionPanel();
            this.vector21 = new Arch.Editor.Toolkit.Vector2();
            this.darkSectionPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // darkLabel1
            // 
            this.darkLabel1.AutoSize = true;
            this.darkLabel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel1.Location = new System.Drawing.Point(6, 33);
            this.darkLabel1.Name = "darkLabel1";
            this.darkLabel1.Size = new System.Drawing.Size(35, 13);
            this.darkLabel1.TabIndex = 2;
            this.darkLabel1.Text = "Name";
            // 
            // darkTextBox1
            // 
            this.darkTextBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.darkTextBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.darkTextBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.darkTextBox1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkTextBox1.Location = new System.Drawing.Point(69, 30);
            this.darkTextBox1.Name = "darkTextBox1";
            this.darkTextBox1.Size = new System.Drawing.Size(196, 20);
            this.darkTextBox1.TabIndex = 3;
            this.darkTextBox1.Click += new System.EventHandler(this.darkTextBox1_Click);
            // 
            // darkLabel2
            // 
            this.darkLabel2.AutoSize = true;
            this.darkLabel2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel2.Location = new System.Drawing.Point(5, 29);
            this.darkLabel2.Name = "darkLabel2";
            this.darkLabel2.Size = new System.Drawing.Size(44, 13);
            this.darkLabel2.TabIndex = 0;
            this.darkLabel2.Text = "Position";
            // 
            // darkSectionPanel1
            // 
            this.darkSectionPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.darkSectionPanel1.Controls.Add(this.vector21);
            this.darkSectionPanel1.Controls.Add(this.darkLabel2);
            this.darkSectionPanel1.Location = new System.Drawing.Point(6, 56);
            this.darkSectionPanel1.Name = "darkSectionPanel1";
            this.darkSectionPanel1.SectionHeader = "Transformation";
            this.darkSectionPanel1.Size = new System.Drawing.Size(259, 114);
            this.darkSectionPanel1.TabIndex = 1;
            // 
            // vector21
            // 
            this.vector21.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.vector21.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.vector21.Location = new System.Drawing.Point(8, 45);
            this.vector21.Name = "vector21";
            this.vector21.Size = new System.Drawing.Size(247, 30);
            this.vector21.TabIndex = 1;
            this.vector21.X = 0F;
            this.vector21.Y = 0F;
            // 
            // Properties
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.darkTextBox1);
            this.Controls.Add(this.darkLabel1);
            this.Controls.Add(this.darkSectionPanel1);
            this.DefaultDockArea = DarkUI.Docking.DarkDockArea.Right;
            this.DockText = "Properties";
            this.Name = "Properties";
            this.Size = new System.Drawing.Size(272, 597);
            this.darkSectionPanel1.ResumeLayout(false);
            this.darkSectionPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private DarkUI.Controls.DarkLabel darkLabel1;
        private DarkUI.Controls.DarkTextBox darkTextBox1;
        private DarkUI.Controls.DarkLabel darkLabel2;
        private DarkUI.Controls.DarkSectionPanel darkSectionPanel1;
        private Toolkit.Vector2 vector21;
    }
}
