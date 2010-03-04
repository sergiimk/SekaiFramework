/*========================================================
* typeof.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPEOF_H__
#define _TYPEOF_H__

#include "module/module.h"
#include "Type.h"
#include "TypeTag.h"
#include "typetraits.h"
#include "../descriptors/typedesc.h"

#include "BuiltInType.h"
#include "ArrayType.h"
#include "PointerType.h"
#include "UserType.h"
#include "FunctionType.h"

#include "../delegate/Delegate.h"

#include "common/ifthenelse.h"
#include "common/typetraits.h"


namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	namespace detail
	{

		template<class T>
		struct _type_of_builtin_ {
		static Type* get() {
			static BuiltInType<T> type;
			return &type; }
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_user_ {
			static Type* get() {
				static type_desc<T> cd;
				static UserType ut;
				ut._init(&cd);
				return ut.Tag() != RL_T_UNKNOWN ? &ut : 0; }
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_ {
			static Type* get()
			{
				return Utils::IfThenElse<	r_is_user_type<T>::value,
											_type_of_user_<T>,
											_type_of_builtin_<T> >::value::get();
			}
		};

		//////////////////////////////////////////////////////////////////////////

		template<class PT>
		struct _type_of_pointer_ {
			static Type* get() { static PointerType pt(_type_of_<PT>::get());
				return &pt; }
		};

		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct _type_of_<T*> {
			static Type* get() { return _type_of_pointer_<T>::get(); }
		};

	} // detail

	//////////////////////////////////////////////////////////////////////////

	/// Returns reflection of type specified as template parameter
	/** @ingroup Reflection */
	template<class T>
	Type* type_of()
	{
		return detail::_type_of_<typename Utils::TStripType<T>::noref>::get();
	}

	/// Returns reflection of type passed as parameter
	/** @ingroup Reflection */
	template<class T>
	Type* type_of(const T&)
	{
		return detail::_type_of_<T>::get();
	}

	/// Special version that deduces the size of an array
	/** @ingroup Reflection */
	template<class T, int S>
	Type* type_of(T (&)[S])
	{
		static ArrayType at(type_of<typename Utils::TStripType<T>::noref>(), S);
		return &at;
	}

	/// Special version for class fields
	/** @ingroup Reflection */
	template<class T, class C>
	Type* type_of(T C::*)
	{
		return type_of<typename Utils::TStripType<T>::noref>();
	}

	/// Helper function to import the reflection from other module
	/** @ingroup Reflection */
	inline Type* type_of(SF_RIID clsid, Module::ModuleHandle module)
	{
		return module.GetType(clsid);
	}

	//////////////////////////////////////////////////////////////////////////

	#include "../generated/invokers.inc"
	#include "../generated/invcreators.inc"

	//////////////////////////////////////////////////////////////////////////

	#define CONST_METH
	#include "../generated/invcreators_method.inc"
	#undef CONST_METH
	#define CONST_METH const
	#include "../generated/invcreators_method.inc"
	#undef CONST_METH

	#include "../generated/makedeleg.inc"

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _TYPEOF_H__
