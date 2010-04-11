/*========================================================
* array_type.cpp
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "types/array_type.h"
#include "type_impl.h"
#include "common/stack_string.h"
#include <stdio.h>

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	struct array_type::array_type_impl : public type::type_impl
	{
		array_type_impl(type* elem_type, size_t length)
			: type_impl(T_ARRAY, ARCH_ARRAY, elem_type ? elem_type->size() * length : 0)
			, m_elem_t(elem_type)
			, m_length(length)
		{ }

		virtual void print_name() const
		{
			stack_string<> buf = m_elem_t->name();
			*buf += " [";
			char ib[64];
			sprintf(ib, "%d", m_length);
			*buf += ib;
			*buf += ']';
			set_name(buf->c_str());
		}

		type* m_elem_t;
		size_t m_length;
	};

	//////////////////////////////////////////////////////////////////////////

	array_type::array_type(type* elem_type, size_t length)
		: type(new array_type_impl(elem_type, length))
	{
		m_impl = static_cast<array_type_impl*>(type::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	type* array_type::element_type() const
	{
		return m_impl->m_elem_t;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t array_type::length() const
	{
		return m_impl->m_length;
	}

	//////////////////////////////////////////////////////////////////////////

	bool array_type::equal(const type* other) const
	{
		if(!type::equal(other)) 
			return false;
		const array_type* at = static_cast<const array_type*>(other);
		return m_impl->m_elem_t->equal(at->m_impl->m_elem_t)
			&& m_impl->m_length == at->m_impl->m_length;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
