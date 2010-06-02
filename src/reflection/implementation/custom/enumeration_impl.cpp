/*========================================================
* enumeration_impl.cpp
* @author Sergey Mikhtonyuk
* @date 04 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "custom/enumeration_member.h"
#include "member_impl.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	struct enumeration_member::enumeration_impl : public member::member_impl
	{
		enumeration_impl(const char* name, unsigned int value)
			: member_impl(MEMBER_ENUMERATION, name)
			, m_value(value)
		{ }

		unsigned int m_value;
	};

	//////////////////////////////////////////////////////////////////////////

	enumeration_member::enumeration_member(const char* name, unsigned int value)
		: member(new enumeration_impl(name, value))
	{ }

	//////////////////////////////////////////////////////////////////////////

	unsigned int enumeration_member::get_value() const
	{
		return static_cast<enumeration_impl*>(m_impl)->m_value;
	}

	//////////////////////////////////////////////////////////////////////////

	void enumeration_member::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
