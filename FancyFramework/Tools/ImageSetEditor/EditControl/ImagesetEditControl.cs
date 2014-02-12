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
                previewPictureBox.Image = null;
                nameToolStripTextBox.Text = "不可用";
                rectToolStripTextBox.Text = "不可用";
                sizeToolStripTextBox.Text = "不可用";
                nameToolStripTextBox.ReadOnly = true;
                previrePanel.Visible = false;
            }
            else
            {
                previewPictureBox.Image = select.Image;
                nameToolStripTextBox.Text = select.Name;
                rectToolStripTextBox.Text =
                    String.Format("{0},{1}", select.Position.X, select.Position.Y);
                sizeToolStripTextBox.Text =
                    String.Format("{0},{1}", select.Size.Width, select.Size.Height);
                nameToolStripTextBox.ReadOnly = false;
                previrePanel.Visible = true;
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
            
        }

        private void imageSetBox_Paint(object sender, PaintEventArgs e)
        {
            m_canvas.Begin(e.Graphics);

            foreach (ListViewItem item in usedListView.Items)
            {
                m_canvas.DrawImage((SubImage)item.Tag);
            }

            m_canvas.Graphics.DrawLine(new Pen(Color.Black), new Point(0, 0), new Point(50, 50));

            m_canvas.End(); 
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
                    unusedListView.Items.Add(newItem);
                }
            }
        }

        private void clearMenuItem_Click(object sender, EventArgs e)
        {
            if (unusedListView.Items.Count == 0)
                return;
            if (DialogResult.OK == MessageBox.Show("删除所有？", "删除", MessageBoxButtons.OKCancel, MessageBoxIcon.Question))
            {
                foreach (ListViewItem item in unusedListView.Items)
                {
                    ((SubImage)item.Tag).Dispose();
                    item.Tag = null;
                    item.Remove();
                }
            }
        }

        private void clearUsedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (usedListView.Items.Count == 0)
                return;
            if (DialogResult.OK == MessageBox.Show("删除所有？", "删除", MessageBoxButtons.OKCancel, MessageBoxIcon.Question))
            {
                foreach (ListViewItem item in usedListView.Items)
                {
                    ((SubImage)item.Tag).Dispose();
                    item.Tag = null;
                    item.Remove();
                }
            }

            imageSetBoxUpdate();
        }

        private void enableToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in unusedListView.SelectedItems)
            {
                ListViewItem newItem = (ListViewItem)item.Clone();

                ((SubImage)newItem.Tag).BindItem = newItem;

                usedListView.Items.Add(newItem);

                item.Remove();
            }

            imageSetBoxUpdate();
        }

        private void delImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (unusedListView.SelectedItems.Count == 0)
                return;
            if (DialogResult.OK == MessageBox.Show("确定从列表中删除所选的 " + unusedListView.SelectedItems.Count + " 个图片？", "删除", MessageBoxButtons.OKCancel, MessageBoxIcon.Question))
            {
                foreach (ListViewItem item in unusedListView.SelectedItems)
                {
                    ((SubImage)item.Tag).Dispose();
                    item.Tag = null;
                    item.Remove();
                }
            }
        }

        private void delusedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (usedListView.SelectedItems.Count == 0)
                return;
            if (DialogResult.OK == MessageBox.Show("确定从列表中删除所选的 " + usedListView.SelectedItems.Count + " 个图片？", "删除", MessageBoxButtons.OKCancel, MessageBoxIcon.Question))
            {
                foreach (ListViewItem item in usedListView.SelectedItems)
                {
                    ((SubImage)item.Tag).Dispose();
                    item.Tag = null;
                    item.Remove();
                }
            }

            imageSetBoxUpdate();
        }

        private void disableToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in usedListView.SelectedItems)
            {
                ListViewItem newItem = (ListViewItem)item.Clone();

                ((SubImage)newItem.Tag).BindItem = newItem;

                unusedListView.Items.Add(newItem);

                item.Remove();
            }

            imageSetBoxUpdate();
        }

        private void unusedListView_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                delImageToolStripMenuItem_Click(null, null);
            }
        }

        private void usedListView_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                delusedToolStripMenuItem_Click(null, null);
            }
        }

        private void sizeSetToolStripComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int n = int.Parse(((ToolStripComboBox)sender).Text.Split('*')[0]);
            
        }

        private void unusedListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (unusedListView.SelectedItems.Count != 1)
                return;
            SetSelect((SubImage)unusedListView.SelectedItems[0].Tag);
        }

        private void nameToolStripTextBox_Leave(object sender, EventArgs e)
        {
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

        private void unusedListView_Leave(object sender, EventArgs e)
        {
            previrePanel.Visible = false;
        }

        private void unusedListView_Enter(object sender, EventArgs e)
        {
            if (m_select != null)
            {
                previrePanel.Visible = true;
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

        #endregion Events

        #region Constructors

        public ImagesetEditControl()
        {
            m_canvas = new Canvas();
            InitializeComponent();
            SetSelect(null);
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

        #endregion Fields

        #region Methods

        public void Begin(Graphics viewGraph)
        {
            m_viewGraph = viewGraph;
        }

        public void End()
        {
        }

        public void DrawImage(SubImage image)
        {
            m_viewGraph.DrawImage(image.Image, image.Position);
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
        }

        #endregion Constructors
    };

    class SubImage : IDisposable
    {

        #region Fields

        private Point m_position;
        private Bitmap m_image;
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
            return false;
        }

        public bool Intersect(Rectangle rect)
        {
            return false;
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
            set { m_position = value; }
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

        #endregion Properties

        #region Constructors

        public SubImage(string file)
        {
            m_position = new Point(0, 0);
            m_image = new Bitmap(file);
            m_filePath = file;
            m_name = m_filePath.Split('\\').Last().Split('.').First();
            m_bindItem = null;
        }

        #endregion Constructors
    };
}
