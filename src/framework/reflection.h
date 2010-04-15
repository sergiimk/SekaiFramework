/*========================================================
* Reflection.h
* @author Sergey Mikhtonyuk
* @date 26 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _FRAMEWORK_REFLECTION_H__
#define _FRAMEWORK_REFLECTION_H__

#include "reflection/reflection.h"
#include "framework/IBundle.h"

reflect_enum(Framework::EBundleState, "EBundleState")
	.def_enum("INSTALLED", Framework::eBndlState_Installed)
	.def_enum("RESOLVED", Framework::eBndlState_Resolved)
	.def_enum("STARTING", Framework::eBndlState_Starting)
	.def_enum("ACTIVE", Framework::eBndlState_Active)
	.def_enum("STOPPING", Framework::eBndlState_Stopping)
	.def_enum("UNINSTALLED", Framework::eBndlState_Uninstalled)
end_reflection()

#endif // _FRAMEWORK_REFLECTION_H__
