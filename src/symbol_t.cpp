module;
#pragma once
#include <cstddef>
export module NectarCore:symbol_t;

export namespace NectarCore
{
	struct symbol_t
	{
		static constexpr const char* type = "symbol";
		static unsigned int SymbolCounter;
		unsigned int id;
		symbol_t() : id(SymbolCounter++){};
		std::size_t hash() const { return id; }
	};
}
unsigned int NectarCore::symbol_t::SymbolCounter = 0;
