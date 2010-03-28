/*========================================================
* basetype_impl.cpp
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "custom/basetype_attribute.h"
#include "attribute_impl.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	struct base_type::base_type_impl : public attribute::attribute_impl
	{
		base_type_impl(type* base)
			: attribute_impl(ATTR_BASE_TYPE)
			, m_base(base)
		{ }

		type* m_base;
	};

	//////////////////////////////////////////////////////////////////////////

	base_type::base_type(type* base)
		: attribute(new base_type_impl(base))
	{
		m_impl = static_cast<base_type_impl*>(attribute::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	type* base_type::get_base() const
	{
		return m_impl->m_base;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
