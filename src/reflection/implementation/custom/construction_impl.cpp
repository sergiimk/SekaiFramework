/*========================================================
* construction_impl.cpp
* @author Sergey Mikhtonyuk
* @date 08 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "attribute_impl.h"
#include "custom/construction_attribute.h"

using namespace delegates;

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	struct construct_attribute::construct_impl : public attribute::attribute_impl
	{
		construct_impl(function_type* ctorType, delegate_dynamic_base* ctorDeleg, TDtor d)
			: attribute_impl(ATTR_CONSTRUCTION)
			, m_deleg(ctorDeleg)
			, m_ctorType(ctorType)
			, m_dtor(d)
		{ }

		~construct_impl()
		{
			delete m_deleg;
		}

		void* create_instance(void** args) const
		{
			void* ret = 0;
			m_deleg->invoke(args, &ret);
			return ret;
		}

		void destroy_instance(void* v) const
		{
			m_dtor(v);
		}

		delegate_dynamic_base* m_deleg;
		function_type* m_ctorType;
		TDtor m_dtor;
	};

	//////////////////////////////////////////////////////////////////////////

	construct_attribute::construct_attribute(function_type *ctorType, delegate_dynamic_base *ctorDeleg, TDtor d)
		: attribute(new construct_impl(ctorType, ctorDeleg, d))
	{ }

	//////////////////////////////////////////////////////////////////////////

	void* construct_attribute::create_instance(void** args) const
	{
		return static_cast<construct_impl*>(m_impl)->create_instance(args);
	}

	//////////////////////////////////////////////////////////////////////////

	void construct_attribute::destroy_instance(void* v) const
	{
		static_cast<construct_impl*>(m_impl)->destroy_instance(v);
	}

	//////////////////////////////////////////////////////////////////////////

	const function_type& construct_attribute::ctor_type() const
	{
		return *static_cast<construct_impl*>(m_impl)->m_ctorType;
	}

	//////////////////////////////////////////////////////////////////////////

	void construct_attribute::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////


	
} // namespace
