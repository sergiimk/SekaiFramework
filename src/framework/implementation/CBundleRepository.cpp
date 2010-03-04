/*========================================================
* CBundleRegistry.cpp
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CBundleRepository.h"
#include "CSystemBundle.h"
#include "Listeners.h"
#include "CEventServer.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CBundleRepository::CBundleRepository()
		: m_lastBundleId(0)
		, m_systemBundle(0)
	{ }

	void CBundleRepository::Init(CSystemBundle* systemBundle)
	{
		THREAD_LAUNCHER();

		m_systemBundle = systemBundle;

		write_lock l(m_lock);
		m_bundlesById.insert(std::make_pair(0, systemBundle));
		m_bundlesByLocation.insert(std::make_pair(systemBundle->getLocation(), systemBundle));
	}

	//////////////////////////////////////////////////////////////////////////

	CBundleRepository::~CBundleRepository()
	{
		THREAD_LAUNCHER();
		write_lock l(m_lock);

		for(TBundleById::const_iterator it = m_bundlesById.begin(), end = m_bundlesById.end();
			it != end; ++it)
		{
			if(it->first != 0)
			{
				it->second->Finalize();
				it->second->Release();
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundle> CBundleRepository::CreateNewBundle(const char* location)
	{
		THREAD_ANY();

		CBundle* bundle;
		create_instance_impl(&bundle);

		bundle->FinalConstruct(++m_lastBundleId, location, m_systemBundle);

		{
			write_lock l(m_lock);
			m_bundlesById.insert(std::make_pair(m_lastBundleId, bundle));
			m_bundlesByLocation.insert(std::make_pair(location, bundle));
			return bundle;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundle> CBundleRepository::getBundle(size_t bundleId) const
	{
		THREAD_ANY();

		read_lock l(m_lock);
		TBundleById::const_iterator it = m_bundlesById.find(bundleId);
		return it != m_bundlesById.end() ? it->second : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundle> CBundleRepository::getBundle(const char* location) const
	{
		THREAD_ANY();

		read_lock l(m_lock);
		TBundleByLocation::const_iterator it = m_bundlesByLocation.find(location);
		return it != m_bundlesByLocation.end() ? it->second : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleRepository::getBundles(IDynArray<com_ptr<IBundle> >& bundles) const
	{
		THREAD_ANY();
		read_lock l(m_lock);

		for(TBundleById::const_iterator it = m_bundlesById.begin(), end = m_bundlesById.end();
			it != end; ++it)
		{
			bundles.push_back(it->second);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleRepository::RemoveBundle(IBundle* bundle)
	{
		THREAD_ANY();
		write_lock l(m_lock);

		m_bundlesById.erase(bundle->getBundleId());
		m_bundlesByLocation.erase(bundle->getLocation());

		static_cast<CBundle*>(bundle)->Finalize();
		bundle->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	const CEventListenerQueue& CBundleRepository::getListeners() const
	{
		THREAD_ANY();

		return m_listeners;
	}

	//////////////////////////////////////////////////////////////////////////

	const CEventListenerQueue& CBundleRepository::getSyncListeners() const
	{
		THREAD_ANY();

		return m_syncListeners;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleRepository::AddListener(IBundleListener *listener)
	{
		THREAD_FRAMEWORK();

		if(implements_interface(listener, uuid_of(ISynchronousBundleListener)))
			m_syncListeners.AddListener(listener);
		else
			m_listeners.AddListener(listener);
	}

	//////////////////////////////////////////////////////////////////////////

	void CBundleRepository::RemoveListener(IBundleListener* listener)
	{
		THREAD_FRAMEWORK();

		if(implements_interface(listener, uuid_of(ISynchronousBundleListener)))
			m_syncListeners.RemoveListener(listener);
		else
			m_listeners.RemoveListener(listener);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
