/*========================================================
* Logging.h
* @author Sergey Mikhtonyuk
* @date 13 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _LOGGING_H__
#define _LOGGING_H__

#include "ILogService.h"
#include "ILogListener.h"

namespace Logging
{

	// {af7a6c3a-d711-4cad-903c-f4b2685e7b31} 
	static const module::guid CLSID_CLogService = 
	{ 0xaf7a6c3a, 0xd711, 0x4cad, { 0x90, 0x3c, 0xf4, 0xb2, 0x68, 0x5e, 0x7b, 0x31 } };

} // namespace

#endif // _LOGGING_H__
