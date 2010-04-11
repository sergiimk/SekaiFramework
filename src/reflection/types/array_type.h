/*========================================================
* array_type.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ARRAYTYPE_H__
#define _ARRAYTYPE_H__

#include "types/type.h"

namespace reflection
{
	/// Array type class
	/** @ingroup reflection */
	class REFLECTION_API array_type : public type
	{
	public:
		array_type(type* elem_type, size_t length);

		/// Type of array element
		type* element_type() const;

		/// Length of array
		size_t length() const;

		virtual bool equal(const type* other) const;

	private:
		struct array_type_impl;
		array_type_impl* m_impl;
	};

} // namespace

#endif //_ARRAYTYPE_H__
