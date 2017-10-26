using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace B2M2.CLRGenerator.Framework
{
    class Generator
    {
        [STAThread]
        public static void Main(string[] args)
        {
            Application.Run(new Demo());
        }
    }
}
