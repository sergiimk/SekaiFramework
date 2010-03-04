/*========================================================
* Framework.cpp
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "Framework.h"
#include "CFrameworkFactory.h"

namespace Framework
{

	BEGIN_MODULE_MAP()
		OBJECT_ENTRY(CLSID_FrameworkFactory, uuid_of(IFrameworkFactory), CFrameworkFactory)
	END_MODULE_MAP()

} // namespace
