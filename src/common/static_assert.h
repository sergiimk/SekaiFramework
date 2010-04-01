/*========================================================
* static_assert.h
* @author Sergey Mikhtonyuk
* @date 30 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _STATIC_ASSERT_H__
#define _STATIC_ASSERT_H__

#define static_assert(expr, msg)   \
	extern char STATIC_ASSERTION[1]; \
	extern char STATIC_ASSERTION[(expr)?1:2]

#endif //_STATIC_ASSERT_H__
