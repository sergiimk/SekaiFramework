/*========================================================
* builtin_type.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _BUILTINTYPE_H__
#define _BUILTINTYPE_H__

#include "types/type.h"

namespace reflection
{
	/// Built-in type class
	/** @ingroup reflection */
	template<class T>
	class builtin_type : public type
	{
	public:
		builtin_type();
	};

	//////////////////////////////////////////////////////////////////////////

	/// Built-in specialization for void type
	/** @ingroup reflection */
	template<>
	class REFLECTION_API builtin_type<void> : public type
	{
	public:
		builtin_type();
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif //_BUILTINTYPE_H__