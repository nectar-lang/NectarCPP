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
	class FixedArray : public virtual Base
	{
	public:
		// Constructors
		FixedArray();
		FixedArray(count_t length);
		// Properties
		count_t counter = 0;
		count_t length;
		NectarCore::VAR *value;
		NectarCore::Type::object_t object;
		// Methods
		inline void Delete() noexcept;
		inline void *Copy() noexcept;
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NectarCore::VAR const operator[](NectarCore::VAR key) const;
		NectarCore::VAR const operator[](int key) const;
		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](int key);
		NectarCore::VAR &operator[](double key);
		NectarCore::VAR &operator[](const char *key);

		NectarCore::VAR _toPrimitive(std::true_type) const;
		NectarCore::VAR _toPrimitive(std::false_type) const;
	};
} // namespace NectarCore::Class
