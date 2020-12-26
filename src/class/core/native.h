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
// #include "native_header.h"
// #include <functional>
// #include <limits>

namespace NectarCore::Class
{
	// Constructors
	Native::Native() {}
	Native::Native(void *val)
	{
		value = val;
	}
	// Methods
	inline void Native::Delete() noexcept
	{
		if (--counter < 1)
		{
			if ((*this)["__Nectar_On_Destroy"])
				(*this)["__Nectar_On_Destroy"]();
			delete this;
		}
	}
	inline void *Native::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Native::operator std::string() const noexcept
	{
		return "[native code]";
	}
	// Main operators
	NectarCore::VAR &Native::operator[](NectarCore::VAR key)
	{
		return (*this)[(std::string)key];
	}

	NectarCore::VAR &Native::operator[](int key)
	{
		return (*this)[std::to_string(key)];
	}

	NectarCore::VAR &Native::operator[](double key)
	{
		return (*this)[std::to_string(key)];
	}

	NectarCore::VAR &Native::operator[](const char *key)
	{
		std::string str = key;
#ifndef __Nectar__OBJECT_VECTOR
		return object[str];
#else
		for (auto &search : object)
		{
			if (str.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t(str, NectarCore::VAR()));
		return object[object.size() - 1].second;
#endif
	}
} // namespace NectarCore::Class
