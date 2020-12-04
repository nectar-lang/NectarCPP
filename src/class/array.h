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
#include "array_header.h"
#include <sstream>
#include <limits>
		
namespace NectarCore::Class
{
	// Constructors
	Array::Array()
	{

	}
	Array::Array(NectarCore::Type::vector_t vec)
	{
		value = vec;
	}
	// Methods
	inline void Array::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	inline void Array::jsDelete(NectarCore::VAR _key) noexcept
	{
		if(_key.type == NectarCore::Enum::Type::String)
		{
			#ifndef __Nectar__OBJECT_VECTOR
				object.erase((std::string)_key);
			#else
				for (NectarCore::Type::object_t::iterator it = object.begin() ; it != object.end(); ++it)
				{
					if (((std::string_key)).compare(it->first) == 0)
					{
						object.erase(it);
						return;
					}
				}
			#endif
		}
		else if(_key.type == NectarCore::Enum::Type::Number)
		{
			value[(double)_key] = NectarCore::Global::undefined;
		}
	}
	inline void* Array::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Array::operator bool() const noexcept { return true; }
	Array::operator double() const noexcept { return (double)value[0]; }
	Array::operator int() const noexcept { return (int)value[0]; }
	Array::operator long long() const noexcept { return (long long)value[0]; }
	Array::operator std::string() const noexcept
	{
		NectarCore::VAR _arg = {};
		auto str = (*this)["toString"](_arg, 0);
		return (std::string)str;
	}
	// Main operators
	NectarCore::VAR const Array::operator[](NectarCore::VAR key) const
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
		}
		
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR const Array::operator[](int key) const
	{
		if (key >= 0 && key <= value.size())
		{
			return value.at(key);
		}
		
		return NectarCore::Global::undefined;
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Array::operator[](NectarCore::VAR key)
	{	
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;

			if (i < 0)
			{
				return NectarCore::Global::undefined;
			}
			else
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
				}
			}
			return value[i];
		}
		
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj) return _obj;
		
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("@@iterator", __iterator);
		__Nectar_Method_Lazy_Loader("@@unscopables", __unscopables);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("copyWithin", copyWithin);
		__Nectar_Method_Lazy_Loader("entries", entries);
		__Nectar_Method_Lazy_Loader("every", every);
		__Nectar_Method_Lazy_Loader("fill", fill);
		__Nectar_Method_Lazy_Loader("filter", filter);
		__Nectar_Method_Lazy_Loader("find", find);
		__Nectar_Method_Lazy_Loader("findIndex", findIndex);
		__Nectar_Method_Lazy_Loader("flat", flat);
		__Nectar_Method_Lazy_Loader("flatMap", flatMap);
		__Nectar_Method_Lazy_Loader("forEach", forEach);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("join", join);
		__Nectar_Method_Lazy_Loader("keys", keys);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("map", map);
		__Nectar_Method_Lazy_Loader("pop", pop);
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("reduce", reduce);
		__Nectar_Method_Lazy_Loader("reduceRight", reduceRight);
		__Nectar_Method_Lazy_Loader("reverse", reverse);
		__Nectar_Method_Lazy_Loader("shift", shift);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("some", some);
		__Nectar_Method_Lazy_Loader("sort", sort);
		__Nectar_Method_Lazy_Loader("splice", splice);
		__Nectar_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("unshift", unshift);
		__Nectar_Method_Lazy_Loader("values", values);
		
		return _obj;
	}
	#else
	NectarCore::VAR &Array::operator[](NectarCore::VAR key)
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return NectarCore::Global::undefined;
			}
			else
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
				}
			}
			return value[i];
		}
		
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("@@iterator", __iterator);
		__Nectar_Method_Lazy_Loader("@@unscopables", __unscopables);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("copyWithin", copyWithin);
		__Nectar_Method_Lazy_Loader("entries", entries);
		__Nectar_Method_Lazy_Loader("every", every);
		__Nectar_Method_Lazy_Loader("fill", fill);
		__Nectar_Method_Lazy_Loader("filter", filter);
		__Nectar_Method_Lazy_Loader("find", find);
		__Nectar_Method_Lazy_Loader("findIndex", findIndex);
		__Nectar_Method_Lazy_Loader("flat", flat);
		__Nectar_Method_Lazy_Loader("flatMap", flatMap);
		__Nectar_Method_Lazy_Loader("forEach", forEach);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("join", join);
		__Nectar_Method_Lazy_Loader("keys", keys);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("map", map);
		__Nectar_Method_Lazy_Loader("pop", pop);
		__Nectar_Method_Lazy_Loader("reduce", reduce);
		__Nectar_Method_Lazy_Loader("reduceRight", reduceRight);
		__Nectar_Method_Lazy_Loader("reverse", reverse);
		__Nectar_Method_Lazy_Loader("shift", shift);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("some", some);
		__Nectar_Method_Lazy_Loader("sort", sort);
		__Nectar_Method_Lazy_Loader("splice", splice);
		__Nectar_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("unshift", unshift);
		__Nectar_Method_Lazy_Loader("values", values);
		

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	NectarCore::VAR &Array::operator[](int key)
	{
		if (key < 0)
		{
			return NectarCore::Global::undefined;
		}
		else
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
		}
		return value[key];
	}
	
	NectarCore::VAR &Array::operator[](double key)
	{
		if (key < 0)
		{
			return NectarCore::Global::undefined;
		}
		else
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
		}
		return value[key];
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Array::operator[](const char* key)
	{		
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj) return _obj;
		
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("@@iterator", __iterator);
		__Nectar_Method_Lazy_Loader("@@unscopables", __unscopables);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("copyWithin", copyWithin);
		__Nectar_Method_Lazy_Loader("entries", entries);
		__Nectar_Method_Lazy_Loader("every", every);
		__Nectar_Method_Lazy_Loader("fill", fill);
		__Nectar_Method_Lazy_Loader("filter", filter);
		__Nectar_Method_Lazy_Loader("find", find);
		__Nectar_Method_Lazy_Loader("findIndex", findIndex);
		__Nectar_Method_Lazy_Loader("flat", flat);
		__Nectar_Method_Lazy_Loader("flatMap", flatMap);
		__Nectar_Method_Lazy_Loader("forEach", forEach);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("join", join);
		__Nectar_Method_Lazy_Loader("keys", keys);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("map", map);
		__Nectar_Method_Lazy_Loader("pop", pop);
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("reduce", reduce);
		__Nectar_Method_Lazy_Loader("reduceRight", reduceRight);
		__Nectar_Method_Lazy_Loader("reverse", reverse);
		__Nectar_Method_Lazy_Loader("shift", shift);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("some", some);
		__Nectar_Method_Lazy_Loader("sort", sort);
		__Nectar_Method_Lazy_Loader("splice", splice);
		__Nectar_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("unshift", unshift);
		__Nectar_Method_Lazy_Loader("values", values);
		
		return _obj;
	}
	#else
	NectarCore::VAR &Array::operator[](const char* key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("@@iterator", __iterator);
		__Nectar_Method_Lazy_Loader("@@unscopables", __unscopables);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("copyWithin", copyWithin);
		__Nectar_Method_Lazy_Loader("entries", entries);
		__Nectar_Method_Lazy_Loader("every", every);
		__Nectar_Method_Lazy_Loader("fill", fill);
		__Nectar_Method_Lazy_Loader("filter", filter);
		__Nectar_Method_Lazy_Loader("find", find);
		__Nectar_Method_Lazy_Loader("findIndex", findIndex);
		__Nectar_Method_Lazy_Loader("flat", flat);
		__Nectar_Method_Lazy_Loader("flatMap", flatMap);
		__Nectar_Method_Lazy_Loader("forEach", forEach);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("join", join);
		__Nectar_Method_Lazy_Loader("keys", keys);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("map", map);
		__Nectar_Method_Lazy_Loader("pop", pop);
		__Nectar_Method_Lazy_Loader("reduce", reduce);
		__Nectar_Method_Lazy_Loader("reduceRight", reduceRight);
		__Nectar_Method_Lazy_Loader("reverse", reverse);
		__Nectar_Method_Lazy_Loader("shift", shift);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("some", some);
		__Nectar_Method_Lazy_Loader("sort", sort);
		__Nectar_Method_Lazy_Loader("splice", splice);
		__Nectar_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("unshift", unshift);
		__Nectar_Method_Lazy_Loader("values", values);
		

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	// Comparation operators
	Array Array::operator!() const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	
	// Numeric operators
	Array Array::operator+() const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator-() const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator++(const int _v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator--(const int _v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator+(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator+=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator-(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator-=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator*(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator*=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	// TODO: "**" and "**=" operators
	Array Array::operator/(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator/=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator%(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator%=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator&(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator|(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator^(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator~() const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator>>(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator<<(const Array &_v1) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator&=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator|=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator^=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator>>=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	Array Array::operator<<=(const Array &_v1)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Array();
	}
	// TODO: ">>>" and ">>>=" operators
	
	
	NectarCore::VAR Array::__iterator(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::__unscopables(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::concat(NectarCore::VAR* args, int _length) const
	{
		auto res = new Array();
		auto &arr = res->value;
		for (int i = 0; i < _length; ++i)
		{
			auto &vec = ((Array*)args[i].data.ptr)->value;
			arr.insert(arr.end(), vec.begin(), vec.end());
		}
		return res;
	}
	NectarCore::VAR Array::copyWithin(NectarCore::VAR* args, int _length)
	{
		if (_length == 0 || value.empty()) return this;
		int size = value.size();

		int target = (int)args[0];
		if (target < 0) target += size;
		if (target > size) return this;
		int start = _length > 1 ? (int)args[1] : 0;
		if (start < 0) start += size;
		int end = _length > 2 ? (int)args[2] : size;
		if (end < 0) end += size;
		std::copy(value.begin() + start, value.begin() + end, value.begin() + target);
		return this;
	}
	NectarCore::VAR Array::entries(NectarCore::VAR* args, int _length) const
	{
		auto res = new Array();
		auto& arr = res->value;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto entry = NectarCore::Type::vector_t({ i, value[i] });
			arr.push_back(NectarCore::VAR(new Array(entry)));
		}
		return res;
	}
	NectarCore::VAR Array::every(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto& func = *((NectarCore::Class::Function*)args[0].data.ptr);
		auto& _this = _length > 1 ? args[1] : func.This;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto& el = value[i];
			if (!(bool)el.property[1]) continue;
			NectarCore::VAR args[] = { el, i, this };
			if (!func.Call(_this, args, 3)) return false;
		}
		return true;
	}
	NectarCore::VAR Array::fill(NectarCore::VAR* args, int _length)
	{
		auto& val = _length ? args[0] : NectarCore::Global::undefined;
		value.assign(value.size(), val);
		return this;
	};
	NectarCore::VAR Array::filter(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto res = new Array();
		auto& arr = res->value;
		auto& func = *((NectarCore::Class::Function*)args[0].data.ptr);
		auto& _this = _length > 1 ? args[1] : func.This;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto el = value[i];
			if (!(bool)el.property[1]) continue;
			NectarCore::VAR args[] = { el, i, this };
			if (func.Call(_this, args, 3)) arr.push_back(el);
		}
		return res;
	}
	NectarCore::VAR Array::find(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto& func = *((NectarCore::Class::Function*)args[0].data.ptr);
		auto& _this = _length > 1 ? args[1] : func.This;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto& el = value[i];
			if (!(bool)el.property[1]) continue;
			NectarCore::VAR args[] = { el, i, this };
			if (func.Call(_this, args, 3)) return el;
		}
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR Array::findIndex(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto& func = *((NectarCore::Class::Function*)args[0].data.ptr);
		auto& _this = _length > 1 ? args[1] : func.This;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto& el = value[i];
			if (!(bool)el.property[1]) continue;
			NectarCore::VAR args[] = { el, i, this };
			if (func.Call(_this, args, 3)) return i;
		}
		return -1;
	}
	NectarCore::Type::vector_t Array::_flat(double depth) const
	{
		NectarCore::Type::vector_t arr = {};
		for (auto& el : value)
		{
			if (!(bool)el.property[1]) continue;
			if (el.type == NectarCore::Enum::Type::Array && depth > 0)
			{
				auto vec = ((Array*)el.data.ptr)->_flat(depth - 1);
				arr.insert(arr.end(), vec.begin(), vec.end());
			}
			else
			{
				arr.push_back(el);
			}
		}
		return arr;
	}
	NectarCore::VAR Array::flat(NectarCore::VAR* args, int _length) const
	{
		// Infinity cannot be represented as int
		return new Array(_flat(_length > 0 ? (double)args[0] : 1));
	}
	NectarCore::VAR Array::flatMap(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto res = new Array();
		auto& arr = res->value;
		auto& func = *((NectarCore::Class::Function*)args[0].data.ptr);
		auto& _this = _length > 1 ? args[1] : func.This;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto el = value[i];
			if ((bool)el.property[1])
			{
				NectarCore::VAR args[] = { el, i, this };
				el = func.Call(_this, args, 3);
			}
			if (el.type == NectarCore::Enum::Type::Array)
			{
				auto& vec = ((Array*)el.data.ptr)->value;
				arr.insert(arr.end(), vec.begin(), vec.end());
			}
			else
			{
				arr.push_back(el);
			}
		}
		return res;
	}
	NectarCore::VAR Array::forEach(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto& func = *((NectarCore::Class::Function*)args[0].data.ptr);
		auto& _this = _length > 1 ? args[1] : func.This;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto& el = value[i];
			if (!(bool)el.property[1]) continue;
			NectarCore::VAR args[] = { el, i, this };
			func.Call(_this, args, 3)
		}
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR Array::includes(NectarCore::VAR* args, int _length) const
	{
		auto& search = _length > 0 ? args[0] : NectarCore::Global::undefined;
		if (search.type == NectarCore::Enum::Type::Number && std::isnan(search.data.number))
		{
			for (auto& el : value)
			{
				if ((bool)el.property[1] // Is enumerable
					&& el.type == NectarCore::Enum::Type::Number // Is number
					&& std::isnan(el.data.number) // Is NaN
				) return true;
			}
			return false;
		}
		for (auto& el : value)
		{
			if ((bool)el.property[1] // Is enumerable
				&& search.type == el.type // Is same type
				&& search == el // Is equal
			) return true;
		}
		return false;
	}
	NectarCore::VAR Array::indexOf(NectarCore::VAR* args, int _length) const
	{
		auto search = _length > 0 ? args[0] : NectarCore::Global::undefined;
		for (int i = _length > 1 ? (int)args[1] : 0, l = value.size(); i < l; ++i)
		{
			auto& el = value[i];
			if ((bool)el.property[1] // Is enumerable
				&& search.type == el.type // Is same type
				&& search == el // Is equal
			) return i;
		}
		return -1;
	}
	NectarCore::VAR Array::join(NectarCore::VAR* args, int _length) const
	{
		if (value.empty()) return "";
		std::string _str = _length ? args[0] : NectarCore::Global::undefined;
		std::stringstream stream;
		stream << (std::string)value[0];
		for (auto& el : value)
		{
			stream << _str << (std::string)el;
		}
		return stream.str();
	};
	NectarCore::VAR Array::keys(NectarCore::VAR* args, int _length) const
	{
		auto res = new Array();
		auto& arr = res->value;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			arr.push_back(i);
		}
		return res;
	}
	NectarCore::VAR Array::lastIndexOf(NectarCore::VAR* args, int _length) const
	{
		auto& search = _length > 0 ? args[0] : NectarCore::Global::undefined;
		int index = -1;
		for (int i = _length > 1 ? (int)args[1] : 0, l = value.size(); i < l; ++i)
		{
			auto& el = value[i];
			if ((bool)el.property[1] // Is enumerable
				&& search.type == el.type // Is same type
				&& search == el // Is equal
			) { index = i; }
		}
		return index;
	}
	NectarCore::VAR Array::map(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto res = new Array();
		auto& arr = res->value;
		auto& func = *((NectarCore::Class::Function*)args[0].data.ptr);
		auto& _this = _length > 1 ? args[1] : func.This;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto el = value[i];
			if ((bool)el.property[1])
			{
				NectarCore::VAR args[] = { el, i, this };
				el = func.Call(_this, args, 3);
			}
			arr.push_back(el);
		}
		return res;
	}
	NectarCore::VAR Array::pop(NectarCore::VAR* args, int _length)
	{
		auto last = value.back();
		value.pop_back();
		return last;
	}
	NectarCore::VAR Array::push(NectarCore::VAR* args, int _length)
	{
		for (int i = 0; i < _length; ++i)
		{
			value.push_back(args[i]);
		}
		return this;
	};
	NectarCore::VAR Array::reduce(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto& func = args[0];
		auto result = _length > 1 ? args[1] : value[0];
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto& el = value[i];
			if ((bool)el.property[1])
			{
				result = func(result, el, i, this);
			}
		}
		return result;
	}
	NectarCore::VAR Array::reduceRight(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto& func = args[0];
		auto result = _length > 1 ? args[1] : value[0];
		for (int i = value.size() - 1; i > -1; --i)
		{
			auto& el = value[i];
			if ((bool)el.property[1])
			{
				result = func(result, el, i, this);
			}
		}
		return result;
	}
	NectarCore::VAR Array::reverse(NectarCore::VAR* args, int _length)
	{
		std::reverse(value.begin(), value.end());
		return this;
	}
	NectarCore::VAR Array::shift(NectarCore::VAR* args, int _length)
	{
		auto ret = value.front();
		value.erase(value.begin());
		return ret;
	}
	NectarCore::VAR Array::slice(NectarCore::VAR* args, int _length) const
	{
		if (value.empty()) return new Array(value);
		int start = 0;
		int end = value.size();
		if (_length > 0)
		{
			start = (int)args[0] > -1 ? (int)args[0] : (value.size() + (int)args[0]);
			if (start > value.size()) start = value.size();
		}
		if (_length > 1)
		{
			end = (int)args[1] > 0 ? (start + (int)args[1]) : (value.size() + (int)args[1]);
			if (end > value.size()) end = value.size();
		}
		auto ret = NectarCore::Type::vector_t(value.begin() + start, value.begin() + end);
		return new Array(ret);
	}
	NectarCore::VAR Array::some(NectarCore::VAR* args, int _length) const
	{
		if (_length == 0 || args[0].type != NectarCore::Enum::Type::Function)
		{
			throw InvalidTypeException();
		}
		auto& func = *((NectarCore::Class::Function*)args[0].data.ptr);
		auto& _this = _length > 1 ? args[1] : func.This;
		for (int i = 0, l = value.size(); i < l; ++i)
		{
			auto& el = value[i];
			if (!(bool)el.property[1]) continue;
			NectarCore::VAR args[] = { el, i, this };
			if (func.Call(_this, args, 3)) return true;
		}
		return false;
	}
	NectarCore::VAR Array::sort(NectarCore::VAR* args, int _length) const
	{
		// TODO: Implement custom sorting algorithm
		// using -1/0/1 instead of true/false
		return NectarCore::Global::undefined;

		if (value.empty()) return false;
		if (_length)
		{
			// TODO: Implement
		}
		else
		{
			// Do lexicographical comparisons
			std::sort(value.begin(), value.end());
		}
		return this;
	}
	NectarCore::VAR Array::splice(NectarCore::VAR* args, int _length)
	{
		if (_length == 0) return new Array(value);
		auto ret = slice(args, _length);
		int start = 0;
		int end = value.size();
		if (_length > 0)
		{
			start = (int)args[0] > -1 ? (int)args[0] : (value.size() + (int)args[0]);
			if (start > value.size()) start = value.size();
		}
		if (_length > 1)
		{
			end = (int)args[1] > 0 ? (start + (int)args[1]) : 0;
			if (end > value.size()) end = value.size();
		}
		if (end != 0)
		{
			value.erase(value.begin() + start, value.begin() + end);
		}
		for (int i = 2; i < _length; ++i)
		{
			value.push_back(args[i]);
		}
		return ret;
	}
	NectarCore::VAR Array::toLocaleString(NectarCore::VAR* args, int _length) const
	{
		return toString(args, _length);
	}
	NectarCore::VAR Array::toString(NectarCore::VAR* args, int _length) const
	{
		NectarCore::VAR args[] = {","};
		return join(args, 1);
	}

	NectarCore::VAR Array::unshift(NectarCore::VAR* args, int _length)
	{
		auto it = value.begin();
		for (int i = 0; i < _length; ++i)
		{
			it = value.insert(it, args[i]);
		}
		return (int)value.size();
	}
	NectarCore::VAR Array::values(NectarCore::VAR* args, int _length) const
	{
		// TODO: Add iterator
		return new Array(value);
	}

} // namespace NectarCore::Class
