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
auto __fn = []() {std::cout << "Hello" << std::endl;};

int main(int argc, char** argv)
{
	try 
	{
		var _struct = new NativeTPL(new s({3,4}));
		std::cout << _struct.toNative(typeStruct)->i << std::endl;
		
		var _fn = new NativeTPL(__fn);
		_fn.toNative(__fn)();
	}
	catch(var e)
	{
		println(e);
	}
	return 0;
}
