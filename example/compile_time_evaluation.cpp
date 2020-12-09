#include "../src/nectar.hpp"
using namespace NectarCore;
using namespace NectarCore::Global;
using namespace NectarCore::Class;
using namespace NectarCore::Functions;

int main(int argc, char** argv)
{
	try 
	{
		var a = 0;
		for(var i = 0; i < 100000; i++)
		{
			a += i;
		}
		println(a);
	}
	catch(var e)
	{
		println(e);
	}
	return 0;
}
