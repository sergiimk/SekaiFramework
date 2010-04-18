/*========================================================
* type.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPE_H__
#define _TYPE_H__

#include "../reflection_fwd.h"
#include "../types/typetag.h"
#include <iterator>

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Type information class
	/** @ingroup reflection */
	class REFLECTION_API type
	{
	public:

		#include "type_iters.inc"

		type(ETypeTag tag, EArchType arch, size_t size);

		virtual ~type();

		/// Tag of the type
		ETypeTag tag() const;

		/// Returns the arch-type of this type
		EArchType arch_type() const;

		/// Size of the instance of this type
		size_t size() const;

		/// Returns the name of the type
		const char* name() const;

		/// Checks whether two types are equal
		virtual bool equal(const type* other) const;

	private:
		type(const type& other);
		type& operator=(const type& rhs);

	protected:

		virtual size_t _attribute_count() const;
		virtual const attribute* _get_attribute(size_t i) const;

		class type_impl;

		/// Derived classes can specify own impl
		type(type_impl* impl);

		void set_name(const char* name);

		type_impl* m_impl;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Value pointer - Type pair
	/** @ingroup reflection */
	struct value_type_pair
	{
		void* Value;
		const type* Type;

		value_type_pair() : Value(0), Type(0) { }
		value_type_pair(void* val, const type* t) : Value(val), Type(t) { }
	};

	template<typename T>
	inline value_type_pair make_typed_pair(T& value)
	{
		return value_type_pair(&value, type_of<T>());
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_TYPE_H__
