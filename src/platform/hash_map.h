/*========================================================
* hash_map.h
* @author Sergey Mikhtonyuk
* @date 23 Feb 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "platform/platform.h"

#if defined (STDLIB_STLPORT)

	#include <hash_map>

#elif defined (STDLIB_MS)

	#include <hash_map>

	namespace std
	{
		using stdext::hash_map;
		using stdext::hash_multimap;
	}

#elif defined (STDLIB_GNU)

	#include <hash_map>

	namespace std
	{
		using __gnu_cxx::hash_map;
		using __gnu_cxx::hash_multimap;
	}

#else

	#error not supported stdlib

#endif
