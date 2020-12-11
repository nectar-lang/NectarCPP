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
#include "string_header.h"
#include <string>
#include <limits>
#include <locale>

namespace NectarCore::Class
{
	// Constructors
	String::String()
	{
	}
	String::String(std::string val)
	{
		value = val;
	}
	String::String(const char *val)
	{
		value = val;
	}
	// Methods
	inline void String::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	inline void *String::Copy() noexcept
	{
		return new String(value);
	}
	// Native cast
	String::operator bool() const noexcept { return value.size() > 0; }
	String::operator double() const noexcept
	{
		std::string::size_type end;
		double res;
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		try
		{
			res = std::stod(value, &end);
		}
		catch (...)
		{
		}
#else
		res = std::stod(value, &end);
#endif

		return end == value.size() ? res : std::numeric_limits<double>::quiet_NaN();
	}
	String::operator int() const noexcept
	{
		std::string::size_type end;
		int res;
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		try
		{
			res = std::stoi(value, &end, 10);
		}
		catch (...)
		{
		}
#else
		res = std::stoi(value, &end, 10);
#endif

		return end == value.size() ? res : std::numeric_limits<int>::quiet_NaN();
	}
	String::operator long long() const noexcept
	{
		std::string::size_type end;
		long long res;
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		try
		{
			res = std::stoll(value, &end, 10);
		}
		catch (...)
		{
		}
#else
		res = std::stoll(value, &end, 10);
#endif

		return end == value.size() ? res : std::numeric_limits<long long>::quiet_NaN();
	}
	String::operator std::string() const noexcept { return value; }
	// Main operators
	NectarCore::VAR const String::operator[](NectarCore::VAR key) const
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			int i = key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
			else
				return NectarCore::Global::undefined;
		}
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;

		if (_sview.compare("length") == 0)
			return (int)value.size();

		return NectarCore::Global::undefined;
	}
	static NectarCore::VAR _char;
	static NectarCore::VAR _length;

	NectarCore::VAR &String::operator[](NectarCore::VAR key)
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			int i = key;
			if (i >= 0)
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
				}
				_char = value.at(i);
			}
			else
				_char = "";
			return _char;
		}
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
#ifndef __Nectar__OBJECT_VECTOR
		auto &_obj = object[_str];
		if (_obj)
			return _obj;
#else
		for (auto &search : object)
		{
			if (_sview.compare(search.first) == 0)
				return search.second;
		}
#endif
		__Nectar_Method_Lazy_Loader("anchor", anchor);
		__Nectar_Method_Lazy_Loader("big", big);
		__Nectar_Method_Lazy_Loader("blink", blink);
		__Nectar_Method_Lazy_Loader("bold", bold);
		__Nectar_Method_Lazy_Loader("charAt", charAt);
		__Nectar_Method_Lazy_Loader("charCodeAt", charCodeAt);
		__Nectar_Method_Lazy_Loader("codePointAt", codePointAt);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("endsWith", endsWith);
		__Nectar_Method_Lazy_Loader("fixed", fixed);
		__Nectar_Method_Lazy_Loader("fontcolor", fontcolor);
		__Nectar_Method_Lazy_Loader("fontsize", fontsize);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("italics", italics);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("link", link);
		__Nectar_Method_Lazy_Loader("localeCompare", localeCompare);
		__Nectar_Method_Lazy_Loader("match", match);
		__Nectar_Method_Lazy_Loader("matchAll", matchAll);
		__Nectar_Method_Lazy_Loader("normalize", normalize);
		__Nectar_Method_Lazy_Loader("padEnd", padEnd);
		__Nectar_Method_Lazy_Loader("padStart", padStart);
		__Nectar_Method_Lazy_Loader("repeat", repeat);
		__Nectar_Method_Lazy_Loader("replace", replace);
		__Nectar_Method_Lazy_Loader("replaceAll", replaceAll);
		__Nectar_Method_Lazy_Loader("search", search);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("small", small);
		__Nectar_Method_Lazy_Loader("split", split);
		__Nectar_Method_Lazy_Loader("startsWith", startsWith);
		__Nectar_Method_Lazy_Loader("strike", strike);
		__Nectar_Method_Lazy_Loader("sub", sub);
		__Nectar_Method_Lazy_Loader("substr", substr);
		__Nectar_Method_Lazy_Loader("substring", substring);
		__Nectar_Method_Lazy_Loader("sup", sup);
		__Nectar_Method_Lazy_Loader("toLocaleLowerCase", toLocaleLowerCase);
		__Nectar_Method_Lazy_Loader("toLocaleUpperCase", toLocaleUpperCase);
		__Nectar_Method_Lazy_Loader("toLowerCase", toLowerCase);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("toUpperCase", toUpperCase);
		__Nectar_Method_Lazy_Loader("trim", trim);
		__Nectar_Method_Lazy_Loader("trimEnd", trimEnd);
		__Nectar_Method_Lazy_Loader("trimRight", trimEnd);
		__Nectar_Method_Lazy_Loader("trimLeft", trimStart);
		__Nectar_Method_Lazy_Loader("trimStart", trimStart);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);

		if (_sview.compare("length") == 0)
		{
			_length = (int)value.size();
			return _length;
		}
