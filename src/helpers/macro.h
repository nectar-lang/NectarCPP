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

/*** HELPERS ***/
#define __Nectar_GET_String(_var) _var.get().s->value
#define __Nectar_Create_Boolean(_value) NectarCore::VAR(NectarCore::Enum::Type::Boolean, _value)
#define __Nectar_Create_Number(_value) NectarCore::VAR(_value)
#define __Nectar_Create_Function(_value) NectarCore::VAR(NectarCore::Enum::Type::Function, _value)
#define __Nectar_Create_Undefined() NectarCore::VAR()
#define __Nectar_Create_String(_value) NectarCore::VAR(_value)
#define __Nectar_Create_Infinity() NectarCore::VAR(std::numeric_limits<double>::infinity)
#define __Nectar_Create_Null() NectarCore::VAR(NectarCore::Enum::Type::Null, 0)
#define __Nectar_Create_Struct(_value) NectarCore::VAR(new _value(), new NectarCore::Type::clean_struct([](void* _ptr){ delete (_value*)_ptr;}))
#define __Nectar_Create_FixedArray(_length) NectarCore::VAR(new NectarCore::Class::FixedArray(_length))
#define __Nectar_Create_Lambda(name) NectarCore::Type::function_t* name = new NectarCore::Type::function_t([](NectarCore::VAR __Nectar_THIS, NectarCore::VAR* __Nectar_VARARGS, int __Nectar_VARLENGTH)
#define __Nectar_Create_Ptr_Scoped_Anon(__CONTENT__) new NectarCore::Type::function_t([&](NectarCore::VAR __Nectar_THIS, NectarCore::VAR* __Nectar_VARARGS, int __Nectar_VARLENGTH){ __CONTENT__ })
#define __Nectar_Create_Ptr_Unscoped_Anon(__CONTENT__) new NectarCore::Type::function_t([](NectarCore::VAR __Nectar_THIS, NectarCore::VAR* __Nectar_VARARGS, int __Nectar_VARLENGTH){ __CONTENT__ })
#define __Nectar_Create_Var_Scoped_Anon(__CONTENT__) NectarCore::VAR(NectarCore::Enum::Type::Function, __Nectar_Create_Ptr_Scoped_Anon(__CONTENT__))
#define __Nectar_Create_Var_Unscoped_Anon(__CONTENT__) NectarCore::VAR(NectarCore::Enum::Type::Function, __Nectar_Create_Ptr_Unscoped_Anon(__CONTENT__))
#define __Nectar_Init_Int(_name, _value) int _name = _value
#define __Nectar_Init_Double(_name, _value) double _name = _value
#define __Nectar_Init_String(_name, _value) std::string _name = _value
#define __Nectar_EXCEPTION_PARAMETER NectarCore::VAR &e
#define finally ;
#define __Nectar_Throw_Error(_err) NectarCore::VAR(NectarCore::VAR(_err) + NectarCore::VAR(", line: ") + std::to_string(__LINE__) + NectarCore::VAR(", file: ") + NectarCore::VAR(__FILE__))
#define __Nectar_Boolean_TRUE __Nectar_Create_Boolean(true)
#define __Nectar_Boolean_FALSE __Nectar_Create_Boolean(false)
#define __Nectar_FAST_INT double
#define __Nectar_CreateMethodToClass(_name, _fn) __Nectar_Object_Set(_name, __Nectar_Create_Var_Scoped_Anon( return _fn(__Nectar_VARARGS, __Nectar_VARLENGTH); ), &object);
#define __Nectar_NEW(_fn) ((NectarCore::Class::Function*)_fn.data.ptr)->New
#define __Nectar_SET_CONST(_var) _var.property.set(0,1)
#define __Nectar_Access_Struct(_exp, _name) (*(_name*)((NectarCore::Class::Struct*)_exp.data.ptr)->value)

#ifndef __Nectar__OBJECT_VECTOR
#define __Nectar_Method_Lazy_Loader(_name, _fn) \
if(_sview.compare(_name) == 0) { \
object[_str] = __Nectar_Create_Var_Scoped_Anon( return _fn(__Nectar_VARARGS, __Nectar_VARLENGTH); ); \
object[_str].property.set(1,1); \
return object[_str];}
#define __Nectar_Object_Lazy_Loader(_name) \
if(_sview.compare(_name) == 0) { \
object[_str] = new NectarCore::Class::Object(); \
object[_str].property.set(1,1); \
return object[_str];}
#else
#define __Nectar_Method_Lazy_Loader(_name, _fn) \
if(_sview.compare(_name) == 0) { \
object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return _fn(__Nectar_VARARGS, __Nectar_VARLENGTH); ))); \
object.back().second.property.set(1,1); \
return object.back().second;}
#define __Nectar_Object_Lazy_Loader(_name) \
if(_sview.compare(_name) == 0) { \
object.push_back(NectarCore::Type::pair_t(_str, new NectarCore::Class::Object())); \
object.back().second.property.set(1,1); \
return object.back().second;}
#endif

/* END HELPERS */
