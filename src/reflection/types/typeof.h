/*========================================================
* typeof.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPEOF_H__
#define _TYPEOF_H__

#include "reflection_fwd.h"
#include "types/type.h"
#include "types/builtin_type.h"
#include "types/pointer_type.h"
#include "types/reference_type.h"
#include "types/function_type.h"
#include "types/user_type.h"
#include "types/array_type.h"
#include "custom/custom.h"
#include "common/ifthenelse.h"
#include "common/typetraits.h"
#include "delegate/Delegate.h"

namespace reflection
{
	namespace detail
	{
		//////////////////////////////////////////////////////////////////////////

		// Deduces most specialized Type class for specific T
		template<class T>
		struct meta_type
		{
			typedef typename if_then_else<t_strip<T>::is_ptr, pointer_type,
				typename if_then_else<t_strip<T>::is_ref, reference_type,
				typename if_then_else<is_user_type<T>::value, user_type, builtin_type<T>
				>::value
				>::value
			>::value value;
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_builtin_ {
			static type* get() {
				static builtin_type<T> type;
				return &type; 
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_pointer_ {
			static type* get() {
				static pointer_type type(_type_of_<T>::get());
				return &type; 
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_reference_ {
			static type* get() {
				static reference_type type(_type_of_<T>::get());
				return &type;
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_user_ {
			static type* get() {
				static type_desc<T> desc;
				return desc.get_type(); 
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_ 
		{
			static type* get()
			{
				typedef typename if_then_else<t_strip<T>::is_ptr, _type_of_pointer_<t_strip<T>::noptr>,
					typename if_then_else<t_strip<T>::is_ref, _type_of_reference_<t_strip<T>::noref>,
					typename if_then_else<is_user_type<T>::value, _type_of_user_<T>, _type_of_builtin_<T>
					>::value
					>::value
				>::value tof;
				return tof::get();
			}
		};

		//////////////////////////////////////////////////////////////////////////
		
	} // namespace

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	typename detail::meta_type<T>::value* type_of()
	{
		return static_cast<detail::meta_type<T>::value*>(detail::_type_of_<t_strip<T>::nomod>::get());
	}

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	typename detail::meta_type<T>::value* type_of(const T&)
	{
		return type_of<T>();
	}

	//////////////////////////////////////////////////////////////////////////

	// Special version that deduces the size of an array
	template<class T, int S>
	array_type* type_of(T (&)[S])
	{
		static array_type at(type_of<T>(), S);
		return &at;
	}

	//////////////////////////////////////////////////////////////////////////

	#include "generated/invoke_generic.inc"
	#include "generated/function_typeof.inc"

	//////////////////////////////////////////////////////////////////////////

	#define CONST_METH
	#include "generated/method_typeof.inc"
	#undef CONST_METH
	#define CONST_METH const
	#include "generated/method_typeof.inc"
	#undef CONST_METH

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_TYPEOF_H__
