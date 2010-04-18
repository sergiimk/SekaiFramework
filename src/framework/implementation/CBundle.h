/*========================================================
* CBundle.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CBUNDLE_H__
#define _CBUNDLE_H__

#include "IBundle.h"
#include "IBundleActivator.h"
#include "module/module.h"
#include "Impl_fwd.h"
#include "ServiceUsage.h"
#include "Events.h"
#include "common/stlutils.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/thread.hpp>

using namespace module;

//////////////////////////////////////////////////////////////////////////

namespace Framework
{

	/// Bundle implementation
	/** @ingroup Framework */
	class NOVTABLE CBundle :
		public module::ComRootObject<module::MultiThreadModel>,
		public IBundle
	{
	public:

		DECLARE_IMPLEMENTATION(CBundle)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IBundle)
		END_INTERFACE_MAP()

		CBundle();
		~CBundle();
		void Finalize();
		void CheckValid() const;

		void FinalConstruct(size_t id, const char* location, CSystemBundle* systemBundle);

		virtual size_t getBundleId();
		virtual com_ptr<IBundleContext> getBundleContext();
		virtual EBundleState getState();
		void setState(EBundleState state);
		virtual const char* getLocation();
		virtual void getRegisteredServices(IDynArray<com_ptr<IServiceReference> >& services);
		virtual void getServicesInUse(IDynArray<com_ptr<IServiceReference> >& services);
		virtual void Start();
		virtual void Stop();
		virtual void Uninstall();

		CServiceRegistration* RegisterService(SF_RIID riid, IUnknown* object);
		void UnregisterService(CServiceRegistration* service);
		com_ptr<IUnknown> getService(CServiceReference* reference);
		bool ungetService(CServiceReference* reference);
		void ForceUngetService(CServiceRegistration* service);

	private:
		void UnregisterServices();
		void ReleaseUsedServices();

	protected:
		virtual void PreStart();
		virtual void PostStart();
		virtual void PreStop();
		virtual void PostStop(bool wasUnregistered, bool activatorError);
		virtual void PostUninstall();
		virtual void Resolve();

	protected:
		typedef std::vector<CServiceRegistration*> TServiceContainer;
		typedef std::unordered_map<CServiceRegistration*, ServiceUsage, stl::hash_ptr> TServicesInUseContainer;

		size_t					m_id;
		EBundleState			m_state;
		std::string				m_location;
		CSystemBundle*			m_systemBundle;
		CBundleContext*			m_context;
		IBundleActivator*		m_activator;
		ModuleHandle			m_module;
		TServiceContainer		m_publishedServices;
		TServicesInUseContainer	m_servicesInUse;

		typedef boost::mutex::scoped_lock scoped_lock;
		boost::mutex			m_lock;
	};

} // namespace

#endif // _CBUNDLE_H__
