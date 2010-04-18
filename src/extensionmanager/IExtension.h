/*========================================================
* IExtension.h
* @author Sergey Mikhtonyuk
* @date 29 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IEXTENSION_H__
#define _IEXTENSION_H__

#include "Core_fwd.h"
#include "module/interfaces.h"
#include <string>
#include <map>

namespace Extensions
{
	/// Extension binds extension point with implementation class of extender and contains extension parameters
	/** @ingroup Extensions */
	sf_interface IExtension : public module::IUnknown
	{
		sf_uuid("a4fe0296-4f81-4643-ab29-37a9039d85ac")

		/// Returns the shadow of extender plug-in
		virtual IPluginShadow* Extender() = 0;

		/// Gets the point this extension extends
		virtual IExtensionPoint* ExtensionPoint() = 0;

		/// Gets the implementation class guid, check IsZero before using it
		virtual const module::guid& ImplClassID() = 0;

		/// Returns parameter of extension by it's name
		/** Parameter map is widely used to increase the 'lazyness' of plugin creation 
		 *  @return value of parameter, 0 if not found */
		virtual const char* getParameter(const char* name) = 0;
	};


} // namespace


#endif // _IEXTENSION_H__