/*========================================================
* hash_set.h
* @author Sergey Mikhtonyuk
* @date 23 Feb 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "platform/platform.h"

#if defined (STDLIB_STLPORT)

	#include <hash_set>

#elif defined (STDLIB_MS)

	#include <hash_set>

	namespace std
	{
		using stdext::hash_set;
		using stdext::hash_multiset;
	}

#elif defined (STDLIB_GNU)

	#include <hash_set>

	namespace std
	{
		using __gnu_cxx::hash_set;
		using __gnu_cxx::hash_multiset;
	}

#else

	#error not supported stdlib

#endif
