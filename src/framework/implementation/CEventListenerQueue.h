/*========================================================
* CEventListenerQueue.h
* @author Sergey Mikhtonyuk
* @date 09 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CEVENTLISTENERQUEUE_H__
#define _CEVENTLISTENERQUEUE_H__

#include "module/interfaces.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

using namespace module;

namespace Framework
{
	//
	// TODO: Separate a non-modifiable base class to pass to dispatchers
	//

	/// Event listener container
	/** With requirement to deliver messages only to the objects who
	 *  exist at the time of the call in multi threaded environment, this
	 *  class uses Copy-on-Write pattern to copy data only when needed
	 *  @ingroup Framework */
	class CEventListenerQueue
	{
	public:
		CEventListenerQueue();

		CEventListenerQueue(const CEventListenerQueue& source);

		~CEventListenerQueue();

		void AddListener(IUnknown* listener);

		void RemoveListener(IUnknown* listener);

		size_t Size() const;

		IUnknown** getListeners() const;

	private:
		void PreModify();

	private:
		typedef std::vector<IUnknown*> TListenerQueue;
		typedef boost::shared_ptr<TListenerQueue> TSharedQueue;

		TSharedQueue m_queue;

		typedef boost::mutex::scoped_lock scoped_lock;
		mutable boost::mutex m_lock;
	};

} // namespace

#endif // _CEVENTLISTENERQUEUE_H__
