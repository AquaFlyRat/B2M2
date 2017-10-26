using B2M2.CLRGenerator.Framework;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace B2M2.CLRGenerator
{
    public partial class Demo : Form
    {
        public Demo()
        {
            InitializeComponent();
        }

        private void cppInput_TextChanged(object sender, EventArgs e)
        {
            string output = "";
            FileParser parser = new FileParser();
            parser.SetText(cppInput.Text);
            parser.Parse();
            foreach(var classData in parser.Classes)
            {
                StringBuilder strBuilder = new StringBuilder();
                strBuilder.AppendLine("#using <mscorlib.dll>");
                
                strBuilder.AppendLine(string.Format("public ref class {0} {{", classData.Name));
                strBuilder.AppendLine("public:");
                foreach(Method method in classData.Methods)
                {
                    strBuilder.AppendLine(string.Format("\tpublic {0} {1}() {{}}", method.ReturnType.TypeName, method.Name));
                }

                strBuilder.AppendLine("}");
                output += strBuilder.ToString();
            }
            csOutput.Text = output;
        }
    }
}
