module;
#pragma once
#include <cmath>
#include <string>
#include <limits>
export module NectarCore:value;
import NectarCore:concepts;

export namespace NectarCore
{
	template <typename T>
	struct Value
	{
		static constexpr const bool is_primitive = Concepts::is_primitive<T>;
		static constexpr const bool is_pointer = Concepts::is_pointer<T>;
		static constexpr const char* type = Value<T>::compute_type();
		T value;
		Value(T val) : value(val){};
		// Integral types: bool, int, double...
		template<Concepts::is_integral T2>
		constexpr operator T2() const { return std::numeric_limits<T2>::quiet_NaN(); }
		template<Concepts::is_integral T2>
		constexpr operator T2() const requires Concepts::is_pointer<T> { return 1; }
		template<Concepts::is_integral T2>
		constexpr operator T2() const requires Concepts::convertible_to<T, T2> { return (T2)get(); }
		// String
		constexpr operator std::string() const requires Concepts::is_number<T>
		{
			if constexpr (std::is_floating_point_v<T>)
			{
				if (std::isnan(value))
					return "NaN";
				if (std::isinf(value))
					return value < 0 ? "-Infinity" : "Infinity";
			}
			return std::to_string(value);
		}
		constexpr operator std::string() const
		requires Concepts::is_boolean<T> { return value ? "true" : "false"; }
		constexpr operator std::string() const
		requires Concepts::is_undefined<T> { return "undefined"; }
		constexpr operator std::string() const
		requires Concepts::convertible_to<T, std::string> { return (std::string)get(); }
		constexpr operator std::string() const { return ""; }
		// Itself
		constexpr operator T() const requires Concepts::should_define_T<T> { return get(); }
		// Getter/Setter
		inline constexpr T get() const requires Concepts::is_pointer<T> { return *value; };
		inline constexpr T get() const { return value; };
		inline constexpr void set(const T *v) { set(*v); };
		inline constexpr void set(const T &v)
		{
			if constexpr (Concepts::is_pointer<T>)
				delete value;
			value = v;
		};
		// operator[]
		template <typename T2> constexpr auto &operator[](const T2 k) const
		requires Concepts::has_lookup<T, T2> { return value[k]; };
		template <typename T2> constexpr auto &operator[](const T2 k)
		requires Concepts::has_lookup<T, T2> { throw value[k]; };
		template <typename T2>
		constexpr auto &operator[](const T2 k) const { throw nullptr; };
		template <typename T2>
		constexpr auto &operator[](const T2 k) { throw nullptr; };
		// compute_type
		static consteval char* compute_type() requires Concepts::has_type<T> { return T::type; };
		static consteval char* compute_type() requires Concepts::is_boolean<T> { return "boolean"; };
		static consteval char* compute_type() requires Concepts::is_number<T> { return "number"; };
		static consteval char* compute_type() requires Concepts::is_undefined<T> { return "undefined"; };
		static consteval char* compute_type() { return "native"; };
	};
}
