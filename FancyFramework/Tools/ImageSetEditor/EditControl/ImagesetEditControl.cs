////////////////////////////////////////////////////////////////////////////////
/// Copyright(c) 2014, frimin
/// All rights reserved.
/// 
/// Redistribution and use in source and binary forms, with or without modification,
/// are permitted provided that the following conditions are met :
/// 
/// * Redistributions of source code must retain the above copyright notice, this
/// list of conditions and the following disclaimer.
/// 
/// * Redistributions in binary form must reproduce the above copyright notice, this
/// list of conditions and the following disclaimer in the documentation and / or
/// other materials provided with the distribution.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
/// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
/// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
/// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
/// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
/// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
/// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
/// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///        file :   ImagesetEditControl.cs
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

namespace ImageSetEditor.EditControl
{
    public partial class ImagesetEditControl : UserControl, IDisposable
    {
        #region Fields

        /// <summary>
        /// 当前鼠标状态
        /// </summary>
        enum MouseStatus
        {
            Normal, /// 正常
            Drag,   /// 拖拽图片
            Select, /// 选择图片
        };

        /// <summary>
        /// 当前文档路径
        /// </summary>
        private string m_documentPath;

        /// <summary>
        /// 当前文档是否被修改
        /// </summary>
        private bool m_modify;

        /// <summary>
        /// 画布
        /// </summary>
        private Canvas m_canvas;

        /// <summary>
        /// 当前选中的图片
        /// </summary>
        private SubImage m_select;

        /// <summary>
        /// 当前选中的图片组
        /// </summary>
        private List<SubImage> m_selects;

        /// <summary>
        /// 操作开始时鼠标起始位置
        /// </summary>
        private Point m_beginMousePos;

        /// <summary>
        /// 当前鼠标位置
        /// </summary>
        private Point m_curMousePos;

        /// <summary>
        /// 当前鼠标状态
        /// </summary>
        private MouseStatus m_MouseStatus;

        /// <summary>
        /// 鼠标在已选择的图片范围内
        /// </summary>
        private bool m_inSelects;

        private enum SortTypes
        {
            Name        = 0,
            NameReverse = 1,
            Size        = 2,
            SizeReverse = 3,
        };

        #endregion Fields

        #region Methods

        public void Open(string fileName)
        {
        }

        public void Close()
        {
        }

        public void Save(string fileName)
        {
        }

        public string GetCurrentName()
        {
            return "";
        }

        private void imageSetBoxUpdate()
        {
            imageSetBox.Invalidate();
        }

        private void SetSelect(SubImage select)
        {
            if (select == null)
            {
                nameToolStripTextBox.Text = "不可用";
                rectToolStripTextBox.Text = "不可用";
                sizeToolStripTextBox.Text = "不可用";
                nameToolStripTextBox.ReadOnly = true;
            }
            else
            {
                nameToolStripTextBox.Text = select.Name;
                rectToolStripTextBox.Text =
                    String.Format("{0},{1}", select.Position.X, select.Position.Y);
                sizeToolStripTextBox.Text =
                    String.Format("{0},{1}", select.Size.Width, select.Size.Height);
                nameToolStripTextBox.ReadOnly = false;
            }
            m_select = select;
        }

        private class CompareName : IComparer
        {
            public int Compare(object x, object y)
            {
                return CompareOriginal(x, y);
            }

            public static int CompareOriginal(object x, object y)
            {
                SubImage imageX = (SubImage)x;
                SubImage imageY = (SubImage)y;

                return String.CompareOrdinal(imageX.Name, imageY.Name);
            }
        }

        private class CompareNameReverse : IComparer
        {
            public int Compare(object x, object y)
            {
                return CompareName.CompareOriginal(x, y) * -1;
            }
        }

        private class CompareSize : IComparer
        {
            public int Compare(object x, object y)
            {
                return CompareOriginal(x, y);
            }

