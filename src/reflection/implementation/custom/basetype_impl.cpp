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
		base_type_impl(user_type* base)
			: attribute_impl(ATTR_BASE_TYPE)
			, m_base(base)
		{ }

		virtual base_type_impl* clone() const
		{
			return new base_type_impl(m_base);
		}

		user_type* m_base;
	};

	//////////////////////////////////////////////////////////////////////////

	base_type::base_type(user_type* base)
		: attribute(new base_type_impl(base))
	{
		m_impl = static_cast<base_type_impl*>(attribute::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	base_type::base_type(base_type_impl* impl)
		: attribute(impl)
		, m_impl(impl)
	{ }

	//////////////////////////////////////////////////////////////////////////

	user_type* base_type::get_base() const
	{
		return m_impl->m_base;
	}

	//////////////////////////////////////////////////////////////////////////

	base_type* base_type::clone() const
	{
		return new base_type(new base_type_impl(*m_impl));
	}

	//////////////////////////////////////////////////////////////////////////

	void base_type::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
