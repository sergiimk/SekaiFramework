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
// guid hashing and comparing
//////////////////////////////////////////////////////////////////////////

#if defined(_SF_GUID_H__)

namespace module
{
    /// guid hash functor
    /** @ingroup Common */
    struct guid_hash
    {
        size_t operator() (const guid& g) const
        {
            unsigned long val;
            val = g.data1 ^ g.data2 ^ g.data3;
            for(int i = 0; i < 8; i += sizeof(unsigned long))
                val ^= (unsigned long)g.data4[i];
            return size_t(val);
        }
    };
} // namespace

#endif

//////////////////////////////////////////////////////////////////////////

namespace stl
{

	//////////////////////////////////////////////////////////////////////////

	struct hash_ptr
	{
		size_t operator()(void* p) const { return (size_t)p; }
	};

	//////////////////////////////////////////////////////////////////////////

	template<class T = module::IUnknown>
	struct fn_release
	{
		void operator()(T *itf) const { itf->Release(); }
	};

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	struct fn_delete
	{
		void operator()(T *ptr) const { delete ptr; }
		void operator()(T &ref) const { delete &ref; }
	};

	//////////////////////////////////////////////////////////////////////////

}

//////////////////////////////////////////////////////////////////////////

#endif //_STLUTILS_H__
