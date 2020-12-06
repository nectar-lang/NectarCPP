#include "../src/nectar.hpp"
using namespace NectarCore;
using namespace NectarCore::Global;
using namespace NectarCore::Class;
using namespace NectarCore::Functions;

int main(int argc, char** argv)
{
	var args = getArguments(argc, argv);
	println(args);
	
	var o = new Object();
	o["int"] = 1;
	o["string"] = "str";
	println(o);

	return 0;
}
