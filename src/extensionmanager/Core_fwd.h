/*========================================================
* Core_fwd.h
* @author Sergey Mikhtonyuk
* @date 29 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CORE_FWD_H__
#define _CORE_FWD_H__

namespace Logging { struct ILogService; }

namespace Extensions
{
	struct ICore;
	struct IPlugin;
	struct IPluginManager;
	struct IPluginShadow;
	struct IExtension;
	struct IStartListener;
	struct IExtensionPoint;
	struct GlobalEnvironment;

} // namespace

#endif // _CORE_FWD_H__