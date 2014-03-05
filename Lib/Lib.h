// Lib.h

#pragma once
#include <v8.h>
#include <string>

using namespace std;

namespace V8DOM_NET {

	public ref class Lib
	{
	public:
		System::String^ RunJS(System::String^ js);
		void AttachObject(System::Object^ o);

		// http://msdn.microsoft.com/en-us/library/1b4az623%28VS.80%29.aspx
		// converts System::String to std::string
		static void MarshalString(System::String^ s, string& os);
	};
}
