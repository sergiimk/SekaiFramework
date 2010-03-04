/*========================================================
* CSystemBundle.cpp
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CSystemBundle.h"
#include "CBundleContext.h"
#include "CSystemBundleActivator.h"
#include "Listeners.h"
#include "EventDispatchers.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////
	// For debugging purposes
	int _s_vb_tabs = -1;
	boost::thread::id fwk_thread_id;
	boost::thread::id launcher_thread_id;
	//////////////////////////////////////////////////////////////////////////

	CSystemBundle::CSystemBundle()
		: m_exiting(false)
		, m_eventServer(m_fwkLock, m_fwkEvent)
	{
		launcher_thread_id = boost::this_thread::get_id();
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::FinalConstruct(int argc, char *argv[], const char* settingsFile)
	{
		THREAD_LAUNCHER();

		CBundle::FinalConstruct(0, "System Bundle", this);
		m_bundleRepository.Init(this);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::Resolve()
	{
		THREAD_ANY_USER();

		m_state = eBndlState_Resolved;
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::PreStart()
	{
		THREAD_ANY_USER();

		CSystemBundleActivator* sba;
		create_instance_impl(&sba);
		sba->FinalConstruct(this);
		m_activator = sba;

		create_instance_impl(&m_context);
		m_context->FinalConstruct(this, this);

		m_state = eBndlState_Starting;
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::PostStart()
	{
		THREAD_ANY_USER();

		ASSERT_SOFT(m_state == eBndlState_Starting);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::Start()
	{
		THREAD_ANY_USER();
		
		{
			scoped_lock l(m_fwkLock);

			if(m_state != eBndlState_Starting)
				return;

			m_exiting = false;
			setState(eBndlState_Active);

			m_fwkThread = boost::thread(boost::bind(&CSystemBundle::ThreadLoop, this));
		}

		PostFrameworkEvent(eFwkEvntT_Started);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::Stop()
	{
		THREAD_ANY_USER();

		{
			scoped_lock l(m_fwkLock);
			m_exiting = true;
		}
		m_fwkEvent.notify_all();
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::Uninstall()
	{
		throw "BundleException";
	}

	//////////////////////////////////////////////////////////////////////////
	// Framework
	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::Init()
	{
		THREAD_ANY_USER();

		{
			scoped_lock l(m_fwkLock);

			if(	m_state == eBndlState_Starting || 
				m_state == eBndlState_Active ||
				m_state == eBndlState_Stopping)
				return;

			m_eventServer.Start();
		}

		/// \todo need to protect this also, recursive mutex?
		CBundle::Start();
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::Shutdown()
	{
		THREAD_FRAMEWORK();
		/// \todo need to protect this also?

		// Activator will do all the work
		CBundle::Stop();

		m_eventServer.Stop();
		m_eventServer.DeliverEvents();
	}

	//////////////////////////////////////////////////////////////////////////

	SFrameworkEvent CSystemBundle::WaitForStop(long timeout)
	{
		THREAD_ANY_USER();

		if(timeout)
		{
			if(!m_fwkThread.timed_join(boost::posix_time::milliseconds(timeout)))
				return SFrameworkEvent(0, eFwkEvntT_WaitTimeout);
		}
		else
		{
			m_fwkThread.join();
		}

		return m_exitCode;
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::ThreadLoop()
	{
		fwk_thread_id = boost::this_thread::get_id();

		while(!m_exiting)
		{
			{
				scoped_lock l(m_fwkLock);
				while(!m_exiting && !m_eventServer.HasPendingEvents())
					m_fwkEvent.wait(l);
			}

			m_eventServer.DeliverEvents();
		}
		
		Shutdown();
	}

	//////////////////////////////////////////////////////////////////////////

	CBundleRepository* CSystemBundle::getBundleRepository()
	{
		return &m_bundleRepository;
	}

	//////////////////////////////////////////////////////////////////////////

	CServiceRegistry* CSystemBundle::getServiceRegistry()
	{
		return &m_serviceRegistry;
	}

	//////////////////////////////////////////////////////////////////////////

	CEventServer* CSystemBundle::getEventServer()
	{
		return &m_eventServer;
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::AddListener(IFrameworkListener *listener)
	{
		THREAD_ANY();

		m_listeners.AddListener(listener);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::RemoveListener(IFrameworkListener *listener)
	{
		THREAD_ANY();

		m_listeners.RemoveListener(listener);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::PostBundleEvent(IBundle *bndl, EBundleEventType e)
	{
		THREAD_ANY();
		VERBOSE("[%s] %s : %d", bndl->getLocation(), __FUNCTION__, (int)e);

		CBundleEventDispatcher* disp = new CBundleEventDispatcher(SBundleEvent(bndl, e));

		m_eventServer.SendEvent(m_bundleRepository.getSyncListeners(), disp);
		m_eventServer.PostEvent(m_bundleRepository.getListeners(), disp);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::PostFrameworkEvent(EFrameworkEventType e)
	{
		VERBOSE("[%s] %s : %d", getLocation(), __FUNCTION__, (int)e);

		CFrameworkEventDispatcher* disp = new CFrameworkEventDispatcher(
			SFrameworkEvent(static_cast<CBundle*>(this), e));

		m_eventServer.PostEvent(m_listeners, disp);
	}

	//////////////////////////////////////////////////////////////////////////

	void CSystemBundle::SendServiceEvent(IServiceReference* ref, EServiceEventType e)
	{
		VERBOSE("[%s] %s : %d", getLocation(), __FUNCTION__, (int)e);

		CServiceEventDispatcher disp(SServiceEvent(ref, e));

		m_eventServer.SendEvent(m_serviceRegistry.getListeners(), &disp);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
