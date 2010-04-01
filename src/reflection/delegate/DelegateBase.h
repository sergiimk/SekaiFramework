/*========================================================
* DelegateBase.h
* @author Sergey Mikhtonyuk
* @date 19 September 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _DELEGATEBASE_H__
#define _DELEGATEBASE_H__

namespace reflection
{
	#define DELEG_MAX_INVOKE_PARAMS 8

	class DelegateBase
	{
	};

	typedef void (*generic_invoker)(DelegateBase*, void**, void*);

} // namespace

#endif // _DELEGATEBASE_H__
