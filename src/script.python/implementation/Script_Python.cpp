/*========================================================
* Script_Python.cpp
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
/** @defgroup Py Python
*  Python-based script system
*  @ingroup Script */
#include "Scripting.h"
#include "implementation/CScriptManager.h"

namespace ScriptPy
{

	// {43982851-519b-413f-957e-57bc61a7f80b}
	static const module::guid CLSID_CScriptManager =
	{ 0x43982851, 0x519b, 0x413f, { 0x95, 0x7e, 0x57, 0xbc, 0x61, 0xa7, 0xf8, 0x0b } };

	BEGIN_MODULE_MAP()
		OBJECT_ENTRY(CLSID_CScriptManager, uuid_of(IScriptManager), CScriptManager)
	END_MODULE_MAP()

} // namespace
