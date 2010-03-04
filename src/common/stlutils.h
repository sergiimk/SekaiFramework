/*========================================================
* stringutils.h
* @author Sergey Mikhtonyuk
* @date 30 March 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _STLUTILS_H__
#define _STLUTILS_H__

#include "platform/platform.h"

//////////////////////////////////////////////////////////////////////////
// GUID hashing and comparing
//////////////////////////////////////////////////////////////////////////

#if defined(_SF_GUID_H__)

namespace Module
{
    /// GUID hash functor
    /** @ingroup Common */
    struct guid_hash
    {
        size_t operator() (const GUID& guid) const
        {
            unsigned long val;
            val = guid.Data1 ^ guid.Data2 ^ guid.Data3;
            for(int i = 0; i < 8; i += sizeof(unsigned long))
                val ^= (unsigned long)guid.Data4[i];
            return size_t(val);
        }
    };
} // namespace

#endif

//////////////////////////////////////////////////////////////////////////

struct hash_ptr
{
    size_t operator()(void* p) const
	{
		return (size_t)p;
	}
};

//////////////////////////////////////////////////////////////////////////

#endif //_STLUTILS_H__
