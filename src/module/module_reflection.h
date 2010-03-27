/*========================================================
* Module_reflection.h
* @author Sergey Mikhtonyuk
* @date 08 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _MODULE_REFLECTION_H__
#define _MODULE_REFLECTION_H__

#include "interfaces.h"
#include "reflection/reflection.h"

//////////////////////////////////////////////////////////////////////////
// GUID
//////////////////////////////////////////////////////////////////////////

namespace Reflection
{
	template<>
	inline void* type_ctor<Module::GUID, Module::NewAllocator>()
	{
		Module::GUID* g = new Module::GUID();
		g->SetZero();
		return g;
	}
} // namespace

reflect_struct(Module::GUID)
	map_ctor()
	map_parsable()
end_reflection()


reflect_class(Module::IUnknown)
	map_method("AddRef", AddRef)
	map_method("Release", Release)
end_reflection()

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

#endif // _MODULE_REFLECTION_H__