/*========================================================
* module.cpp
* @author Sergey Mikhtonyuk
* @date 02 May 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "module.h"
#include "platform/shared.h"

namespace module
{
	//////////////////////////////////////////////////////////////////////////
	// ModuleHandleImpl
	//////////////////////////////////////////////////////////////////////////

	struct ModuleHandle::ModuleHandleImpl
	{
		ModuleHandleImpl()
			: m_module(0)
			, m_initFunc(0)
			, m_shutdownFunc(0)
			, m_getModuleMap(0)
			, m_refCount(0)
		{ }

		ModuleHandleImpl(ModuleHandle::GET_MAP_FUNC getFunc)
			: m_module(0)
			, m_initFunc(0)
			, m_shutdownFunc(0)
			, m_getModuleMap(getFunc)
			, m_refCount(0)
		{
		}

		~ModuleHandleImpl()
		{
			ASSERT_STRICT(!m_refCount);
			Shutdown();
			if(m_module)
				Sekai_FreeLibrary(m_module);
		}

		void Shutdown()
		{
			// Shutting down module is legal when only one handle left
			ASSERT_SOFT(m_refCount <= 1);

			m_initFunc = 0;
			if(m_shutdownFunc)
			{
				m_shutdownFunc();
				m_shutdownFunc = 0;
			}
		}

		void*						m_module;
		ModuleHandle::INIT_FUNC		m_initFunc;
		ModuleHandle::SHUTDOWN_FUNC	m_shutdownFunc;
		ModuleHandle::GET_MAP_FUNC	m_getModuleMap;
		size_t						m_refCount;
	};


	//////////////////////////////////////////////////////////////////////////
	// ModuleHandle
	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::ModuleHandle()
		: m_impl(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::ModuleHandle(const char* moduleName)
		: m_impl(0)
	{
		Init(moduleName);
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::ModuleHandle(GET_MAP_FUNC mapFunc)
		: m_impl(new ModuleHandleImpl(mapFunc))
	{
		++m_impl->m_refCount;
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::ModuleHandle(const ModuleHandle& other)
		: m_impl(other.m_impl)
	{
		if(m_impl)
			++m_impl->m_refCount;
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::~ModuleHandle()
	{
		Release();
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle& ModuleHandle::operator =(const ModuleHandle &rhs)
	{
		if(this == &rhs)
			return *this;

		Release();
		if(rhs.m_impl)
		{
			m_impl = rhs.m_impl;
			++m_impl->m_refCount;
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	bool ModuleHandle::IsLoaded() const
	{
		return m_impl != 0;
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::iterator ModuleHandle::MapBegin() const
	{
		return iterator(m_impl->m_getModuleMap());
	}

	//////////////////////////////////////////////////////////////////////////

	ModuleHandle::iterator ModuleHandle::MapEnd() const
	{
		return iterator(0);
	}

	//////////////////////////////////////////////////////////////////////////

	HResult ModuleHandle::CreateInstance(SF_RIID clsid, SF_RIID riid, void** outObj) const
	{
		if(!IsLoaded()) 
			return SF_E_FAIL;

		HResult hr = SF_E_POINTER;
		if(outObj == 0) 
			return hr;

		detail::MODULE_MAP_ENTRY* ent = m_impl->m_getModuleMap();
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
		if(!IsLoaded()) 
			return SF_E_FAIL;

		HResult hr = SF_E_POINTER;
		if(outObj == 0) 
			return hr;

		detail::MODULE_MAP_ENTRY* ent = m_impl->m_getModuleMap();
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

	reflection::user_type* ModuleHandle::GetType(const guid &clsid) const
	{
		if(!IsLoaded()) 
			return 0;

		detail::MODULE_MAP_ENTRY* ent = m_impl->m_getModuleMap();
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
		Release();

		/// \todo Support unicode paths
		void* mod = Sekai_LoadLibrary(moduleName);
		if(!mod)
			return SF_E_FAIL;

		GET_MAP_FUNC gmf = (GET_MAP_FUNC)Sekai_GetProcAddress(mod, "GetModuleMap");
		if(!gmf)
		{
			Sekai_FreeLibrary(mod);
			return SF_E_FAIL;
		}

		INIT_FUNC inf = static_cast<INIT_FUNC>(Sekai_GetProcAddress(mod, "ModuleInit"));
		SHUTDOWN_FUNC snf = static_cast<SHUTDOWN_FUNC>(Sekai_GetProcAddress(mod, "ModuleShutdown"));

		if(inf)
			inf();

		m_impl = new ModuleHandleImpl();
		m_impl->m_module = mod;
		m_impl->m_getModuleMap = gmf;
		m_impl->m_initFunc = inf;
		m_impl->m_shutdownFunc = snf;
		++m_impl->m_refCount;

		return SF_S_OK;
	}

	//////////////////////////////////////////////////////////////////////////

	void ModuleHandle::Shutdown()
	{
		if(m_impl)
			m_impl->Shutdown();
	}

	//////////////////////////////////////////////////////////////////////////

	void ModuleHandle::Release()
	{
		if(m_impl)
		{
			if(!(--m_impl->m_refCount))
				delete m_impl;

			m_impl = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
