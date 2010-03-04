/*========================================================
* PointerType.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _POINTERTYPE_H__
#define _POINTERTYPE_H__

#include "Type.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////
	
	/// Type specification for pointer types
	/** @ingroup Reflection */
	class PointerType : public Type
	{
	public:
		PointerType(Type* pointedType) : mPointed(pointedType)
		{ }

		size_t Name(char* buf, size_t size) const;

		size_t FullName(char* buf, size_t size) const;

		ETypeTag Tag() const { return RL_T_POINTER; }

		EArchType ArchType() const { return RL_ARCH_POINTER; }

		size_t Size() const { return sizeof(void*); }

		void Assign(void* to, void* val) const;

		bool ToString(void* value, char* buf, size_t size) const;

		bool TryParse(void * value, const char* str) const { return false; }

		/// Returns the type it points to
		Type* getPointedType() const { return mPointed; }

		bool Equal(const Type* other) const;

		void* CreateInstance() const { return new void*; }

		void DestroyInstance(void* v) const { delete ((void**)v); }

	private:

		Type* mPointed;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _POINTERTYPE_H__
