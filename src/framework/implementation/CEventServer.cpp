/*========================================================
* CEventServer.cpp
* @author Sergey Mikhtonyuk
* @date 10 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CEventServer.h"
#include "EventDispatchers.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CEventServer::CEventServer(boost::mutex& lock, boost::condition_variable& evnt)
		: m_active(false)
		, m_refFwkLock(lock)
		, m_refFwkEvent(evnt)
	{ }

	//////////////////////////////////////////////////////////////////////////

	CEventServer::~CEventServer()
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CEventServer::SendEvent(CEventListenerQueue listeners, IEventDispatcher* dispatcher)
	{
		THREAD_ANY();

		if(!m_active) return;

		DoSendEvent(listeners, dispatcher);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventServer::PostEvent(const CEventListenerQueue &listeners, IEventDispatcher *dispatcher)
	{
		THREAD_ANY();

		if(!m_active)
		{
			delete dispatcher;
			return;
		}

		{
			scoped_lock l(m_refFwkLock);
			m_queue.push(std::make_pair<CEventListenerQueue, IEventDispatcher*>(listeners, dispatcher));
		}
		m_refFwkEvent.notify_one();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventServer::DeliverEvents()
	{
		THREAD_FRAMEWORK();
		VERBOSE("[EventServer] Delivering events...");

		CEventListenerQueue* listeners;
		IEventDispatcher* dispatcher;

		while(true)
		{
			{
				scoped_lock l(m_refFwkLock);

				if(m_queue.empty()) break;

				listeners = &m_queue.front().first;
				dispatcher = m_queue.front().second;
			}

			if(m_active)
				DoSendEvent(*listeners, dispatcher);

			{
				scoped_lock l(m_refFwkLock);

				delete dispatcher;
				m_queue.pop();
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	bool CEventServer::HasPendingEvents() const
	{
		THREAD_FRAMEWORK();
		return !m_queue.empty();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventServer::DoSendEvent(const CEventListenerQueue &listeners, IEventDispatcher *dispatcher)
	{
		IUnknown** lst = listeners.getListeners();

		for(size_t i = 0, size = listeners.Size(); i != size; ++i)
			dispatcher->Dispatch(lst[i]);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
