/*========================================================
* Module.cpp
* @author Sergey Mikhtonyuk
* @date 02 May 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "module.h"

#ifdef OS_WINDOWS
#include <Windows.h>
void* Sekai_LoadLibrary(const char* name)
{
	return LoadLibraryExA(name, 0, 0);
}
void* Sekai_GetProcAddress(void* library, const char* name)
{
	return GetProcAddress((HMODULE)library, name);
}
void Sekai_FreeLibrary(void* library)
{
	FreeLibrary((HMODULE)library);
}
#else
#include <dlfcn.h>
void* Sekai_LoadLibrary(const char* name)
{
	return dlopen(name, RTLD_NOW);
}
void* Sekai_GetProcAddress(void* library, const char* name)
{
	return dlsym(library, name);
}
void* Sekai_FreeLibrary(void* library)
{
	return (void*)dlclose(library);
}
#endif

namespace Module
{
	//////////////////////////////////////////////////////////////////////////
	// ModuleHandle
	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::ModuleHandle()
		: mModule(0)
		, mInitFunc(0)
		, mShutdownFunc(0)
		, mGetModuleMap(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::ModuleHandle(const char* moduleName)
		: mModule(0)
		, mInitFunc(0)
		, mShutdownFunc(0)
		, mGetModuleMap(0)
	{
		Init(moduleName);
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::ModuleHandle(GET_MAP_FUNC mapFunc)
		: mModule(0)
		, mInitFunc(0)
		, mShutdownFunc(0)
		, mGetModuleMap(mapFunc)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::ModuleHandle(const ModuleHandle& other)
		: mModule(0)
		, mInitFunc(0)
		, mShutdownFunc(0)
		, mGetModuleMap(other.mGetModuleMap)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::~ModuleHandle()
	{
		Shutdown();
		Unload();
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle& ModuleHandle::operator =(const Module::ModuleHandle &rhs)
	{
		Shutdown();
		mGetModuleMap = rhs.mGetModuleMap;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	bool ModuleHandle::IsLoaded() const
	{
		return mGetModuleMap != 0;
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle ModuleHandle::GetWeakHandle() const
	{
		return ModuleHandle(mGetModuleMap);
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::iterator ModuleHandle::MapBegin() const
	{
		return iterator(mGetModuleMap());
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::iterator ModuleHandle::MapEnd() const
	{
		return iterator(0);
	}

	//////////////////////////////////////////////////////////////////////////

	HResult ModuleHandle::CreateInstance(SF_RIID clsid, SF_RIID riid, void** outObj) const
	{
		if(!IsLoaded()) return SF_E_FAIL;

		HResult hr = SF_E_POINTER;
		if(outObj == 0) return hr;

		detail::MODULE_MAP_ENTRY* ent = mGetModuleMap();
		while(ent->pClsid)
		{
			if(clsid == *ent->pClsid)
			{
				if(!ent->pClassFactory)
				{
					hr = ent->pCreateFactoryFn(UUID_PPV(IClassFactory, &ent->pClassFactory));
					if(SF_FAILED(hr))
						return hr;
				}
				hr = ent->pClassFactory->CreateInstance(riid, outObj);
				return hr;
			}
			++ent;
		}
		return SF_E_FAIL;
	}

	//////////////////////////////////////////////////////////////////////////

	HResult ModuleHandle::CreateInstance(SF_RIID riid, void** outObj) const
	{
		if(!IsLoaded()) return SF_E_FAIL;

		HResult hr = SF_E_POINTER;
		if(outObj == 0) return hr;

		detail::MODULE_MAP_ENTRY* ent = mGetModuleMap();
		while(ent->pClsid)
		{
			if(ent->pInterfaceId && riid == *ent->pInterfaceId)
			{
				if(!ent->pClassFactory)
				{
					hr = ent->pCreateFactoryFn(UUID_PPV(IClassFactory, &ent->pClassFactory));
					if(SF_FAILED(hr))
						return hr;
				}
				hr = ent->pClassFactory->CreateInstance(riid, outObj);
				return hr;
			}
			++ent;
		}
		return SF_E_FAIL;
	}

	//////////////////////////////////////////////////////////////////////////

	Reflection::Type* ModuleHandle::GetType(const Module::GUID &clsid) const
	{
		if(!IsLoaded()) return 0;

		detail::MODULE_MAP_ENTRY* ent = mGetModuleMap();
		while(ent->pClsid)
		{
			if(clsid == *ent->pClsid && ent->pTypeOf)
			{
				return ent->pTypeOf();
			}
			++ent;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	HResult ModuleHandle::Init(const char* moduleName)
	{
		/// \todo Support unicode paths
		mModule = Sekai_LoadLibrary(moduleName);
		if(!mModule) return SF_E_FAIL;

		mGetModuleMap = (GET_MAP_FUNC)Sekai_GetProcAddress(mModule, "GetModuleMap");
		if(!mGetModuleMap)
		{
			Unload();
			return SF_E_FAIL;
		}

		mInitFunc = (INIT_FUNC)Sekai_GetProcAddress(mModule, "ModuleInit");
		mShutdownFunc = (SHUTDOWN_FUNC)Sekai_GetProcAddress(mModule, "ModuleShutdown");

		if(mInitFunc)
			mInitFunc();

		return SF_S_OK;
	}

	//////////////////////////////////////////////////////////////////////////

	void ModuleHandle::Shutdown()
	{
		mInitFunc = 0;
		if(mShutdownFunc)
		{
			mShutdownFunc();
			mShutdownFunc = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void ModuleHandle::Unload()
	{
		if(mModule)
		{
			Sekai_FreeLibrary(mModule);
			mModule = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
