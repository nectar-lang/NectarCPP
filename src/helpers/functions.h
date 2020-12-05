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

NectarCore::VAR getArguments(int argc, char** argv)
{
	NectarCore::VAR __NJS_ARGS = new NectarCore::Class::Array();
	for( int i = 0; i < argc; i++)
	{
		__NJS_ARGS[i] = argv[i];
	}
	return __NJS_ARGS;
}

#ifndef __Nectar__OBJECT_VECTOR
NectarCore::VAR __Nectar_Object_Set(std::string _index, NectarCore::VAR _value, NectarCore::Type::object_t *_obj)
{
	
	if (_value.type == NectarCore::Enum::Type::String)
	{
		(*_obj)[_index] = new NectarCore::Class::String((std::string)_value);
	}
	else
	{
		(*_obj)[_index].data.ptr = _value.data.ptr;
	}
		
	return NectarCore::Global::undefined;
}
#else
NectarCore::VAR __Nectar_Object_Set(std::string _index, NectarCore::VAR _value, NectarCore::Type::object_t *_obj)
{
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (_index.compare((*_obj)[_i].first) == 0)
		{

			if (_value.type == NectarCore::Enum::Type::String)
			{
				(*_obj)[_i].second = new NectarCore::Class::String((std::string)_value);
			}
			else
			{
				(*_obj)[_i].second.data.ptr = _value.data.ptr;
			}

			return NectarCore::Global::undefined;
		}
	}

	(*_obj).push_back(NectarCore::Type::pair_t(_index, _value));
	return NectarCore::Global::undefined;
}
#endif
/**/

NectarCore::VAR __Nectar_Object_Set(NectarCore::VAR _index, NectarCore::VAR _value, NectarCore::VAR _array)
{
	if (_array.type == NectarCore::Enum::Type::Array && _index.type == NectarCore::Enum::Type::Number)
	{

		if (((NectarCore::Class::Array*)_array.data.ptr)->value.size() <= (int)_index.data.number)
		{
			((NectarCore::Class::Array*)_array.data.ptr)->value.resize( (int)_index.data.number + 1);
		}

		((NectarCore::Class::Array*)_array.data.ptr)->value.at( (int)_index.data.number ) = _value;
		
		return NectarCore::Global::undefined;
	}
	else if (_array.type == NectarCore::Enum::Type::Object || _array.type == NectarCore::Enum::Type::String || _array.type == NectarCore::Enum::Type::Function || _array.type == NectarCore::Enum::Type::Array || _array.type == NectarCore::Enum::Type::Native)
	{
		NectarCore::Type::object_t *_obj;
		if (_array.type == NectarCore::Enum::Type::Object)
			_obj = &((NectarCore::Class::Object*)_array.data.ptr)->object;
		else if (_array.type == NectarCore::Enum::Type::Array)
			_obj = &((NectarCore::Class::Array*)_array.data.ptr)->object;
		else if (_array.type == NectarCore::Enum::Type::String)
			_obj = &((NectarCore::Class::String*)_array.data.ptr)->object;
		else if (_array.type == NectarCore::Enum::Type::Function)
			_obj = &((NectarCore::Class::Function*)_array.data.ptr)->object;
		else
			return NectarCore::Global::undefined;

		return __Nectar_Object_Set((std::string)_index, _value, _obj);
	}

	return NectarCore::Global::undefined;
}
