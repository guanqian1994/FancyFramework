using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImageSetEditor.EditControl
{
    interface IDocument
    {
        void Open(string fileName);

        void Close();

        void Save(string fileName);

        string GetCurrentName();
    }
}
