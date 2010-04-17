/*========================================================
* CEventListenerQueue.cpp
* @author Sergey Mikhtonyuk
* @date 09 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CEventListenerQueue.h"
#include "platform/platform.h"
#include "Impl_fwd.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CEventListenerQueue::CEventListenerQueue()
		: m_queue(new TListenerQueue)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CEventListenerQueue::CEventListenerQueue(const CEventListenerQueue& source)
	{
		THREAD_ANY();

		// Protect source queue against simultaneous read/write access
		scoped_lock l(source.m_lock);

		m_queue = source.m_queue;
	}

	//////////////////////////////////////////////////////////////////////////

	CEventListenerQueue::~CEventListenerQueue()
	{
		THREAD_ANY();

		// Safe - writes on different pointers (even sharing the ref count) are allowed
		m_queue.reset();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventListenerQueue::AddListener(IUnknown* listener)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		PreModify();

		listener->AddRef();
		m_queue->push_back(listener);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventListenerQueue::RemoveListener(IUnknown* listener)
	{
		THREAD_ANY();
		scoped_lock l(m_lock);

		PreModify();

		TListenerQueue::iterator it = std::find(m_queue->begin(), m_queue->end(), listener);
		ASSERT_STRICT(it != m_queue->end());

		if(it != m_queue->end())
		{
			m_queue->erase(it);
			listener->Release();
		}
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CEventListenerQueue::Size() const
	{
		return m_queue->size();
	}

	//////////////////////////////////////////////////////////////////////////

	IUnknown** CEventListenerQueue::getListeners() const
	{
		THREAD_ANY();

		return Size() != 0 ? &(*m_queue)[0] : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventListenerQueue::PreModify()
	{
		if(m_queue.unique()) return;

		TListenerQueue* old = m_queue.get();
		m_queue.reset(new TListenerQueue(*old));
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
