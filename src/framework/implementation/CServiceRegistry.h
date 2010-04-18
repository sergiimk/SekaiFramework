/*========================================================
* CServiceRegistry.h
* @author Sergey Mikhtonyuk
* @date 22 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSERVICEREGISTRY_H__
#define _CSERVICEREGISTRY_H__

#include "Framework_fwd.h"
#include "Services.h"
#include "CEventListenerQueue.h"
#include "Impl_fwd.h"
#include "common/stlutils.h"
#include <unordered_map>
#include <boost/thread.hpp>

using namespace module;

namespace Framework
{
	/// Manages service lifetimes
	/** @ingroup Framework */
	class CServiceRegistry
	{
	public:
		CServiceRegistry();
		~CServiceRegistry();

		void Init(CSystemBundle* systemBundle);

		CServiceRegistration* RegisterService(SF_RIID riid, module::IUnknown *service, CBundle* bundle);
		void UnregisterService(CServiceRegistration* service);
		com_ptr<IServiceReference> getServiceReference(SF_RIID riid);

		const CEventListenerQueue& getListeners() const;
		void AddListener(IServiceListener* listener);
		void RemoveListener(IServiceListener* listener);

	private:
		typedef std::unordered_multimap<guid, CServiceRegistration*, module::guid_hash> TServiceByID;

		TServiceByID m_servicesByID;
		CEventListenerQueue m_listeners;
		CSystemBundle* m_systemBundle;

		typedef boost::shared_lock<boost::shared_mutex> read_lock;
		typedef boost::unique_lock<boost::shared_mutex> write_lock;
		mutable boost::shared_mutex m_lock;
	};

} // namespace

#endif // _CSERVICEREGISTRY_H__
