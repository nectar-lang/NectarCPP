#include "../src/nectar.hpp"
using namespace NectarCore;
using namespace NectarCore::Global;
using namespace NectarCore::Class;
using namespace NectarCore::Functions;

int main(int argc, char **argv)
{
	try
	{
		var tmp = new Array();
		var arr = new Array();
		var isPositive = __Nectar_Create_Ptr_Unscoped_Anon(
			var v = __Nectar_VARARGS[0];
			var i = __Nectar_VARARGS[1];
			var a = __Nectar_VARARGS[2];
			print("Value: " + v);
			print(" | Index: " + i);
			print(" | Array: " + a);
			print("\n");
			return v > 0;
		);
		var isEven = __Nectar_Create_Ptr_Unscoped_Anon(
			return __Nectar_VARARGS[0] % 2;
		);

		for (var i = 0, l = 10; i < l; i++)
		{
			if (i % 2)
			{
				arr[i] = i * i;
			}
			else
			{
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
	}
	catch (var &error)
	{
		println(error);
	}
	return 0;
}
