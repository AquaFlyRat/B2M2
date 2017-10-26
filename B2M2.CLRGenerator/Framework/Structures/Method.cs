using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B2M2.CLRGenerator.Framework
{
    class Method
    {
        public string Name { get; private set; }
        public CppType ReturnType { get; private set; }
        public bool IsInline { get; private set; }

        public Method(string name, string returnType, bool isInline)
        {
            Name = name;
            ReturnType = new CppType(returnType);
            IsInline = isInline;
        }
    }
}
