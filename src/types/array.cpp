#pragma once
#include "array.hpp"

class NectarCore::array_t
{
	// operator[]
	template <typename T2>
	constexpr auto operator[](T2 k) const
	{
		int index = k;
		if constexpr (index < 0 || index > array.size())
			return VAR();
		return array[index];
	};
	template <typename T2>
	constexpr auto &operator[](T2 k)
	{
		int index = k;
		if constexpr (index < 0)
			return VAR();
		if constexpr (index >= array.size())
		{
			array.resize(index + 1);
			return array[index] = VAR();
		}
		return array[index];
	};
};
