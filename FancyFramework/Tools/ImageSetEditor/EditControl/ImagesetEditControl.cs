using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageSetEditor.EditControl
{
    public partial class ImagesetEditControl : UserControl, IDocument, IDisposable
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

        #endregion Fields

        #region Methods

        #region IDocumentImplements

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

        #endregion IDocumentImplements

        #endregion Methods

        #region Properties
        #endregion Properties

        #region Events

        private void ImagesetEditControl_Load(object sender, EventArgs e)
        {
            this.Dock = DockStyle.Fill;
        }

        private void imageSetBox_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            StringFormat f = new StringFormat(StringFormatFlags.DirectionVertical);
            SolidBrush brush = new SolidBrush(Color.Black);
            Pen pen = new Pen(Color.Black);
            pen.Width = 5;


        }

        #endregion Events

        #region Constructors

        public ImagesetEditControl()
        {
            InitializeComponent();
            unusedListView.Items.Add("[64*64] image_001.png");
        }

        #endregion Constructors
    }

    struct SubImage : IDisposable
    {
        private Point m_p;
        private Bitmap m_bitmap;

        #region Fields
        #endregion Fields

        #region Methods

        /// <summary>
        /// 检查是否与另一个对象相交
        /// </summary>
        /// <returns></returns>
        public bool Intersect(SubImage image) {
            return false;
        }

        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                // Free managed objects.  
            }

            // Free unmanaged objects
            if (m_bitmap != null)
            {
                m_bitmap.Dispose();
                m_bitmap = null;
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
            get { return m_p; }
            set { m_p = value; }
        }

        #endregion Properties

        #region Constructors

        public SubImage(string file)
        {
            m_p = new Point(0, 0);
            m_bitmap = new Bitmap(file);
        }

        #endregion Constructors
    };
}
