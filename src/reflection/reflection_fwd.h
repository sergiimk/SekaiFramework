/*========================================================
* reflection_fwd.h
* @author Sergey Mikhtonyuk
* @date 23 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _REFLECTION_FWD_H__
#define _REFLECTION_FWD_H__

#include "platform/platform.h"

#if defined BUILD_SHARED && defined REFLECTION_EXPORTS
#	define REFLECTION_API SHARED_EXPORT
#else
#	define REFLECTION_API SHARED_IMPORT
#endif

namespace reflection
{

	class type;
	//class builtin_type;
	class pointer_type;
	class reference_type;
	class function_type;
	class user_type;
	class array_type;

	class member;
	class method_member;
	class method;
	class accessor_member;
	class accessor;
	class enumeration_member;

	class attribute;
	class base_type;
	
} // namespace

#endif // _REFLECTION_FWD_H__
