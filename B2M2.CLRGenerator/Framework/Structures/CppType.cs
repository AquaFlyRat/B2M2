using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace B2M2.CLRGenerator.Framework
{
    class CppType
    {
        public bool IsPointer { get; private set; }
        public string TypeName { get; private set; }
        public bool IsReference { get; private set; }
        public bool IsConst { get; private set; }

        public CppType(string typeText)
        {
            IsConst = Regex.IsMatch(typeText, "const\\s+[A-Za-z0-9:*&]");
            IsPointer = typeText.Contains("*");
            IsReference = typeText.Contains("&");

            string regex = "(const\\s+)?([A-Za-z0-9_:]+)";
            TypeName = Regex.Match(typeText, regex).Groups[0].Value;
        }
    }
}
