#include "../src/nectar.hpp"
using namespace NectarCore;
using namespace NectarCore::Global;
using namespace NectarCore::Class;
using namespace NectarCore::Functions;

struct s 
{
	int i = 10;
	int j;
};

s* typeStruct = new s();

int main(int argc, char** argv)
{
	try 
	{
		#if __cplusplus > 202002L
			auto __fn = []() {std::cout << "Hello" << std::endl;};
			
			var _struct = new NativeTPL(new s({3,4}));
			std::cout << _struct.toNative(typeStruct)->i << std::endl;
			
			var _fn = new NativeTPL(__fn);
			_fn.toNative(__fn)();
		#else
			var _struct = new NativeTPL<s*>(new s({3,4}));
			std::cout << _struct.toNative(typeStruct)->i << std::endl;
		#endif
	}
	catch(var e)
	{
		println(e);
	}
	return 0;
}
