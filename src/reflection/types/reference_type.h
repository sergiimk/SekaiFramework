/*========================================================
* reference_type.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _REFERENCETYPE_H__
#define _REFERENCETYPE_H__

#include "types/Type.h"

namespace reflection
{
	/// Reference type class
	/** @ingroup reflection */
	class REFLECTION_API reference_type : public type
	{
	public:

		reference_type(type* pointee);

		/// Returns type this one references
		type* referenced_type() const;

	private:
		struct reference_type_impl;
		reference_type_impl* m_impl;
	};

} // namespace

#endif //_REFERENCETYPE_H__
