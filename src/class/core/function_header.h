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

#pragma once
#include <functional>
#include "../base_header.h"

namespace NectarCore::Class
{
	class Function : public virtual Base
	{
	public:
		// Constructors
		Function();
		Function(void *val);
		Function(void *val, NectarCore::VAR bind);
		// Properties
		count_t counter = 0;
#ifdef __Nectar_DEBUG
		std::string code = "[native code]";
#endif
		function_t *value = nullptr;
		NectarCore::VAR This;
		object_t object;

		inline void Delete() noexcept;
		inline void jsDelete(std::string _key) noexcept;
		inline void *Copy() noexcept;
		inline NectarCore::VAR Call(NectarCore::VAR &__Nectar_THIS, NectarCore::VAR *_args, int i)
		{
			return (*static_cast<function_t *>(value))(__Nectar_THIS, _args, i);
		}
		template <class... Args>
		NectarCore::VAR New(Args... args)
		{
			NectarCore::VAR _args[] = {args...};
			int i = sizeof...(args);

			NectarCore::VAR _this = __Nectar_Object_Clone((*this)["prototype"]);
			if (_this.type == NectarCore::Enum::Type::Undefined)
				_this = new NectarCore::Class::Object();

			NectarCore::VAR _ret = this->Call(_this, _args, i);

			if (_ret.type == NectarCore::Enum::Type::Object)
			{
				auto &obj = (NectarCore::Class::Object *)_ret.data.ptr;
				obj->property.set(1, 1);
				obj->instance.push_back((*this)["prototype"].data.ptr);
				return _ret;
			}
			else
			{
				auto &obj = (NectarCore::Class::Object *)_this.data.ptr;
				obj->property.set(1, 1);
				obj->instance.push_back((*this)["prototype"].data.ptr);
				return _this;
			}
		}

		template <class... Args>
		NectarCore::VAR operator()(Args... args)
		{
			NectarCore::VAR _args[] = {args...};
			int i = sizeof...(args);
			return (*static_cast<function_t *>(value))(This, _args, i);
		}

		explicit operator std::string() const noexcept;

		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](int key);
		NectarCore::VAR &operator[](double key);
		NectarCore::VAR &operator[](const char *key);

		NectarCore::VAR apply(NectarCore::VAR *_args, int _length);
		NectarCore::VAR bind(NectarCore::VAR *_args, int _length);
		NectarCore::VAR call(NectarCore::VAR *_args, int _length);
		NectarCore::VAR toString(NectarCore::VAR *_args, int _length) const;
		NectarCore::VAR valueOf(NectarCore::VAR *_args, int _length) const;
	};
} // namespace NectarCore::Class