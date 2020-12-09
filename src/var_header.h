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
 
namespace NectarCore
{
	union Data
	{
		void* ptr;
		double number;		
	};
	
	struct VAR
	{
		NectarCore::Enum::Type type;
		std::bitset<2> property; // const, enumerable
		Data data;
		
		VAR();
		~VAR();

		/**/
		VAR(VAR const &_v);
		VAR(VAR const &&_v);
		/**/
		
		/*** CONSTRUCTOR ***/

		VAR(NectarCore::Enum::Type _type, int _value);
		VAR(NectarCore::Enum::Type _type, double _value);
		VAR(int _value);
		VAR(double _value);
		VAR(long long _value);
		VAR(char *_value);
		VAR(std::string _value);
		VAR(const char *_value);
		VAR(std::string_view _value);
		VAR(NectarCore::Class::FixedArray *_value);
		VAR(NectarCore::Class::Array *_value);
		VAR(std::initializer_list<NectarCore::VAR> l);
		VAR(const NectarCore::Class::Array *_value);
		VAR(bool _value);
		VAR(NectarCore::Class::Function *_value);
		VAR(NectarCore::Class::Object *_value);
		VAR(NectarCore::Class::String *_value);
		VAR(NectarCore::Class::Native *_value);
		VAR(NectarCore::Class::Undefined *_value);
		VAR(void *_value, void* fn);
		VAR(NectarCore::Enum::Type _type, void *_value);
		VAR(NectarCore::Enum::Type _type, void *_value, VAR _this);
		VAR(std::function<VAR(NectarCore::VAR*, int)> &_value);
		
		
		
		template<typename T>
		VAR(NectarCore::Class::NativeTPL<T>* _value)
		{
			this->type = NectarCore::Enum::Type::NativeTPL;
			data.ptr = _value;
		};

		
		template <typename T>
		T toNative (T _type)
		{
			if(type == NectarCore::Enum::Type::NativeTPL)
			{
				return (*(NectarCore::Class::NativeTPL<T>*)data.ptr)(_type);
			}
			else
			{
		#ifndef __Nectar_NO_EXCEPT
				throw VAR("TypeError: Object is not a Native object");
		#endif
				exit(1);
			} 
		}
		
		template <typename T>
		T toNative ()
		{
			if(type == NectarCore::Enum::Type::NativeTPL)
			{
				return (*(NectarCore::Class::NativeTPL<T>*)data.ptr)();
			}
			else
			{
		#ifndef __Nectar_NO_EXCEPT
				throw VAR("TypeError: Object is not a Native object");
		#endif
				exit(1);
			} 
		}
		
		
		template <class... Args>
		VAR operator() (Args... args) const
		{
			if (type != NectarCore::Enum::Type::Function)
			{
		#ifndef __Nectar_NO_EXCEPT
				throw VAR("TypeError: object is not a function");
		#endif
				exit(1);
			}
			else return (*(NectarCore::Class::Function*)data.ptr)((VAR)(args)...);
		}
		
		/* END CALL OVERLOAD */

		VAR & operator[] (VAR _index);
		VAR & operator[] (VAR _index) const;
		VAR & operator[] (int _index) const;
		VAR & operator[] (int _index);
		VAR & operator[] (double _index);
		VAR & operator[] (const char* _index);
		/* END ACCESS OVERLOAD */

		/*** END CONSTRUCTOR ***/

		/*** OPERATOR ***/
		void operator=(const VAR &_v);

		/// Unary operators
		VAR operator+();
		VAR operator-();
		VAR operator!();

		/// Logical operators
		VAR operator&&(const VAR &_v1) const;
		VAR operator||(const VAR &_v1) const;

		/// Arithmetic operators
		VAR operator+(const VAR &_v1);
		VAR operator+(const char _v1[]);
		VAR& operator+=(const VAR &_v1);
		VAR operator-(const VAR &_v1);
		VAR& operator-=(const VAR &_v1);
		VAR operator*(const VAR &_v1);
		VAR& operator*=(const VAR &_v1);
		VAR operator/(const VAR &_v1);
		VAR& operator/=(const VAR &_v1);
		VAR operator%(const VAR &_v1);
		VAR& operator%=(const VAR &_v1);
		// TODO: "**" and "**=" operators
		VAR& operator++(const int _v1);
		VAR& operator++();
		VAR& operator--(const int _v1);
		VAR& operator--();
		/// Comparison operators
		VAR operator==(const VAR &_v1) const;
		// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
		VAR operator!=(const VAR &_v1);
		// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
		VAR operator<(const VAR &_v1);
		VAR operator<=(const VAR &_v1);
		VAR operator>(const VAR &_v1);
		VAR operator>=(const VAR &_v1);
		/// Bitwise operators
		VAR operator&(const VAR &_v1);
		VAR& operator&=(const VAR &_v1);
		VAR operator|(const VAR &_v1);
		VAR operator|=(const VAR &_v1);
		VAR operator^(const VAR &_v1);
		VAR operator^=(const VAR &_v1);
		VAR operator~();
		VAR operator>>(const VAR &_v1);
		VAR operator>>=(const VAR &_v1);
		VAR operator<<(const VAR &_v1);
		VAR operator<<=(const VAR &_v1);

		explicit operator int() const;
		operator int();
		explicit operator double() const;
		operator double();
		explicit operator bool() const;
		operator bool();
		explicit operator std::string() const;
		operator std::string();
		operator const char*() const;
		operator long long();
		explicit operator long long() const;
		operator std::string_view() const;
		
	};
} // namespace NectarCore