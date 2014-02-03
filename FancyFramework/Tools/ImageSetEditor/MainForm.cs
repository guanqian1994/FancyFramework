using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageSetEditor
{
    public partial class MainForm : Form
    {
        #region Fields
        #endregion Fields
  
        #region Events

        private void MainForm_Load(object sender, EventArgs e)
        {
            
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            (new AboutForm()).ShowDialog();
        }

        #endregion Events

        #region Constructors

        public MainForm()
        {
            InitializeComponent();
            this.Controls.Add(new EditControl.ImagesetEditControl());
        }

        #endregion Constructors
    }
}
