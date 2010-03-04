/*========================================================
* testmodule.cpp
* @author Sergey Mikhtonyuk
* @date 06 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "module/maps.h"
#include "test_implementations.h"

BEGIN_MODULE_MAP()
	OBJECT_ENTRY_REFLECTED(CLSID_FancyAdder, uuid_of(IFancyInterface), CFancyAdder, &Reflection::type_of<CFancyAdder>)
END_MODULE_MAP()