#ifndef __Nectar__OBJECT_VECTOR
		return _obj;
#else
		object.push_back(NectarCore::Type::pair_t(((std::string) * this), NectarCore::Global::undefined));
		return object[object.size() - 1].second;
#endif
	}

	NectarCore::VAR &String::operator[](int key)
	{
		if (key >= 0)
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
			_char = value.at(key);
		}
		else
			_char = "";
		return _char;
	}

	NectarCore::VAR &String::operator[](double key)
	{
		if (key >= 0)
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
			_char = value.at(key);
		}
		else
			_char = "";
		return _char;
	}

	NectarCore::VAR &String::operator[](const char *key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
#ifndef __Nectar__OBJECT_VECTOR
		NectarCore::VAR &_obj = object[_str];
		if (_obj)
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
		__Nectar_Method_Lazy_Loader("anchor", anchor);
		__Nectar_Method_Lazy_Loader("big", big);
		__Nectar_Method_Lazy_Loader("blink", blink);
		__Nectar_Method_Lazy_Loader("bold", bold);
		__Nectar_Method_Lazy_Loader("charAt", charAt);
		__Nectar_Method_Lazy_Loader("charCodeAt", charCodeAt);
		__Nectar_Method_Lazy_Loader("codePointAt", codePointAt);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("endsWith", endsWith);
		__Nectar_Method_Lazy_Loader("fixed", fixed);
		__Nectar_Method_Lazy_Loader("fontcolor", fontcolor);
		__Nectar_Method_Lazy_Loader("fontsize", fontsize);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("italics", italics);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("link", link);
		__Nectar_Method_Lazy_Loader("localeCompare", localeCompare);
		__Nectar_Method_Lazy_Loader("match", match);
		__Nectar_Method_Lazy_Loader("matchAll", matchAll);
		__Nectar_Method_Lazy_Loader("normalize", normalize);
		__Nectar_Method_Lazy_Loader("padEnd", padEnd);
		__Nectar_Method_Lazy_Loader("padStart", padStart);
		__Nectar_Method_Lazy_Loader("repeat", repeat);
		__Nectar_Method_Lazy_Loader("replace", replace);
		__Nectar_Method_Lazy_Loader("replaceAll", replaceAll);
		__Nectar_Method_Lazy_Loader("search", search);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("small", small);
		__Nectar_Method_Lazy_Loader("split", split);
		__Nectar_Method_Lazy_Loader("startsWith", startsWith);
		__Nectar_Method_Lazy_Loader("strike", strike);
		__Nectar_Method_Lazy_Loader("sub", sub);
		__Nectar_Method_Lazy_Loader("substr", substr);
		__Nectar_Method_Lazy_Loader("substring", substring);
		__Nectar_Method_Lazy_Loader("sup", sup);
		__Nectar_Method_Lazy_Loader("toLocaleLowerCase", toLocaleLowerCase);
		__Nectar_Method_Lazy_Loader("toLocaleUpperCase", toLocaleUpperCase);
		__Nectar_Method_Lazy_Loader("toLowerCase", toLowerCase);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("toUpperCase", toUpperCase);
		__Nectar_Method_Lazy_Loader("trim", trim);
		__Nectar_Method_Lazy_Loader("trimEnd", trimEnd);
		__Nectar_Method_Lazy_Loader("trimRight", trimEnd);
		__Nectar_Method_Lazy_Loader("trimLeft", trimStart);
		__Nectar_Method_Lazy_Loader("trimStart", trimStart);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);

		if (_sview.compare("length") == 0)
		{
			_length = (int)value.size();
			return _length;
		}
