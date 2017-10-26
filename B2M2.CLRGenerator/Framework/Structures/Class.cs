using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace B2M2.CLRGenerator.Framework
{
    class Class
    {
        private static string MethodNameAndTypeRegex = "\\s+([const A-Za-z0-9:*&_]+)\\s+([A-Za-z0-9]+)\\(";
        private static string IsInlineMethodRegex = "^inline";

        public string Name { get; private set; }
        public string BodyText { get; private set; }

        public List<Method> Methods { get; private set; } = new List<Method>();

        public Class(string name, string bodyText)
        {
            Name = name;
            BodyText = bodyText;

            ParseMethods();
        }

        private void ParseMethods()
        {
            MatchCollection methodNameMatches = Regex.Matches(BodyText, MethodNameAndTypeRegex);
            foreach(Match methodNameMatch in methodNameMatches)
            {
                string methodName = methodNameMatch.Groups[2].Value;
                string returnType = methodNameMatch.Groups[1].Value;

                bool isInline = Regex.IsMatch(returnType, IsInlineMethodRegex);
                if(isInline)
                    returnType = returnType.Replace("inline", string.Empty);

                Method method = new Method(methodName, returnType, isInline);
                Methods.Add(method);
            }
        }
    }
}
