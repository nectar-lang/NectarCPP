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
#include "_meta.h"


namespace NectarCore::Class
{
	template<typename T>
	class NativeTPL : public virtual Base
	{
		
	private:
		void internalDelete(std::true_type)
		{
			if((*this)["__Nectar_On_Destroy"]) (*this)["__Nectar_On_Destroy"]();
			if(std::is_pointer<T>::value) delete value;
		}
		void internalDelete(std::false_type)
		{
			if((*this)["__Nectar_On_Destroy"]) (*this)["__Nectar_On_Destroy"]();
		}
	public:
		// Constructors
		bool is_ptr = 0;
		const char* info;
		NativeTPL(T val)
		{
			is_ptr = std::is_pointer<T>::value;
			info = typeid(T).name();
			value = val;
		}
		// Properties
		count_t counter = 1;
		T value;
		NectarCore::Type::object_t object;
		// Methods
		
		inline void Delete() noexcept
		{
			if (--counter == 0)
			{
				internalDelete(std::is_pointer<T>());
				delete this;
			}
		}
		
		inline void* Copy() noexcept
		{
			counter++;
			return this;
		}
		
		template<typename Cast>
		const inline T operator()(Cast& c) const
		{
			if(std::string(typeid(Cast).name()).compare(info) == 0)
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
	
		operator bool() const noexcept { return true; }
		operator double() const noexcept
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
		operator int() const noexcept
		{
			return std::numeric_limits<int>::quiet_NaN();
		}
		operator long long() const noexcept
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
		operator std::string() const noexcept
		{
			return std::string("[native ") +  std::string(typeid(T).name()) +  std::string("]");
		}
		
		// Main operators
		NectarCore::VAR const operator[](NectarCore::VAR key) const
		{
			return NectarCore::Global::undefined;
		}
		NectarCore::VAR &operator[](NectarCore::VAR key)
		{
			#ifndef __Nectar__OBJECT_VECTOR
			return object[(std::string)key];
			#else
			for (auto & search : object)
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
			for (auto & search : object)
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
			for (auto & search : object)
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
		
		
		NectarCore::VAR &operator[](const char* key)
		{
			std::string str = key;
			#ifndef __Nectar__OBJECT_VECTOR
			return object[str];
			#else
			for (auto & search : object)
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
		
		// Comparation operators
		NativeTPL operator!() const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		bool operator==(const NativeTPL<T> &_v1) const { return false; }
		// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
		// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const NativeTPL<T> &_v1) const { return true; }
		bool operator<(const NativeTPL<T> &_v1) const { return false; }
		bool operator<=(const NativeTPL<T> &_v1) const { return true; }
		bool operator>(const NativeTPL<T> &_v1) const { return false; }
		bool operator>=(const NativeTPL<T> &_v1) const { return true; }
		// Numeric operators
		NativeTPL operator+() const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator-() const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator++(const int _v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator--(const int _v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator+(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator+=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator-(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator-=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator*(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator*=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		// TODO: "**" and "**=" operators
		NativeTPL operator/(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator/=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator%(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator%=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator&(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator|(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator^(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator~() const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator>>(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator<<(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator&=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator|=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator^=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator>>=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator<<=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		// TODO: ">>>" and ">>>=" operators
		
	};
} // namespace NectarCore::Class
