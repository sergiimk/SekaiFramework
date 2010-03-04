/*========================================================
* TypeTag.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPETAG_H__
#define _TYPETAG_H__

#include <platform/platform.h>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Allow at least run-time type safety for built-in types
	/** @ingroup Reflection */
	enum ETypeTag
	{
		RL_T_EMPTY = 0, ///< Uninitialized

		//RL_ARCH_BUILTIN
		RL_T_VOID,
		RL_T_CHAR,
		RL_T_UCHAR,
		RL_T_SHORT,
		RL_T_USHORT,
		RL_T_BOOL,
		RL_T_INT,
		RL_T_UINT,
		RL_T_LONG,
		RL_T_ULONG,
		RL_T_LONGLONG,
		RL_T_ULONGLONG,
		RL_T_FLOAT,
		RL_T_DOUBLE,

		// Special
		RL_T_POINTER,	// RL_ARCH_POINTER
		RL_T_ARRAY,		// RL_ARCH_ARRAY
		RL_T_FUNCTION,	// RL_ARCH_FUNCTION
		RL_T_METHOD,
		RL_T_ENUM,		// RL_ARCH_USERDEFINED
		RL_T_CLASS,
		RL_T_STRUCT,

		RL_T_UNKNOWN,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Describes the arch-type of the type
	/** @ingroup Reflection */
	enum EArchType
	{
		RL_ARCH_BUILTIN,
		RL_ARCH_POINTER,
		RL_ARCH_ARRAY,
		RL_ARCH_USERDEFINED,
		RL_ARCH_FUNCTION,
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _TYPETAG_H__
