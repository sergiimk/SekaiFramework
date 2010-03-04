/*========================================================
* stringutils.h
* @author Sergey Mikhtonyuk
* @date 30 March 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
/** @defgroup Common Common
 *  Commonly used utilities */

#ifndef _STRINGUTILS_H__
#define _STRINGUTILS_H__

#include "platform/platform.h"
#include <functional>
#include <exception>
#include <string.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

#ifdef stricmp
#	undef stricmp
#endif

#if defined (COMPILER_MSC)
#	define stricmp _stricmp
#elif defined (COMPILER_GNUC)
#   include <strings.h>
#   define stricmp strcasecmp
#endif

//////////////////////////////////////////////////////////////////////////

//! Equality comparer for char* (case sensitive)
/** @ingroup Common */
struct cstrcmp_eq : public std::binary_function<const char*, const char*, bool>
{
	bool operator () (const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) == 0;
	}
};

//! Equality comparer for char* (case insensitive)
/** @ingroup Common */
struct cstricmp_eq : public std::binary_function<const char*, const char*, bool>
{
	bool operator () (const char* s1, const char* s2) const
	{
		return stricmp(s1, s2) == 0;
	}
};

//////////////////////////////////////////////////////////////////////////

//! Less comparer for char* (case sensitive)
/** @ingroup Common */
struct cstrcmp_less : public std::binary_function<const char*, const char*, bool>
{
	bool operator () (const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

//! Less comparer for char* (case insensitive)
/** @ingroup Common */
struct cstricmp_less : public std::binary_function<const char*, const char*, bool>
{
	bool operator () (const char* s1, const char* s2) const
	{
		return stricmp(s1, s2) < 0;
	}
};

//////////////////////////////////////////////////////////////////////////

/// Hashing functor for char* (case sensitive)
/** @ingroup Common */
struct cstr_hash
{
	size_t operator() (const char* s) const
    {
		unsigned long h = 0;
		for ( ; *s; ++s)
		{
			char c = *s;
			h = 5 * h + c;
		}
		return size_t(h);
	}
};

//////////////////////////////////////////////////////////////////////////

/// Hashing functor for char* (case sensitive)
/** @ingroup Common */
struct str_hash
{
	size_t operator() (const std::string& s) const
    {
		cstr_hash h;
		return h(s.c_str());
	}
};

//////////////////////////////////////////////////////////////////////////

#endif // _STRINGUTILS_H__
