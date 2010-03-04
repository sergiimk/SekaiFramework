#include "testclasses.h"

std::ostream& operator<<(std::ostream& os, const TestEnum& cc)
{
	if(cc == VAL_1) os<<"VAL_1";
	if(cc == VAL_2) os<<"VAL_2";
	return os;
}

std::istream& operator>>(std::istream& os, TestEnum& cc)
{
	std::string s;
	os >> s;
	if(s == "VAL_1") cc = VAL_1;
	else if(s == "VAL_2") cc = VAL_2;
	else os.setstate(std::ios::failbit);
	return os;
}

