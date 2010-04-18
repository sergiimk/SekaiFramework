/*========================================================
* EventDispatchers.cpp
* @author Sergey Mikhtonyuk
* @date 09 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "EventDispatchers.h"
#include "Listeners.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////
	// CFrameworkEventDispatcher
	//////////////////////////////////////////////////////////////////////////

	CFrameworkEventDispatcher::CFrameworkEventDispatcher(const SFrameworkEvent &e)
		: Event(e)
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CFrameworkEventDispatcher::Dispatch(module::IUnknown *listener) const
	{
		static_cast<IFrameworkListener*>(listener)->FrameworkEvent(Event);
	}

	//////////////////////////////////////////////////////////////////////////
	// CBundleEventDispatcher
	//////////////////////////////////////////////////////////////////////////

	CBundleEventDispatcher::CBundleEventDispatcher(const SBundleEvent &e)
		: Event(e)
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CBundleEventDispatcher::Dispatch(module::IUnknown *listener) const
	{
		static_cast<IBundleListener*>(listener)->BundleChanged(Event);
	}

	//////////////////////////////////////////////////////////////////////////
	// CServiceEventDispatcher
	//////////////////////////////////////////////////////////////////////////

	CServiceEventDispatcher::CServiceEventDispatcher(const SServiceEvent &e)
		: Event(e)
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CServiceEventDispatcher::Dispatch(module::IUnknown *listener) const
	{
		static_cast<IServiceListener*>(listener)->ServiceChanged(Event);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