            public static int CompareOriginal(object x, object y)
            {
                SubImage imageX = (SubImage)x;
                SubImage imageY = (SubImage)y;

                int areaX = imageX.Size.Width * imageX.Size.Height;
                int areaY = imageY.Size.Width * imageY.Size.Height;

                if (areaX > areaY && imageX.Size.Width > imageY.Size.Width)
                {
                    return 1;
                }

                if (imageX.Size == imageY.Size)
                {
                    return String.CompareOrdinal(imageX.Name, imageY.Name);
                }

                return -1;
            }
        }

        private class CompareSizeReverse : IComparer
        {
            public int Compare(object x, object y)
            {
                return CompareSize.CompareOriginal(x, y) * -1;
            }
        }

        private void SortItems(SortTypes type, IList items)
        {
            ArrayList list = new ArrayList();

            foreach (ListViewItem item in items)
            {
                list.Add(item.Tag);
            }

            IComparer sorter = null;

            switch (type)
            {
                case SortTypes.Name:
                    sorter = new CompareName();
                    break;
                case SortTypes.NameReverse:
                    sorter = new CompareNameReverse();
                    break;
                case SortTypes.Size:
                    sorter = new CompareSize();
                    break;
                case SortTypes.SizeReverse:
                    sorter = new CompareSizeReverse();
                    break;
            };

            list.Sort((IComparer)sorter);

            for (int i = 0; i != list.Count; ++i)
            {
                SubImage image = (SubImage)list[i];
                ListViewItem item = (ListViewItem)items[i];
                item.Text = image.Name;
                item.Tag = image;
                image.BindItem = item;
            }

            imageSetBoxUpdate();
        }

        #endregion Methods

        #region Properties
        #endregion Properties

        #region Events

        private void ImagesetEditControl_Load(object sender, EventArgs e)
        {
            this.Dock = DockStyle.Fill;
        }

        private void imageSetBox_SizeChanged(object sender, EventArgs e)
        {
            m_canvas.ViewSize = imageSetBox.Size;

            /// 可视范围比画布大
            if (m_canvas.ViewSize.Height >= m_canvas.Size.Height)
            {
                vScrollBar.Visible = false;
            }
            else
            {
                vScrollBar.Maximum = m_canvas.Size.Height;
                vScrollBar.LargeChange = m_canvas.ViewSize.Height;
                vScrollBar.Visible = true;
            }

            if (m_canvas.ViewSize.Width >= m_canvas.Size.Width)
            {
                hScrollBar.Visible = false;
            }
            else
            {
                hScrollBar.Maximum = m_canvas.Size.Width;
                hScrollBar.LargeChange = m_canvas.ViewSize.Width;
                hScrollBar.Visible = true;
            }
            
        }

        private void imageSetBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {

                switch (m_MouseStatus)
                {
                    case MouseStatus.Drag:
                        {
                            m_MouseStatus = MouseStatus.Normal;

                            Point offset = new Point(
                                m_curMousePos.X - m_beginMousePos.X,
                                m_curMousePos.Y - m_beginMousePos.Y);

                            foreach (SubImage image in m_selects)
                            {
                                image.Position = new Point(
                                    image.Position.X + offset.X,
                                    image.Position.Y + offset.Y);
                            }

                            if (m_select != null)
                            {
                                SetSelect(m_select);
                            }

                            imageSetBoxUpdate();
                        }
                        break;
                    case MouseStatus.Select:
                        {
                            /*
                            if (m_selects.Count != 0)
                            {
                                m_selects.Clear();
                                SetSelect(null);
                            }

                            foreach (ListViewItem item in usedListView.Items)
                            {
                                SubImage image = (SubImage)item.Tag;

                            }

                            imageSetBoxUpdate();
                             * */
                        }
                        break;
                }
            }
        }

