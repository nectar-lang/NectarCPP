module;
#pragma once
#include <concepts>
export module NectarCore:operators;
import NectarCore:concepts;

export namespace NectarCore::Operators
{
	template<typename T> constexpr T NullishCoalescing (T lhs, T rhs) {
		[[unlikely]] if (lhs == nullptr) return rhs;
		return lhs;
	}
	template<Concepts::has_nullish T> constexpr T NullishCoalescing (T lhs, T rhs) {
		[[unlikely]] if (lhs.isNullish()) return rhs;
		return lhs;
	}
	template<Concepts::has_nullish T, typename T2>
	T NullishCoalescing (T lhs, T2 rhs) requires Concepts::convertible_to<T2, T> {
		[[unlikely]] if (lhs.isNullish()) return rhs;
		return lhs;
	}
	template<Concepts::has_nullish T, typename T2>
	T NullishCoalescing (T2 lhs, T rhs) requires Concepts::convertible_to<T2, T> {
		[[unlikely]] if (((T)lhs).isNullish()) return rhs;
		return lhs;
	}
}
