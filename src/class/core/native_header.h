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
	class Native : public virtual Base
	{
	public:
		// Constructors
		Native();
		Native(void *val);

		count_t counter = 1;
		void *value = nullptr;
		NectarCore::Type::object_t object;

		inline void Delete() noexcept;
		inline void *Copy() noexcept;
		explicit operator std::string() const noexcept;

		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](int key);
		NectarCore::VAR &operator[](double key);
		NectarCore::VAR &operator[](const char *key);
		NectarCore::VAR _toPrimitive(std::true_type) const;
		NectarCore::VAR _toPrimitive(std::false_type) const;
	};
} // namespace NectarCore::Class
