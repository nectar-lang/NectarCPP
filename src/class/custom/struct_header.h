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
	class Struct : public virtual Base
	{
	public:
		// Constructors
		Struct();
		Struct(void *val);
		Struct(void *val, void *fn);
		// Properties
		count_t counter = 1;
		void *value = nullptr;
		NectarCore::Type::object_t object;
		NectarCore::Type::clean_struct *Clean;
		// Methods
		inline void Delete() noexcept;
		inline void StructDelete() noexcept;
		inline void *Copy() noexcept;
		// Struct cast
		explicit operator std::string() const noexcept;
		// Main operators
		NectarCore::VAR const operator[](NectarCore::VAR key) const;
		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](int key);
		NectarCore::VAR &operator[](double key);
		NectarCore::VAR &operator[](const char *key);

		template <class... Args>
		NectarCore::VAR operator()(Args... args) const
		{
			auto _args = NectarCore::Type::vector_t{(NectarCore::VAR)args...};
			return (*static_cast<std::function<NectarCore::VAR(NectarCore::Type::vector_t)> *>(value))(_args);
		}

		// Comparation operators
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NectarCore::Class
