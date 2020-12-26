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
#include "struct_header.h"
#include <functional>
#include <limits>

namespace NectarCore::Class
{
	// Constructors
	Struct::Struct() {}
	Struct::Struct(void *val)
	{
		value = val;
	}
	Struct::Struct(void *val, void *fn)
	{
		value = val;
		Clean = (NectarCore::Type::clean_struct *)fn;
	}
	// Methods
	inline void Struct::Delete() noexcept
	{
		if (--counter == 0)
		{
			(*static_cast<NectarCore::Type::clean_struct *>(Clean))(value);
			delete Clean;
			delete this;
		}
	}

	inline void *Struct::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Struct::operator std::string() const noexcept
	{
		return "[native struct]";
	}
	// Main operators
	NectarCore::VAR const Struct::operator[](NectarCore::VAR key) const
	{
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR &Struct::operator[](NectarCore::VAR key)
	{
#ifndef __Nectar__OBJECT_VECTOR
		return object[(std::string)key];
#else
		for (auto &search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t((std::string)key, NectarCore::VAR()));
		return object[object.size() - 1].second;
#endif
	}

	NectarCore::VAR &Struct::operator[](int key)
	{
#ifndef __Nectar__OBJECT_VECTOR
		return object[std::to_string(key)];
#else
		std::string _str = std::to_string(key);
		for (auto &search : object)
		{
			if (_str.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::VAR()));
		return object[object.size() - 1].second;
#endif
	}

	NectarCore::VAR &Struct::operator[](double key)
	{
#ifndef __Nectar__OBJECT_VECTOR
		return object[std::to_string(key)];
#else
		std::string _str = std::to_string(key);
		for (auto &search : object)
		{
			if (_str.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::VAR()));
		return object[object.size() - 1].second;
#endif
	}

	NectarCore::VAR &Struct::operator[](const char *key)
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
