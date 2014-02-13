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
            this.usedListView = new System.Windows.Forms.ListView();
            this.usedColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.unsedImageContextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.delusedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripSeparator();
            this.sortToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.usedSelectSortNameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.usedSelectSortNameReverseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem5 = new System.Windows.Forms.ToolStripSeparator();
            this.usedSelectSortSizeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.usedSelectSortSizeReverseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.usedToolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.addImageMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.clearUsedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageSetBox = new System.Windows.Forms.PictureBox();
            this.vScrollBar = new System.Windows.Forms.VScrollBar();
            this.hScrollBar = new System.Windows.Forms.HScrollBar();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.fitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.sizeSetToolStripComboBox = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.nameToolStripTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripLabel3 = new System.Windows.Forms.ToolStripLabel();
            this.rectToolStripTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            this.sizeToolStripTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
            this.splitContainer.Panel1.SuspendLayout();
            this.splitContainer.Panel2.SuspendLayout();
            this.splitContainer.SuspendLayout();
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
            this.splitContainer.Panel1.Controls.Add(this.usedListView);
            this.splitContainer.Panel1.Controls.Add(this.usedToolStrip);
            // 
            // splitContainer.Panel2
            // 
            this.splitContainer.Panel2.Controls.Add(this.imageSetBox);
            this.splitContainer.Panel2.Controls.Add(this.vScrollBar);
            this.splitContainer.Panel2.Controls.Add(this.hScrollBar);
            this.splitContainer.Panel2.Controls.Add(this.toolStrip);
            this.splitContainer.Size = new System.Drawing.Size(1049, 585);
            this.splitContainer.SplitterDistance = 197;
            this.splitContainer.TabIndex = 0;
            // 
            // usedListView
            // 
            this.usedListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.usedColumnHeader});
            this.usedListView.ContextMenuStrip = this.unsedImageContextMenuStrip;
            this.usedListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.usedListView.Location = new System.Drawing.Point(0, 25);
            this.usedListView.Name = "usedListView";
            this.usedListView.Size = new System.Drawing.Size(197, 560);
            this.usedListView.TabIndex = 1;
            this.usedListView.UseCompatibleStateImageBehavior = false;
            this.usedListView.View = System.Windows.Forms.View.Details;
            this.usedListView.SelectedIndexChanged += new System.EventHandler(this.usedListView_SelectedIndexChanged);
            this.usedListView.SizeChanged += new System.EventHandler(this.usedListView_SizeChanged);
            // 
            // usedColumnHeader
            // 
            this.usedColumnHeader.Text = "";
            // 
            // unsedImageContextMenuStrip
            // 
            this.unsedImageContextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectAllToolStripMenuItem,
            this.delusedToolStripMenuItem,
            this.toolStripMenuItem4,
            this.sortToolStripMenuItem});
            this.unsedImageContextMenuStrip.Name = "unusedImageContextMenuStrip";
            this.unsedImageContextMenuStrip.Size = new System.Drawing.Size(166, 82);
            // 
            // selectAllToolStripMenuItem
            // 
            this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
            this.selectAllToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(165, 24);
            this.selectAllToolStripMenuItem.Text = "全选";
            this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.selectAllToolStripMenuItem_Click);
            // 
            // delusedToolStripMenuItem
            // 
            this.delusedToolStripMenuItem.Name = "delusedToolStripMenuItem";
            this.delusedToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.delusedToolStripMenuItem.Size = new System.Drawing.Size(165, 24);
            this.delusedToolStripMenuItem.Text = "删除";
            this.delusedToolStripMenuItem.Click += new System.EventHandler(this.delusedToolStripMenuItem_Click);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(162, 6);
            // 
            // sortToolStripMenuItem
            // 
            this.sortToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.usedSelectSortNameToolStripMenuItem,
            this.usedSelectSortNameReverseToolStripMenuItem,
            this.toolStripMenuItem5,
            this.usedSelectSortSizeToolStripMenuItem,
            this.usedSelectSortSizeReverseToolStripMenuItem});
            this.sortToolStripMenuItem.Name = "sortToolStripMenuItem";
            this.sortToolStripMenuItem.Size = new System.Drawing.Size(165, 24);
            this.sortToolStripMenuItem.Text = "排序";
            // 
            // usedSelectSortNameToolStripMenuItem
            // 
            this.usedSelectSortNameToolStripMenuItem.Name = "usedSelectSortNameToolStripMenuItem";
            this.usedSelectSortNameToolStripMenuItem.Size = new System.Drawing.Size(153, 24);
            this.usedSelectSortNameToolStripMenuItem.Text = "按名称顺序";
            this.usedSelectSortNameToolStripMenuItem.Click += new System.EventHandler(this.usedSelectSortNameToolStripMenuItem_Click);
            // 
            // usedSelectSortNameReverseToolStripMenuItem
            // 
            this.usedSelectSortNameReverseToolStripMenuItem.Name = "usedSelectSortNameReverseToolStripMenuItem";
            this.usedSelectSortNameReverseToolStripMenuItem.Size = new System.Drawing.Size(153, 24);
            this.usedSelectSortNameReverseToolStripMenuItem.Text = "按名称倒序";
            this.usedSelectSortNameReverseToolStripMenuItem.Click += new System.EventHandler(this.usedSelectSortNameReverseToolStripMenuItem_Click);
            // 
            // toolStripMenuItem5
            // 
            this.toolStripMenuItem5.Name = "toolStripMenuItem5";
            this.toolStripMenuItem5.Size = new System.Drawing.Size(150, 6);
            // 
            // usedSelectSortSizeToolStripMenuItem
            // 
            this.usedSelectSortSizeToolStripMenuItem.Name = "usedSelectSortSizeToolStripMenuItem";
            this.usedSelectSortSizeToolStripMenuItem.Size = new System.Drawing.Size(153, 24);
            this.usedSelectSortSizeToolStripMenuItem.Text = "按尺寸顺序";
            this.usedSelectSortSizeToolStripMenuItem.Click += new System.EventHandler(this.usedSelectSortSizeToolStripMenuItem_Click);
            // 
            // usedSelectSortSizeReverseToolStripMenuItem
            // 
            this.usedSelectSortSizeReverseToolStripMenuItem.Name = "usedSelectSortSizeReverseToolStripMenuItem";
            this.usedSelectSortSizeReverseToolStripMenuItem.Size = new System.Drawing.Size(153, 24);
            this.usedSelectSortSizeReverseToolStripMenuItem.Text = "按尺寸倒序";
            this.usedSelectSortSizeReverseToolStripMenuItem.Click += new System.EventHandler(this.usedSelectSortSizeReverseToolStripMenuItem_Click);
            // 
            // usedToolStrip
            // 
            this.usedToolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.usedToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.usedToolStrip.Location = new System.Drawing.Point(0, 0);
            this.usedToolStrip.Name = "usedToolStrip";
            this.usedToolStrip.Size = new System.Drawing.Size(197, 25);
            this.usedToolStrip.TabIndex = 2;
            this.usedToolStrip.Text = "toolStrip2";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addImageMenuItem,
            this.toolStripSeparator5,
            this.clearUsedToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(66, 25);
            this.toolStripMenuItem1.Text = "图片组";
            // 
            // addImageMenuItem
            // 
            this.addImageMenuItem.Name = "addImageMenuItem";
            this.addImageMenuItem.Size = new System.Drawing.Size(153, 24);
            this.addImageMenuItem.Text = "添加图片";
            this.addImageMenuItem.Click += new System.EventHandler(this.addImageMenuItem_Click);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(150, 6);
            // 
            // clearUsedToolStripMenuItem
            // 
            this.clearUsedToolStripMenuItem.Name = "clearUsedToolStripMenuItem";
            this.clearUsedToolStripMenuItem.Size = new System.Drawing.Size(153, 24);
            this.clearUsedToolStripMenuItem.Text = "清空图片组";
            this.clearUsedToolStripMenuItem.Click += new System.EventHandler(this.clearUsedToolStripMenuItem_Click);
            // 
            // imageSetBox
            // 
            this.imageSetBox.BackColor = System.Drawing.Color.Gray;
            this.imageSetBox.Cursor = System.Windows.Forms.Cursors.SizeAll;
            this.imageSetBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.imageSetBox.Location = new System.Drawing.Point(0, 27);
            this.imageSetBox.Name = "imageSetBox";
            this.imageSetBox.Size = new System.Drawing.Size(827, 537);
            this.imageSetBox.TabIndex = 2;
            this.imageSetBox.TabStop = false;
            this.imageSetBox.SizeChanged += new System.EventHandler(this.imageSetBox_SizeChanged);
            this.imageSetBox.Paint += new System.Windows.Forms.PaintEventHandler(this.imageSetBox_Paint);
            this.imageSetBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.imageSetBox_MouseDown);
            this.imageSetBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.imageSetBox_MouseMove);
            this.imageSetBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.imageSetBox_MouseUp);
            this.imageSetBox.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.imageSetBox_PreviewKeyDown);
            // 
            // vScrollBar
            // 
            this.vScrollBar.Dock = System.Windows.Forms.DockStyle.Right;
            this.vScrollBar.LargeChange = 20;
            this.vScrollBar.Location = new System.Drawing.Point(827, 27);
            this.vScrollBar.Name = "vScrollBar";
            this.vScrollBar.Size = new System.Drawing.Size(21, 537);
            this.vScrollBar.TabIndex = 1;
            this.vScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBar_Scroll);
            // 
            // hScrollBar
            // 
            this.hScrollBar.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hScrollBar.Location = new System.Drawing.Point(0, 564);
            this.hScrollBar.Name = "hScrollBar";
            this.hScrollBar.Size = new System.Drawing.Size(848, 21);
            this.hScrollBar.TabIndex = 0;
            this.hScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar_Scroll);
            // 
            // toolStrip
            // 
            this.toolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2,
            this.toolStripSeparator1,
            this.toolStripLabel1,
            this.sizeSetToolStripComboBox,
            this.toolStripSeparator4,
            this.toolStripLabel2,
            this.nameToolStripTextBox,
            this.toolStripLabel3,
            this.rectToolStripTextBox,
            this.toolStripLabel4,
            this.sizeToolStripTextBox});
            this.toolStrip.Location = new System.Drawing.Point(0, 0);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.Size = new System.Drawing.Size(848, 27);
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
            "128*128",
            "256*256",
            "512*512",
            "1024*1024",
            "2048*2048",
            "4096*4096"});
            this.sizeSetToolStripComboBox.Name = "sizeSetToolStripComboBox";
            this.sizeSetToolStripComboBox.Size = new System.Drawing.Size(121, 27);
            this.sizeSetToolStripComboBox.SelectedIndexChanged += new System.EventHandler(this.sizeSetToolStripComboBox_SelectedIndexChanged);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 27);
            // 
            // toolStripLabel2
            // 
            this.toolStripLabel2.Name = "toolStripLabel2";
            this.toolStripLabel2.Size = new System.Drawing.Size(54, 24);
            this.toolStripLabel2.Text = "索引名";
            // 
            // nameToolStripTextBox
            // 
            this.nameToolStripTextBox.Name = "nameToolStripTextBox";
            this.nameToolStripTextBox.Size = new System.Drawing.Size(150, 27);
            this.nameToolStripTextBox.Leave += new System.EventHandler(this.nameToolStripTextBox_Leave);
            this.nameToolStripTextBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.nameToolStripTextBox_KeyUp);
            // 
            // toolStripLabel3
            // 
            this.toolStripLabel3.Name = "toolStripLabel3";
            this.toolStripLabel3.Size = new System.Drawing.Size(39, 24);
            this.toolStripLabel3.Text = "位置";
            // 
            // rectToolStripTextBox
            // 
            this.rectToolStripTextBox.Name = "rectToolStripTextBox";
            this.rectToolStripTextBox.ReadOnly = true;
            this.rectToolStripTextBox.Size = new System.Drawing.Size(100, 27);
            // 
            // toolStripLabel4
            // 
            this.toolStripLabel4.Name = "toolStripLabel4";
            this.toolStripLabel4.Size = new System.Drawing.Size(39, 24);
            this.toolStripLabel4.Text = "尺寸";
            // 
            // sizeToolStripTextBox
            // 
            this.sizeToolStripTextBox.Name = "sizeToolStripTextBox";
            this.sizeToolStripTextBox.ReadOnly = true;
            this.sizeToolStripTextBox.Size = new System.Drawing.Size(100, 27);
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
            this.Size = new System.Drawing.Size(1049, 585);
            this.Load += new System.EventHandler(this.ImagesetEditControl_Load);
            this.splitContainer.Panel1.ResumeLayout(false);
            this.splitContainer.Panel1.PerformLayout();
            this.splitContainer.Panel2.ResumeLayout(false);
            this.splitContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).EndInit();
            this.splitContainer.ResumeLayout(false);
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
        private System.Windows.Forms.VScrollBar vScrollBar;
        private System.Windows.Forms.HScrollBar hScrollBar;
        private System.Windows.Forms.PictureBox imageSetBox;
        private System.Windows.Forms.ToolStrip toolStrip;
        private System.Windows.Forms.ToolStripComboBox sizeSetToolStripComboBox;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ListView usedListView;
        private System.Windows.Forms.ToolStrip usedToolStrip;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripMenuItem clearUsedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem fitToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
        private System.Windows.Forms.ContextMenuStrip unsedImageContextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem delusedToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem4;
        private System.Windows.Forms.ToolStripMenuItem sortToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem usedSelectSortNameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem usedSelectSortNameReverseToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem5;
        private System.Windows.Forms.ToolStripMenuItem usedSelectSortSizeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem usedSelectSortSizeReverseToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripLabel toolStripLabel2;
        private System.Windows.Forms.ToolStripTextBox nameToolStripTextBox;
        private System.Windows.Forms.ToolStripLabel toolStripLabel3;
        private System.Windows.Forms.ToolStripTextBox rectToolStripTextBox;
        private System.Windows.Forms.ToolStripLabel toolStripLabel4;
        private System.Windows.Forms.ToolStripTextBox sizeToolStripTextBox;
        private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
        private System.Windows.Forms.ColumnHeader usedColumnHeader;
        private System.Windows.Forms.ToolStripMenuItem addImageMenuItem;
    }
}
