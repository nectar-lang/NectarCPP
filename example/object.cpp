#include "../src/nectar.hpp"
using namespace Nectar;
using namespace Nectar::Global;
using namespace Nectar::Class;
using namespace Nectar::Functions;

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
