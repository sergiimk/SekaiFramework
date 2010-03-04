/*========================================================
 * FSExceptions.h
 * @author Sergey Mikhtonyuk
 * @date 01 May 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _FSEXCEPTIONS_H__
#define _FSEXCEPTIONS_H__

#include "common/exceptions.h"

namespace FileSystem
{

	/// Base class for all exceptions generated in file system
	/** @ingroup FileSystem */
	class FSException : public framework_exception
	{
	public:
		FSException() { }
		FSException(const char* msg) : framework_exception(msg) { }
	};

	//////////////////////////////////////////////////////////////////////////

	/// Generated in adapters when parsing fails
	/** @ingroup FileSystem */
	class FSParsingException : public FSException
	{
	public:
		FSParsingException() { }
		FSParsingException(const char* msg) : FSException(msg) { }
	};

} // namespace

#endif	// _FSEXCEPTIONS_H__
