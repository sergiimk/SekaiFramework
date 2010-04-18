/*========================================================
* CBundleContext.cpp
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CBundleContext.h"
#include "CBundle.h"
#include "CSystemBundle.h"
#include "CServiceReference.h"
#include "CServiceRegistration.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CBundleContext::CBundleContext()
		: m_systemBundle(0)
		, m_bundle(0)
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::FinalConstruct(CSystemBundle* systemBundle, CBundle* bundle)
	{
		m_bundle = bundle;
		m_systemBundle = systemBundle;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::DropListeners()
	{
		THREAD_ANY();

		while(!m_frameworkListeners.empty())
			RemoveFrameworkListener(m_frameworkListeners.back());

		while(!m_bundleListeners.empty())
			RemoveBundleListener(m_bundleListeners.back());

		while(!m_serviceListeners.empty())
			RemoveServiceListener(m_serviceListeners.back());
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::Finalize()
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		m_bundle = 0;
		m_systemBundle = 0;

		// swap trick to free memory in case of stale references
		TBndlLnr().swap(m_bundleListeners);
		TSvcLnr().swap(m_serviceListeners);
		TFwkLnr().swap(m_frameworkListeners);
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::CheckValid() const
	{
		if(!m_bundle || !m_systemBundle)
			throw "BundleException";
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundle> CBundleContext::getBundle()
	{
		THREAD_ANY();

		return m_bundle;
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundle> CBundleContext::getBundle(size_t id)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		CheckValid();

		return m_systemBundle->getBundleRepository()->getBundle(id);
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::getBundles(IDynArray<com_ptr<IBundle> >& bundles)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		CheckValid();

		return m_systemBundle->getBundleRepository()->getBundles(bundles);
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundle> CBundleContext::InstallBundle(const char* location)
	{
		THREAD_ANY();

		// Cache pointer and protect fwk from being deleted mid call
		com_ptr_impl<CSystemBundle> sys_bundle(m_systemBundle);

		CheckValid();

		CBundleRepository* repo = sys_bundle->getBundleRepository();
		com_ptr<IBundle> bndl = repo->getBundle(location);
		if(!bndl)
		{
			bndl = repo->CreateNewBundle(location);
			sys_bundle->PostBundleEvent(bndl, eBndlEvntT_Installed);
		}

		return bndl;
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IServiceRegistration> CBundleContext::RegisterService(const module::guid &riid, module::IUnknown *object)
	{
		THREAD_ANY();

		// Cache and protect bundle
		com_ptr_impl<CBundle> bndl(m_bundle);

		CheckValid();

		// Deadlock warning, can't use locks because register notifies listeners
		return bndl->RegisterService(riid, object);
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IServiceReference> CBundleContext::getServiceReference(SF_RIID riid)
	{
		THREAD_ANY();

		com_ptr_impl<CSystemBundle> sys_bundle(m_systemBundle);
		CheckValid();

		return m_systemBundle->getServiceRegistry()->getServiceReference(riid);
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IUnknown> CBundleContext::getService(IServiceReference *reference)
	{
		THREAD_ANY();

		com_ptr_impl<CBundle> bndl(m_bundle);
		CheckValid();

		return bndl->getService(static_cast<CServiceReference*>(reference));
	}

	//////////////////////////////////////////////////////////////////////////

	bool CBundleContext::ungetService(Framework::IServiceReference *reference)
	{
		THREAD_ANY();

		com_ptr_impl<CBundle> bndl(m_bundle);
		CheckValid();

		return bndl->ungetService(static_cast<CServiceReference*>(reference));
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::AddBundleListener(IBundleListener *listener)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		CheckValid();

		ASSERT_SOFT(listener);
		if(listener)
		{
			m_bundleListeners.push_back(listener);
			m_systemBundle->getBundleRepository()->AddListener(listener);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::RemoveBundleListener(IBundleListener *listener)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		CheckValid();

		ASSERT_SOFT(listener);
		if(listener)
		{
			TBndlLnr::iterator it = std::find(m_bundleListeners.begin(), m_bundleListeners.end(), listener);
			if(it != m_bundleListeners.end()) m_bundleListeners.erase(it);
			m_systemBundle->getBundleRepository()->RemoveListener(listener);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::AddFrameworkListener(IFrameworkListener *listener)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		CheckValid();

		ASSERT_SOFT(listener);
		if(listener)
		{
			m_frameworkListeners.push_back(listener);
			m_systemBundle->AddListener(listener);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::RemoveFrameworkListener(IFrameworkListener *listener)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		CheckValid();

		ASSERT_SOFT(listener);
		if(listener)
		{
			TFwkLnr::iterator it = std::find(m_frameworkListeners.begin(), m_frameworkListeners.end(), listener);
			if(it != m_frameworkListeners.end()) m_frameworkListeners.erase(it);
			m_systemBundle->RemoveListener(listener);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::AddServiceListener(IServiceListener *listener)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		CheckValid();

		ASSERT_SOFT(listener);
		if(listener)
		{
			m_serviceListeners.push_back(listener);
			m_systemBundle->getServiceRegistry()->AddListener(listener);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleContext::RemoveServiceListener(IServiceListener *listener)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		CheckValid();

		ASSERT_SOFT(listener);
		if(listener)
		{
			TSvcLnr::iterator it = std::find(m_serviceListeners.begin(), m_serviceListeners.end(), listener);
			if(it != m_serviceListeners.end()) m_serviceListeners.erase(it);
			m_systemBundle->getServiceRegistry()->RemoveListener(listener);
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
