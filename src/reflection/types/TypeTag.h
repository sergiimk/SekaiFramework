/*========================================================
* typetag.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPETAG_H__
#define _TYPETAG_H__

#include "../reflection_fwd.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	/// Allow at least run-time type safety for built-in types
	/** @ingroup reflection */
	enum ETypeTag
	{
		T_EMPTY = 0, ///< Uninitialized

		// ARCH_BUILTIN
		T_VOID,
		T_CHAR,
		T_UCHAR,
		T_SHORT,
		T_USHORT,
		T_BOOL,
		T_INT,
		T_UINT,
		T_LONG,
		T_ULONG,
		T_LONGLONG,
		T_ULONGLONG,
		T_FLOAT,
		T_DOUBLE,

		// ARCH_POINTER
		T_POINTER,
		// ARCH_REFERENCE
		T_REFERENCE,

		// ARCH_ARRAY
		T_ARRAY,
		
		// ARCH_FUNCTION
		T_FUNCTION,	
		T_METHOD,

		// ARCH_USERDEFINED
		T_ENUM,		
		T_CLASS,
		T_STRUCT,

		T_UNKNOWN,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Describes the arch-type of the type
	/** @ingroup reflection */
	enum EArchType
	{
		ARCH_BUILTIN,
		ARCH_POINTER,
		ARCH_REFERENCE,
		ARCH_ARRAY,
		ARCH_USERDEFINED,
		ARCH_FUNCTION,
	};

	//////////////////////////////////////////////////////////////////////////

	namespace detail
	{

		//////////////////////////////////////////////////////////////////////////

		const char* get_type_name(ETypeTag tag);

		//////////////////////////////////////////////////////////////////////////
		
		template<class T> struct type_tag { static const ETypeTag tag = T_UNKNOWN; };

		template<> struct type_tag<void> { static const ETypeTag tag = T_VOID; };

		template<> struct type_tag<char> { static const ETypeTag tag = T_CHAR; };
		template<> struct type_tag<unsigned char> { static const ETypeTag tag = T_UCHAR; };

		template<> struct type_tag<short> { static const ETypeTag tag = T_SHORT; };
		template<> struct type_tag<unsigned short> { static const ETypeTag tag = T_USHORT; };

		template<> struct type_tag<int> { static const ETypeTag tag = T_INT; };
		template<> struct type_tag<unsigned int> { static const ETypeTag tag = T_UINT; };

		template<> struct type_tag<long> { static const ETypeTag tag = T_LONG; };
		template<> struct type_tag<unsigned long> { static const ETypeTag tag = T_ULONG; };

		template<> struct type_tag<long long> { static const ETypeTag tag = T_LONGLONG; };
		template<> struct type_tag<unsigned long long> { static const ETypeTag tag = T_ULONGLONG; };

		template<> struct type_tag<bool> { static const ETypeTag tag = T_BOOL; };
		template<> struct type_tag<float> { static const ETypeTag tag = T_FLOAT; };
		template<> struct type_tag<double> { static const ETypeTag tag = T_DOUBLE; };

		//////////////////////////////////////////////////////////////////////////

		template<class T> struct is_user_type { enum { value = type_tag<T>::tag == T_UNKNOWN }; };

		//////////////////////////////////////////////////////////////////////////

	} // namespace
	
} // namespace

#endif //_TYPETAG_H__
