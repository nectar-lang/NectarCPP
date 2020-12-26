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
	template <typename T>
	class NativeTPL : public virtual Base
	{

	private:
		void internalDelete(std::true_type);
		void internalDelete(std::false_type);

	public:
		// Constructors
		bool is_ptr = 0;
		const char *info;
		NativeTPL(T val);
		// Properties
		count_t counter = 1;
		T value;
		NectarCore::Type::object_t object;
		// Methods
		inline void Delete() noexcept;
		inline void *Copy() noexcept;

		template <typename Cast>
		const inline T operator()(Cast &c) const;
		inline T operator()() const { return value; }

		operator std::string() const noexcept
		{
			return std::string("[native ") + std::string(typeid(T).name()) + std::string("]");
		}

		// Main operators
		NectarCore::VAR &operator[](NectarCore::VAR key)
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

		NectarCore::VAR &operator[](int key)
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

		NectarCore::VAR &operator[](double key)
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

		NectarCore::VAR &operator[](const char *key)
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
