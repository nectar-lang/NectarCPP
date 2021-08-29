module;
#pragma once
#include <concepts>
#include <string>
export module NectarCore:concepts;

export namespace NectarCore::Concepts
{
		template <typename T>
		concept is_boolean = std::is_same_v<T, bool>;
		template <typename T>
		concept is_integral = std::is_integral_v<T>;
		template <typename T>
		concept is_number = is_integral<T> && !is_boolean<T>;
		template <typename T>
		concept is_undefined = std::is_null_pointer_v<T>;
		template <typename T>
		concept is_string = std::is_same_v<T, std::string *>;
		template <typename T>
		concept is_pointer = std::is_pointer_v<T> && !is_undefined<T>;

		template <typename T>
		concept is_primitive = is_integral<T> || is_undefined<T>;
		template <typename T>
		concept is_standard = is_integral<T> || std::is_same_v<T, std::string>;
		template <typename T>
		concept should_define_T = !is_standard<T>;

		template <typename T, typename T2>
		concept convertible_to = requires(T v) { { (T2)v } -> std::same_as<T2>; };

		template <typename T, typename T2>
		concept has_lookup = requires(T t, T2 k) { { t[k] }; };

		template <typename T>
		concept has_type = requires { typename T::type; };

		template<typename T>
		concept var_nullish = requires(T t) { t.isNullish(); };

		template<typename T>
		concept var_type = requires(T t) { t.property.type; };
};