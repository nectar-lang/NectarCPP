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
	class Symbol : public virtual Base
	{
	public:
		// Constructors
		Symbol();
		Symbol(std::string val);
		Symbol(const char *val);
		// Properties
		const char* name = "";
		count_t counter = 1;
		// Methods
		inline void Delete() noexcept;
		inline void *Copy() noexcept;
		// Native cast
		explicit operator std::string() const noexcept;
		// Main operators
		NectarCore::VAR const operator[](NectarCore::VAR key) const;
		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](const char *key);

		template <class... Args>
		NectarCore::VAR operator()(Args... args) const
		{
#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
#endif
			return NectarCore::Global::undefined;
		}

		NectarCore::VAR _toPrimitive(std::true_type) const;
		NectarCore::VAR _toPrimitive(std::false_type) const;
		/*** Symbol METHODS ***/
		NectarCore::VAR valueOf(NectarCore::VAR *_args, int _length) const;
		NectarCore::VAR toString(NectarCore::VAR *_args, int _length) const;
		/* END Symbol METHODS */
	};
} // namespace NectarCore::Class
