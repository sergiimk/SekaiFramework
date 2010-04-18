/*========================================================
* IBundleActivator.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IBUNDLEACTIVATOR_H__
#define _IBUNDLEACTIVATOR_H__

#include "module/interfaces.h"
#include "Framework_fwd.h"

namespace Framework
{

	/// Customizes the starting and stopping of this bundle
	/** @ingroup Framework */
	sf_interface IBundleActivator : public module::IUnknown
	{
		sf_uuid("0955b77d-f178-434d-adb0-9c2e55d93894")

		/// Called when this bundle is started so the Framework can perform the bundle-specific activities necessary to start this bundle
		virtual void Start(IBundleContext* context) = 0;

		/// Called when this bundle is stopped so the Framework can perform the bundle-specific activities necessary to stop the bundle
		virtual void Stop(IBundleContext* context) = 0;
	};

} // namespace

#endif // _IBUNDLEACTIVATOR_H__
