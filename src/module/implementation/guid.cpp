/*========================================================
* guid.cpp
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

namespace module
{
	//////////////////////////////////////////////////////////////////////////

	bool guid::parse(const char* s)
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
				&data1, &data2, &data3,
				&_data[0], &_data[1], &_data[2], &_data[3],
				&_data[4], &_data[5], &_data[6], &_data[7]) != 11)
			return false;

		for(int i = 0; i != 8; ++i)
			data4[i] = (unsigned char)_data[i];
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void guid::to_string(char* buf) const
	{
		sprintf( buf, "%08lX-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X",
			data1, data2, data3,
			data4[0], data4[1], data4[2], data4[3],
			data4[4], data4[5], data4[6], data4[7] );
	}

	//////////////////////////////////////////////////////////////////////////

	std::ostream& operator<<(std::ostream& os, const guid& g)
	{
		char buff[37];
		g.to_string(buff);
		os << buff;
		return os;
	}

	//////////////////////////////////////////////////////////////////////////

	std::istream& operator>>(std::istream& is, guid& g)
	{
		char buff[39];
		is.get(buff, 37, '\n');
		if(buff[0] == '{')
			is.get(&buff[36], 3, '\n');

		if(!is) return is;
		if(!g.parse(buff))
			is.setstate(std::ios_base::failbit);

		return is;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
