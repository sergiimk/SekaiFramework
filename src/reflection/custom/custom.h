/*========================================================
* custom.h
* @author Sergey Mikhtonyuk
* @date 29 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CUSTOM_H__
#define _CUSTOM_H__

#include "types/user_type.h"

namespace reflection
{

	namespace detail
	{
		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct type_desc
		{			
			user_type* get_type() { return 0; }
		};

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		
	} // namespace
	
} // namespace

#endif //_CUSTOM_H__
