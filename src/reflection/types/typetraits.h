/*========================================================
* typetraits.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _RTYPETRAITS_H__
#define _RTYPETRAITS_H__

#include "TypeTag.h"

namespace Reflection
{

	class Type;

	namespace detail
	{

		const char* get_type_name(ETypeTag tag);

		size_t type_get_name_safe(Type* t, char* buffer, size_t size);

		//////////////////////////////////////////////////////////////////////////
		template<class T> struct r_type_traits 
		{ 
			static const ETypeTag type_tag = RL_T_UNKNOWN;
		};

		//////////////////////////////////////////////////////////////////////////

		template<> struct r_type_traits<void> { static const ETypeTag type_tag = RL_T_VOID; };

		template<> struct r_type_traits<char> { static const ETypeTag type_tag = RL_T_CHAR; };
		template<> struct r_type_traits<unsigned char> { static const ETypeTag type_tag = RL_T_UCHAR; };

		template<> struct r_type_traits<short> { static const ETypeTag type_tag = RL_T_SHORT; };
		template<> struct r_type_traits<unsigned short> { static const ETypeTag type_tag = RL_T_USHORT; };

		template<> struct r_type_traits<int> { static const ETypeTag type_tag = RL_T_INT; };
		template<> struct r_type_traits<unsigned int> { static const ETypeTag type_tag = RL_T_UINT; };

		template<> struct r_type_traits<long> { static const ETypeTag type_tag = RL_T_LONG; };
		template<> struct r_type_traits<unsigned long> { static const ETypeTag type_tag = RL_T_ULONG; };

		template<> struct r_type_traits<long long> { static const ETypeTag type_tag = RL_T_LONGLONG; };
		template<> struct r_type_traits<unsigned long long> { static const ETypeTag type_tag = RL_T_ULONGLONG; };

		template<> struct r_type_traits<bool> { static const ETypeTag type_tag = RL_T_BOOL; };
		template<> struct r_type_traits<float> { static const ETypeTag type_tag = RL_T_FLOAT; };
		template<> struct r_type_traits<double> { static const ETypeTag type_tag = RL_T_DOUBLE; };

		//////////////////////////////////////////////////////////////////////////

		template<class T> struct r_is_user_type { enum { value = r_type_traits<T>::type_tag == RL_T_UNKNOWN }; };
		template<class T> struct r_is_user_type<T*> { enum { value = 0 }; };

		//////////////////////////////////////////////////////////////////////////

	} // detail

} // namespace

#endif // _RTYPETRAITS_H__
