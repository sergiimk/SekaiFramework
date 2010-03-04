/*========================================================
* PointerType.cpp
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "PointerType.h"
#include "typetraits.h"

#include <string.h>
#include <string>
#include <sstream>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	size_t PointerType::Name( char* buf, size_t size ) const
	{
		size_t p = detail::type_get_name_safe(mPointed, buf, size);
		buf[p - 1] = '*';
		buf[p++] = '\0';
		return p;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t PointerType::FullName( char* buf, size_t size ) const
	{
		return Name(buf, size);
	}

	//////////////////////////////////////////////////////////////////////////

	bool PointerType::Equal( const Type* other ) const
	{
		if(	ArchType() != other->ArchType())
			return false;

		return getPointedType()->Equal(static_cast<const PointerType*>(other)->getPointedType());
	}

	//////////////////////////////////////////////////////////////////////////

	bool PointerType::ToString( void* value, char* buf, size_t size ) const
	{
		std::ostringstream ss; 
		ss << "0x" << std::hex << reinterpret_cast<size_t>(*(void**)value); 
		std::string t = ss.str();
		strncpy(buf, t.c_str(), std::min(t.size(), size));
		return size > t.size();
	}

	//////////////////////////////////////////////////////////////////////////

	void PointerType::Assign( void* to, void* val ) const
	{
		memcpy(to, val, sizeof(void*));
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