        private void imageSetBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                if (m_inSelects)
                {
                    m_MouseStatus = MouseStatus.Drag;
                    m_beginMousePos = e.Location;
                    m_curMousePos = e.Location;
                }
                else
                {
                    m_MouseStatus = MouseStatus.Select;
                    m_beginMousePos = e.Location;
                    m_curMousePos = e.Location;
                }
            }
        }

        private void imageSetBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (m_MouseStatus != MouseStatus.Normal)
            {
                m_curMousePos = e.Location;

                imageSetBoxUpdate();

                return;
            }

            /// 鼠标移动到已经选择的图片里时变更光标

            m_inSelects = false;

            
            foreach (SubImage image in m_selects)
            {
                if (image.Rectangle.Contains(new Point(
                    e.X + m_canvas.ViewPos.X,
                    e.Y + m_canvas.ViewPos.Y)))
                {
                    m_inSelects = true;
                    break;
                }
            }

            if (m_inSelects)
            {
                imageSetBox.Cursor = Cursors.SizeAll;
            }
            else
            {
                imageSetBox.Cursor = Cursors.Default;
            }
        }

        private void imageSetBox_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            
        }

        private void imageSetBox_Paint(object sender, PaintEventArgs e)
        {
            m_canvas.Begin(e.Graphics);

            foreach (ListViewItem item in usedListView.Items)
            {
                if (m_MouseStatus == MouseStatus.Drag)
                {
                    if (item.Selected)
                        continue;
                }

                SubImage image = (SubImage)item.Tag;
                m_canvas.DrawImage(image);
            }

            if (m_MouseStatus == MouseStatus.Drag)
            {
                Point offset = new Point(
                    m_curMousePos.X - m_beginMousePos.X, 
                    m_curMousePos.Y - m_beginMousePos.Y);

                foreach (SubImage image in m_selects)
                {
                    m_canvas.DrawImage(image, offset);
                    m_canvas.DrawImageArea(image, offset);
                }
            }
            else
            {
                foreach (SubImage image in m_selects)
                {
                    m_canvas.DrawImageArea(image);
                }
            }

            if (m_MouseStatus == MouseStatus.Select)
            {

            }

            m_canvas.End(); 
        }

        private void vScrollBar_Scroll(object sender, ScrollEventArgs e)
        {
            m_canvas.ViewPos = new Point(hScrollBar.Value, vScrollBar.Value);

            imageSetBoxUpdate();
        }

        private void hScrollBar_Scroll(object sender, ScrollEventArgs e)
        {
            m_canvas.ViewPos = new Point(hScrollBar.Value, vScrollBar.Value);

            imageSetBoxUpdate();
        }

        private void addImageMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                foreach (string file in openFileDialog.FileNames)
                {
                    ListViewItem newItem = new ListViewItem();
                    SubImage newImage = new SubImage(file);
                    newImage.BindItem = newItem;
                    newItem.Tag = newImage;
                    newItem.Text = newImage.Name;
                    usedListView.Items.Add(newItem);
                }

                imageSetBoxUpdate();
            }
        }

        private void clearUsedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (usedListView.Items.Count == 0)
                return;
            if (DialogResult.OK == MessageBox.Show("删除所有？", "删除", MessageBoxButtons.OKCancel, MessageBoxIcon.Question))
            {
                SetSelect(null);
                foreach (ListViewItem item in usedListView.Items)
                {
                    ((SubImage)item.Tag).Dispose();
                    item.Tag = null;
                    item.Remove();
                }
            }

            imageSetBoxUpdate();
        }

        private void delusedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (usedListView.SelectedItems.Count == 0)
                return;
            if (DialogResult.OK == MessageBox.Show("确定从列表中删除所选的 " + usedListView.SelectedItems.Count + " 个图片？", "删除", MessageBoxButtons.OKCancel, MessageBoxIcon.Question))
            {
                SetSelect(null);
                foreach (ListViewItem item in usedListView.SelectedItems)
                {
                    ((SubImage)item.Tag).Dispose();
                    item.Tag = null;
                    item.Remove();
                }
            }

            imageSetBoxUpdate();
        }

        private void sizeSetToolStripComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int n = int.Parse(((ToolStripComboBox)sender).Text.Split('*')[0]);

            m_canvas.Size = new Size(n, n);

            m_canvas.ViewPos = new Point(0, 0);
            hScrollBar.Value = 0;
            vScrollBar.Value = 0;

            imageSetBox_SizeChanged(null, null);

            imageSetBoxUpdate();
        }

        private void nameToolStripTextBox_Leave(object sender, EventArgs e)
        {
            if (m_select != null)
                nameToolStripTextBox.Text = m_select.Name;
        }

        private void nameToolStripTextBox_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (nameToolStripTextBox.Text.Length == 0)
                {
                    nameToolStripTextBox.Text = m_select.Name;
                    return;
                }
                m_select.Name = nameToolStripTextBox.Text;
                m_select.BindItem.Text = m_select.Name;
            }
        }

        private void usedSelectSortNameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (usedListView.SelectedItems.Count == 0)
                return;
            SortItems(SortTypes.Name, usedListView.SelectedItems);
        }

        private void usedSelectSortNameReverseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (usedListView.SelectedItems.Count == 0)
                return;
            SortItems(SortTypes.NameReverse, usedListView.SelectedItems);
        }

        private void usedSelectSortSizeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (usedListView.SelectedItems.Count == 0)
                return;
            SortItems(SortTypes.Size, usedListView.SelectedItems);
        }

        private void usedSelectSortSizeReverseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (usedListView.SelectedItems.Count == 0)
                return;
            SortItems(SortTypes.SizeReverse, usedListView.SelectedItems);
        }

        private void selectAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in usedListView.Items)
            {
                item.Selected = true;
            }
        }

        private void usedListView_SizeChanged(object sender, EventArgs e)
        {
            usedColumnHeader.Width = usedListView.Width;
        }

        private void usedListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            int n = usedListView.SelectedItems.Count;
            if (n != 1)
            {
                SetSelect(null);
            }
            else
            {
                SetSelect((SubImage)usedListView.SelectedItems[0].Tag);
            }

            m_selects.Clear();
            foreach (ListViewItem item in usedListView.SelectedItems)
            {
                m_selects.Add((SubImage)item.Tag);
            }

            imageSetBoxUpdate();
        }

        #endregion Events

        #region Constructors

        public ImagesetEditControl()
        {
            m_canvas = new Canvas();
            m_selects = new List<SubImage>();

            m_MouseStatus = MouseStatus.Normal;

            InitializeComponent();

            SetSelect(null);

            sizeSetToolStripComboBox.SelectedIndex = 3;
        }

        #endregion Constructors
    }

    /// <summary>
    /// 画布对象
    /// </summary>
    class Canvas
    {
        #region Fields

        /// <summary>
        /// 画布位图绘图接口
        /// </summary>
        private Graphics m_viewGraph;

        /// <summary>
        /// 画布位图尺寸
        /// </summary>
        private Size m_canvasSize;
        
        /// <summary>
        /// 当前查看位置
        /// </summary>
        private Point m_viewPosition;

        /// <summary>
        /// 查看范围
        /// </summary>
        private Size m_viewSize;

        /// <summary>
        /// 整体范围
        /// </summary>
        private Size m_size;

        private Pen m_dashedPen;

        private Pen m_blackPen;

        private Pen m_whitePen;

        #endregion Fields

        #region Methods

        public void Begin(Graphics viewGraph)
        {
            m_viewGraph = viewGraph;
            m_viewGraph.FillRectangle(
                m_whitePen.Brush,
                -m_viewPosition.X,
                -m_viewPosition.Y,
                m_size.Width,
                m_size.Height);
        }

        public void End()
        {
            m_viewGraph.DrawRectangle(
                m_dashedPen,
                -m_viewPosition.X,
                -m_viewPosition.Y,
                m_size.Width,
                m_size.Height);
        }

        public void DrawImage(SubImage image, Point offset)
        {
            m_viewGraph.DrawImage(
                image.Image,
                image.Position.X - m_viewPosition.X + offset.X,
                image.Position.Y - m_viewPosition.Y + offset.Y,
                image.Size.Width,
                image.Size.Height);
        }

        public void DrawImage(SubImage image)
        {
            m_viewGraph.DrawImage(
                image.Image,
                image.Position.X - m_viewPosition.X, 
                image.Position.Y - m_viewPosition.Y,
                image.Size.Width,
                image.Size.Height);
        }

        public void DrawImageArea(SubImage image)
        {
            DrawSmallBox(image.Position.X, image.Position.Y);
            DrawSmallBox(image.Position.X + image.Size.Width, image.Position.Y);
            DrawSmallBox(image.Position.X + image.Size.Width, image.Position.Y + image.Size.Height);
            DrawSmallBox(image.Position.X, image.Position.Y + image.Size.Height);

            m_viewGraph.DrawRectangle(
                m_dashedPen,
                image.Position.X - m_viewPosition.X,
                image.Position.Y - m_viewPosition.Y,
                image.Size.Width,
                image.Size.Height);
        }

        public void DrawImageArea(SubImage image, Point offset)
        {
            Point p = new Point(image.Position.X + offset.X, image.Position.Y + offset.Y);

            DrawSmallBox(p.X, p.Y);
            DrawSmallBox(p.X + image.Size.Width, p.Y);
            DrawSmallBox(p.X + image.Size.Width, p.Y + image.Size.Height);
            DrawSmallBox(p.X, p.Y + image.Size.Height);

            m_viewGraph.DrawRectangle(
                m_dashedPen,
                p.X - m_viewPosition.X,
                p.Y - m_viewPosition.Y,
                image.Size.Width,
                image.Size.Height);
        }

        public void DrawSmallBox(int x, int y)
        {
            m_viewGraph.FillRectangle(
                m_blackPen.Brush, x - 3 - m_viewPosition.X, y - 3 - m_viewPosition.Y, 6, 6);
        }

        #endregion Methods

        #region Properties

        public Graphics Graphics
        {
            get { return m_viewGraph; }
        }

        public Point ViewPos
        {
            get { return m_viewPosition; }
            set { m_viewPosition = value; }
        }

        public Size ViewSize
        {
            get { return m_viewSize; }
            set { m_viewSize = value; }
        }

        public Size Size
        {
            get { return m_size; }
            set { m_size = value; }
        }

        #endregion Properties

        #region Constructors

        public Canvas()
        {
            m_viewGraph = null;

            m_dashedPen = new Pen(Color.Gray);
            m_dashedPen.DashStyle = DashStyle.DashDot;

            m_blackPen = new Pen(Color.Black);

            m_whitePen = new Pen(Color.White);
        }

        #endregion Constructors
    };

    class SubImage : IDisposable
    {

        #region Fields

        private Point m_position;
        private Bitmap m_image;
        private Rectangle m_rect;
        private string m_filePath;
        private string m_name;
        private ListViewItem m_bindItem;

        #endregion Fields

        #region Methods

        /// <summary>
        /// 检查是否与另一个对象相交
        /// </summary>
        /// <returns></returns>
        public bool Intersect(SubImage image)
        {
            Rectangle rect = new Rectangle(image.Position, image.Size);

            return Rectangle.IntersectsWith(rect);
        }

        public bool Intersect(Rectangle rect)
        {
            return Rectangle.IntersectsWith(rect);
        }

        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                // Free managed objects.  
            }

            // Free unmanaged objects
            if (m_image != null)
            {
                m_image.Dispose();
                m_image = null;
            }
        }

        public void Dispose()
        {
            Dispose(true);
            // Ensure that the destructor is not called  
            GC.SuppressFinalize(this);
        }

        #endregion Methods

        #region Properties

        public Point Position
        {
            get { return m_position; }
            set { m_position = value; m_rect = new Rectangle(this.Position, this.Size); }
        }

        public Size Size
        {
            get { return m_image.Size; }
        }

        public Bitmap Image
        {
            get { return m_image; }
        }

        public string FilePath
        {
            get { return m_filePath; }
        }

        public string Name
        {
            get { return m_name; }
            set { m_name = value; }
        }

        public ListViewItem BindItem
        {
            get { return m_bindItem; }
            set { m_bindItem = value; }
        }

        public Rectangle Rectangle
        {
            get { return m_rect; }
        }

        #endregion Properties

        #region Constructors

        public SubImage(string file)
        {
            m_position = new Point(0, 0);
            m_image = new Bitmap(file);
            m_filePath = file;
            m_name = m_filePath.Split('\\').Last().Split('.').First();
            m_bindItem = null;
            m_rect = new Rectangle(this.Position, this.Size);
        }

        #endregion Constructors
    };
}
