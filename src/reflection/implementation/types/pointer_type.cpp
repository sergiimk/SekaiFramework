/*========================================================
* pointer_type.cpp
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "types/pointer_type.h"
#include "type_impl.h"
#include "common/stack_string.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	struct pointer_type::pointer_type_impl : public type::type_impl
	{
		pointer_type_impl(type* pointee)
			: type_impl(T_POINTER, ARCH_POINTER, sizeof(void*))
			, m_pointee(pointee)
		{ }

		virtual void print_name() const
		{
			stack_string<> buf = m_pointee->name();
			*buf += '*';
			set_name(buf->c_str());
		}

		type* m_pointee;
	};

	//////////////////////////////////////////////////////////////////////////

	pointer_type::pointer_type(type* pointee)
		: type(new pointer_type_impl(pointee))
	{
		m_impl = static_cast<pointer_type_impl*>(type::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	type* pointer_type::pointee_type() const
	{
		return m_impl->m_pointee;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
