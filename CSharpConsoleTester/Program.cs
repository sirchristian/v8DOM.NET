using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using V8DOM_NET;

namespace CSharpConsoleTester
{
	class Program
	{
		static void Main(string[] args)
		{
			string js1 = @"
var add = function addFunc(x, y) {
	return x + y;
};
add(4,4);";

			string js2 = @"
var add = function addFunc(x, y) {
	return x + y;
};
log(add(4,4));
log(document.getElementById());
";
			//JsContext jsctx = new JsContext("");
			//jsctx.RunJS();


			Lib l = new Lib();
			
			Console.WriteLine(l.RunJS(js1));
		}
	}
}
