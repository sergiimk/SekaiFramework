/*========================================================
* ServiceTracker.h
* @author Sergey Mikhtonyuk
* @date 20 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
/** @defgroup Utils Utils
 *  Framework utilities
 *  @ingroup Framework */
#ifndef _SERVICETRACKER_H__
#define _SERVICETRACKER_H__

#include "IServiceTrackerCostumizer.h"

namespace Framework
{
	/// Simplifies using services from the Framework's service registry
	/** @ingroup Utils */
	class ServiceTracker : public IServiceTrackerCustomizer
	{
	public:

		/// Create a ServiceTracker on the specified ServiceReference
		/** @param context The BundleContext against which the tracking is done
		 *  @param reference The ServiceReference for the service to be tracked
		 *  @param customizer The customizer object to call when services are added,
		 *	modified, or removed in this ServiceTracker.
		 *  If customizer is null, then this ServiceTracker will be used as the
		 *  ServiceTrackerCustomizer and this ServiceTracker will call the
		 *  ServiceTrackerCustomizer methods on itself */
		ServiceTracker(	IBundleContext* context,
						IServiceReference* reference,
						IServiceTrackerCustomizer* customizer);

		/// Create a ServiceTracker on the specified interface ID
		/** @param context The BundleContext against which the tracking is done
		 *  @param riid The interface Id of the services to be tracked
		 *  @param customizer The customizer object to call when services are added */
		ServiceTracker(IBundleContext* context, SF_RIID riid, IServiceTrackerCustomizer* customizer);

		/// Create a ServiceTracker on the specified Filter object
		/** @param context The BundleContext against which the tracking is done
		 *  @param filter The  Filter to select the services to be tracked
		 *  @param customizer The customizer object to call when services are added */
		ServiceTracker(IBundleContext* context, IFilter* filter, IServiceTrackerCustomizer* customizer);

		/// Open this ServiceTracker and begin tracking services
		void Open();

		/// Close this ServiceTracker
		void Close();

		/// Default implementation of the AddingService method
		module::IUnknown* AddingService(IServiceReference* reference);

		/// Default implementation of the ModifiedService method
		void ModifiedService(IServiceReference* reference, module::IUnknown* service);

		/// Default implementation of the RemovedService method
		void RemovedService(IServiceReference* reference, module::IUnknown* service);

		/** Wait for at least one service to be tracked by this ServiceTracker.
		 *  This method will also return when this ServiceTracker is closed. */
		module::IUnknown* WaitForService(long timeout);

		/// Return an collection of ServiceReferences for all services being tracked
		//ServiceReference[] getServiceReferences();

		/// Returns a ServiceReference for one of the services being tracked
		/** If multiple services are being tracked, the service with the highest
		 *  ranking (as specified in its service.ranking property) is returned */
		IServiceReference* getServiceReference();

		/// Returns the service object for the specified ServiceReference
		/** @param reference The reference to the desired service
		 *  @return A service object or null if the service is not being tracked */
		module::IUnknown* getService(IServiceReference* reference);

		/// Return an collection of service objects for all services being tracked by this ServiceTracker
		//Object[] getServices();

		/// Returns a service object for one of the services being tracked by this ServiceTracker
		module::IUnknown* getService();

		/// Remove a service from this ServiceTracker
		void Remove(IServiceReference* reference);

		/// Return the number of services being tracked
		size_t Size();

		/// Called by the Tracked object whenever the set of tracked services is modified. Clears the cache.
		void Modified();
	};


} // namespace

#endif // _SERVICETRACKER_H__
