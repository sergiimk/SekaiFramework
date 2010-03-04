/*========================================================
* AdapterFactoyContainer.h
* @author Sergey Mikhtonyuk
* @date 23 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ADAPTERFACTOYCONTAINER_H__
#define _ADAPTERFACTOYCONTAINER_H__

#include "IAdapterFactory.h"
#include <vector>
#include "platform/hash_map.h"
#include "stlutils.h"

/// Provides means to combine multiple adapter factories
/** @ingroup Extensions */
class AdapterFactoyContainer
{
public:
    /// Releases all factories
    ~AdapterFactoyContainer()
    {
        for(size_t i = 0; i != mFactories.size(); ++i)
            mFactories[i]->Release();
    }

    /// Adds factory to registry
    void AddFactory(IAdapterFactory *pFactory)
    {
        pFactory->AddRef();
        mFactories.push_back(pFactory);

        Module::GUID** ppGuid = pFactory->DestInterfaceList();
        while(*ppGuid)
        {
            /// \todo use multimap
            if(mAdatperFactoryMap.find(**ppGuid) == mAdatperFactoryMap.end())
                mAdatperFactoryMap.insert(std::make_pair(**ppGuid, pFactory));
            else
                assert(false);

            ++ppGuid;
        }
    }

    /// Creates adapter from first suitable factory
    Module::HResult CreateAdapter(Module::IUnknown* object, SF_RIID uid, void **ppAdapter)
    {
        TAdapterFactoryMap::const_iterator it =
                mAdatperFactoryMap.find(uid);

        if(it == mAdatperFactoryMap.end())
            return SF_E_NOINTERFACE;

        return it->second->GetAdapter(object, uid, ppAdapter);
    }

protected:
    typedef std::hash_map<Module::GUID, IAdapterFactory*, Module::guid_hash> TAdapterFactoryMap;

    TAdapterFactoryMap				mAdatperFactoryMap;

    std::vector<IAdapterFactory*>	mFactories;
};

#endif // _ADAPTERFACTOYCONTAINER_H__
