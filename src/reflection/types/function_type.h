/*========================================================
* function_type.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _FUNCTIONTYPE_H__
#define _FUNCTIONTYPE_H__

#include "types/type.h"
#include "delegate/DelegateBase.h"

namespace reflection
{
	/// Function type class
	/** @ingroup reflection */
	class REFLECTION_API function_type : public type
	{
	public:

		function_type(generic_invoker inv, bool isMethod, type* rt, type** arguments, int argc);

		/// Returns the result type
		type* return_type() const;

		/// Returns the number of arguments
		size_t argument_count() const;

		/// Returns the types of arguments
		type** argument_types() const;

		/// Make a function call (in case of methods first argument is class instance)
		void invoke(DelegateBase* deleg, void** args, void* result) const;

		virtual bool equal(const type* other) const;

	private:
		class function_type_impl;
		function_type_impl* m_impl;
	};

} // namespace

#endif //_FUNCTIONTYPE_H__
