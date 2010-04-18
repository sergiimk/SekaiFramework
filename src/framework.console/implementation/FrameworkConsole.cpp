/*========================================================
* FrameworkConsole.cpp
* @author Sergey Mikhtonyuk
* @date 19 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "ConsoleBundle.h"
#include "module/maps.h"

// {bf1e1254-3c27-474d-9572-62011b7595ba}
static const guid CLSID_CConsoleBundle =
{ 0xbf1e1254, 0x3c27, 0x474d, { 0x95, 0x72, 0x62, 0x01, 0x1b, 0x75, 0x95, 0xba } };

BEGIN_MODULE_MAP()
	OBJECT_ENTRY(CLSID_CConsoleBundle, uuid_of(IBundleActivator), CConsoleBundle)
END_MODULE_MAP()
