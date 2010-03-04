/*========================================================
* threading.h
* @author Sergey Mikhtonyuk
* @date 22 April 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _THREADING_H__
#define _THREADING_H__

//////////////////////////////////////////////////////////////////////////

#include "platform/platform.h"

#if defined (COMPILER_MSC)
#	include <intrin.h>
#endif

//////////////////////////////////////////////////////////////////////////

namespace Utils
{

	//////////////////////////////////////////////////////////////////////////

	/// Thread-safe increment
	/** @ingroup Utils */
	inline void AtomicIncrement(volatile long* pl)
	{
		#if defined (COMPILER_MSC)
			_InterlockedIncrement(pl);
		#elif defined (COMPILER_GNUC)
			int r;
			asm volatile (

			"lock ; xaddl %0, (%1) \n\t"
			: "=r" (r)
			: "r" (pl), "0" (1)
			: "memory"

			);
		#else
			#error no suitable implementation for your compiler
		#endif
	}

	//////////////////////////////////////////////////////////////////////////

	/// Thread-safe decrement
	/** @ingroup Utils */
	inline void AtomicDecrement(volatile long* pl)
	{
		#if defined (COMPILER_MSC)
			_InterlockedDecrement(pl);
		#elif defined (COMPILER_GNUC)
			int r;
			asm volatile (

			"lock ; xaddl %0, (%1) \n\t"
			: "=r" (r)
			: "r" (pl), "0" (-1)
			: "memory"

			);
		#else
			#error no suitable implementation for your compiler
		#endif
	}

} // namespace

#endif // _THREADING_H__
