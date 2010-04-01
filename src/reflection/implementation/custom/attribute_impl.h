/*========================================================
* attribute_impl.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ATTRIBUTE_IMPL_H__
#define _ATTRIBUTE_IMPL_H__

#include "custom/attribute.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	class attribute::attribute_impl
	{
	public:

		attribute_impl(EAttributeType type);

		virtual ~attribute_impl();

		EAttributeType get_type() const;

		virtual attribute_impl* clone() const = 0;

	private:
		EAttributeType m_type;
	};

	//////////////////////////////////////////////////////////////////////////

	inline EAttributeType attribute::attribute_impl::get_type() const
	{
		return m_type;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_ATTRIBUTE_IMPL_H__

