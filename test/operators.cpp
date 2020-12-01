#include "../src/nectar.hpp"

using namespace NectarCore;
using namespace NectarCore::Global;
using namespace NectarCore::Class;
using namespace NectarCore::Functions;

int main()
{
	try 
	{
		var a = 1;
		
		println(a + a);
		println(a + 1);
		println(a + "1");
		
		println(1 + a);
		println("1" + a);
		
		println(a - a);
		println(a - 1);
		println(a - "1");
		
		println(1 - a);
		println("1" - a);
		
		println(a * a);
		println(a * 1);
		println(a * "1");
		
		println(1 * a);
		println("1" * a);
		
		println(a / a);
		println(a / 1);
		println(a / "1");
		
		println(1 / a);
		println("1" / a);
		
		println(a == a);
		println(a == 1);
		println(a == "1");
		
		println(a != a);
		println(a != 1);
		println(a != "1");
		
		println(a > a);
		println(a > 1);
		println(a > "1");
		
		println(a < a);
		println(a < 1);
		println(a < "1");
		
		println(a >= a);
		println(a >= 1);
		println(a >= "1");
		
		println(a <= a);
		println(a <= 1);
		println(a <= "1");
		
		println(a | a);
		println(a | 1);
		println(a | "1");
		
		println(a & a);
		println(a & 1);
		println(a & "1");
		
		println(a ^ a);
		println(a ^ 1);
		println(a ^ "1");
	}
	catch(var& error)
	{
		println(error);
	}
	return 0;
}