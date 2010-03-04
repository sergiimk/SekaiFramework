/*========================================================
* Listeners.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _LISTENERS_H__
#define _LISTENERS_H__

#include "module/interfaces.h"
#include "Framework_fwd.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	/// Listener of the framework events
	/** @ingroup Framework */
	sf_interface IFrameworkListener : public Module::IUnknown
	{
		sf_uuid("2f57c518-1a6d-454e-8b87-6665d49833ab")

		/// Receives notification of a general FrameworkEvent object
		virtual void FrameworkEvent(const SFrameworkEvent& evnt) = 0;
	};		

	//////////////////////////////////////////////////////////////////////////

	/// Listener of the bundle events
	/** @ingroup Framework */
	sf_interface IBundleListener : public Module::IUnknown
	{
		sf_uuid("740930d5-da70-40e2-915c-e7470307d11a")

		/// Receives notification that a bundle has had a lifecycle change
		virtual void BundleChanged(const SBundleEvent& evnt) = 0;
	};

	/// Synchronously called during bundle life cycle processing
	/** @ingroup Framework */
	sf_interface ISynchronousBundleListener : public IBundleListener
	{
		sf_uuid("eaf4b056-93af-4894-ab9d-8ea8c28a6ad9")
	};

	//////////////////////////////////////////////////////////////////////////

	/// Listener of the service events
	/** @ingroup Framework */
	sf_interface IServiceListener : public Module::IUnknown
	{
		sf_uuid("c924003d-6935-4c26-9559-58c9bb677783")

		/// Receives notification that a service has had a lifecycle change
		virtual void ServiceChanged(const SServiceEvent& evnt) = 0;
	};
	
	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _LISTENERS_H__
