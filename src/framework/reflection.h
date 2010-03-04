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

reflect_enum(Framework::EBundleState)
	map_enum2(Framework::eBndlState_Installed, "INSTALLED")
	map_enum2(Framework::eBndlState_Resolved, "RESOLVED")
	map_enum2(Framework::eBndlState_Starting, "STARTING")
	map_enum2(Framework::eBndlState_Active, "ACTIVE")
	map_enum2(Framework::eBndlState_Stopping, "STOPPING")
	map_enum2(Framework::eBndlState_Uninstalled, "UNINSTALLED")
end_reflection_enum()

#endif // _FRAMEWORK_REFLECTION_H__
