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
    public partial class AboutForm : Form
    {
        #region Events

        private void okButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void toProjectWebButton_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://github.com/frimin/FancyFramework");
        }

        #endregion Events

        #region Constructors

        public AboutForm()
        {
            InitializeComponent();
        }

        #endregion Constructors
    }
}
