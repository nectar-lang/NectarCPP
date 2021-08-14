module;
#pragma once
#include <functional>
#include <string>
#include <unordered_map>
export module NectarCore:prototype;

export namespace NectarCore
{
	template<class T> struct PropertyDescriptor
	{
		struct Accessor
		{
			std::function<T(T&, T*, int)> *get;
			std::function<T(T&, T*, int)> *set;
		};
		struct
		{
			bool configurable : 1 = false;
			bool enumerable : 1 = false;
			bool writable : 1 = false;
			bool hasValue : 1 = true;
		};
		union
		{
			Accessor accessor;
			T *value;
		};
	};

	template <class Type, class Key = Type> class Prototype
	{
	private:
		std::unordered_map<Key, PropertyDescriptor<Type>> properties = {};
	public:
		Prototype *parent = nullptr;
		Prototype() = default;
		Prototype(Prototype &parent) : parent(&parent){};
		Prototype(const Prototype &) = delete;
		const Type &operator[](Key &key) const {
			const auto& desc = getDescriptor(key);
			[[likely]] if (desc.hasValue) return desc.value;
			return (*desc.accessor.get)(nullptr, 0);
		};
		Type &operator[](Key key) {
		auto& desc = getDescriptor(key);
			[[likely]] if (desc.hasValue) return desc.value;
			auto value = (*desc.accessor.get)(nullptr, 0);
			// TODO: Setter
			value.isWritable = false;
			return value;
		};
		PropertyDescriptor<Type> getDescriptor(Key &key) const {
			[[likely]] if (properties.contains(key)) return properties.at(key);
			[[unlikely]] if (parent == nullptr) return PropertyDescriptor<Type>();
			return parent->getDescriptor(key);
		};
		PropertyDescriptor<Type> &getDescriptor(Key &key) {
			[[likely]] if (properties.contains(key)) return properties.at(key);
			[[unlikely]] if (parent == nullptr)
			{
				PropertyDescriptor<Type> desc = {};
				properties.insert_or_assign(key, desc);
				return desc;
			}
			return parent->getDescriptor(key);
		};
	};
}
