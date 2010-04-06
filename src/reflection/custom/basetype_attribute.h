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
		base_type(user_type* base, size_t this_offset);

		/// Returns base type
		user_type* get_base() const;

		/// Returns offset of 'this' pointer from base class
		size_t get_offset() const;

		virtual base_type* clone() const;

		virtual void release();

	private:
		struct base_type_impl;
		base_type_impl* m_impl;

		base_type(base_type_impl* impl);
	};
	
} // namespace

#endif //_BASETYPE_ATTRIBUTE_H__
