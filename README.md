# NectarCPP
Nectar C++ lib/runtime. C++20 compatible.

# About NectarCPP
NectarCPP lets you write JS like code in C++:

```
var a = 0;
for(var i = 0; i < 100000; i++)
{
	a += i;
}
println(a);
```

# Gettin started

You need a C++ compiler (g++11 or clang++) to use NectarCPP.

Clone this repository, and create a file mycode.cpp. Add in this file the folling lines: 

```
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
```

then:
- Compile the main lib: `gcc -std=c++20 -fmodules-ts -Ofast concepts.cpp operators.cpp prototype.cpp symbol_t.cpp value.cpp var.cpp`
- Compile your code 
	* on Windows: `g++ -std=c++20 -fmodules-ts -Ofast var.o mycode.cpp -lpthread -o myapp`
	* on unix/linux: `g++ -std=c++20 -fmodules-ts -Ofast mycode.cpp nectar.o -lpthread -o myapp`
