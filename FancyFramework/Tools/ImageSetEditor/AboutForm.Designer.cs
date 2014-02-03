namespace ImageSetEditor
{
    partial class AboutForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.okButton = new System.Windows.Forms.Button();
            this.toProjectWebButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(166, 100);
            this.label1.TabIndex = 0;
            this.label1.Text = "ImageSetEditor\r\n\r\n版本 0.1.0\r\n作者 frimin\r\n邮箱 frimin@msn.com";
            // 
            // okButton
            // 
            this.okButton.Location = new System.Drawing.Point(397, 195);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(120, 32);
            this.okButton.TabIndex = 1;
            this.okButton.Text = "确定";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // toProjectWebButton
            // 
            this.toProjectWebButton.Location = new System.Drawing.Point(271, 195);
            this.toProjectWebButton.Name = "toProjectWebButton";
            this.toProjectWebButton.Size = new System.Drawing.Size(120, 32);
            this.toProjectWebButton.TabIndex = 2;
            this.toProjectWebButton.Text = "访问项目网页";
            this.toProjectWebButton.UseVisualStyleBackColor = true;
            this.toProjectWebButton.Click += new System.EventHandler(this.toProjectWebButton_Click);
            // 
            // AboutForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(529, 239);
            this.Controls.Add(this.toProjectWebButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AboutForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "关于";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button toProjectWebButton;
    }
}