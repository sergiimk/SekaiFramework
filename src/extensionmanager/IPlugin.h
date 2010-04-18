/*========================================================
* IPlugin.h
* @author Sergey Mikhtonyuk
* @date 02 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IPLUGIN_H__
#define _IPLUGIN_H__

#include "GlobalEnvironment.h"
#include "module/interfaces.h"

namespace Extensions
{
	struct ICore;
	struct IPluginManager;
	struct IPluginShadow;


	/// IPlugin interface eases the interaction between the plug-in and Core
	/** IPlugin interface is used for a convenient access to plug-in information,
	  * like current plug-in's shadow, core object and plugin manager instance 
	  * so you won't have to load in by yourself. IPlugin implementation is meant to be
	  * a singleton, so after plug-in module is loaded all the info will be passes into it
	  * by Core. After the module's loading each object inside the plugin will have a 
	  * convenient access to all interfaces.
	  * 
	  * To expose your plug-in from module map use OBJECT_ENTRY_I macro,
	  * this means that plug-in lookup will happen by interface, not by class ID.
	  * 
	  * @ingroup Extensions */
	sf_interface IPlugin : public module::IUnknown
	{
		sf_uuid("6c6c333c-861f-4948-90e1-9588613e3495")

		/// Used by core to initialize newly-created plug-in
		///
		/// @param pEnv		global environment pointer (original or substituted)
		/// @param pShadow	shadow of created plug-in
		virtual void Initialize(GlobalEnvironment* pEnv, IPluginShadow* pShadow) = 0;

		/// Returns your plug-in shadow
		virtual IPluginShadow* PluginShadow() = 0;
	};



} // namespace


#endif // _IPLUGIN_H__