/*========================================================
* GUID.cpp
* @author Sergey Mikhtonyuk
* @date 22 April 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "guid.h"
#include <stdio.h>
#include <iostream>

namespace Module
{
	//////////////////////////////////////////////////////////////////////////

	bool GUID::FromString(const char* s)
	{
		if (!s)
			return false;

		size_t size = strlen(s);

		if(size != 38 && size != 36)
			return false;

		if (size == 38 && ( s[0] != '{' || s[37] != '}' ) )
			return false;

		size_t start = size == 38 ? 1 : 0;

		int _data[8];

		if(sscanf(&s[start], "%08lX-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X",
				&Data1, &Data2, &Data3,
				&_data[0], &_data[1], &_data[2], &_data[3],
				&_data[4], &_data[5], &_data[6], &_data[7]) != 11)
			return false;

		for(int i = 0; i != 8; ++i)
			Data4[i] = (unsigned char)_data[i];
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void GUID::ToString(char* buf) const
	{
		sprintf( buf, "%08lX-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X",
			Data1, Data2, Data3,
			Data4[0], Data4[1], Data4[2], Data4[3],
			Data4[4], Data4[5], Data4[6], Data4[7] );
	}

	//////////////////////////////////////////////////////////////////////////

	std::ostream& operator<<(std::ostream& os, const GUID& guid)
	{
		char buff[37];
		guid.ToString(buff);
		os << buff;
		return os;
	}

	//////////////////////////////////////////////////////////////////////////

	std::istream& operator>>(std::istream& is, GUID& guid)
	{
		char buff[39];
		is.get(buff, 37, '\n');
		if(buff[0] == '{')
			is.get(&buff[36], 3, '\n');

		if(!is) return is;
		if(!guid.FromString(buff))
			is.setstate(std::ios_base::failbit);

		return is;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
