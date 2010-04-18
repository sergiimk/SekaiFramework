/*========================================================
* CommonPlugin.h
* @author Sergey Mikhtonyuk
* @date 02 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _COMMONPLUGIN_H__
#define _COMMONPLUGIN_H__

#include "IPlugin.h"
#include "ICore.h"
#include "module/implementations.h"

namespace Extensions
{
	/// Common implementation of IPlugin interface
	/** This class provides basic implementation of IPlugin suited in most cases,
	  * all you have to do is to include this header and add CommonPlugin to your module map 
	  * 
	  * @ingroup Extensions */
	class NOVTABLE CommonPlugin : 
		public module::ComRootObject<>,
		public IPlugin
	{
	public:
		DECLARE_IMPLEMENTATION2(CommonPlugin, module::ComClassFactorySingleton)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IPlugin)
		END_INTERFACE_MAP()

		CommonPlugin() 
		{
			Instance = this;
		}

		void Initialize(GlobalEnvironment* pEnv, IPluginShadow* pShadow)
		{
			gEnv = pEnv;
			MyShadow = pShadow;
		}

		IPluginShadow* PluginShadow() { return MyShadow; }
		IPluginShadow *MyShadow;

		static CommonPlugin *Instance;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Class ID of common plug-in, it is not important, because plug-in lookup is done by interface.
	/// {ba518e45-a5c9-4222-8617-71c794c633da}
	static const module::guid CLSID_CommonPlugin = 
	{ 0xba518e45, 0xa5c9, 0x4222, { 0x86, 0x17, 0x71, 0xc7, 0x94, 0xc6, 0x33, 0xda } };

	//////////////////////////////////////////////////////////////////////////

} // namespace


#endif // _COMMONPLUGIN_H__