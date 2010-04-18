/*========================================================
* Events.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _EVENTS_H__
#define _EVENTS_H__

#include "IBundle.h"
#include "Services.h"
#include "module/intellectual.h"

namespace Framework
{

	//////////////////////////////////////////////////////////////////////////

	enum EFrameworkEventType
	{
		eFwkEvntT_Error,				///< An error has occurred
		eFwkEvntT_Info,					///< An informational event has occurred
		eFwkEvntT_PackagesRefreshed,	///< A PackageAdmin.refreshPackage operation has completed
		eFwkEvntT_Started,				///< The Framework has started
		eFwkEvntT_StartlevelChanged,	///< A StartLevel.setStartLevel operation has completed
		eFwkEvntT_Stopped,				///< The Framework has stopped
		eFwkEvntT_StoppedUpdate,		///< The Framework has stopped during update
		eFwkEvntT_WaitTimeout,			///< The Framework did not stop before the wait timeout expired
		eFwkEvntT_Warning,				///< A warning has occurred
	};

	/// Arguments of the framework event
	/** @ingroup Framework */
	struct SFrameworkEvent
	{
		/// Returns the bundle associated with the event
		module::com_ptr<IBundle> getBundle() const { return m_bundle; }
		
		/// Returns the type of bundle state change
		EFrameworkEventType getType() const { return m_type; }

		/// Returns the exception associated with the event
		//java.lang.Throwable	getThrowable();

		SFrameworkEvent()
		{ }

		SFrameworkEvent(IBundle* bundle, EFrameworkEventType type)
			: m_bundle(bundle), m_type(type)
		{ }

	private:
		module::com_ptr<IBundle> m_bundle;
		EFrameworkEventType m_type;
	};

	//////////////////////////////////////////////////////////////////////////

	enum EBundleEventType
	{
		eBndlEvntT_Installed,		///< The bundle has been installed
		eBndlEvntT_LazyActivation,	///< The bundle will be lazily activated
		eBndlEvntT_Resolved,		///< The bundle has been resolved
		eBndlEvntT_Starting,		///< The bundle is about to be activated
		eBndlEvntT_Started,			///< The bundle has been started
		eBndlEvntT_Stopping,		///< The bundle is about to deactivated
		eBndlEvntT_Stopped,			///< The bundle has been stopped
		eBndlEvntT_Unresolved,		///< The bundle has been unresolved
		eBndlEvntT_Uninstalled,		///< The bundle has been uninstalled
		eBndlEvntT_Updated,			///< The bundle has been updated
	};

	/// Arguments of the bundle event
	/** @ingroup Framework */
	struct SBundleEvent
	{
		/// Returns the bundle which had a lifecycle change
		module::com_ptr<IBundle> getBundle() const { return m_bundle; }

		/// Returns the type of lifecyle event
		int getType() const { return m_type; }

		SBundleEvent()
		{ }
		
		SBundleEvent(IBundle* bundle, EBundleEventType type)
			: m_bundle(bundle), m_type(type)
		{ }

	private:
		module::com_ptr<IBundle> m_bundle;
		EBundleEventType m_type;
	};

	//////////////////////////////////////////////////////////////////////////

	enum EServiceEventType
	{
		eSvcEvntT_Registered,		///< This service has been registered
		eSvcEvntT_Modified,			///< The properties of a registered service have been modified
		eSvcEvntT_ModifiedEndMatch,	///< The properties have been modified and no longer match the listener's filter
		eSvcEvntT_Unregistering,	///< This service is in the process of being unregistered
	};

	struct SServiceEvent
	{
		/// Returns a reference to the service that had a change occur in its lifecycle
		module::com_ptr<IServiceReference> getServiceReference() const { return m_service; }

		/// Returns the type of lifecyle event
		int getType() const { return m_type; }

		SServiceEvent()
		{ }

		SServiceEvent(IServiceReference* service, EServiceEventType type)
			: m_service(service), m_type(type)
		{ }

	private:
		module::com_ptr<IServiceReference> m_service;
		EServiceEventType m_type;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _EVENTS_H__
