#include "stdafx.h"
#include "JsContext.h"
#include "Lib.h"
#include <v8.h>
#include <string>

using namespace std;
using namespace v8;

namespace V8DOM_NET 
{

	JsContext::JsContext(/*System::Object^ o*/)
	{
		// Create a handle scope to hold the temporary references.
		HandleScope handle_scope;

		// Setup the global object 
		Handle<ObjectTemplate> global = ObjectTemplate::New();
		_global = &Persistent<ObjectTemplate>::New(global);

		// Instanciate the global context
		Persistent<Context> context = Context::New(NULL, *_global);
		_context = &context;

		// Enter in our global context
		Context::Scope context_scope(*_context);

		// TODO: Insert object 'o' into global context
	}

	void JsContext::RunJS(/*System::String^ js*/ string js)
	{
		// Create a handle scope to hold the temporary references.
		HandleScope handle_scope;



		// Convert System::String => std::string
		//string s;
		//Lib::MarshalString(js, s);
		Handle<String> source = String::New(js.c_str(), js.length());

		// Compile the source code
		Handle<Script> script = Script::Compile(source);
		
		// Run the script to get the result.
		Handle<Value> result = script->Run();
	}


	JsContext::~JsContext()
	{
		// Dispose the persistent context.
		_context->Dispose();
		delete _context;
	}


}