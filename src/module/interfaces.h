/*========================================================
* Interfaces.h
* @author Sergey Mikhtonyuk
* @date 09 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
/** @defgroup module Module
*  module management library  */

#ifndef _INTERFACES_H__
#define _INTERFACES_H__

#include "guid.h"
#include "errors.h"

namespace module
{

	//////////////////////////////////////////////////////////////////////////

	//@{
	/** Helper interface definition macros */
	#ifdef COMPILER_MSC
		#define NOVTABLE _declspec(novtable)
	#else
		#define NOVTABLE
	#endif

	#define sf_interface struct NOVTABLE

	#define sf_uuid(str)															\
		static const module::guid& _get_uuid() {									\
			static const module::guid g = module::guid::guid_from_string(str);		\
			return g; }

	#define uuid_of(intrfc) intrfc::_get_uuid()
	//@}

	//////////////////////////////////////////////////////////////////////////

	/// IUnknown interface.
	/** Base interface for all implementations.
	 *  @ingroup module */
	sf_interface IUnknown
	{
		sf_uuid("91B5E844-05DB-434d-AAAA-9E0FE55C39D1")

		/// Dynamic casting method
		/** QueryInterface is used for dynamic casting and checking
		 *  if objects implements specific interface.
		 *
		 *  @param riid UUID of interface to cast to
		 *  @param ppObject pointer to returned interface pointer */
		virtual std::error_code QueryInterface(guid const& riid, void **ppObject) = 0;

		/// Increases reference counter
		virtual unsigned long AddRef() = 0;

		/// Decreases reference counter
		virtual unsigned long Release() = 0;
	};


	//////////////////////////////////////////////////////////////////////////


	/// IClassFactory interface.
	/** Base interface for creatable objects.
	 *  @ingroup module */
	sf_interface IClassFactory : public IUnknown
	{
		sf_uuid("C1621CCE-40F5-46c0-9397-088475E0B2FA")

		/// Creates instance and casts it to 'riid' interface
		/** @param riid			Unique identifier of class
		 *  @param ppvObject	Where to put class pointer */
		virtual std::error_code CreateInstance(guid const& riid, void **ppvObject) = 0;
	};

} // namespace

//////////////////////////////////////////////////////////////////////////

/// Performs the type casting
/** @ingroup module */
template<class I>
std::error_code interface_cast(module::IUnknown* pUnk, I** pp)
{
	return pUnk->QueryInterface(UUID_PPV(I, pp));
}

//////////////////////////////////////////////////////////////////////////

/// Checks that type implements specified interface
MODULE_API bool implements_interface(module::IUnknown* pUnk, const module::guid& riid);

//////////////////////////////////////////////////////////////////////////

/// Releases object with null check
/** @ingroup module */
inline void safe_release(module::IUnknown* pUnk)
{
	if(pUnk) pUnk->Release();
}

//////////////////////////////////////////////////////////////////////////

#endif // _INTERFACES_H__
