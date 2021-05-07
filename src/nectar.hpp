/*
 * This file is part of NectarCPP
 * Copyright (c) 2020 - 2020 Adrien THIERRY
 * https://nectar-lang.org - https://seraum.com/
 *
 * sources : https://github.com/nectar-lang/NectarCPP
 * 
 * NectarCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarCPP.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <stdarg.h>
#include <tuple>
#include <bitset>

#ifdef __Nectar_ENV_ARDUINO
#include <util/delay.h>
#include <WString.h>
#include <new.h>
#include <time.h>
#include <nonstd-function.h>
#include <math.h>
#undef max
#undef min
#include <limits>
#else
#include <functional>
#include <cmath>
#include <limits>
#include <mutex>
#include <chrono>
#include <thread>
#endif

namespace NectarCore
{
	struct VAR;
	
	namespace Class
	{
		class Base;
		class Undefined;
		class Boolean;
		class String;
		class Array;
		class Object;
		class Function;
		class Native;
		class Struct;
		class FixedArray;
		
		template<typename T>
		class NativeTPL;
	}
} // namespace NectarCore

#include "enum.h"
#include "types.h"
#include "values_header.h"
#include "class_header.h"
#include "helpers_header.h"
#include "component_header.h"
#include "var_header.h"
