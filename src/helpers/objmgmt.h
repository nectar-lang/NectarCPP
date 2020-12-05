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
 
int __Nectar_Get_Int(NectarCore::VAR _v)
{
	return (int)_v.data.number;
}

const char *__Nectar_Get_String(NectarCore::VAR _v)
{
	if (_v.type != NectarCore::Enum::Type::String)
		return "";
	return ((NectarCore::Class::String*)_v.data.ptr)->value.c_str();
}

const std::string _array[] = {"object", "boolean", "number", "string", "native", "struct", "fixed_array", "array", "object", "function", "NectarCore::Global::undefined" };
NectarCore::VAR __Nectar_typeof(NectarCore::VAR _var)
{
	return __Nectar_Create_String(_array[_var.type]);
}

NectarCore::VAR __Nectar_instanceof(NectarCore::VAR _left, NectarCore::VAR _right)
{
	if(_left.type < NectarCore::Enum::Type::Object) return __Nectar_Boolean_FALSE;
	
	NectarCore::VAR protoRight = _right["prototype"];
	if(!protoRight) return __Nectar_Boolean_FALSE;
	
	NectarCore::Type::vector_p vLeft = ((NectarCore::Class::Object*)_left.data.ptr)->instance;
		
	for (auto searchLeft : vLeft)
	{
		if(searchLeft == protoRight.data.ptr) return __Nectar_Boolean_TRUE;
	}
	return __Nectar_Boolean_FALSE;
}

NectarCore::VAR __Nectar_delete(NectarCore::VAR _left, NectarCore::VAR _right)
{
	if(_left.type == NectarCore::Enum::Type::Object)
	{
		((NectarCore::Class::Object*)_left.data.ptr)->jsDelete(_right);
		return __Nectar_Boolean_TRUE;
	}
	else if(_left.type == NectarCore::Enum::Type::Array)
	{
		((NectarCore::Class::Array*)_left.data.ptr)->jsDelete(_right);
		return __Nectar_Boolean_TRUE;
	}
	else if(_left.type == NectarCore::Enum::Type::Function)
	{
		((NectarCore::Class::Function*)_left.data.ptr)->jsDelete(_right);
		return __Nectar_Boolean_TRUE;
	}
	return __Nectar_Boolean_FALSE;
}

/*** ***/
template <typename T> NectarCore::VAR __Nectar_InitVar(T _init)
{
	return NectarCore::VAR(_init);
}