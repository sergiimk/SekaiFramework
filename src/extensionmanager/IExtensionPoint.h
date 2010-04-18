/*========================================================
* IExtensionPoint.h
* @author Sergey Mikhtonyuk
* @date 29 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IEXTENSIONPOINT_H__
#define _IEXTENSIONPOINT_H__

#include "Core_fwd.h"
#include <string>
#include <vector>

namespace Extensions
{
	
	/// Extension point interface serves a link between extension provider's shadow and extenders
	/** @ingroup Extensions */
	sf_interface IExtensionPoint : public module::IUnknown
	{
		sf_uuid("f46632cb-fc73-4d5f-a418-0c30b8150a61")

		/// Name of extension point
		virtual const std::string& ID() = 0;

		/// Unique id of extension point (in format plugin_name::point_name)
		virtual const std::string& UniqueID() = 0;

		/// Gets provider of this extension point
		virtual IPluginShadow* Provider() = 0;

		/// Interface all extenders must implement
		virtual const module::guid& InterfaceID() = 0;

		/// Returns the number of extensions of this point
		virtual size_t getExtensionCount() = 0;

		/// Retrieves specified extension
		virtual IExtension* getExtension(size_t index) = 0;
	};

} // namespace


#endif // _IEXTENSIONPOINT_H__