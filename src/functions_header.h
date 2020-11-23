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
 
Nectar::VAR __Nectar_Log_Console(Nectar::VAR _var);
Nectar::VAR __Nectar_Object_Keys(Nectar::VAR _var);
Nectar::VAR __Nectar_Object_Stringify(Nectar::VAR _var);
Nectar::VAR __Nectar_Object_Stringify(Nectar::VAR _var, bool _bracket);
Nectar::Class::Object* __Nectar_Create_Object();
Nectar::Class::Array* __Nectar_Create_Array();
Nectar::VAR __Nectar_Object_Clone(Nectar::VAR& _var);
Nectar::VAR __Nectar_Object_Set(std::string _index, Nectar::VAR _value, Nectar::Type::object_t *_obj);
std::string __Nectar_DOUBLE_TO_STRING(double _var);

template <typename m, typename n>
std::string __Nectar_Concat_To_Str(m _left, n _right);

template <typename m>
int __Nectar_Str_To_Int(m _left);

template <typename m>
double __Nectar_Str_To_Double(m _left);

Nectar::VAR getArguments(int argc, char** argv);