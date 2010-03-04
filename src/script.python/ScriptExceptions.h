/*========================================================
* ScriptExceptions.h
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SCRIPTEXCEPTIONS_H__
#define _SCRIPTEXCEPTIONS_H__

#include "common/exceptions.h"

namespace Script
{

	/// Base class for all exceptions generated in script system
	/** @ingroup Script */
	class ScriptException : public framework_exception
	{
	public:
		ScriptException() { }
		ScriptException(const char* msg) : framework_exception(msg) { }
	};

} // namespace

#endif // _SCRIPTEXCEPTIONS_H__
