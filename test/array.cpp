#include "../src/nectar.hpp"
using namespace NectarCore;
using namespace NectarCore::Global;
using namespace NectarCore::Class;
using namespace NectarCore::Functions;

int main(int argc, char** argv)
{
	var arr = new Array();
	println(arr);
	
	var initArr = new Array(0, "one", 2, "three");
	println(initArr);

	var initArr2 = {"zero", 1, "two", 3};
	println(initArr2);

	return 0;
}
