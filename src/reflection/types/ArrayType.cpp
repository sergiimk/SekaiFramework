/*========================================================
* ArrayType.cpp
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "ArrayType.h"
#include "typetraits.h"
#include <stdio.h>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	ArrayType::ArrayType(Type* elemType, int elems)
		: mElemCount(elems)
		, mElem(elemType)
	{ }

	//////////////////////////////////////////////////////////////////////////

	size_t ArrayType::Name(char *buf, size_t size) const 
	{
		size_t p = detail::type_get_name_safe(mElem, buf, size);
		p += sprintf(&buf[p - 1], " [%d]", mElemCount);
		return p;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t ArrayType::FullName(char *buf, size_t size) const 
	{
		return Name(buf, size);
	}

	//////////////////////////////////////////////////////////////////////////

	bool ArrayType::ToString(void* value, char* buf, size_t size) const
	{
		Name(buf, size);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool ArrayType::Equal(const Type* other) const
	{
		if(ArchType() != other->ArchType())
			return false;

		return Tag() == other->Tag();
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
