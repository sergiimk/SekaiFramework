/*========================================================
* IScriptFunction.h
* @author Sergey Mikhtonyuk
* @date 14 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ISCRIPTFUNCTION_H__
#define _ISCRIPTFUNCTION_H__

#include "module/interfaces.h"
#include "reflection/reflection_fwd.h"

namespace Script
{

	//////////////////////////////////////////////////////////////////////////

	/// Object bound to function defined in script
	/** @ingroup Script */
	sf_interface IScriptFunction : public module::IUnknown
	{
		sf_uuid("3b86f95d-fb47-4a4c-bf72-a6b84cd96fd8")
	
		/// Invokes the script function using packed arguments
		/** All errors during the call are translated to C++ exceptions
		 *  @param args Packed arguments in form of value-type pairs
		 *  @param nargs Number of arguments
		 *  @param ret Return value, can be 0 */
		virtual void Invoke(reflection::value_type_pair* args, size_t nargs, reflection::value_type_pair* ret) = 0;
	};

} // namespace

#endif // _ISCRIPTFUNCTION_H__