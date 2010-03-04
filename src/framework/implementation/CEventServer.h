/*========================================================
* CEventServer.h
* @author Sergey Mikhtonyuk
* @date 10 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CEVENTSERVER_H__
#define _CEVENTSERVER_H__

#include "Impl_fwd.h"
#include "CEventListenerQueue.h"
#include <queue>
#include <boost/thread.hpp>

namespace Framework
{

	/// Implements event delivery system
	/** @ingroup Framework */
	class CEventServer
	{
	public:

		CEventServer(boost::mutex& lock, boost::condition_variable& evnt);

		~CEventServer();

		void Start() { THREAD_LAUNCHER(); m_active = true; }

		void Stop()  { THREAD_FRAMEWORK(); m_active = false; }

		bool isActive() { return m_active; }

		/// Sends notifications synchronously
		void SendEvent(CEventListenerQueue listeners, IEventDispatcher* dispatcher);

		/// Adds event to notification queue
		void PostEvent(const CEventListenerQueue& listeners, IEventDispatcher* dispatcher);

		/// Dispatches all scheduled events
		void DeliverEvents();

		/// Server has some events to be delivered
		bool HasPendingEvents() const;

	private:

		void DoSendEvent(const CEventListenerQueue& listeners, IEventDispatcher* dispatcher);

	private:
		/// \todo Add dispatcher pool
		typedef std::queue<std::pair<CEventListenerQueue, IEventDispatcher*> > TEventQueue;
		typedef boost::mutex::scoped_lock scoped_lock;

		TEventQueue m_queue;
		boost::mutex& m_refFwkLock;
		boost::condition_variable& m_refFwkEvent;
		bool m_active;
	};

} // namespace

#endif // _CEVENTSERVER_H__
