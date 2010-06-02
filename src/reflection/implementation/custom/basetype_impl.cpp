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
		base_type_impl(user_type* base, size_t this_offset)
			: attribute_impl(ATTR_BASE_TYPE)
			, m_base(base)
			, m_offser(this_offset)
		{ }

		user_type* m_base;
		size_t m_offser;
	};

	//////////////////////////////////////////////////////////////////////////

	base_type::base_type(user_type* base, size_t this_offset)
		: attribute(new base_type_impl(base, this_offset))
	{ }

	//////////////////////////////////////////////////////////////////////////

	const user_type& base_type::get_base() const
	{
		return *static_cast<base_type_impl*>(m_impl)->m_base;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t base_type::get_offset() const
	{
		return static_cast<base_type_impl*>(m_impl)->m_offser;
	}

	//////////////////////////////////////////////////////////////////////////

	void base_type::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
