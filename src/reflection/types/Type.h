/*========================================================
* Type.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPE_H__
#define _TYPE_H__

#include "TypeTag.h"
#include "../reflection_fwd.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Reflected type of the object
	/** @ingroup Reflection */
	class Type
	{
	public:
		virtual ~Type() { }

		/// Writes type name to the buffer with specified size
		/** @return number of characters written */
		virtual size_t Name(char* buf, size_t size) const = 0;

		/// Writes fully-qualified type name to the buffer with specified size
		/** @return number of characters written */
		virtual size_t FullName(char* buf, size_t size) const = 0;

		/// Tag of the type
		virtual ETypeTag Tag() const = 0;

		/// Returns the arch-type of this type
		virtual EArchType ArchType() const = 0;

		/// Size of the type object
		virtual size_t Size() const = 0;


		/// Assigns value to variable
		virtual void Assign(void* to, void* val) const = 0;

		/// Converts value of this type to string
		virtual bool ToString(void* value, char* buf, size_t size) const = 0;

		/// Tries to reconstruct value from string
		virtual bool TryParse(void * value, const char* str) const = 0;

		/// Compares types for equality
		virtual bool Equal(const Type* other) const = 0;

		/// Creates instance of user type
		virtual void* CreateInstance() const = 0;

		/// Destroys instance of user type
		virtual void DestroyInstance(void* v) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Value pointer - Type pair, used for invoking the function in script
	/** @ingroup Script */
	struct ValueTypePair
	{
		void* pValue;
		Type* pType;

		ValueTypePair() : pValue(0), pType(0) { }
		ValueTypePair(void* val, Type* t) : pValue(val), pType(t) { }
	};

	template<typename T>
	inline ValueTypePair make_typed_pair(T& value)
	{
		return ValueTypePair(&value, type_of<T>());
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _TYPE_H__
