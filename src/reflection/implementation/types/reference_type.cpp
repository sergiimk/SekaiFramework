/*========================================================
* reference_type.cpp
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "types/reference_type.h"
#include "type_impl.h"
#include "common/stack_string.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	struct reference_type::reference_type_impl : public type::type_impl
	{
		reference_type_impl(type* referenced)
			: type_impl(T_POINTER, ARCH_POINTER, sizeof(void*))
			, m_referenced(referenced)
		{ }

		virtual void print_name() const
		{
			stack_string<> buf = m_referenced->name();
			*buf += '*';
			set_name(buf->c_str());
		}

		type* m_referenced;
	};

	//////////////////////////////////////////////////////////////////////////

	reference_type::reference_type(type* referenced)
		: type(new reference_type_impl(referenced))
	{
		m_impl = static_cast<reference_type_impl*>(type::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	type* reference_type::referenced_type() const
	{
		return m_impl->m_referenced;
	}

	//////////////////////////////////////////////////////////////////////////

	bool reference_type::equal(const type* other) const
	{
		if(!type::equal(other))
			return false;
		const reference_type* rt = static_cast<const reference_type*>(other);
		return referenced_type()->equal(rt->referenced_type());
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
