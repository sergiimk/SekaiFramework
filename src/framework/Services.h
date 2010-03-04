/*========================================================
* Services.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SERVICES_H__
#define _SERVICES_H__

#include "module/interfaces.h"
#include "module/intellectual.h"
#include "Framework_fwd.h"

namespace Framework
{

	//////////////////////////////////////////////////////////////////////////

	sf_interface IServiceReference : public Module::IUnknown
	{
		sf_uuid("affd3937-b9a9-4f35-8c95-dd6e50d4d799")

		/// Returns the bundle that registered the service referenced by this ServiceReference object
		virtual Module::com_ptr<IBundle> getBundle() = 0;

		/*/// Returns the property value to which the specified property key is mapped in the properties Dictionary object of the service referenced by this ServiceReference object
		virtual java.lang.Object getProperty(const char* key) = 0;

		/// Returns an array of the keys in the properties Dictionary object of the service referenced by this ServiceReference object
		virtual const char*[] getPropertyKeys() = 0;

		/// Returns the bundles that are using the service referenced by this ServiceReference object
		virtual IBundle*[] getUsingBundles() = 0;*/
	};


	//////////////////////////////////////////////////////////////////////////


	/// A registered service
	/** @ingroup Framework */
	sf_interface IServiceRegistration : public Module::IUnknown
	{
		sf_uuid("a53de5fe-b51e-4015-b079-db99303fa13b")

		// Returns a ServiceReference object for this registration
		virtual Module::com_ptr<IServiceReference> getReference() = 0;

		/// Update the properties associated with this service
		//virtual void setProperties(java.util.Dictionary properties) = 0;

		/// Unregister the service
		virtual void Unregister() = 0;
	};


	//////////////////////////////////////////////////////////////////////////


	/// Allows services to provide customized service objects in the OSGi environment
	/** @ingroup Framework */
	sf_interface IServiceFactory : public Module::IUnknown
	{
		/*/// Creates a new service object
		virtual com_ptr<Module::IUnknown> getService(IBundle* bundle, IServiceRegistration* registration) = 0;

		/// Releases a service object
		virtual void ungetService(IBundle* bundle, IServiceRegistration* registration, Module::IUnknown* service) = 0;*/
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _SERVICES_H__
