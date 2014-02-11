using System;
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
                    newItem.Tag = newImage;
                    newItem.Text = newImage.ToString();
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

        #endregion Events

        #region Constructors

        public ImagesetEditControl()
        {
            m_canvas = new Canvas();
            InitializeComponent();
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

        public override string ToString()
        {
            return string.Format("{0} ({1}*{2})", m_filePath.Split('\\').Last(), Size.Width.ToString(), Size.Height.ToString());
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

        #endregion Properties

        #region Constructors

        public SubImage(string file)
        {
            m_position = new Point(0, 0);
            m_image = new Bitmap(file);
            m_filePath = file;
        }

        #endregion Constructors
    };
}
