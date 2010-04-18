/*========================================================
* ThreadingModel.h
* @author Sergey Mikhtonyuk
* @date 22 April 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _THREADINGMODEL_H__
#define _THREADINGMODEL_H__

#include "threading/threading.h"

namespace module
{
	//! Single-threading model for ComRootObject
	/** @ingroup module */
	struct SingleThreadModel
	{
		static void Increment(long& l) { ++l; }
		static void Decrement(long& l) { --l; }
	};

	//! Multi-threading model for ComRootObject
	/** @ingroup module */
	struct MultiThreadModel
	{
		static void Increment(long& l) { Utils::AtomicIncrement(&l); }
		static void Decrement(long& l) { Utils::AtomicDecrement(&l); }
	};	
} // namespace

#endif // _THREADINGMODEL_H__
