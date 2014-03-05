// This is the main DLL file.

#include "stdafx.h"
#include "Lib.h"
#include <v8.h>
#include <string>
#include "JsContext.h"

using namespace std;
using namespace v8;

namespace V8DOM_NET {
	
	class TestDOM {
	public: 
		// DOM Constructor
		TestDOM(string doc) {
			document = doc;
		}
		
		// our document
		string document;

		// Creates a new dom and that can be passed to JS
		static Handle<ObjectTemplate> NewDOMTemplate() {
			// Create the handle scope to create the DOM
			HandleScope handle_scope;

			Handle<ObjectTemplate> dom = ObjectTemplate::New();
			dom->SetInternalFieldCount(1);

			// Add the function getElementById to the document
			dom->Set(String::New("getElementById"), FunctionTemplate::New(getElementById));

			// Add URL as an accessor to URL
			dom->SetAccessor(String::NewSymbol("URL"), URL);


			// Return the result through the current handle scope.
			return handle_scope.Close(dom);
		}

	private:
		// Define getElementById
		static Handle<Value> getElementById(const Arguments& args) { 
			return String::New("hello"); 
		}
		// Define URL
		static Handle<Value> URL(Local<String> id, const AccessorInfo& info) { 
			return String::New("http://URL"); 
		}
	};

	// http://msdn.microsoft.com/en-us/library/1b4az623%28VS.80%29.aspx
	// converts System::String to std::string
	void Lib::MarshalString (System::String^ s, string & os) {
	   using namespace System::Runtime::InteropServices;
	   const char* chars = 
		  (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	   os = chars;
	   Marshal::FreeHGlobal(System::IntPtr((void*)chars));
	}

	// Define log as a wrapper around printf
	static Handle<Value> log(const Arguments& args) { 
		if (args.Length() < 1) return v8::Undefined();
		HandleScope scope;
		Handle<Value> arg = args[0];
		String::AsciiValue ascii(arg);
		printf("%s\n", *ascii);
		return v8::Undefined();
	}

	// Runs some JS
	System::String^ Lib::RunJS(System::String^ js)
	{
		
		// Create a stack-allocated handle scope.
		HandleScope handle_scope;

		// Create the global object 
		Handle<ObjectTemplate> global = ObjectTemplate::New();

		// Wrap printf to log in the global scope
		global->Set(String::New("log"), FunctionTemplate::New(log));

		Persistent<Context> context = Context::New(NULL, global);
		Context::Scope context_scope(context);

		// Create a DOM template object
		Handle<v8::ObjectTemplate> dom_templ = TestDOM::NewDOMTemplate();

		// Create the DOM and attach it so JS can access it
		TestDOM* testdom = new TestDOM("<div id=\"a_div\">HTML Text</div>");
		Handle<v8::Object> document = dom_templ->NewInstance();
		
		document->SetInternalField(0, External::New(testdom));

		// Set the document object as a property on the global object.
		context->Global()->Set(String::New("document"), document);

		//global->SetAccessor(String::New("x"), XGetter, XSetter);
		//result->SetAccessor(String::NewSymbol("path"), GetPath);

		// Create a string containing the JavaScript source code.
		string s;
		Lib::MarshalString(js, s);
		Handle<String> source = String::New(s.c_str(), s.length());

		// Compile the source code.
		Handle<Script> script = Script::Compile(source);
		
		// Run the script to get the result.
		Handle<Value> result = script->Run();

		// Dispose the persistent context.
		context.Dispose();

		JsContext jsctx = JsContext();
		jsctx.RunJS(s);

		// Convert the result to a CLR string and return it
		String::AsciiValue ascii(result);
		System::String^ clrString = gcnew System::String(*ascii);
		return clrString;
	};

	void Lib::AttachObject(System::Object^ o)
	{
		return;
	}
}