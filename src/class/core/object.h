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
#include "object_header.h"

namespace NectarCore::Class
{
	NectarCore::VAR __proxy;
	// Constructors
	Object::Object() {}
	// Methods
	inline void Object::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	inline void Object::jsDelete(const std::string _key) noexcept
	{
#ifndef __Nectar__OBJECT_VECTOR
		object.erase(_key);
#else
		for (NectarCore::Type::object_t::iterator it = object.begin(); it != object.end(); ++it)
		{
			if (_key.compare(it->first) == 0)
			{
				object.erase(it);
				return;
			}
		}
#endif
	}
	inline void *Object::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Object::operator std::string() const noexcept
	{
		return "[object Object]";
	}
	// Main operators

	NectarCore::VAR &Object::operator[](NectarCore::VAR key)
	{
		return (*this)[(std::string)key];
	}

	NectarCore::VAR &Object::operator[](int key)
	{
		return (*this)[std::to_string(key)];
	}

	NectarCore::VAR &Object::operator[](double key)
	{
		return (*this)[std::to_string(key)];
	}

	NectarCore::VAR &Object::operator[](const char *key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;

#ifndef __Nectar__OBJECT_VECTOR
		NectarCore::VAR &_obj = object[_str];
		if (_obj.type != NectarCore::Enum::Type::Undefined)
		{
			if (!property[1])
			{
				if (!property[0])
					return _obj;
				else
				{
					__proxy = _obj;
					return __proxy;
				}
			}
			else
			{
				if (_obj.type == NectarCore::Enum::Type::Function)
				{
					((NectarCore::Class::Function *)_obj.data.ptr)->This.type = NectarCore::Enum::Type::Object;
					((NectarCore::Class::Function *)_obj.data.ptr)->This.data.ptr = this;
				}
				if (!property[0])
					return _obj;
				else
				{
					__proxy = _obj;
					return __proxy;
				}
			}
		}
		if (_sview.compare("toString") == 0 || _sview.compare("toLocaleString") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon(return __Nectar_Object_Stringify(this););
		}
		else if (_sview.compare("valueOf") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon(return this;);
		}

		if (!property[0])
			return _obj;
		__proxy = NectarCore::Global::undefined;
		return __proxy;
#else
		for (auto &search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				if (!property[1])
				{
					return search.second;
				}
				else
				{
					if (search.second.type == NectarCore::Enum::Type::Function)
					{
						((NectarCore::Class::Function *)search.second.data.ptr)->This.type = NectarCore::Enum::Type::Object;
						((NectarCore::Class::Function *)search.second.data.ptr)->This.data.ptr = this;
					}

					return search.second;
				}
			}
		}
		if (_sview.compare("toString") == 0 || _sview.compare("toLocaleString") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon(return __Nectar_Object_Stringify(this);)));
		}
		else if (_sview.compare("valueOf") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon(return this;)));
		}
		else
		{
			object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		}

		return object[object.size() - 1].second;
#endif
	}

	NectarCore::VAR Object::_toPrimitive(std::true_type) const
	{
#ifndef __Nectar__OBJECT_VECTOR
		if (!object.contains("valueOf") && !object.contains("toString"))
		{
			return NectarCore::Global::undefined;
		}
#endif
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
	NectarCore::VAR Object::_toPrimitive(std::false_type) const
	{
#ifndef __Nectar__OBJECT_VECTOR
		if (!object.contains("valueOf") && !object.contains("toString"))
		{
			return "[object Object]";
		}
#endif
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
} // namespace NectarCore::Class
