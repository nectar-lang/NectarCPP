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
	template<Concepts::var_nullish T> constexpr T NullishCoalescing (T lhs, T rhs) {
		[[unlikely]] if (lhs.isNullish()) return rhs;
		return lhs;
	}
	template<Concepts::var_nullish T, typename T2>
	T NullishCoalescing (T lhs, T2 rhs) requires Concepts::convertible_to<T2, T> {
		[[unlikely]] if (lhs.isNullish()) return rhs;
		return lhs;
	}
	template<Concepts::var_nullish T, typename T2>
	T NullishCoalescing (T2 lhs, T rhs) requires Concepts::convertible_to<T2, T> {
		[[unlikely]] if (((T)lhs).isNullish()) return rhs;
		return lhs;
	}

	template<typename T, typename T2> constexpr T UnsignedRightShift (T lhs, T2 rhs)
	requires (Concepts::convertible_to<T, int> && Concepts::convertible_to<T2, int>)
	{
		return (int)(reinterpret_cast<unsigned int>((int)lhi) >> (int)rhi);
	}

	template<typename T> constexpr bool StrictEqual (T lhs, T rhs) {
		return lhs == rhs;
	}
	template<Concepts::var_type T, typename T2>
	constexpr bool StrictEqual (T lhs, T2 rhs) requires Concepts::convertible_to<T2, T> {
		T _rhs = rhs;
		return lhs.property.type == _rhs.property.type && StrictEqual(lhs, _rhs);
	}
}
