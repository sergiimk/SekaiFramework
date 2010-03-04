/*========================================================
* SekaiCore.cpp
* @author Sergey Mikhtonyuk
* @date 13 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CCore.h"
#include "SekaiCore.h"

namespace Extensions
{
	
	BEGIN_MODULE_MAP()
		OBJECT_ENTRY(CLSID_CCore, uuid_of(ICore), CCore)
	END_MODULE_MAP()

} // namespace
