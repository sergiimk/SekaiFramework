/*========================================================
* CServiceRegistry.cpp
* @author Sergey Mikhtonyuk
* @date 22 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CServiceRegistry.h"
#include "CServiceRegistration.h"
#include "CSystemBundle.h"
#include "Listeners.h"
#include "EventDispatchers.h"
#include "CEventServer.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CServiceRegistry::CServiceRegistry()
		: m_systemBundle(0)
	{ }

	//////////////////////////////////////////////////////////////////////////

	CServiceRegistry::~CServiceRegistry()
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CServiceRegistry::Init(CSystemBundle* systemBundle)
	{
		THREAD_LAUNCHER();
		m_systemBundle = systemBundle;
	}

	//////////////////////////////////////////////////////////////////////////

	CServiceRegistration* CServiceRegistry::RegisterService(SF_RIID riid, IUnknown *service, CBundle* bundle)
	{
		THREAD_ANY();

		CServiceRegistration* pReg;
		create_instance_impl(&pReg);

		pReg->FinalConstruct(riid, service, bundle);

		{
			write_lock l(m_lock);
			m_servicesByID.insert(std::make_pair(riid, pReg));
		}

		return pReg;
	}

	//////////////////////////////////////////////////////////////////////////

	void CServiceRegistry::UnregisterService(Framework::CServiceRegistration *service)
	{
		/// \todo make smaller scope by upgrading lock
		THREAD_ANY();
		write_lock l(m_lock);

		std::pair<TServiceByID::iterator, TServiceByID::iterator> range = m_servicesByID.equal_range(service->getID());
		while(range.first != range.second)
		{
			if(range.first->second == service)
			{
				m_servicesByID.erase(range.first);
				service->Release();
				break;
			}
			++range.first;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IServiceReference> CServiceRegistry::getServiceReference(SF_RIID riid)
	{
		THREAD_ANY();
		read_lock l(m_lock);

		std::pair<TServiceByID::iterator, TServiceByID::iterator> range = m_servicesByID.equal_range(riid);
		/// \todo select using service rank
		if(range.first != range.second)
			return range.first->second->getReference();

		return com_ptr<IServiceReference>();
	}

	//////////////////////////////////////////////////////////////////////////

	const CEventListenerQueue& CServiceRegistry::getListeners() const
	{
		return m_listeners;
	}

	//////////////////////////////////////////////////////////////////////////

	void CServiceRegistry::AddListener(IServiceListener* listener)
	{
		THREAD_ANY();

		m_listeners.AddListener(listener);
	}

	//////////////////////////////////////////////////////////////////////////

	void CServiceRegistry::RemoveListener(IServiceListener* listener)
	{
		THREAD_ANY();

		m_listeners.RemoveListener(listener);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
