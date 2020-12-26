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
#include "undefined_header.h"
// #include <limits>

namespace NectarCore::Class
{
	// Constructors
	Undefined::Undefined() {}
	// Methods
	inline void Undefined::Delete() noexcept
	{
	}
	inline void *Undefined::Copy() noexcept
	{
		return this;
	}
	// Native cast
	Undefined::operator bool() const noexcept { return false; }
	Undefined::operator std::string() const noexcept { return "undefined"; }
	// Main operators
	NectarCore::VAR const Undefined::operator[](NectarCore::VAR key) const
	{
		throw NectarCore::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
	}
	NectarCore::VAR &Undefined::operator[](NectarCore::VAR key)
	{
		throw NectarCore::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
	}
	NectarCore::VAR &Undefined::operator[](int key)
	{
		throw NectarCore::VAR("TypeError: Cannot read property " + std::to_string(key) + " of undefined ");
	}
	NectarCore::VAR &Undefined::operator[](double key)
	{
		throw NectarCore::VAR("TypeError: Cannot read property " + std::to_string(key) + " of undefined ");
	}
	NectarCore::VAR &Undefined::operator[](const char *key)
	{
		throw NectarCore::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
	}
	// Comparation operators
	bool Undefined::operator==(const Undefined &_v1) const { return true; }
	bool Undefined::operator!=(const Undefined &_v1) const { return false; }
	bool Undefined::operator<(const Undefined &_v1) const { return false; }
	bool Undefined::operator<=(const Undefined &_v1) const { return false; }
	bool Undefined::operator>(const Undefined &_v1) const { return false; }
	bool Undefined::operator>=(const Undefined &_v1) const { return false; }
} // namespace NectarCore::Class
