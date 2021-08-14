#pragma once
#include <vector>

namespace NectarCore
{
	struct VAR
	{
	};

	class array_t
	{
		static constexpr char type[] = "array";
		std::vector<VAR> array;
		array_t();
		array_t(const array_t &) = default;
		array_t(const array_t &&) = default;
		// operator[]
		template <typename T2>
		constexpr auto operator[](T2 k) const;
		template <typename T2>
		constexpr auto &operator[](T2 k);
	};
}
