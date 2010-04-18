/*========================================================
* EventDispatchers.h
* @author Sergey Mikhtonyuk
* @date 09 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _EVENTDISPATCHERS_H__
#define _EVENTDISPATCHERS_H__

#include "module/interfaces.h"
#include "Events.h"

using namespace module;

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	/// Event dispatcher interface
	/** @ingroup Framework */
	struct IEventDispatcher
	{
		virtual ~IEventDispatcher() { }
		virtual void Dispatch(IUnknown* listener) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////

	struct CFrameworkEventDispatcher : public IEventDispatcher
	{
		SFrameworkEvent Event;

		CFrameworkEventDispatcher(const SFrameworkEvent& e);

		virtual void Dispatch(IUnknown* listener) const;
	};

	//////////////////////////////////////////////////////////////////////////

	struct CBundleEventDispatcher : public IEventDispatcher
	{
		SBundleEvent Event;

		CBundleEventDispatcher(const SBundleEvent& e);

		virtual void Dispatch(IUnknown* listener) const;
	};

	//////////////////////////////////////////////////////////////////////////

	struct CServiceEventDispatcher : public IEventDispatcher
	{
		SServiceEvent Event;

		CServiceEventDispatcher(const SServiceEvent& e);

		virtual void Dispatch(IUnknown* listener) const;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _EVENTDISPATCHERS_H__
