#include "../src/nectar.hpp"
using namespace NectarCore;
using namespace NectarCore::Global;
using namespace NectarCore::Class;
using namespace NectarCore::Functions;

var _isPositive (var* args, int len)
{
	var v = args[0];
	var i = args[1];
	var a = args[2];
	println("Value: " + v + " | Index: " + i + " | Array: " + a);
	return v > 0;
}

var _isEven (var* args, int len)
{
	var v = args[0];
	return v % 2;
}

int main(int argc, char** argv)
{
	var args = getArguments(argc, argv);
	
	var tmp = new Array();
	var arr = new Array();
	var isPositive = _isPositive;
	var isEven = _isEven;

	for (var i = 0, l = 10; i < l; i++)
	{
		if (i % 2) {
			arr[i] = i * i;
		} else {
			arr["push"](i);
			tmp["push"](i * i);
		}
	}
	println("Array::concat");
	println(arr["concat"](tmp));
	println("Array::copyWithin");
	println(arr["copyWithin"](2, 1, 3));
	println("Array::entries");
	println(arr["entries"]());
	println("Array::every");
	println(arr["every"](isPositive));
	println("Array::fill");
	println(arr["fill"](tmp));
	println("Array::filter");
	println(arr["filter"](isEven));
	println("Array::concat");
	println(arr["concat"](tmp));

	println("Array::keys");
	println(arr["keys"]());
	println("Array::values");
	println(arr["values"]());

	return 0;
}
