/*========================================================
* module_reflection.h
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
// guid
//////////////////////////////////////////////////////////////////////////

namespace detail
{
	inline void* _create_guid()
	{
		module::guid* g = new module::guid();
		g->reset();
		return g;
	}

	inline void _delete_guid(void* inst)
	{
		delete (module::guid*)inst;
	}
} // namespace

reflect_struct(module::guid, "guid")
	.def_ctor_custom(&::detail::_create_guid, &::detail::_delete_guid)
	.def_parsable()
end_reflection()


reflect_class(module::IUnknown, "IUnknown")
	.def_method("AddRef", AddRef)
	.def_method("Release", Release)
end_reflection()

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

#endif // _MODULE_REFLECTION_H__