// JsContext.h

#pragma once
#include <v8.h>
#include <string>

using namespace std;
using namespace v8;

namespace V8DOM_NET 
{
	public class JsContext
	{
	public:
		// Constructor. Takes in an object to expose to JS
		JsContext(/*System::Object^ o*/);

		// Runs some JS 
		void RunJS(/*System::String^ js*/ string js);

		// Destructor.  
		~JsContext();
		// Finalizer
		//!JsContext();
	private:
		Persistent<Context>* _context;
		Persistent<ObjectTemplate>* _global;
	};
}
