/*========================================================
* ArrayType.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ARRAYTYPE_H__
#define _ARRAYTYPE_H__

#include "Type.h"
#include "platform/platform.h"

namespace Reflection
{

	//////////////////////////////////////////////////////////////////////////

	/// Specification for array types
	/** @ingroup Reflection */
	class ArrayType : public Type
	{
	public:
		ArrayType(Type* elemType, int elems);

		size_t Name(char* buf, size_t size) const;

		size_t FullName(char* buf, size_t size) const;

		ETypeTag Tag() const { return RL_T_ARRAY; }

		EArchType ArchType() const { return RL_ARCH_ARRAY; }

		size_t Size() const { return mElem ? mElem->Size() * mElemCount : 0; }

		void Assign(void* to, void* val) const { NOT_IMPLEMENTED(); }

		bool ToString(void* value, char* buf, size_t size) const;

		bool TryParse(void * value, const char* str) const { return false; }

		/// Returns the type of array elements
		Type* getElementType() const { return mElem; }

		/// Returns the number of elements in array
		int getElementNumber() const { return mElemCount; }

		bool Equal(const Type* other) const;

		void* CreateInstance() const { NOT_IMPLEMENTED(); }

		void DestroyInstance(void* v) const { }

	private:
		int		mElemCount;
		Type*	mElem;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ARRAYTYPE_H__