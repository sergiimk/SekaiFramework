/*========================================================
* attribute_impl.cpp
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "attribute_impl.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	attribute::attribute_impl::attribute_impl(EAttributeType type)
		: m_type(type)
	{ }

	//////////////////////////////////////////////////////////////////////////

	attribute::attribute_impl::~attribute_impl()
	{ }

	//////////////////////////////////////////////////////////////////////////

	attribute::attribute_impl* attribute::attribute_impl::clone() const
	{
		return new attribute_impl(m_type);
	}

	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// attribute
	//////////////////////////////////////////////////////////////////////////

	attribute::attribute(EAttributeType type)
		: m_impl(new attribute_impl(type))
	{ }

	//////////////////////////////////////////////////////////////////////////

	attribute::attribute(attribute_impl* impl)
		: m_impl(impl)
	{ }

	//////////////////////////////////////////////////////////////////////////

	attribute::~attribute()
	{
		delete m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	attribute* attribute::clone() const
	{
		return new attribute(m_impl->clone());
	}

	//////////////////////////////////////////////////////////////////////////

	void attribute::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace