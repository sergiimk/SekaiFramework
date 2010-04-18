/*========================================================
* IServiceTrackerCostumizer.h
* @author Sergey Mikhtonyuk
* @date 20 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ISERVICETRACKERCOSTUMIZER_H__
#define _ISERVICETRACKERCOSTUMIZER_H__

#include "framework/Framework_fwd.h"
#include "module/interfaces.h"

namespace Framework
{
	/// This interface allows a ServiceTracker to customize the service objects that are tracked
	/** @ingroup Utils */
	struct IServiceTrackerCustomizer
	{
		/// Called before a service which matched the search parameters is added to the ServiceTracker
		/** @param reference The reference to the service being added to the ServiceTracker
		 *  @return The service object to be tracked for the specified referenced
		 *  service or null if the specified referenced service should not be tracked */
		virtual module::IUnknown* AddingService(IServiceReference* reference) = 0;

		/// A service tracked by the ServiceTracker has been modified
		/** @param reference The reference to the service that has been modified
		 *  @param service The service object for the specified referenced service */
		virtual void ModifiedService(IServiceReference* reference, module::IUnknown* service) = 0;

		/// A service tracked by the ServiceTracker has been removed
		/** @param reference The reference to the service that has been removed
		 *  @param service The service object for the specified referenced service */
		virtual void RemovedService(IServiceReference* reference, module::IUnknown* service) = 0;
	};

} // namespace

#endif // _ISERVICETRACKERCOSTUMIZER_H__
