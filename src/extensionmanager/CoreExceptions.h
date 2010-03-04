/*========================================================
* CoreExceptions.h
* @author Sergey Mikhtonyuk
* @date 28 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _COREEXCEPTIONS_H__
#define _COREEXCEPTIONS_H__

#include "common/exceptions.h"

namespace Extensions
{
	/// Base class for all exception generated in core
	/** @ingroup Extensions */
	class CoreException : public framework_exception
	{
	public:
		CoreException() { }
		CoreException(const char* msg) : framework_exception(msg) { }
	};

	/// Exception generated during the plug-in shadow loading
	/** @ingroup Extensions */
	class ParsingException : public CoreException
	{
	public:
		ParsingException() { }
		ParsingException(const char* msg) : CoreException(msg) { }
	};

} // namespace


#endif // _COREEXCEPTIONS_H__
