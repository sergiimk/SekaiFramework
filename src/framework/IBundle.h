/*========================================================
* IBundle.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IBUNDLE_H__
#define _IBUNDLE_H__

#include "module/interfaces.h"
#include "module/intellectual.h"
#include "common/containers.h"
#include "Framework_fwd.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	/// Bundle state
	/** @ingroup Framework */
	enum EBundleState
	{
		eBndlState_Installed,	///< This is the state after a bundle has been successfully installed
		eBndlState_Resolved,	///< All dependencies been made available, bundle is ready to be started. Stopped modules put in this state
		eBndlState_Starting,	///< This indicates that the bundle is being started
		eBndlState_Active,		///< This indicates that the bundle is being stopped
		eBndlState_Stopping,	///< A bundle has successfully started and is running
		eBndlState_Uninstalled,	///< The bundle has been uninstalled. It cannot move into any other states.
	};

	//////////////////////////////////////////////////////////////////////////

	/// A Bundle object is the access point to define the life cycle of an installed bundle.
	/** Each bundle installed in the OSGi environment will have an associated Bundle object.
	*   A bundle will have a unique identity, a long, chosen by the Framework.
	*   This identity will not change during the life cycle of a bundle, even when the bundle is updated.
	*   Uninstalling and then reinstalling the bundle will create a new unique identity.
	*
	*   @ingroup Framework */
	sf_interface IBundle : public Module::IUnknown
	{
		sf_uuid("937db03e-fb35-4e7f-9a81-e6f43ade912b")

		/// Returns this bundle's identifier
		virtual size_t getBundleId() = 0;

		/// The returned BundleContext can be used by the caller to act on behalf of this bundle
		virtual Module::com_ptr<IBundleContext> getBundleContext() = 0;

		/// Returns this bundle's current state
		virtual EBundleState getState() = 0;

		/// Returns this bundle's location identifier
		virtual const char* getLocation() = 0;

		/*
		/// Returns the symbolic name of this Framework
		virtual const char* getSymbolicName() = 0;

		/// Returns this bundle's Manifest headers and values
		virtual java.util.Dictionary getHeaders() = 0;*/

		/// Returns this bundle's ServiceReference list for all services it has registered
		virtual void getRegisteredServices(IDynArray<Module::com_ptr<IServiceReference> >& services) = 0;

		/// Returns this bundle's ServiceReference list for all services it is using
		virtual void getServicesInUse(IDynArray<Module::com_ptr<IServiceReference> >& services) = 0;

		/*/// Find the specified resource in this bundle
		virtual java.net.URL getResource(java.lang.String name) = 0;

		/// Determines if this bundle has the specified permissions
		virtual boolean	hasPermission(java.lang.Object permission) = 0;
		*/

		/// Starts this bundle
		virtual void Start() = 0;

		/// Stops this bundle
		virtual void Stop() = 0;

		/// Uninstalls this bundle
		virtual void Uninstall() = 0;

		/// Updates this bundle
		/*virtual void Update() = 0;

		/// Updates this bundle from an InputStream
		virtual void Update(java.io.InputStream in) = 0;*/

	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _IBUNDLE_H__
