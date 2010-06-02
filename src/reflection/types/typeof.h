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
#include "common/ifthenelse.h"
#include "common/typetraits.h"

namespace reflection
{
	namespace detail
	{
		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct type_desc
		{			
			user_type* get_type() { return 0; }
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_builtin_ {
			typedef builtin_type<T>* ret_t;
			static ret_t get() {
				static builtin_type<T> type;
				return &type;
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_pointer_ {
			typedef pointer_type* ret_t;
			static ret_t get() {
				static pointer_type type(_type_of_<T>::get());
				return &type; 
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_reference_ {
			typedef reference_type* ret_t;
			static ret_t get() {
				static reference_type type(_type_of_<T>::get());
				return &type;
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_user_ {
			typedef user_type* ret_t;
			static ret_t get() {
				static type_desc<T> desc;
				return desc.get_type(); 
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_ 
		{
			typedef typename t_strip<T>::nomod pure;

			typedef typename if_then_else<t_strip<T>::is_ptr, _type_of_pointer_<typename t_strip<pure>::noptr>,
					typename if_then_else<t_strip<T>::is_ref, _type_of_reference_<typename t_strip<pure>::noref>,
					typename if_then_else<is_user_type<T>::value, _type_of_user_<pure>, _type_of_builtin_<pure>
					>::value
					>::value
				>::value type_function;

			typedef typename type_function::ret_t return_type;

			static return_type get()
			{
				return type_function::get();
			}
		};

		//////////////////////////////////////////////////////////////////////////
		
	} // namespace

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	typename detail::_type_of_<T>::return_type type_of()
	{
		return detail::_type_of_<T>::get();
	}

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	typename detail::_type_of_<T>::return_type type_of(const T&)
	{
		return detail::_type_of_<T>::get();
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
