using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Arch.Editor.Toolkit
{
    public class DesignerUtils
    {
        public static bool InDesignMode()
        {
            return LicenseManager.UsageMode == LicenseUsageMode.Designtime;
        }
    }
}
