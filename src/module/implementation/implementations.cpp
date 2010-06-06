/*========================================================
* Implementations.cpp
* @author Sergey Mikhtonyuk
* @date 22 April 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "implementations.h"

namespace module
{
	namespace detail
	{
		//////////////////////////////////////////////////////////////////////////

		std::error_code _Chain(void *pThis, void* pChain, guid const& riid, void **ppv)
		{
			_CHAINDATA* pcd = static_cast<_CHAINDATA*>(pChain);
			void* p = adjustptr(pThis, pcd->dwOffset);
			return _QueryInterface(p, pcd->pFunc(), riid, ppv);
		}

		//////////////////////////////////////////////////////////////////////////

		std::error_code _QueryInterface(void* pThis, const INTERFACE_MAP_ENTRY* pEntries, guid const& riid, void** ppvObject)
		{
			if(!ppvObject)
				return module_error::invalid_pointer;

			// To avoid ambiguity always cast first entry to IUnknown
			if (riid == uuid_of(IUnknown))
			{
				// first entry must be an offset
				assert( pEntries->locator == SF_OFFSET_ENTRY );
				*ppvObject = adjustptr(pThis, reinterpret_cast<size_t>(pEntries->OffChain));
				static_cast<IUnknown*>(*ppvObject)->AddRef();
				return std::error_code();
			}
			else
			{
				std::error_code err = module_error::no_interface;
				// until end
				while (pEntries->locator)
				{
					if (!pEntries->piid || (riid == *pEntries->piid))
					{
						if (pEntries->locator == SF_OFFSET_ENTRY)
						{
							*ppvObject = adjustptr(pThis, reinterpret_cast<size_t>(pEntries->OffChain));
							static_cast<IUnknown*>(*ppvObject)->AddRef();
							err = std::error_code();
							break;
						}
						else
						{
							err = pEntries->locator(pThis, pEntries->OffChain, riid, ppvObject);
							if (!err)
								break;
						}
					}
					++pEntries;
				}
				if (err)
					*ppvObject = 0;
				return err;
			}
		}

		//////////////////////////////////////////////////////////////////////////

	} // detail

} // namespace

//////////////////////////////////////////////////////////////////////////

bool implements_interface(module::IUnknown* pUnk, const module::guid& riid)
{
	/// \todo Improve

	if(pUnk)
	{
		void* dummy;
		if(!pUnk->QueryInterface(riid, &dummy))
		{
			// Compensate reference
			pUnk->Release();
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////

