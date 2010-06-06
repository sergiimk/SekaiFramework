/*========================================================
* IPluginShadow.h
* @author Sergey Mikhtonyuk
* @date 16 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IPLUGINSHADOW_H__
#define _IPLUGINSHADOW_H__

#include "Core_fwd.h"
#include "module/interfaces.h"
#include <string>
#include <vector>

namespace Extensions
{
	/// IPluginShadow interface
	/** Plug-in shadow is the proxy object that used to
	 *  access some plug-in information without loading 
	 *  the actual plug-in
	 *  
	 *  @ingroup Extensions */
	sf_interface IPluginShadow : public module::IUnknown
	{
		sf_uuid("b8e5b63a-4b08-4dcf-8fa2-9e0a54379c37")

		/// Gets plug-in name
		virtual const std::string& PluginName() = 0;
		/// Gets module name (usualy pluginname + ".dll")
		virtual const std::string& ModuleName() = 0;

		/// Checks if this plugin exports this class id
		virtual bool Exports(const module::guid &clsid) = 0;
		/// Checks if this plugin provides such extension point (simplified format only)
		virtual bool Provides(const std::string& extpoint) = 0;
		/// Checks if this plugin extends this extension point (UniqueID only)
		virtual bool Extends(const std::string& extpoint) = 0;

		/// Queries the creation of object (loads module automatically)
		virtual std::error_code CreateInstance(module::guid const& clsid, module::guid const& riid, void** ppv) = 0;
		/// Queries the creation of first found interface implementation (loads module automatically)
		virtual std::error_code CreateInstance(module::guid const& riid, void** ppv) = 0;

		/// Returns the number of extension provided by this plug-in
		virtual size_t getExtensionCount() = 0;
		/// Returns the extension, provided by this plug-in
		virtual IExtension* getExtension(size_t index) = 0;

		/// Returns the number of extension points provided by this plug-in
		virtual size_t getExtensionPointCount() = 0;
		/// Returns the extension point, provided by this plug-in
		virtual IExtensionPoint* getExtensionPoint(size_t index) = 0;

		/// Finds the extension point by it's name (simplified format only)
		virtual IExtensionPoint* FindExtensionPoint(const std::string& name) = 0;
	};


} // namespace

#endif // _IPLUGINSHADOW_H__