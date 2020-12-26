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
#include "native_tpl_header.h"

namespace NectarCore::Class
{
	template <typename T>
	class NativeTPL : public virtual Base
	{
		void internalDelete(std::true_type)
		{
			if ((*this)["__Nectar_On_Destroy"])
				(*this)["__Nectar_On_Destroy"]();
			if (std::is_pointer<T>::value)
				delete value;
		}
		void internalDelete(std::false_type)
		{
			if ((*this)["__Nectar_On_Destroy"])
				(*this)["__Nectar_On_Destroy"]();
		}

		NativeTPL::NativeTPL(T val)
		{
			is_ptr = std::is_pointer<T>::value;
			info = typeid(T).name();
			value = val;
		}
		inline void Delete() noexcept
		{
			if (--counter == 0)
			{
				internalDelete(std::is_pointer<T>());
				delete this;
			}
		}

		inline void *NativeTPL::Copy() noexcept
		{
			counter++;
			return this;
		}

		template <typename Cast>
		const inline T operator()(Cast &c) const
		{
			if (std::string(typeid(Cast).name()).compare(info) == 0)
			{
				return value;
			}
			else
			{
				throw(__Nectar_Throw_Error("Invalid native type casting"));
			}
		}

		inline T operator()() const
		{
			return value;
		}

		operator std::string() const noexcept
		{
			return std::string("[native ") + std::string(typeid(T).name()) + std::string("]");
		}

		// Main operators
		NectarCore::VAR &NativeTPL::operator[](NectarCore::VAR key)
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

		NectarCore::VAR &NativeTPL::operator[](int key)
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

		NectarCore::VAR &NativeTPL::operator[](double key)
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

		NectarCore::VAR &NativeTPL::operator[](const char *key)
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
	};
} // namespace NectarCore::Class
