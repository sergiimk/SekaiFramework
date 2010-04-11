/*========================================================
* construction_impl.cpp
* @author Sergey Mikhtonyuk
* @date 08 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "custom/construction_attribute.h"
#include "attribute_impl.h"
#include "types/function_type.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	struct construct_attribute::construct_impl : public attribute::attribute_impl
	{
		construct_impl(function_type* ctorType, void* ctorDeleg, TDtor d)
			: attribute_impl(ATTR_CONSTRUCTION)
			, m_ctorType(ctorType)
			, m_dtor(d)
		{
			memcpy(m_delegBuf, ctorDeleg, sizeof(m_delegBuf));
		}

		char m_delegBuf[member::_deleg_buf_size];
		function_type* m_ctorType;
		TDtor m_dtor;
	};

	//////////////////////////////////////////////////////////////////////////

	construct_attribute::construct_attribute(function_type *ctorType, void *ctorDeleg, TDtor d)
		: attribute(new construct_impl(ctorType, ctorDeleg, d))
	{
		m_impl = static_cast<construct_impl*>(attribute::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	construct_attribute::construct_attribute(construct_impl *impl)
		: attribute(impl)
		, m_impl(impl)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void* construct_attribute::create_instance(void** args) const
	{
		void* ret = 0;
		m_impl->m_ctorType->invoke((DelegateBase*)m_impl->m_delegBuf, args, &ret);
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	void construct_attribute::destroy_instance(void* v) const
	{
		m_impl->m_dtor(v);
	}

	//////////////////////////////////////////////////////////////////////////

	const function_type& construct_attribute::ctor_type() const
	{
		return *m_impl->m_ctorType;
	}	

	//////////////////////////////////////////////////////////////////////////

	construct_attribute* construct_attribute::clone() const
	{
		return new construct_attribute(new construct_impl(*m_impl));
	}

	//////////////////////////////////////////////////////////////////////////

	void construct_attribute::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////


	
} // namespace
