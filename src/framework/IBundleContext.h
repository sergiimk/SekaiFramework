/*========================================================
* IBundleContext.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IBUNDLECONTEXT_H__
#define _IBUNDLECONTEXT_H__

#include "module/interfaces.h"
#include "module/intellectual.h"
#include "common/containers.h"
#include "Framework_fwd.h"

namespace Framework
{

	/** A bundle's execution context within the Framework.
	*  The context is used to grant access to other methods so that this bundle can interact with the Framework.
	*  
	*  @ingroup Framework */
	sf_interface IBundleContext : public module::IUnknown
	{
		sf_uuid("21c69b4c-122a-4a77-bb21-cd7115ec1641")

		/// Returns the Bundle object for this context bundle
		virtual module::com_ptr<IBundle> getBundle() = 0;

		/// Returns the bundle with the specified identifier
		virtual module::com_ptr<IBundle> getBundle(size_t id) = 0;

		/// Returns a list of all installed bundles
		virtual void getBundles(IDynArray<module::com_ptr<IBundle> >& bundles) = 0;

		/// Installs the bundle from the specified location string
		virtual module::com_ptr<IBundle> InstallBundle(const char* location) = 0;

		/// Installs the bundle from the specified InputStream object
		//virtual IBundle* InstallBundle(const char* location, java.io.InputStream in) = 0;


		/// Registers the specified service object with the specified properties under the specified class name into the Framework
		/** @param riid service interface ID
		 *  @param service service instance 
		 *  @return service registration object */
		virtual module::com_ptr<IServiceRegistration> RegisterService(SF_RIID riid, module::IUnknown* service /*, java.util.Dictionary properties*/) = 0;

		/// Registers the specified service object with the specified properties under the specified class names into the Framework
		//virtual IServiceRegistration* registerService(const char*[] clazzes, module::IUnknown* service, java.util.Dictionary properties)  = 0;

		/// Returns a ServiceReference object for a service that implements, and was registered under, the specified class
		/** @param riid service interface ID
		 *  @return service reference object */
		virtual module::com_ptr<IServiceReference> getServiceReference(SF_RIID riid)  = 0;

		/// Returns a list of ServiceReference objects
		//virtual IServiceReference*[] getServiceReferences(const char* clazz, IFilter* filter)  = 0;

		/// Returns the specified service object for a service
		virtual module::com_ptr<IUnknown> getService(IServiceReference* reference)  = 0;

		/// Releases the service object referenced by the specified ServiceReference object
		virtual bool ungetService(IServiceReference* reference)  = 0;
		
		/*/// Creates a Filter object
		virtual module::com_ptr<IFilter> createFilter(const char* filter)  = 0;

		/// Creates a File object for a file in the persistent storage area provided for the bundle by the Framework
		virtual com_ptr<IFile> getDataFile(const char* filename)  = 0;

		/// Returns the value of the specified environment property
		virtual const char*	getProperty(const char* key)  = 0;
		*/
		
		/// Adds the specified BundleListener object to this context bundle's list of listeners if not already present
		virtual void AddBundleListener(IBundleListener* listener) = 0;

		/// Removes the specified BundleListener object from this context bundle's list of listeners
		virtual void RemoveBundleListener(IBundleListener* listener)  = 0;

		
		/// Adds the specified FrameworkListener object to this context bundle's list of listeners if not already present
		virtual void AddFrameworkListener(IFrameworkListener* listener)  = 0;

		/// Removes the specified FrameworkListener object from this context bundle's list of listeners
		virtual void RemoveFrameworkListener(IFrameworkListener* listener)  = 0;


		/// Adds the specified ServiceListener object to this context bundle's list of listeners
		virtual void AddServiceListener(IServiceListener* listener)  = 0;

		/// Adds the specified ServiceListener object with the specified filter to this context bundle's list of listeners
		//virtual void AddServiceListener(IServiceListener* listener, const char* filter)  = 0;

		/// Removes the specified ServiceListener object from this context bundle's list of listeners
		virtual void RemoveServiceListener(IServiceListener* listener)  = 0;
	};

} // namespace

#endif // _IBUNDLECONTEXT_H__
