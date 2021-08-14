#include "../src/nectar.hpp"

int main()
{
	try 
	{

auto &console = NectarCore::Global::console;
auto &Object = NectarCore::Global::Object;
NectarCore::VAR maching_pairs=NectarCore::Class::Object((NectarCore::Class::object_t){(NectarCore::Type::pair_t)({'[',']'),(NectarCore::Type::pair_t)({'(',')')});
NectarCore::VAR fibonacci = NectarCore::Class::Function([&](NectarCore::VAR __Nectar_THIS, NectarCore::VAR* __Nectar_VARARGS, int __Nectar_VARLENGTH) {
NectarCore::VAR n;
if (__Nectar_VARLENGTH > 0) n = __Nectar_VARARGS[0];

if (n < 2) {
return n;
}
return fibonacci(n - 2) + fibonacci(n - 1);
)
console["log"](fibonacci(45));
NectarCore::VAR elements=NectarCore::Class::Array((NectarCore::Class::vector_t){NectarCore::Global::undefined,NectarCore::Global::null,NectarCore::Global::NaN,1,"str",NectarCore::Class::Array(),NectarCore::Class::Array((NectarCore::Class::vector_t){0,1,2}),NectarCore::Class::Object((NectarCore::Class::object_t){(NectarCore::Type::pair_t)({"key","value")}),NectarCore::Class::Object()});
for (NectarCore::VAR i=0;;i < elements["length"];i++) {
for (NectarCore::VAR j=0;;j < elements["length"];j++) {
console["log"](elements[i],"+",elements[j],"=",elements[i] + elements[j],"- type:",typeofelements[i] + elements[j]);
console["log"](elements[i],"-",elements[j],"=",elements[i] - elements[j],"- type:",typeofelements[i] - elements[j]);
console["log"](elements[i],"*",elements[j],"=",elements[i] * elements[j],"- type:",typeofelements[i] * elements[j]);
console["log"](elements[i],"/",elements[j],"=",elements[i] / elements[j],"- type:",typeofelements[i] / elements[j]);
console["log"](elements[i],">",elements[j],"=",elements[i] > elements[j],"- type:",typeofelements[i] > elements[j]);
console["log"](elements[i],"<",elements[j],"=",elements[i] < elements[j],"- type:",typeofelements[i] < elements[j]);
console["log"](elements[i],"%",elements[j],"=",elements[i] % elements[j],"- type:",typeofelements[i] % elements[j]);
console["log"](elements[i],"^",elements[j],"=",elements[i] ^ elements[j],"- type:",typeofelements[i] ^ elements[j]);
console["log"](elements[i],"&",elements[j],"=",elements[i] & elements[j],"- type:",typeofelements[i] & elements[j]);
console["log"](elements[i],">>",elements[j],"=",elements[i] >> elements[j],"- type:",typeofelements[i] >> elements[j]);
console["log"](elements[i],"<<",elements[j],"=",elements[i] << elements[j],"- type:",typeofelements[i] << elements[j]);
console["log"](elements[i],"==",elements[j],"=",elements[i] == elements[j],"- type:",typeofelements[i] == elements[j]);
console["log"](elements[i],"!=",elements[j],"=",elements[i] != elements[j],"- type:",typeofelements[i] != elements[j]);
console["log"](elements[i],"===",elements[j],"=",elements[i] <NectarCore::::Operator::StrictEqual> elements[j],"- type:",typeofelements[i] <NectarCore::::Operator::StrictEqual> elements[j]);
console["log"](elements[i],"!==",elements[j],"=",elements[i] <NectarCore::::Operator::StrictNotEqual> elements[j],"- type:",typeofelements[i] <NectarCore::::Operator::StrictNotEqual> elements[j]);
}
}
for (NectarCore::VAR i=0;;i < elements["length"];i++) {
NectarCore::VAR _left=Object["clone"](elements[i]);
console["log"](_left,"+=",elements[j],"=",_left += elements[j],"- type:",typeof_left);
_left = Object["clone"](elements[i]);
console["log"](_left,"*=",elements[j],"=",_left *= elements[j],"- type:",typeof_left);
_left = Object["clone"](elements[i]);
console["log"](_left,"-=",elements[j],"=",_left -= elements[j],"- type:",typeof_left);
_left = Object["clone"](elements[i]);
console["log"](_left,"/=",elements[j],"=",_left /= elements[j],"- type:",typeof_left);
_left = Object["clone"](elements[i]);
console["log"](_left,"%=",elements[j],"=",_left %= elements[j],"- type:",typeof_left);
_left = Object["clone"](elements[i]);
console["log"](_left,"^=",elements[j],"=",_left ^= elements[j],"- type:",typeof_left);
_left = Object["clone"](elements[i]);
console["log"](_left,"&=",elements[j],"=",_left &= elements[j],"- type:",typeof_left);
}
for (NectarCore::VAR i=0;;i < elements["length"];i++) {
NectarCore::VAR _left=Object["clone"](elements[i]);
console["log"](_left,"++","=",_left++,"- type:",typeof_left);
_left = Object["clone"](elements[i]);
console["log"](_left,"--","=",_left--,"- type:",typeof_left);
}

}
	catch(var& error)
	{
		println(error);
		return 1;
	}
	return 0;
}