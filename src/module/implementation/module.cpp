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

		std::error_code Init(const char* moduleName)
		{
			/// \todo Support unicode paths
			m_module = Sekai_LoadLibrary(moduleName);
			if(!m_module)
				return std::make_error_code(std::errc::not_connected);

			m_getModuleMap = (GET_MAP_FUNC)Sekai_GetProcAddress(m_module, "GetModuleMap");
			if(!m_getModuleMap)
			{
				Sekai_FreeLibrary(m_module);
				return std::make_error_code(std::errc::not_connected);
			}

			m_initFunc = static_cast<INIT_FUNC>(Sekai_GetProcAddress(m_module, "ModuleInit"));
			m_shutdownFunc = static_cast<SHUTDOWN_FUNC>(Sekai_GetProcAddress(m_module, "ModuleShutdown"));

			if(m_initFunc)
			{
				std::error_code err;
				m_initFunc(&err);
				if(err)
				{
					Sekai_FreeLibrary(m_module);
					return err;
				}
			}

			return std::error_code();
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

	std::error_code ModuleHandle::CreateInstance(guid const& clsid, guid const& riid, void** outObj) const
	{
		if(!IsLoaded()) 
			return std::make_error_code(std::errc::not_connected);

		if(outObj == 0) 
			return module_error::invalid_pointer;

		std::error_code err = std::make_error_code(std::errc::address_not_available);

		detail::MODULE_MAP_ENTRY* ent = m_impl->m_getModuleMap();
		while(ent->pClsid)
		{
			if(clsid == *ent->pClsid)
			{
				if(!ent->pClassFactory)
				{
					err = ent->pCreateFactoryFn(UUID_PPV(IClassFactory, &ent->pClassFactory));
					if(err)
						return err;
				}
				err = ent->pClassFactory->CreateInstance(riid, outObj);
				return err;
			}
			++ent;
		}
		return err;
	}

	//////////////////////////////////////////////////////////////////////////

	std::error_code ModuleHandle::CreateInstance(guid const& riid, void** outObj) const
	{
		if(!IsLoaded()) 
			return std::make_error_code(std::errc::not_connected);

		if(outObj == 0) 
			return module_error::invalid_pointer;

		std::error_code err = std::make_error_code(std::errc::address_not_available);

		detail::MODULE_MAP_ENTRY* ent = m_impl->m_getModuleMap();
		while(ent->pClsid)
		{
			if(ent->pInterfaceId && riid == *ent->pInterfaceId)
			{
				if(!ent->pClassFactory)
				{
					err = ent->pCreateFactoryFn(UUID_PPV(IClassFactory, &ent->pClassFactory));
					if(err)
						return err;
				}
				err = ent->pClassFactory->CreateInstance(riid, outObj);
				return err;
			}
			++ent;
		}
		return err;
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

	std::error_code ModuleHandle::Init(const char* moduleName)
	{
		Release();

		
		ModuleHandleImpl* impl = new ModuleHandleImpl();
		std::error_code err = impl->Init(moduleName);
		
		if(!err)
		{
			m_impl = impl;
			++m_impl->m_refCount;
		}

		return std::error_code();
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