#ifndef __Nectar__OBJECT_VECTOR
		return _obj;
#else
		object.push_back(NectarCore::Type::pair_t(((std::string) * this), NectarCore::Global::undefined));
		return object[object.size() - 1].second;
#endif
	}

	// Comparation operators
	String String::operator!() const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	bool String::operator==(const String &_v1) const { return value.compare(_v1.value) == 0; }
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
	bool String::operator!=(const String &_v1) const { return value.compare(_v1.value) != 0; }
	bool String::operator<(const String &_v1) const { return value.compare(_v1.value) < 0; }
	bool String::operator<=(const String &_v1) const { return value.compare(_v1.value) <= 0; }
	bool String::operator>(const String &_v1) const { return value.compare(_v1.value) > 0; }
	bool String::operator>=(const String &_v1) const { return value.compare(_v1.value) >= 0; }
	// Numeric operators
	String String::operator+() const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator-() const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator++(const int _v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator--(const int _v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator+(const String &_v1) const { return value + _v1.value; }
	String String::operator+=(const String &_v1)
	{
		value += _v1.value;
		return *this;
	}
	String String::operator-(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator-=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator*(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator*=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	// TODO: "**" and "**=" operators
	String String::operator/(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator/=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator%(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator%=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator&(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator|(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator^(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator~() const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator>>(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator<<(const String &_v1) const
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator&=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator|=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator^=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator>>=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	String String::operator<<=(const String &_v1)
	{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
#endif
		return String();
	}
	// TODO: ">>>" and ">>>=" operators
	/*** STRING METHODS ***/
	inline std::string String::_wrapText(std::string tag) const
	{
		return "<" + tag + ">" + value + "</" + tag + ">";
	}

	NectarCore::VAR String::__iterator(NectarCore::VAR *_args, int _length) const
	{
		return;
	}
	NectarCore::VAR String::anchor(NectarCore::VAR *_args, int _length) const
	{
		std::string str = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		return "<a name=\"" + str + "\">" + value + "</a>";
	}
	NectarCore::VAR String::big(NectarCore::VAR *_args, int _length) const { return _wrapText("big"); }
	NectarCore::VAR String::blink(NectarCore::VAR *_args, int _length) const { return _wrapText("blink"); }
	NectarCore::VAR String::bold(NectarCore::VAR *_args, int _length) const { return _wrapText("bold"); }
	NectarCore::VAR String::charAt(NectarCore::VAR *_args, int _length) const
	{
		auto index = _length > 0 ? (int)_args[0] : 0;
		if (index >= 0 && index < value.size()) return value.at(index);
		return "";
	}
	NectarCore::VAR String::charCodeAt(NectarCore::VAR *_args, int _length) const
	{
		auto index = _length > 0 ? (int)_args[0] : 0;
		return (index >= 0 && index < value.size())
			? (int)value.at(index)
			: std::numeric_limits<double>::quiet_NaN();
	}
	NectarCore::VAR String::codePointAt(NectarCore::VAR *_args, int _length) const
	{
		auto index = _length > 0 ? (int)_args[0] : 0;
		auto size = (int)value.size();
		if (index < 0 || index >= size) return NectarCore::Global::undefined;
		auto first = (int)value.at(index);
		if (
			first >= 0xD800 && first <= 0xDBFF &&
        	size > index + 1
		) {
			auto second = (int)value.at(index + 1);
			if (second >= 0xDC00 && second <= 0xDFFF) {
			// https://mathiasbynens.be/notes/javascript-encoding#surrogate-formulae
				return (first - 0xD800) * 0x400 + second - 0xDC00 + 0x10000;
			}
		}
		return first;
	}
	NectarCore::VAR String::concat(NectarCore::VAR *_args, int _length) const
	{
		auto str = value;
		for (int i = 0; i < _length; ++i) {
			str += (std::string)_args[i];
		}
		return str;
	}
	NectarCore::VAR String::endsWith(NectarCore::VAR *_args, int _length) const
	{
		std::string needle = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		auto size = value.size();
		auto needleSize = needle.size();
		return size >= needleSize && value.substr(size - needleSize, needleSize) == needle;
	}
	NectarCore::VAR String::fixed(NectarCore::VAR *_args, int _length) const { return _wrapText("tt"); }
	NectarCore::VAR String::fontcolor(NectarCore::VAR *_args, int _length) const
	{
		std::string str = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		return "<font color=\"" + str + "\">" + value + "</font>";
	}
	NectarCore::VAR String::fontsize(NectarCore::VAR *_args, int _length) const
	{
		std::string str = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		return "<font size=\"" + str + "\">" + value + "</font>";
	}
	NectarCore::VAR String::includes(NectarCore::VAR *_args, int _length) const
	{
		std::string needle = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		auto index = _length > 1 ? (int)_args[1] : 0;
		auto loc = value.find(needle, index);
		return loc != std::string::npos;
	}
	NectarCore::VAR String::indexOf(NectarCore::VAR *_args, int _length) const
	{
		std::string needle = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		auto index = _length > 1 ? (int)_args[1] : 0;
		auto loc = value.find_first_of(needle, index);
		return loc != std::string::npos ? (int)loc : -1;
	}
	NectarCore::VAR String::italics(NectarCore::VAR *_args, int _length) const { return _wrapText("i"); }
	NectarCore::VAR String::lastIndexOf(NectarCore::VAR *_args, int _length) const
	{
		std::string needle = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		auto index = _length > 1 ? (int)_args[1] : 0;
		auto loc = value.find_last_of(needle, index);
		return loc != std::string::npos ? (int)loc : -1;
	}
	NectarCore::VAR String::link(NectarCore::VAR *_args, int _length) const
	{
		std::string str = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		return "<a href=\"" + str + "\">" + value + "</a>";
	}
	NectarCore::VAR String::localeCompare(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Locale
		return NectarCore::Global::undefined;
		// std::string s1 = value;
		// std::string s2 = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		// auto& f = std::use_facet<std::collate<CharT>>(_args[1]);
		// return f.compare(&s1[0], &s1[0] + s1.size(), &s2[0], &s2[0] + s2.size());
	}
	NectarCore::VAR String::match(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Implement
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::matchAll(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Implement
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::normalize(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Locale
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::padEnd(NectarCore::VAR *_args, int _length) const
	{
		int targetLength = _length > 0 ? (int)_args[0] : 0;
		int size = value.size();
		if (targetLength > size) return value;
		targetLength -= size;
		size = 0;
		std::string padString =
			(_length > 1 && _args[1].type == NectarCore::Enum::Type::Undefined)
			? (std::string)_args[1] : " ";
		std::string str = "";
		for (int padSize = padString.size(); size < targetLength; size += padSize) {
			str += padString;
		}
		return value + (size > targetLength ? str.substr(0, targetLength) : str);
	}
	NectarCore::VAR String::padStart(NectarCore::VAR *_args, int _length) const
	{
		int targetLength = _length > 0 ? (int)_args[0] : 0;
		int size = value.size();
		if (targetLength > size) return value;
		targetLength -= size;
		size = 0;
		std::string padString =
			(_length > 1 && _args[1].type == NectarCore::Enum::Type::Undefined)
			? (std::string)_args[1] : " ";
		std::string str = "";
		for (int padSize = padString.size(); size < targetLength; size += padSize) {
			str += padString;
		}
		return (size > targetLength ? str.substr(0, targetLength) : str) + value;
	}
	NectarCore::VAR String::repeat(NectarCore::VAR *_args, int _length) const
	{
		int count = _length > 0 ? (int)_args[0] : 0;
		if (count < 0) throw new NectarCore::VAR('repeat count must be non-negative');
		if (_length > 0 && std::isinf((double)_args[0])) throw new NectarCore::VAR('repeat count must be less than infinity');
		std::string str = "";
		for (int i = 0; i < count; ++i) {
			str += value;
		}
		return str;
	}
	NectarCore::VAR String::replace(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Refactor
		NectarCore::VAR _search;
		NectarCore::VAR _replace;
		if (_length > 0)
			_search = _args[0];
		else
			return value;
		if (_length > 1)
			_replace = _args[1];

		size_t start_pos = value.find((std::string)_search);
		if (start_pos == std::string::npos)
		{
			return value;
		}

		std::string _new = value;
		return _new.replace(start_pos, ((std::string)_search).length(), (std::string)_replace);
	}
	NectarCore::VAR String::replaceAll(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Implement
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::search(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Refactor
		NectarCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return -1;

		std::string::size_type loc = value.find((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return (int)loc;
		}
		return -1;
	}
	NectarCore::VAR String::slice(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Refactor
		if (_length == 0)
			return value;
		int len = value.size();
		int start = _length > 0 ? (int)_args[0] : 0;
		int end = _length > 1 ? (int)_args[1] : len;
		if (start < 0)
			start += len;
		if (end < 0)
			end += len;
		if (end >= len)
			end = len;
		if (start >= len || end <= start)
			return "";
		return value.substr(start, end - start);
	}
	NectarCore::VAR String::small(NectarCore::VAR *_args, int _length) const { return _wrapText("small"); }
	NectarCore::VAR String::split(NectarCore::VAR *_args, int _length) const
	{
		if (_length == 0) return value;
		std::string needle = _args[0];

		NectarCore::VAR _arr = new NectarCore::Class::Array();
		char *_v = (char *)malloc(strlen(value.c_str()) + 1);
		strcpy(_v, value.c_str());
		char *delim = (char *)malloc(strlen(needle.c_str()) + 1);
		strcpy(delim, needle.c_str());

		char *ptr = strtok(_v, delim);
		int i = 0;
		char *_new;
		while (ptr != NULL)
		{
			_new = (char *)malloc(strlen(ptr) + 1);
			strcpy(_new, ptr);
			__Nectar_Object_Set(i, _new, _arr);
			free(_new);
			ptr = strtok(NULL, delim);
			i++;
		}

		free(delim);
		return _arr;
	}
	NectarCore::VAR String::startsWith(NectarCore::VAR *_args, int _length) const
	{
		std::string needle = _length > 0 ? _args[0] : NectarCore::Global::undefined;
		auto needleSize = needle.size();
		return value.size() >= needleSize && value.substr(0, needleSize) == needle;
	}
	NectarCore::VAR String::strike(NectarCore::VAR *_args, int _length) const { return _wrapText("s"); }
	NectarCore::VAR String::sub(NectarCore::VAR *_args, int _length) const { return _wrapText("sub"); }
	NectarCore::VAR String::substr(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Refactor
		NectarCore::VAR _start;
		NectarCore::VAR _end;
		if (_length > 0)
			_start = _args[0];
		else
			return value;
		if (_length > 1)
			_end = _args[1];

		if (_end.type == NectarCore::Enum::Type::Undefined)
			return value.substr((int)_start, std::string::npos);
		return value.substr((int)_start, (int)_end);
	}
	NectarCore::VAR String::substring(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Implement
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::sup(NectarCore::VAR *_args, int _length) const { return _wrapText("sup"); }
	NectarCore::VAR String::toLocaleLowerCase(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Locale
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::toLocaleUpperCase(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Locale
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::toLowerCase(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Implement
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::toString(NectarCore::VAR *_args, int _length) const
	{
		return valueOf(_args, _length);
	}
	NectarCore::VAR String::toUpperCase(NectarCore::VAR *_args, int _length) const
	{
		// TODO: Implement
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR String::trim(NectarCore::VAR *_args, int _length) const
	{
		int l = value.size();
		int i1 = 0;
		for (; i1 < l; i1++) {
			int c = value[i1];
			if (!(c == 9 || c == 10 || c == 32 || c == 0xA0 || c == 0xFEFF)) break;
		}
		int i2 = l;
		for (; i2 >= i1; i2--) {
			int c = value[i2];
			if (!(c == 9 || c == 10 || c == 32 || c == 0xA0 || c == 0xFEFF)) break;
		}
		return value.substr(i1, i2);
	}
	NectarCore::VAR String::trimEnd(NectarCore::VAR *_args, int _length) const
	{
		int i = value.size();
		for (; i >= 0; i--) {
			int c = value[i];
			if (!(c == 9 || c == 10 || c == 32 || c == 0xA0 || c == 0xFEFF)) break;
		}
		return value.substr(0, i);
	}
	NectarCore::VAR String::trimStart(NectarCore::VAR *_args, int _length) const
	{
		int i = 0;
		int l = value.size();
		for (; i < l; i++) {
			int c = value[i];
			if (!(c == 9 || c == 10 || c == 32 || c == 0xA0 || c == 0xFEFF)) break;
		}
		return value.substr(i, l);
	}
	std::string String::valueOf(NectarCore::VAR *_args, int _length) const
	{
		return value;
	}
	/* END STRING METHODS */
} // namespace NectarCore::Class
