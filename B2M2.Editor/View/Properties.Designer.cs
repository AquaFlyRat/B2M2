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
            this.ObjectName = new DarkUI.Controls.DarkTextBox();
            this.darkCollapseSection1 = new Arch.Editor.Toolkit.DarkCollapseSection();
            this.vector21 = new Arch.Editor.Toolkit.Vector2();
            this.darkLabel4 = new DarkUI.Controls.DarkLabel();
            this.ObjectScale = new Arch.Editor.Toolkit.Vector2();
            this.darkLabel3 = new DarkUI.Controls.DarkLabel();
            this.Position = new Arch.Editor.Toolkit.Vector2();
            this.darkLabel2 = new DarkUI.Controls.DarkLabel();
            this.darkCollapseSection1.SuspendLayout();
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
            // ObjectName
            // 
            this.ObjectName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ObjectName.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.ObjectName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ObjectName.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.ObjectName.Location = new System.Drawing.Point(69, 30);
            this.ObjectName.Name = "ObjectName";
            this.ObjectName.Size = new System.Drawing.Size(307, 20);
            this.ObjectName.TabIndex = 3;
            this.ObjectName.Click += new System.EventHandler(this.darkTextBox1_Click);
            // 
            // darkCollapseSection1
            // 
            this.darkCollapseSection1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.darkCollapseSection1.Controls.Add(this.vector21);
            this.darkCollapseSection1.Controls.Add(this.darkLabel4);
            this.darkCollapseSection1.Controls.Add(this.ObjectScale);
            this.darkCollapseSection1.Controls.Add(this.darkLabel3);
            this.darkCollapseSection1.Controls.Add(this.Position);
            this.darkCollapseSection1.Controls.Add(this.darkLabel2);
            this.darkCollapseSection1.Location = new System.Drawing.Point(9, 56);
            this.darkCollapseSection1.Name = "darkCollapseSection1";
            this.darkCollapseSection1.SectionHeader = "Transformation";
            this.darkCollapseSection1.Size = new System.Drawing.Size(367, 225);
            this.darkCollapseSection1.TabIndex = 4;
            // 
            // vector21
            // 
            this.vector21.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.vector21.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.vector21.Location = new System.Drawing.Point(67, 89);
            this.vector21.Name = "vector21";
            this.vector21.Size = new System.Drawing.Size(296, 25);
            this.vector21.TabIndex = 6;
            this.vector21.X = 0F;
            this.vector21.Y = 0F;
            // 
            // darkLabel4
            // 
            this.darkLabel4.AutoSize = true;
            this.darkLabel4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel4.Location = new System.Drawing.Point(13, 92);
            this.darkLabel4.Name = "darkLabel4";
            this.darkLabel4.Size = new System.Drawing.Size(47, 13);
            this.darkLabel4.TabIndex = 5;
            this.darkLabel4.Text = "Rotation";
            // 
            // ObjectScale
            // 
            this.ObjectScale.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ObjectScale.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.ObjectScale.Location = new System.Drawing.Point(67, 60);
            this.ObjectScale.Name = "ObjectScale";
            this.ObjectScale.Size = new System.Drawing.Size(297, 30);
            this.ObjectScale.TabIndex = 4;
            this.ObjectScale.X = 0F;
            this.ObjectScale.Y = 0F;
            // 
            // darkLabel3
            // 
            this.darkLabel3.AutoSize = true;
            this.darkLabel3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel3.Location = new System.Drawing.Point(14, 64);
            this.darkLabel3.Name = "darkLabel3";
            this.darkLabel3.Size = new System.Drawing.Size(34, 13);
            this.darkLabel3.TabIndex = 3;
            this.darkLabel3.Text = "Scale";
            // 
            // Position
            // 
            this.Position.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Position.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.Position.Location = new System.Drawing.Point(67, 31);
            this.Position.Name = "Position";
            this.Position.Size = new System.Drawing.Size(297, 30);
            this.Position.TabIndex = 2;
            this.Position.X = 0F;
            this.Position.Y = 0F;
            // 
            // darkLabel2
            // 
            this.darkLabel2.AutoSize = true;
            this.darkLabel2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel2.Location = new System.Drawing.Point(14, 35);
            this.darkLabel2.Name = "darkLabel2";
            this.darkLabel2.Size = new System.Drawing.Size(44, 13);
            this.darkLabel2.TabIndex = 1;
            this.darkLabel2.Text = "Position";
            // 
            // Properties
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.darkCollapseSection1);
            this.Controls.Add(this.ObjectName);
            this.Controls.Add(this.darkLabel1);
            this.DefaultDockArea = DarkUI.Docking.DarkDockArea.Right;
            this.DockText = "Properties";
            this.Name = "Properties";
            this.Size = new System.Drawing.Size(383, 597);
            this.darkCollapseSection1.ResumeLayout(false);
            this.darkCollapseSection1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private DarkUI.Controls.DarkLabel darkLabel1;
        private Toolkit.DarkCollapseSection darkCollapseSection1;
        private DarkUI.Controls.DarkLabel darkLabel2;
        private DarkUI.Controls.DarkLabel darkLabel3;
        private Toolkit.Vector2 vector21;
        private DarkUI.Controls.DarkLabel darkLabel4;
        public Toolkit.Vector2 Position;
        public Toolkit.Vector2 ObjectScale;
        public DarkUI.Controls.DarkTextBox ObjectName;
    }
}
