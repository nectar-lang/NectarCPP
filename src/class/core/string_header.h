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
#include "../base_header.h"

namespace NectarCore::Class
{
	class String : public virtual Base
	{
	public:
		// Constructors
		String();
		String(std::string val);
		String(const char* val);
		// Properties
		std::string value;
		NectarCore::Type::object_t object;
		count_t counter = 1;
		// Methods
		inline void Delete() noexcept;
		inline void* Copy() noexcept;
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NectarCore::VAR const operator[](NectarCore::VAR key) const;
		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](int key);
		NectarCore::VAR &operator[](double key);
		NectarCore::VAR &operator[](const char* key);
		
		// Comparation operators
		template <class... Args>
		NectarCore::VAR operator() (Args... args)
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NectarCore::Global::undefined;
		}
		String operator!() const;
		bool operator==(const String &_v1) const;
		// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
		// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const String &_v1) const;
		bool operator<(const String &_v1) const;
		bool operator<=(const String &_v1) const;
		bool operator>(const String &_v1) const;
		bool operator>=(const String &_v1) const;
		// Numeric operators
		String operator+() const;
		String operator-() const;
		String operator++(const int _v1);
		String operator--(const int _v1);
		String operator+(const String &_v1) const;
		String operator+=(const String &_v1);
		String operator-(const String &_v1) const;
		String operator-=(const String &_v1);
		String operator*(const String &_v1) const;
		String operator*=(const String &_v1);
		// TODO: "**" and "**=" operators
		String operator/(const String &_v1) const;
		String operator/=(const String &_v1);
		String operator%(const String &_v1) const;
		String operator%=(const String &_v1);
		String operator&(const String &_v1) const;
		String operator|(const String &_v1) const;
		String operator^(const String &_v1) const;
		String operator~() const;
		String operator>>(const String &_v1) const;
		String operator<<(const String &_v1) const;
		String operator&=(const String &_v1);
		String operator|=(const String &_v1);
		String operator^=(const String &_v1);
		String operator>>=(const String &_v1);
		String operator<<=(const String &_v1);
		// TODO: ">>>" and ">>>=" operators
		/*** STRING METHODS ***/
		inline std::string _wrapText(std::string tag) const;

		NectarCore::VAR __iterator(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR anchor(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR big(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR blink(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR bold(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR charAt(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR charCodeAt(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR codePointAt(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR concat(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR endsWith(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR fixed(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR fontcolor(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR fontsize(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR includes(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR indexOf(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR italics(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR lastIndexOf(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR link(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR localeCompare(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR match(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR matchAll(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR normalize(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR padEnd(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR padStart(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR repeat(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR replace(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR replaceAll(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR search(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR slice(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR small(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR split(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR startsWith(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR strike(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR sub(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR substr(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR substring(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR sup(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR toLowerCase(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR toString(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR toUpperCase(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR trim(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR trimEnd(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR trimStart(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR valueOf(NectarCore::VAR* _args, int _length) const;
		/* END STRING METHODS */
	};
} // namespace NectarCore::Class
