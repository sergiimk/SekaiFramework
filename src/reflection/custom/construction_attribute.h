/*========================================================
* construction_attribute.h
* @author Sergey Mikhtonyuk
* @date 08 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CONSTRUCTION_ATTRIBUTE_H__
#define _CONSTRUCTION_ATTRIBUTE_H__

#include "attribute.h"
#include "member.h"
#include "dynamic_delegates/delegate_dynamic.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	#include "generated/construction.inc"

	//////////////////////////////////////////////////////////////////////////

	/// Types tagged with this attribute support object creation and destruction
	/** @ingroup reflection */
	class REFLECTION_API construct_attribute : public attribute
	{
	public:

		typedef void(*TDtor)(void*);

		template<class Deleg>
		static construct_attribute* create(function_type* ctorType, const Deleg& ctorDeleg, TDtor d)
		{
			return new construct_attribute(ctorType, new Deleg(ctorDeleg), d);
		}

		construct_attribute(function_type* ctorType, delegates::delegate_dynamic_base* ctorDeleg, TDtor d);

		virtual void release();

		/// Creates type instance
		void* create_instance(void** args) const;
		
		/// Destroys type instance
		void destroy_instance(void* v) const;

		/// Returns reflected type of factory function
		const function_type& ctor_type() const;

	private:
		struct construct_impl;
	};

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_CONSTRUCTION_ATTRIBUTE_H__
