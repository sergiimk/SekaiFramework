/*========================================================
* CBundle.cpp
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CBundle.h"
#include "CBundleContext.h"
#include "CSystemBundle.h"
#include "CServiceRegistration.h"
#include "EventDispatchers.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CBundle::CBundle()
		: m_id(0)
		, m_state(eBndlState_Installed)
		, m_systemBundle(0)
		, m_context(0)
		, m_activator(0)
	{ }

	//////////////////////////////////////////////////////////////////////////

	CBundle::~CBundle()
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CBundle::FinalConstruct(size_t id, const char* location, CSystemBundle* systemBundle)
	{
		m_systemBundle = systemBundle;
		m_id = id;
		m_location = location;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::Finalize()
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		m_systemBundle = 0;

		TServiceContainer().swap(m_publishedServices);
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::CheckValid() const
	{
		if(!m_systemBundle)
			throw "BundleException";
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CBundle::getBundleId()
	{
		THREAD_ANY();

		return m_id;
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundleContext> CBundle::getBundleContext()
	{
		THREAD_ANY();

		return m_context;
	}

	//////////////////////////////////////////////////////////////////////////

	EBundleState CBundle::getState()
	{
		THREAD_ANY();

		return m_state;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::setState(EBundleState state)
	{
		THREAD_ANY();

		m_state = state;
	}

	//////////////////////////////////////////////////////////////////////////

	const char* CBundle::getLocation()
	{
		THREAD_ANY();

		return m_location.c_str();
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::getRegisteredServices(IDynArray<com_ptr<IServiceReference> >& services)
	{
		for(size_t i = 0, size = m_publishedServices.size(); i != size; ++i)
			services.push_back(m_publishedServices[i]->getReference());
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::getServicesInUse(IDynArray<com_ptr<IServiceReference> >& services)
	{
		for(TServicesInUseContainer::const_iterator it = m_servicesInUse.begin(),
			end = m_servicesInUse.end();
			it != end; ++it)
		{
			if(it->second.getUseCount())
				services.push_back(it->first->getReference());
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::Start()
	{
		THREAD_ANY();

		CheckValid();

		if(m_state == eBndlState_Uninstalled)
			throw "IllegalStateException";

		if(m_state == eBndlState_Starting || m_state == eBndlState_Stopping)
			throw "Wait for finished";

		if(m_state == eBndlState_Active)
			return;

		if(m_state == eBndlState_Installed)
		{
			Resolve();
			if(m_state != eBndlState_Resolved)
				throw "BundleException";
		}

		PreStart();
		if(m_state != eBndlState_Starting)
			throw "BundleException";

		if(m_activator)
		{
			try
			{
				m_activator->Start(m_context);
			}
			catch(...)
			{
				PreStop();
				PostStop(false, false);
				throw "BundleException";
			}

			if(m_state == eBndlState_Uninstalled)
				throw "BundleException";
		}

		PostStart();
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::Stop()
	{
		THREAD_ANY();

		CheckValid();

		if(m_state == eBndlState_Uninstalled)
			throw "IllegalStateException";

		if(m_state == eBndlState_Starting || m_state == eBndlState_Stopping)
			throw "Wait for finished";

		if(m_state != eBndlState_Active)
			return;

		PreStop();

		bool errorStopping = false;
		if(m_activator)
		{
			try
			{
				m_activator->Stop(m_context);
			}
			catch(...)
			{
				errorStopping = true;
			}
		}

		PostStop(m_state == eBndlState_Uninstalled, errorStopping);

		if(m_state == eBndlState_Uninstalled)
			throw "BundleException";

		if(errorStopping)
			throw "BundleException";
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::Uninstall()
	{
		if(m_state == eBndlState_Uninstalled)
			throw "IllegalStateException";

		if(m_state == eBndlState_Active || m_state == eBndlState_Starting || m_state == eBndlState_Stopping)
			Stop();

		PostUninstall();
	}

	//////////////////////////////////////////////////////////////////////////

	CServiceRegistration* CBundle::RegisterService(const guid &riid, IUnknown *object)
	{
		THREAD_ANY();

		CheckValid();

		if(m_state == eBndlState_Resolved || m_state == eBndlState_Uninstalled)
			throw "IllegalStateException";

		// Check that service object actually implements specified interface
		if(!object || !implements_interface(object, riid) /* plus check for service factory */)
			throw "IllegalArgumentException";

		CServiceRegistry* registry = m_systemBundle->getServiceRegistry();
		CServiceRegistration* service = registry->RegisterService(riid, object, this);

		if(service)
			m_publishedServices.push_back(service);

		// Service events delivered synchronously!
		m_systemBundle->SendServiceEvent(service->getReference(), eSvcEvntT_Registered);

		return service;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::UnregisterService(CServiceRegistration *service)
	{
		THREAD_ANY();

		CheckValid();

		TServiceContainer::iterator it = std::find(m_publishedServices.begin(), m_publishedServices.end(), service);
		ASSERT_STRICT(it != m_publishedServices.end());
		m_publishedServices.erase(it);

		m_systemBundle->getServiceRegistry()->UnregisterService(service);

		// Service events delivered synchronously!
		m_systemBundle->SendServiceEvent(service->getReference(), eSvcEvntT_Unregistering);
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::UnregisterServices()
	{
		THREAD_ANY();

		CheckValid();

		while(!m_publishedServices.empty())
			m_publishedServices.back()->Unregister();
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IUnknown> CBundle::getService(CServiceReference *reference)
	{
		THREAD_ANY();

		CheckValid();

		if(!reference) return 0;

		CServiceRegistration* service = reference->getRegistration();
		if(!service) return 0;

		TServicesInUseContainer::iterator it = m_servicesInUse.find(service);
		if(it == m_servicesInUse.end())
		{
			it = m_servicesInUse.insert(std::make_pair(service, ServiceUsage(service, this))).first;
		}

		return it->second.getService();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CBundle::ungetService(CServiceReference* reference)
	{
		THREAD_ANY();

		CheckValid();

		if(!reference) return false;

		CServiceRegistration* service = reference->getRegistration();
		if(!service) return false;

		TServicesInUseContainer::iterator it = m_servicesInUse.find(service);
		if(it == m_servicesInUse.end()) return false;

		return it->second.ungetService();
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::ForceUngetService(CServiceRegistration* service)
	{
		THREAD_ANY();
		VERBOSE("WARNING [%s] Stale service reference", m_location.c_str());

		/// \todo verify
		CheckValid();

		TServicesInUseContainer::iterator it = m_servicesInUse.find(service);
		ASSERT_STRICT(it != m_servicesInUse.end());
		it->second.Reset();
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::ReleaseUsedServices()
	{
		THREAD_ANY();
		m_servicesInUse.clear();
	}

	//////////////////////////////////////////////////////////////////////////
	// Helpers
	//////////////////////////////////////////////////////////////////////////

	void CBundle::Resolve()
	{
		// Resolve dependencies
		m_state = eBndlState_Resolved;

		m_systemBundle->PostBundleEvent(this, eBndlEvntT_Resolved);
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::PreStart()
	{
		if(SF_FAILED( m_module.Init(m_location.c_str()) ))
			return;

		create_instance(&m_activator, m_module);
		create_instance_impl(&m_context);
		m_context->FinalConstruct(m_systemBundle, this);

		m_state = eBndlState_Starting;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::PostStart()
	{
		m_state = eBndlState_Active;
		m_systemBundle->PostBundleEvent(this, eBndlEvntT_Started);
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::PreStop()
	{
		m_state = eBndlState_Stopping;
		m_systemBundle->PostBundleEvent(this, eBndlEvntT_Stopping);
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::PostStop(bool wasUnregistered, bool activatorError)
	{
		UnregisterServices();
		ReleaseUsedServices();
		m_context->DropListeners();

		m_context->Finalize();
		safe_release(m_context);
		safe_release(m_activator);

		VERBOSE("[%s] Unloading module", m_location.c_str());
		m_module.Shutdown();

		if(!wasUnregistered)
		{
			m_state = eBndlState_Resolved;
			m_systemBundle->PostBundleEvent(this, eBndlEvntT_Stopped);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundle::PostUninstall()
	{
		m_state = eBndlState_Uninstalled;
		m_systemBundle->PostBundleEvent(this, eBndlEvntT_Uninstalled);
		m_systemBundle->getBundleRepository()->RemoveBundle(this);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
