namespace ImageSetEditor.EditControl
{
    partial class ImagesetEditControl
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.splitContainer = new System.Windows.Forms.SplitContainer();
            this.imageSetBox = new System.Windows.Forms.PictureBox();
            this.vScrollBar1 = new System.Windows.Forms.VScrollBar();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.sizeSetToolStripComboBox = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.imageListSplitContainer = new System.Windows.Forms.SplitContainer();
            this.unusedListView = new System.Windows.Forms.ListView();
            this.usedListView = new System.Windows.Forms.ListView();
            this.unusedToolStrip = new System.Windows.Forms.ToolStrip();
            this.imageStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.clearMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.usedToolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.检查重叠ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.fitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
            this.splitContainer.Panel1.SuspendLayout();
            this.splitContainer.Panel2.SuspendLayout();
            this.splitContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageSetBox)).BeginInit();
            this.toolStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageListSplitContainer)).BeginInit();
            this.imageListSplitContainer.Panel1.SuspendLayout();
            this.imageListSplitContainer.Panel2.SuspendLayout();
            this.imageListSplitContainer.SuspendLayout();
            this.unusedToolStrip.SuspendLayout();
            this.usedToolStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer
            // 
            this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer.Location = new System.Drawing.Point(0, 0);
            this.splitContainer.Name = "splitContainer";
            // 
            // splitContainer.Panel1
            // 
            this.splitContainer.Panel1.Controls.Add(this.imageListSplitContainer);
            // 
            // splitContainer.Panel2
            // 
            this.splitContainer.Panel2.Controls.Add(this.imageSetBox);
            this.splitContainer.Panel2.Controls.Add(this.vScrollBar1);
            this.splitContainer.Panel2.Controls.Add(this.hScrollBar1);
            this.splitContainer.Panel2.Controls.Add(this.toolStrip);
            this.splitContainer.Size = new System.Drawing.Size(881, 530);
            this.splitContainer.SplitterDistance = 200;
            this.splitContainer.TabIndex = 0;
            // 
            // imageSetBox
            // 
            this.imageSetBox.BackColor = System.Drawing.Color.White;
            this.imageSetBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.imageSetBox.Location = new System.Drawing.Point(0, 27);
            this.imageSetBox.Name = "imageSetBox";
            this.imageSetBox.Size = new System.Drawing.Size(656, 482);
            this.imageSetBox.TabIndex = 2;
            this.imageSetBox.TabStop = false;
            this.imageSetBox.Paint += new System.Windows.Forms.PaintEventHandler(this.imageSetBox_Paint);
            // 
            // vScrollBar1
            // 
            this.vScrollBar1.Dock = System.Windows.Forms.DockStyle.Right;
            this.vScrollBar1.Location = new System.Drawing.Point(656, 27);
            this.vScrollBar1.Name = "vScrollBar1";
            this.vScrollBar1.Size = new System.Drawing.Size(21, 482);
            this.vScrollBar1.TabIndex = 1;
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hScrollBar1.Location = new System.Drawing.Point(0, 509);
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(677, 21);
            this.hScrollBar1.TabIndex = 0;
            // 
            // toolStrip
            // 
            this.toolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2,
            this.toolStripSeparator1,
            this.toolStripLabel1,
            this.sizeSetToolStripComboBox});
            this.toolStrip.Location = new System.Drawing.Point(0, 0);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.Size = new System.Drawing.Size(677, 27);
            this.toolStrip.TabIndex = 3;
            this.toolStrip.Text = "toolStrip1";
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(39, 24);
            this.toolStripLabel1.Text = "尺寸";
            // 
            // sizeSetToolStripComboBox
            // 
            this.sizeSetToolStripComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.sizeSetToolStripComboBox.FlatStyle = System.Windows.Forms.FlatStyle.Standard;
            this.sizeSetToolStripComboBox.Items.AddRange(new object[] {
            "64*64",
            "256*256",
            "512*512",
            "1024*1024",
            "2048*2048",
            "4096*4096"});
            this.sizeSetToolStripComboBox.Name = "sizeSetToolStripComboBox";
            this.sizeSetToolStripComboBox.Size = new System.Drawing.Size(121, 27);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // imageListSplitContainer
            // 
            this.imageListSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.imageListSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.imageListSplitContainer.Name = "imageListSplitContainer";
            this.imageListSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // imageListSplitContainer.Panel1
            // 
            this.imageListSplitContainer.Panel1.Controls.Add(this.unusedListView);
            this.imageListSplitContainer.Panel1.Controls.Add(this.unusedToolStrip);
            // 
            // imageListSplitContainer.Panel2
            // 
            this.imageListSplitContainer.Panel2.Controls.Add(this.usedToolStrip);
            this.imageListSplitContainer.Panel2.Controls.Add(this.usedListView);
            this.imageListSplitContainer.Size = new System.Drawing.Size(200, 530);
            this.imageListSplitContainer.SplitterDistance = 262;
            this.imageListSplitContainer.TabIndex = 0;
            // 
            // unusedListView
            // 
            this.unusedListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.unusedListView.Location = new System.Drawing.Point(0, 25);
            this.unusedListView.Name = "unusedListView";
            this.unusedListView.Size = new System.Drawing.Size(200, 237);
            this.unusedListView.TabIndex = 0;
            this.unusedListView.UseCompatibleStateImageBehavior = false;
            this.unusedListView.View = System.Windows.Forms.View.List;
            // 
            // usedListView
            // 
            this.usedListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.usedListView.Location = new System.Drawing.Point(0, 0);
            this.usedListView.Name = "usedListView";
            this.usedListView.Size = new System.Drawing.Size(200, 264);
            this.usedListView.TabIndex = 1;
            this.usedListView.UseCompatibleStateImageBehavior = false;
            this.usedListView.View = System.Windows.Forms.View.List;
            // 
            // unusedToolStrip
            // 
            this.unusedToolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.unusedToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.imageStripMenuItem});
            this.unusedToolStrip.Location = new System.Drawing.Point(0, 0);
            this.unusedToolStrip.Name = "unusedToolStrip";
            this.unusedToolStrip.Size = new System.Drawing.Size(200, 25);
            this.unusedToolStrip.TabIndex = 1;
            this.unusedToolStrip.Text = "toolStrip1";
            // 
            // imageStripMenuItem
            // 
            this.imageStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addMenuItem,
            this.addFolderToolStripMenuItem,
            this.toolStripSeparator2,
            this.clearMenuItem});
            this.imageStripMenuItem.Name = "imageStripMenuItem";
            this.imageStripMenuItem.Size = new System.Drawing.Size(126, 25);
            this.imageStripMenuItem.Text = "未使用的图片组";
            // 
            // addMenuItem
            // 
            this.addMenuItem.Name = "addMenuItem";
            this.addMenuItem.Size = new System.Drawing.Size(175, 24);
            this.addMenuItem.Text = "添加图片";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(172, 6);
            // 
            // clearMenuItem
            // 
            this.clearMenuItem.Name = "clearMenuItem";
            this.clearMenuItem.Size = new System.Drawing.Size(175, 24);
            this.clearMenuItem.Text = "清空图片组";
            // 
            // addFolderToolStripMenuItem
            // 
            this.addFolderToolStripMenuItem.Name = "addFolderToolStripMenuItem";
            this.addFolderToolStripMenuItem.Size = new System.Drawing.Size(175, 24);
            this.addFolderToolStripMenuItem.Text = "添加文件夹";
            // 
            // usedToolStrip
            // 
            this.usedToolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.usedToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.usedToolStrip.Location = new System.Drawing.Point(0, 0);
            this.usedToolStrip.Name = "usedToolStrip";
            this.usedToolStrip.Size = new System.Drawing.Size(200, 25);
            this.usedToolStrip.TabIndex = 2;
            this.usedToolStrip.Text = "toolStrip2";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.检查重叠ToolStripMenuItem,
            this.toolStripSeparator5,
            this.toolStripMenuItem4});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(126, 25);
            this.toolStripMenuItem1.Text = "已使用的图片组";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(172, 6);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(175, 24);
            this.toolStripMenuItem4.Text = "清空图片组";
            // 
            // 检查重叠ToolStripMenuItem
            // 
            this.检查重叠ToolStripMenuItem.Name = "检查重叠ToolStripMenuItem";
            this.检查重叠ToolStripMenuItem.Size = new System.Drawing.Size(175, 24);
            this.检查重叠ToolStripMenuItem.Text = "检查重叠";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fitToolStripMenuItem});
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(51, 27);
            this.toolStripMenuItem2.Text = "画布";
            // 
            // fitToolStripMenuItem
            // 
            this.fitToolStripMenuItem.Name = "fitToolStripMenuItem";
            this.fitToolStripMenuItem.Size = new System.Drawing.Size(175, 24);
            this.fitToolStripMenuItem.Text = "自动贴合";
            // 
            // ImagesetEditControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer);
            this.Name = "ImagesetEditControl";
            this.Size = new System.Drawing.Size(881, 530);
            this.Load += new System.EventHandler(this.ImagesetEditControl_Load);
            this.splitContainer.Panel1.ResumeLayout(false);
            this.splitContainer.Panel2.ResumeLayout(false);
            this.splitContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).EndInit();
            this.splitContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.imageSetBox)).EndInit();
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
            this.imageListSplitContainer.Panel1.ResumeLayout(false);
            this.imageListSplitContainer.Panel1.PerformLayout();
            this.imageListSplitContainer.Panel2.ResumeLayout(false);
            this.imageListSplitContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageListSplitContainer)).EndInit();
            this.imageListSplitContainer.ResumeLayout(false);
            this.unusedToolStrip.ResumeLayout(false);
            this.unusedToolStrip.PerformLayout();
            this.usedToolStrip.ResumeLayout(false);
            this.usedToolStrip.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer;
        private System.Windows.Forms.VScrollBar vScrollBar1;
        private System.Windows.Forms.HScrollBar hScrollBar1;
        private System.Windows.Forms.PictureBox imageSetBox;
        private System.Windows.Forms.ToolStrip toolStrip;
        private System.Windows.Forms.ToolStripComboBox sizeSetToolStripComboBox;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.SplitContainer imageListSplitContainer;
        private System.Windows.Forms.ListView unusedListView;
        private System.Windows.Forms.ListView usedListView;
        private System.Windows.Forms.ToolStrip unusedToolStrip;
        private System.Windows.Forms.ToolStripMenuItem imageStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem clearMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addFolderToolStripMenuItem;
        private System.Windows.Forms.ToolStrip usedToolStrip;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
        private System.Windows.Forms.ToolStripMenuItem 检查重叠ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem fitToolStripMenuItem;
    }
}
