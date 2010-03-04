/*========================================================
* Framework_fwd.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _FRAMEWORK_FWD_H__
#define _FRAMEWORK_FWD_H__

#include "platform/platform.h"

namespace Framework
{
	struct IFramework;
	struct IFrameworkFactory;

	struct IBundle;
	struct IBundleContext;
	struct IBundleActivator;

	struct IServiceRegistration;
	struct IServiceFactory;
	struct IServiceReference;

	struct IFrameworkListener;
	struct IBundleListener;
	struct IServiceListener;

	struct SFrameworkEvent;
	struct SBundleEvent;
	struct SServiceEvent;

	struct IFilter;

} // namespace

#endif // _FRAMEWORK_FWD_H__
