module;
#pragma once

// TODO: Refactor
#include <vector>
#include <string>
// TODO: Remove
#include <cmath>
#include <limits>

export module NectarCore;
import :concepts;
import :operators;
import :prototype;
import :symbol_t;
import :value;

export namespace NectarCore
{
	class VAR
	{
		public:
		enum VarType
		{
			Undefined = 0,
			Null,
			Boolean,
			Number,
			String,
			Array,
			Object,
			Function,
			// ESNext types
			Symbol,
			BigInt,
			// Custom types
			Native,
			NativeTPL,
			Struct,
			FixedArray,
			// Reserved types
			Reserved,
			Reserved2
		};

		struct Empty {};
		struct VarMeta
		{
			VarType type : 4 = VarType::Undefined;
			bool isConfigurable : 1 = false;
			bool isEnumerable : 1 = false;
			bool isWritable : 1 = true;
			bool _fastNumber : 1 = true;
		};
		union VarData
		{
			Value<int> integer;
			Value<bool> boolean;
			Value<double> number;
			Value<long long> bigint;
			Value<std::string*> string;
			Value<std::vector<VAR>*> array;
			Value<Prototype<VAR, std::string>*> object;
			Value<symbol_t> symbol;
			[[no_unique_address]] Value<std::nullptr_t> undefined;
		};

		VarMeta property;
		VarData data;
		union {
			Prototype<VAR, std::string>* properties;
			[[no_unique_address]] Empty empty;
		};
		// Constructors/Destructors
		VAR() = default;
		~VAR();
		VAR(VAR const &_v);
		VAR(VAR const &&_v);

		// Type casting
		VAR(int value);
		VAR(bool value);
		VAR(double value);
		VAR(std::string value);
		operator int() const;
		operator bool() const;
		operator double() const;
		operator std::string() const;

		// Operators
		// Comparison operators
		auto operator<=>(VAR &compare);
		bool operator==(VAR &compare);
		/// Addition operator
		auto operator+(const VAR &rhs);
		auto operator+(const char rhs[]);
		// Other operators
		void operator=(const VAR &_v);
		template <class... Args>
		auto operator()(Args... args);
		template <typename T>
		auto operator[](T);
		inline constexpr bool isPrimitive();
		inline constexpr bool isNullish();

	private:
		constexpr auto comparablePrimitive();
		constexpr auto comparableStringPrimitive();
	};
}


class NectarCore::VAR
{
public:
	~VAR()
	{
		if (!isPrimitive())
		{
			NectarCore::Class::Base *ptr = data.pointer;
			ptr->Delete();
			delete ptr;
		}
	};
	VAR(VAR const &_v)
	{
		if (!property.isWritable)
			return;

		property = _v.property;
		if (isPrimitive())
		{
			data = _v.data;
		}
		else
			data.pointer = ((NectarCore::Class::Base *)_v.data.pointer)->Copy();
	};
	VAR(VAR const &&_v)
	{
		property = _v.property;
		if (isPrimitive())
		{
			data = _v.data;
		}
		else
			data.pointer = ((NectarCore::Class::Base *)_v.data.pointer)->Copy();
	};

	// Type casting
	VAR(int value) : property.type(VarType::Number), data.integer(value){};
	VAR(bool value) : property.type(VarType::Boolean), data.boolean(value){};
	VAR(double value) : property.type(VarType::Number), property._fastNumber(false), data.number(value){};
	VAR(std::string value) : property.type(VarType::String), data.pointer(*value){};
	// VAR(void* value);
	operator int() const { return getInteger(); };
	operator bool() const { return getBoolean(); };
	operator double() const { return getDouble(); };
	operator std::string() const { return getString(); };
	// explicit operator void*() const;

	// Operators
	// Comparison operators
	auto operator<=>(VAR &compare)
	{
		if (type == compare.type && isPrimitive())
			return data.integer <=> compare.data.integer;
		if (type == NectarCore::Enum::Type::String || compare.type == NectarCore::Enum::Type::String)
			return getString().compare((std::string)compare) <=> 0;
		return getDouble() <=> (double)compare;
	};
	bool operator==(VAR &compare)
	{
		if (type == compare.type)
		{
			if (isPrimitive())
				return data.integer == compare.data.integer;
			if (type == NectarCore::Enum::Type::String)
				return getString().compare((std::string)compare) == 0;
			return false;
		}
		if (type == NectarCore::Enum::Type::String || compare.type == NectarCore::Enum::Type::String)
		{
			return getString().compare((std::string)compare) == 0;
		}
		return getDouble() == (double)compare;
	}
	/// Addition operator
	auto operator+(const VAR &rhs) {
		if (property._fastNumber && rhs.property._fastNumber) {
			return getInteger() + (int)rhs;
		}
		if (isPrimitive() && rhs.isPrimitive()) {
			return getDouble() + (double)rhs;
		}
		return VAR(getString() + (std::string)rhs);
	}
	auto operator+(const char rhs[]) {
		return VAR(getString() + rhs);
	}
	// Other operators
	void operator=(const VAR &_v);
	template <class... Args>
	auto operator()(Args... args);
	template <typename T>
	auto operator[](T);

	constexpr bool isPrimitive() { return property.type <= VarType::Number; }
private:
	constexpr int getInteger()
	{
		if (isPrimitive())
		{
			if (property.type != VarType::Number)
				return property.boolean;
			return property._fastNumber ? data.integer : data.number;
		}
		return getDouble();
	};
	constexpr bool getBoolean()
	{
		if (isPrimitive() && property.type != VarType::Number)
			return data.boolean;
		return getInteger();
	}
	constexpr double getDouble()
	{
		if (isPrimitive())
		{
			if (property.type == VarType::Undefined)
				return std::numeric_limits<double>::quiet_NaN();
			if (property.type != VarType::Number)
				return property.boolean;
			return property._fastNumber ? data.integer : data.number;
		}
		return (double)comparablePrimitive();
	}
	constexpr std::string getString()
	{
		switch (property.type)
		{
		case VarType::Undefined:
			return "undefined";
		case VarType::Null:
			return "null";
		case VarType::Boolean:
			return data.boolean ? "true" : "false";
		case VarType::Number:
			if (property._fastNumber) return data.integer;
			if (std::isnan(data.number))
				return "NaN";
			if (std::isinf(data.number))
				return data.number < 0 ? "-Infinity" : "Infinity";
			return data.number;
		default:
			return (std::string)comparableStringPrimitive();
		}
	}
	constexpr auto comparablePrimitive()
	{
		return this;
	};
	constexpr auto comparableStringPrimitive()
	{
		return this;
	};
};
