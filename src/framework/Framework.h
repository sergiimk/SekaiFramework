/*========================================================
* Framework.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
/** @defgroup Framework Framework
*  OSGi-like component framework */
#ifndef _FRAMEWORK_H__
#define _FRAMEWORK_H__

#include "IBundle.h"
#include "IBundleActivator.h"
#include "IBundleContext.h"
#include "Services.h"
#include "Listeners.h"
#include "Events.h"
#include "IFrameworkFactory.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	// {637b1ed1-12e5-4a4b-b69d-edf6ead5c478}
	static const Module::GUID CLSID_FrameworkFactory =
	{ 0x637b1ed1, 0x12e5, 0x4a4b, { 0xb6, 0x9d, 0xed, 0xf6, 0xea, 0xd5, 0xc4, 0x78 } };


	// {07a4b5f9-495c-45b1-bb91-e8fb11447c05}
	static const Module::GUID CLSID_BundleActivator =
	{ 0x07a4b5f9, 0x495c, 0x45b1, { 0xbb, 0x91, 0xe8, 0xfb, 0x11, 0x44, 0x7c, 0x05 } };

	//////////////////////////////////////////////////////////////////////////

	sf_interface IFilter : public Module::IUnknown
	{
		/// Compares this Filter object to another object
		//boolean equals(java.lang.Object obj)

		/// Returns the hashCode for this Filter object
		//int hashCode()

		/// Filter using a Dictionary object
		//boolean match(java.util.Dictionary dictionary)

		/// Filter using a service's properties
		//boolean match(ServiceReference reference)

		/// Returns this Filter object's filter string
		//java.lang.String toString()
	};

} // namespace

#endif // _FRAMEWORK_H__
