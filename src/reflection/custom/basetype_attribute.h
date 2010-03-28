/*========================================================
* basetype_attribute.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _BASETYPE_ATTRIBUTE_H__
#define _BASETYPE_ATTRIBUTE_H__

#include "attribute.h"

namespace reflection
{
	/// Attribute that links types with inheritance relationships
	/** @ingroup reflection */
	class REFLECTION_API base_type : public attribute
	{
	public:
		base_type(type* base);

		/// Returns base type
		type* get_base() const;

	private:
		struct base_type_impl;
		base_type_impl* m_impl;
	};
	
} // namespace

#endif //_BASETYPE_ATTRIBUTE_H__
