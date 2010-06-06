/*========================================================
* module_fwd.h
* @author Sergey Mikhtonyuk
* @date 23 February 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _MODULE_FWD_H__
#define _MODULE_FWD_H__

#include "platform/platform.h"

#if defined BUILD_SHARED && defined MODULE_EXPORTS
#	define MODULE_API SHARED_EXPORT
#else
#	define MODULE_API SHARED_IMPORT
#endif

namespace module
{
	struct guid;
	struct IUnknown;
	struct IClassFactory;
	class Exception;
}

#endif //_MODULE_FWD_H__
