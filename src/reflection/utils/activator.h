/*========================================================
* activator.h
* @author Sergey Mikhtonyuk
* @date 11 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ACTIVATOR_H__
#define _ACTIVATOR_H__

#include "reflection_fwd.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Helper class for creating instances of objects through reflection
	/** @ingroup reflection */
	class REFLECTION_API activator
	{
	public:
		/// Searches construction attribute in type t with suitable argument set
		static const construct_attribute* find_ctor(const type& t, type* argv[] = 0, size_t argc = 0);

		/// Searches for suitable constructor and creates instance
		static void* create_instance(const type& t, value_type_pair argv[] = 0, size_t argc = 0);

		/// Searches for first destructor and destroys the instance
		static void destroy_instance(const type& t, void* inst);

	private:
		static bool suitable_params(const function_type& ft, type* argv[], size_t argc);
	};

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_ACTIVATOR_H__
