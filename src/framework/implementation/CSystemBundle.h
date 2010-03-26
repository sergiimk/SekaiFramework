/*========================================================
* CSystemBundle.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSYSTEMBUNDLE_H__
#define _CSYSTEMBUNDLE_H__

#include "IFramework.h"
#include "IBundleContext.h"
#include "CBundle.h"
#include "CBundleRepository.h"
#include "CServiceRegistry.h"
#include "CEventServer.h"
#include "CEventListenerQueue.h"
#include "logging/logging.h"

#include <boost/thread.hpp>

using namespace Module;
using namespace Logging;

namespace Framework
{

	/// System bundle implementation
	/** @ingroup Framework */
	class CSystemBundle
		: public CBundle
		, public IFramework
	{
		friend class CSystemBundleActivator;

	public:

		DECLARE_IMPLEMENTATION_DERIVED(CSystemBundle, CBundle)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IFramework)
			INTERFACE_ENTRY_CHAIN(CBundle)
		END_INTERFACE_MAP()

		CSystemBundle();
		void FinalConstruct(int argc, char *argv[], const char* settingsFile);

		// Bundle
		virtual size_t getBundleId()						{ return CBundle::getBundleId(); }
		virtual com_ptr<IBundleContext> getBundleContext()	{ return CBundle::getBundleContext(); }
		virtual EBundleState getState()						{ return CBundle::getState(); }
		virtual const char* getLocation()					{ return CBundle::getLocation(); }
		virtual void getRegisteredServices(IDynArray<com_ptr<IServiceReference> >& services) { return CBundle::getRegisteredServices(services); }
		virtual void getServicesInUse(IDynArray<com_ptr<IServiceReference> >& services) {return CBundle::getServicesInUse(services); }
		virtual void Start();
		virtual void Stop();
		virtual void Uninstall();

	private:
		virtual void Resolve();
		virtual void PreStart();
		virtual void PostStart();


		// Framework
	public:
		virtual void Init();
		virtual SFrameworkEvent WaitForStop(long timeout);
		void ThreadLoop();
		void Shutdown();
		CBundleRepository* getBundleRepository();
		CServiceRegistry* getServiceRegistry();
		CEventServer* getEventServer();
		void AddListener(IFrameworkListener* listener);
		void RemoveListener(IFrameworkListener* listener);

		void PostBundleEvent(IBundle* bndl, EBundleEventType e);
		void PostFrameworkEvent(EFrameworkEventType e);
		void SendServiceEvent(IServiceReference* ref, EServiceEventType e);

	private:
		CBundleRepository m_bundleRepository;
		CServiceRegistry m_serviceRegistry;
		CEventServer m_eventServer;
		CEventListenerQueue m_listeners;

		com_ptr<ILogService> m_log;

		typedef boost::mutex::scoped_lock scoped_lock;
		boost::thread m_fwkThread;
		boost::mutex m_fwkLock;
		boost::condition_variable m_fwkEvent;

		bool m_exiting;
		SFrameworkEvent m_exitCode;
	};

} // namespace

#endif // _CSYSTEMBUNDLE_H__
