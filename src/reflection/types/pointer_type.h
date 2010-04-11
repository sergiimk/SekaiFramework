/*========================================================
* pointer_type.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _POINTERTYPE_H__
#define _POINTERTYPE_H__

#include "types/type.h"

namespace reflection
{
	/// Pointer type class
	/** @ingroup reflection */
	class REFLECTION_API pointer_type : public type
	{
	public:
		pointer_type(type* pointee);

		/// Returns type this one points to
		type* pointee_type() const;

		virtual bool equal(const type* other) const;

	private:
		struct pointer_type_impl;
		pointer_type_impl* m_impl;
	};

} // namespace

#endif //_POINTERTYPE_H__
