using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace B2M2.CLRGenerator.Framework
{
    class FileParser
    {
        private string MatchClassNameRegex = "class\\s+c([A-Za-z]+)";
        private string MatchClassBodyRegex = "class\\s+c[A-Za-z]+\\s+{(.*)};";

        private string _text;
        
        public void SetText(string text)
        {
            _text = text;
        }

        public void Parse()
        {
            if (_text == null) return;

            MatchCollection classNameMatches = Regex.Matches(_text, MatchClassNameRegex);
            foreach(Match classNameMatch in classNameMatches)
            {
                if (!classNameMatch.Success) continue;
                Match bodyMatch = Regex.Match(_text, MatchClassBodyRegex, RegexOptions.Singleline);
                string name = classNameMatch.Groups[1].Value;
                string body = bodyMatch.Groups[1].Value;

                Class cppClass = new Class(name, body);
                Classes.Add(cppClass);
            }
        }

        public List<Class> Classes { get; private set; } = new List<Class>();
    }
}
