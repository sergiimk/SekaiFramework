/*========================================================
* NonCopyable.h
* @author Sergey Mikhtonyuk
* @date 15 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _NONCOPYABLE_H__
#define _NONCOPYABLE_H__

namespace Utils
{
	/// Base class for non-copyable objects
	/** @ingroup Common */
	class NonCopyable
	{
	protected:
		///
		NonCopyable() {}
		///
		~NonCopyable() {}

	private:
		///
		NonCopyable(const NonCopyable&);
		///
		const NonCopyable& operator=(const NonCopyable&);
	};	

} // namespace


#endif // _NONCOPYABLE_H__