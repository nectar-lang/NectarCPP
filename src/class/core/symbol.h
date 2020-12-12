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

#pragma once
// #include "symbol_header.h"
// #include <limits>

namespace NectarCore::Class
{
	// Constructors
	Symbol::Symbol()
	{
		value = SymbolCounter++;
	}
	Symbol::Symbol(NectarCore::VAR val)
	{
		name = (std::string)val;
	}
	Symbol::Symbol(const char *val)
	{
		name = val;
	}
	// Methods
	inline void Symbol::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	inline void *Symbol::Copy() noexcept
	{
		auto obj = new Symbol(name);
		obj->value = value;
		--SymbolCounter;
		return obj;
	}
	// Native cast
	Symbol::operator bool() const noexcept { return true; }
	Symbol::operator double() const noexcept
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return std::numeric_limits<double>::quiet_NaN();
	}
	Symbol::operator int() const noexcept
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return std::numeric_limits<int>::quiet_NaN();
	}
	Symbol::operator long long() const noexcept
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Symbol::operator std::string() const noexcept
	{
		return "Symbol(" + name + ")";
	}
	// Main operators
	NectarCore::VAR const Symbol::operator[](NectarCore::VAR key) const
	{
		if (key == "toString" || key == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return toString(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		if (key == "valueOf" || key == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return valueOf(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		return NectarCore::Global::undefined;
	}

	NectarCore::VAR &Symbol::operator[](NectarCore::VAR key)
	{
		if (key == "toString" || key == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return toString(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		if (key == "valueOf" || key == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return valueOf(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		auto _obj = NectarCore::Global::undefined;
		return _obj;
	}

	NectarCore::VAR &Symbol::operator[](int key)
	{
		return NectarCore::Global::undefined;
	}

	NectarCore::VAR &Symbol::operator[](double key)
	{
		return NectarCore::Global::undefined;
	}

	NectarCore::VAR &Symbol::operator[](const char *key)
	{
		if (key == "toString" || key == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return toString(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		if (key == "valueOf" || key == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return valueOf(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		auto _obj = NectarCore::Global::undefined;
		return _obj;
	}

	// Comparation operators
	bool Symbol::operator!() const { return false; }
	bool Symbol::operator==(const Symbol &_v1) const { return value == _v1.value; }
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
	bool Symbol::operator!=(const Symbol &_v1) const { return value != _v1.value; }
	bool Symbol::operator<(const Symbol &_v1) const { return false; }
	bool Symbol::operator<=(const Symbol &_v1) const { return false; }
	bool Symbol::operator>(const Symbol &_v1) const { return false; }
	bool Symbol::operator>=(const Symbol &_v1) const { return false; }
	// Numeric operators
	Symbol Symbol::operator+() const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator-() const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator++(const int _v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator--(const int _v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator+(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator+=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator-(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator-=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator*(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator*=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	// TODO: "**" and "**=" operators
	Symbol Symbol::operator/(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator/=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator%(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator%=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator&(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator|(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator^(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator~() const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator>>(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator<<(const Symbol &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator&=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator|=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator^=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator>>=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	Symbol Symbol::operator<<=(const Symbol &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return Symbol();
	}
	NectarCore::VAR Symbol::valueOf(NectarCore::VAR *args, int _length) const
	{
		return *this;
	}
	NectarCore::VAR Symbol::toString(NectarCore::VAR *args, int _length) const
	{
		return (std::string)*this;
	}
} // namespace NectarCore::Class
