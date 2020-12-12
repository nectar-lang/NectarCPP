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
#include "function_header.h"
// #include <functional>
#define __Nectar_Function_Methods__ \
	__Nectar_Object_Lazy_Loader("prototype");\
	__Nectar_Method_Lazy_Loader("apply", apply);\
	__Nectar_Method_Lazy_Loader("bind", bind);\
	__Nectar_Method_Lazy_Loader("call", call);\
	__Nectar_Method_Lazy_Loader("toString", toString);\
	__Nectar_Method_Lazy_Loader("valueOf", valueOf);

namespace NectarCore::Class
{
	// Constructors
	Function::Function() {}
	Function::Function(void *val)
	{
		counter++;
		value = (NectarCore::Type::function_t *)val;
	}
	Function::Function(void *val, NectarCore::VAR bind)
	{
		counter++;
		This = bind;
		value = (NectarCore::Type::function_t *)val;
	}
	// Methods
	inline void Function::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete (NectarCore::Type::function_t *)value;
			delete this;
		}
	}
	inline void Function::jsDelete(const std::string key) noexcept
	{
#ifndef __Nectar__OBJECT_VECTOR
		object.erase(key);
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
	inline void *Function::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Function::operator std::string() const noexcept
	{
#ifdef __Nectar_DEBUG
		return code;
#else
		return "[native code]";
#endif
	}
	// Main operators
	NectarCore::VAR const Function::operator[](NectarCore::VAR key) const
	{
		return NectarCore::Global::undefined;
	}

	NectarCore::VAR &Function::operator[](NectarCore::VAR key)
	{
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
#ifndef __Nectar__OBJECT_VECTOR
		NectarCore::VAR &_obj = object[_str];
		if (_obj.type != NectarCore::Enum::Type::Undefined)
			return _obj;
#else
		for (auto &search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
#endif
		if (_sview.compare("length") == 0)
		{
			auto length = NectarCore::VAR(0);
			return length;
		}
		__Nectar_Function_Methods__
#ifndef __Nectar__OBJECT_VECTOR
		return _obj;
#else
		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
#endif

	NectarCore::VAR &Function::operator[](int key)
	{
		std::string _str = std::to_string(key);
		NectarCore::Type::StringView _sview = _str;
#ifndef __Nectar__OBJECT_VECTOR
		NectarCore::VAR &_obj = object[_str];
		if (_obj.type != NectarCore::Enum::Type::Undefined)
			return _obj;
#else
		for (auto &search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
#endif
		__Nectar_Object_Lazy_Loader("prototype");
#ifndef __Nectar__OBJECT_VECTOR
		return _obj;
#else
		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
#endif
	}

#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Function::operator[](double key)
	{
		std::string _str = std::to_string(key);
		NectarCore::Type::StringView _sview = _str;

		NectarCore::VAR &_obj = object[_str];
		if (_obj.type != NectarCore::Enum::Type::Undefined)
			return _obj;

		__Nectar_Object_Lazy_Loader("prototype");

		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);

		return _obj;
	}
#else
	NectarCore::VAR &Function::operator[](double key)
	{
		std::string _str = std::to_string(key);
		NectarCore::Type::StringView _sview = _str;

		for (auto &search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		__Nectar_Object_Lazy_Loader("prototype");

		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
#endif

#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Function::operator[](const char *key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;

		NectarCore::VAR &_obj = object[_str];
		if (_obj.type != NectarCore::Enum::Type::Undefined)
			return _obj;

		__Nectar_Object_Lazy_Loader("prototype");

		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);

		return _obj;
	}
#else
	NectarCore::VAR &Function::operator[](const char *key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;

		for (auto &search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		__Nectar_Object_Lazy_Loader("prototype");

		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
#endif

	// Methods
	NectarCore::VAR Function::toString(NectarCore::VAR *_args, int _length) const
	{
		return (std::string) * this;
	}

	NectarCore::VAR Function::valueOf(NectarCore::VAR *_args, int _length) const
	{
		// TODO return this
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR Function::bind(NectarCore::VAR *_args, int _length)
	{
		return __Nectar_Create_Var_Scoped_Anon(
			counter++;
			NectarCore::VAR _bind;
			if (_length > 0) {
				_bind = _args[0];
			} NectarCore::VAR _binded = new NectarCore::Class::Function(value, _bind);
			return _binded;);
	}

	NectarCore::VAR Function::call(NectarCore::VAR *_args, int _length)
	{
		NectarCore::VAR __THIS;
		if (_length > 0)
		{
			__THIS = _args[0];
			_length--;
		}
		NectarCore::VAR _newArgs[_length];
		for (int i = 1; i < _length; i++)
			_newArgs[i - 1] = _args[i];

		return Call(__THIS, _newArgs, _length);
	}

	NectarCore::VAR Function::apply(NectarCore::VAR *_args, int _length)
	{
		NectarCore::VAR __THIS;
		if (_length > 0)
		{
			__THIS = _args[0];
			_length--;
		}

		if (_length > 0)
		{
			NectarCore::VAR _arr = _args[1];
			if (_arr.type == NectarCore::Enum::Type::Array)
			{
				NectarCore::Type::vector_t _v = ((NectarCore::Class::Array *)_arr.data.ptr)->value;
				NectarCore::VAR __ARGS[_v.size()];
				int i = 0;
				for (auto _var : _v)
				{
					__ARGS[i] = _var;
					i++;
				}
				return Call(__THIS, __ARGS, i);
			}
		}

		NectarCore::VAR __ARGS[0];
		return Call(__THIS, __ARGS, 0);
	}
} // namespace NectarCore::Class
