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
#include <exception>
#include <string_view>
#include "../enum.h"
#include "../types.h"
#include "../var_header.h"

namespace NectarCore::Class
{
#ifdef __Nectar_ENV_ARDUINO
	typedef uint16_t count_t;
	constexpr count_t POOL_SIZE = 256;
#else
	typedef int count_t;
	constexpr count_t POOL_SIZE = 64 * 1024;
#endif
	typedef NectarCore::VAR VAR;
	typedef NectarCore::Type::pair_t pair_t;
	typedef NectarCore::Type::vector_t vector_t;
	typedef NectarCore::Type::object_t object_t;
	typedef NectarCore::Type::function_t function_t;
	typedef NectarCore::Type::StringView str_view;
	class InvalidTypeException : public std::exception
	{
	};
} // namespace NectarCore::Class
