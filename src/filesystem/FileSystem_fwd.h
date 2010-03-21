/*========================================================
* filesystem_fwd.h
* @author Sergey Mikhtonyuk
* @date 20 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _FILESYSTEM_FWD_H__
#define _FILESYSTEM_FWD_H__

#include "platform/platform.h"

#if defined BUILD_SHARED
#	define FILESYSTEM_API SHARED_EXPORT
#else
#	define FILESYSTEM_API SHARED_IMPORT
#endif

namespace filesystem
{
	
	class path;
	class directory_iterator;

} // namespace

#endif //_FILESYSTEM_FWD_H__
