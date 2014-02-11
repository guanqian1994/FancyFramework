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
            this.components = new System.ComponentModel.Container();
            this.splitContainer = new System.Windows.Forms.SplitContainer();
            this.imageListSplitContainer = new System.Windows.Forms.SplitContainer();
            this.unusedListView = new System.Windows.Forms.ListView();
            this.unusedImageContextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.enableToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.delImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.unusedToolStrip = new System.Windows.Forms.ToolStrip();
            this.imageStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addImageMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.clearMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.usedListView = new System.Windows.Forms.ListView();
            this.unsedImageContextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.disableToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.delusedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.usedToolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.检查重叠ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.clearUsedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageSetBox = new System.Windows.Forms.PictureBox();
            this.vScrollBar1 = new System.Windows.Forms.VScrollBar();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.fitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.sizeSetToolStripComboBox = new System.Windows.Forms.ToolStripComboBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
            this.splitContainer.Panel1.SuspendLayout();
            this.splitContainer.Panel2.SuspendLayout();
            this.splitContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageListSplitContainer)).BeginInit();
            this.imageListSplitContainer.Panel1.SuspendLayout();
            this.imageListSplitContainer.Panel2.SuspendLayout();
            this.imageListSplitContainer.SuspendLayout();
            this.unusedImageContextMenuStrip.SuspendLayout();
            this.unusedToolStrip.SuspendLayout();
            this.unsedImageContextMenuStrip.SuspendLayout();
            this.usedToolStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageSetBox)).BeginInit();
            this.toolStrip.SuspendLayout();
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
            this.imageListSplitContainer.Panel2.Controls.Add(this.usedListView);
            this.imageListSplitContainer.Panel2.Controls.Add(this.usedToolStrip);
            this.imageListSplitContainer.Size = new System.Drawing.Size(200, 530);
            this.imageListSplitContainer.SplitterDistance = 218;
            this.imageListSplitContainer.TabIndex = 0;
            // 
            // unusedListView
            // 
            this.unusedListView.ContextMenuStrip = this.unusedImageContextMenuStrip;
            this.unusedListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.unusedListView.Location = new System.Drawing.Point(0, 25);
            this.unusedListView.Name = "unusedListView";
            this.unusedListView.Size = new System.Drawing.Size(200, 193);
            this.unusedListView.TabIndex = 0;
            this.unusedListView.UseCompatibleStateImageBehavior = false;
            this.unusedListView.View = System.Windows.Forms.View.List;
            this.unusedListView.KeyUp += new System.Windows.Forms.KeyEventHandler(this.unusedListView_KeyUp);
            // 
            // unusedImageContextMenuStrip
            // 
            this.unusedImageContextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.enableToolStripMenuItem,
            this.toolStripMenuItem3,
            this.delImageToolStripMenuItem});
            this.unusedImageContextMenuStrip.Name = "unusedImageContextMenuStrip";
            this.unusedImageContextMenuStrip.Size = new System.Drawing.Size(109, 58);
            // 
            // enableToolStripMenuItem
            // 
            this.enableToolStripMenuItem.Name = "enableToolStripMenuItem";
            this.enableToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.enableToolStripMenuItem.Text = "启用";
            this.enableToolStripMenuItem.Click += new System.EventHandler(this.enableToolStripMenuItem_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(105, 6);
            // 
            // delImageToolStripMenuItem
            // 
            this.delImageToolStripMenuItem.Name = "delImageToolStripMenuItem";
            this.delImageToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.delImageToolStripMenuItem.Text = "删除";
            this.delImageToolStripMenuItem.Click += new System.EventHandler(this.delImageToolStripMenuItem_Click);
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
            this.addImageMenuItem,
            this.toolStripSeparator2,
            this.clearMenuItem});
            this.imageStripMenuItem.Name = "imageStripMenuItem";
            this.imageStripMenuItem.Size = new System.Drawing.Size(111, 25);
            this.imageStripMenuItem.Text = "未使用的图片";
            // 
            // addImageMenuItem
            // 
            this.addImageMenuItem.Name = "addImageMenuItem";
            this.addImageMenuItem.Size = new System.Drawing.Size(153, 24);
            this.addImageMenuItem.Text = "添加图片";
            this.addImageMenuItem.Click += new System.EventHandler(this.addImageMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(150, 6);
            // 
            // clearMenuItem
            // 
            this.clearMenuItem.Name = "clearMenuItem";
            this.clearMenuItem.Size = new System.Drawing.Size(153, 24);
            this.clearMenuItem.Text = "清空图片组";
            this.clearMenuItem.Click += new System.EventHandler(this.clearMenuItem_Click);
            // 
            // usedListView
            // 
            this.usedListView.ContextMenuStrip = this.unsedImageContextMenuStrip;
            this.usedListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.usedListView.Location = new System.Drawing.Point(0, 25);
            this.usedListView.Name = "usedListView";
            this.usedListView.Size = new System.Drawing.Size(200, 283);
            this.usedListView.TabIndex = 1;
            this.usedListView.UseCompatibleStateImageBehavior = false;
            this.usedListView.View = System.Windows.Forms.View.List;
            this.usedListView.KeyUp += new System.Windows.Forms.KeyEventHandler(this.usedListView_KeyUp);
            // 
            // unsedImageContextMenuStrip
            // 
            this.unsedImageContextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.disableToolStripMenuItem,
            this.toolStripSeparator3,
            this.delusedToolStripMenuItem});
            this.unsedImageContextMenuStrip.Name = "unusedImageContextMenuStrip";
            this.unsedImageContextMenuStrip.Size = new System.Drawing.Size(109, 58);
            // 
            // disableToolStripMenuItem
            // 
            this.disableToolStripMenuItem.Name = "disableToolStripMenuItem";
            this.disableToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.disableToolStripMenuItem.Text = "弃用";
            this.disableToolStripMenuItem.Click += new System.EventHandler(this.disableToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(105, 6);
            // 
            // delusedToolStripMenuItem
            // 
            this.delusedToolStripMenuItem.Name = "delusedToolStripMenuItem";
            this.delusedToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.delusedToolStripMenuItem.Text = "删除";
            this.delusedToolStripMenuItem.Click += new System.EventHandler(this.delusedToolStripMenuItem_Click);
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
            this.clearUsedToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(111, 25);
            this.toolStripMenuItem1.Text = "已使用的图片";
            // 
            // 检查重叠ToolStripMenuItem
            // 
            this.检查重叠ToolStripMenuItem.Name = "检查重叠ToolStripMenuItem";
            this.检查重叠ToolStripMenuItem.Size = new System.Drawing.Size(175, 24);
            this.检查重叠ToolStripMenuItem.Text = "检查重叠";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(172, 6);
            // 
            // clearUsedToolStripMenuItem
            // 
            this.clearUsedToolStripMenuItem.Name = "clearUsedToolStripMenuItem";
            this.clearUsedToolStripMenuItem.Size = new System.Drawing.Size(175, 24);
            this.clearUsedToolStripMenuItem.Text = "清空图片组";
            this.clearUsedToolStripMenuItem.Click += new System.EventHandler(this.clearUsedToolStripMenuItem_Click);
            // 
            // imageSetBox
            // 
            this.imageSetBox.BackColor = System.Drawing.Color.White;
            this.imageSetBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.imageSetBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.imageSetBox.Location = new System.Drawing.Point(0, 27);
            this.imageSetBox.Name = "imageSetBox";
            this.imageSetBox.Size = new System.Drawing.Size(656, 482);
            this.imageSetBox.TabIndex = 2;
            this.imageSetBox.TabStop = false;
            this.imageSetBox.SizeChanged += new System.EventHandler(this.imageSetBox_SizeChanged);
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
            this.fitToolStripMenuItem.Size = new System.Drawing.Size(138, 24);
            this.fitToolStripMenuItem.Text = "自动贴合";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
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
            this.sizeSetToolStripComboBox.SelectedIndexChanged += new System.EventHandler(this.sizeSetToolStripComboBox_SelectedIndexChanged);
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "图片文件(png,bmp,jpg)|*.png;*.bmp;*.jpg;";
            this.openFileDialog.Multiselect = true;
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
            this.imageListSplitContainer.Panel1.ResumeLayout(false);
            this.imageListSplitContainer.Panel1.PerformLayout();
            this.imageListSplitContainer.Panel2.ResumeLayout(false);
            this.imageListSplitContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageListSplitContainer)).EndInit();
            this.imageListSplitContainer.ResumeLayout(false);
            this.unusedImageContextMenuStrip.ResumeLayout(false);
            this.unusedToolStrip.ResumeLayout(false);
            this.unusedToolStrip.PerformLayout();
            this.unsedImageContextMenuStrip.ResumeLayout(false);
            this.usedToolStrip.ResumeLayout(false);
            this.usedToolStrip.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageSetBox)).EndInit();
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
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
        private System.Windows.Forms.ToolStripMenuItem addImageMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem clearMenuItem;
        private System.Windows.Forms.ToolStrip usedToolStrip;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripMenuItem clearUsedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 检查重叠ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem fitToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.ContextMenuStrip unusedImageContextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem delImageToolStripMenuItem;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
        private System.Windows.Forms.ToolStripMenuItem enableToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ContextMenuStrip unsedImageContextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem disableToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem delusedToolStripMenuItem;
    }
}
