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
#include "symbol_header.h"

namespace NectarCore::Class
{
	// Constructors
	Symbol::Symbol()
	{
	}
	Symbol::Symbol(std::string val)
	{
		name = val.c_str();
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
		return this;
	}
	// Native cast
	Symbol::operator std::string() const noexcept
	{
		return (std::string)_toPrimitive(std::false_type());
	}

	// Main operators
	NectarCore::VAR const Symbol::operator[](NectarCore::VAR key) const
	{
		std::string str = key;
		if (str == "toString" || str == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return toString(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		if (str == "valueOf") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return valueOf(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		return NectarCore::Global::undefined;
	}

	NectarCore::VAR &Symbol::operator[](NectarCore::VAR key)
	{
		std::string str = key;
		if (str == "toString" || str == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return toString(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		if (str == "valueOf") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return valueOf(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		auto _obj = NectarCore::Global::undefined;
		return _obj;
	}

	NectarCore::VAR &Symbol::operator[](const char *key)
	{
		std::string str = key;
		if (str == "toString" || str == "toLocaleString") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return toString(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		if (str == "valueOf") {
			auto obj = __Nectar_Create_Var_Scoped_Anon(
				return valueOf(__Nectar_VARARGS, __Nectar_VARLENGTH);
			);
			return obj;
		}
		static auto _obj = NectarCore::Global::undefined;
		return _obj;
	}

	NectarCore::VAR Symbol::_toPrimitive(std::true_type) const
	{
		static NectarCore::VAR _arg = {};
		auto &_valueOf = (*this)["valueOf"];
		if (_valueOf.type == NectarCore::Enum::Type::Function)
		{
			auto primitive = _valueOf(_arg, 0);
			if (primitive.isPrimitive())
				return primitive;
		}
		auto &_toString = (*this)["toString"];
		if (_toString.type == NectarCore::Enum::Type::Function)
		{
			auto string = _toString(_arg, 0);
			if (string.isPrimitive())
				return string;
		}
		throw InvalidTypeException();
	}
	NectarCore::VAR Symbol::_toPrimitive(std::false_type) const
	{
		static NectarCore::VAR _arg = {};
		auto &_toString = (*this)["toString"];
		if (_toString.type == NectarCore::Enum::Type::Function)
		{
			auto string = _toString(_arg, 0);
			if (string.isPrimitive())
				return string;
		}
		auto &_valueOf = (*this)["valueOf"];
		if (_valueOf.type == NectarCore::Enum::Type::Function)
		{
			auto primitive = _valueOf(_arg, 0);
			if (primitive.isPrimitive())
				return primitive;
		}
		throw InvalidTypeException();
	}

	NectarCore::VAR Symbol::valueOf(NectarCore::VAR *args, int _length) const
	{
		return this;
	}
	NectarCore::VAR Symbol::toString(NectarCore::VAR *args, int _length) const
	{
		return std::string("Symbol(") + name + ")";
	}
} // namespace NectarCore::Class
