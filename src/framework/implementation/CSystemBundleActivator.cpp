/*========================================================
* CSystemBundleActivator.cpp
* @author Sergey Mikhtonyuk
* @date 07 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CSystemBundleActivator.h"
#include "CSystemBundle.h"
#include "IBundleContext.h"
#include "filesystem/FileSystem.h"
#include "BundleRegParser.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CSystemBundleActivator::CSystemBundleActivator()
		: m_context(0)
		, m_systemBundle(0)
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::FinalConstruct(CSystemBundle* systemBundle)
	{
		m_systemBundle = systemBundle;
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::Start(IBundleContext* context)
	{
		VERBOSE("[SysBndleActivator] %s", __FUNCTION__);

		m_context = context;
		m_context->AddServiceListener(this);

		// All installed bundles must be started in accordance with each bundle's
		// persistent autostart setting. This means some bundles will not be started,
		// some will be started with eager activation and some will be started with their
		// declared activation policy. If this Framework implements the optional Start Level
		// Service Specification, then the start level of this Framework is moved to the start
		// level specified by the beginning start level framework property, as described in the
		// Start Level Service Specification. If this framework property is not specified, then the
		// start level of this Framework is moved to start level one (1). Any exceptions that occur
		// during bundle starting must be wrapped in a BundleException and then published as a framework
		// event of type FrameworkEvent.ERROR

		LoadCoreBundles();
		LoadInstalledBundles();
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::Stop(IBundleContext* context)
	{
		VERBOSE("[SysBndleActivator] %s", __FUNCTION__);

		// This Framework's state is set to Bundle.STOPPING.
		//
		// All installed bundles must be stopped without changing each bundle's
		// persistent autostart setting. If this Framework implements the optional
		// Start Level Service Specification, then the start level of this Framework
		// is moved to start level zero (0), as described in the Start Level Service Specification.
		// Any exceptions that occur during bundle stopping must be wrapped in a BundleException
		// and then published as a framework event of type FrameworkEvent.ERROR
		//
		// Unregister all services registered by this Framework.
		// Event handling is disabled.
		// This Framework's state is set to Bundle.RESOLVED.
		// All resources held by this Framework are released. This includes threads, bundle class loaders, open files, etc.
		// Notify all threads that are waiting at waitForStop that the stop operation has completed.

		SaveBundleRegistryState();

		ReleaseCoreServices();

		StopAllBundles();
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::LoadCoreBundles()
	{
		VERBOSE("[SysBndleActivator] %s", __FUNCTION__);

		com_ptr<IBundle> logBundle = m_systemBundle->getBundleRepository()->CreateNewBundle("Logging.dll");
		logBundle->Start();
		m_logRef = m_context->getServiceReference(uuid_of(ILogService));
		m_systemBundle->m_log = m_context->getService(m_logRef);

		if(m_systemBundle->m_log)
			m_systemBundle->m_log->Initialize("Execution.log", "Error.log");
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::LoadInstalledBundles()
	{
		VERBOSE("[SysBndleActivator] %s", __FUNCTION__);

		BundleRegParser parser("BundleRegistry.xml");
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::SaveBundleRegistryState()
	{
		VERBOSE("[SysBndleActivator] %s", __FUNCTION__);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::StopAllBundles()
	{
		VERBOSE("[SysBndleActivator] %s", __FUNCTION__);

		/// \todo what will happen if some bundle will start another one on Stop()?

		DynArrayImplOwned<com_ptr<IBundle> > bundles;
		m_context->getBundles(bundles);

		for(size_t i = 0, size = bundles.size(); i != size; ++i)
			if(bundles[i]->getBundleId() != 0)
				bundles[i]->Stop();
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::ReleaseCoreServices()
	{
		VERBOSE("[SysBndleActivator] %s", __FUNCTION__);

		m_systemBundle->m_log.Release();

		m_context->ungetService(m_logRef);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundleActivator::ServiceChanged(const SServiceEvent &evnt)
	{
		/// \todo Replace with service tracker
		if(evnt.getType() == eSvcEvntT_Unregistering)
		{
			if(evnt.getServiceReference() == m_logRef)
			{
				m_systemBundle->m_log.Release();
				m_context->ungetService(m_logRef);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
