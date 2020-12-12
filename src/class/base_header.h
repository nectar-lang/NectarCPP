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
#include "_meta.h"
#include <string>
#include "../var_header.h"
// #include "../helpers_header.h"

namespace NectarCore::Class
{
	class Base
	{
	public:
#ifdef __Nectar_ENV_ESP32
		virtual ~Base() {};
#endif
		virtual void Delete() noexcept {}
		virtual void jsDelete(const NectarCore::VAR key) noexcept {}
		virtual void *Copy() noexcept { return nullptr; }
		// Cast to primitive
		virtual explicit operator bool() const noexcept { return true; }
		virtual explicit operator std::string() const noexcept { return ""; }
		virtual explicit operator int() const noexcept { return std::numeric_limits<int>::quiet_NaN(); }
		virtual explicit operator double() const noexcept { return std::numeric_limits<double>::quiet_NaN(); }
		virtual explicit operator long long() const noexcept { return std::numeric_limits<long long>::quiet_NaN(); }
		/// Access operators

		virtual NectarCore::VAR &operator[](NectarCore::VAR key)
		{
			static NectarCore::VAR _ret = NectarCore::VAR();
			return _ret;
		}
		virtual NectarCore::VAR &operator[](int key)
		{
			static NectarCore::VAR _ret = NectarCore::VAR();
			return _ret;
		}
		virtual NectarCore::VAR &operator[](double key)
		{
			static NectarCore::VAR _ret = NectarCore::VAR();
			return _ret;
		}
		virtual NectarCore::VAR &operator[](const char *key)
		{
			static NectarCore::VAR _ret = NectarCore::VAR();
			return _ret;
		}
		/// Comparison operators
		// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
		// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE

		virtual bool operator==(const Base &_v1) const { return false; }
		virtual bool operator!=(const Base &_v1) const { return true; }
		/// Numeric operators
		// TODO: "**" and "**=" operators

		virtual Base operator+() { throw InvalidTypeException(); }
		virtual Base operator-() const { throw InvalidTypeException(); }
		virtual Base& operator++(const int) { throw InvalidTypeException(); }
		virtual Base& operator--(const int) { throw InvalidTypeException(); }
		virtual Base operator+(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base operator-(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base operator*(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base operator/(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base operator%(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base& operator+=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base& operator-=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base& operator*=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base& operator/=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base& operator%=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base operator&(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base operator|(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base operator^(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base operator~() const { throw InvalidTypeException(); }
		virtual Base operator>>(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base operator<<(const Base &_v1) const { throw InvalidTypeException(); }
		virtual Base& operator&=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base& operator|=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base& operator^=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base& operator>>=(const Base &_v1) { throw InvalidTypeException(); }
		virtual Base& operator<<=(const Base &_v1) { throw InvalidTypeException(); }
	};
} // namespace NectarCore::Class
