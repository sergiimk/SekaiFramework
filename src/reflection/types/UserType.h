/*========================================================
* UserType.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _USERTYPE_H__
#define _USERTYPE_H__

#include "Type.h"
#include "../descriptors/TypeDescriptor.h"
#include "../descriptors/typedesc.h"
#include "../reflection_fwd.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Type specification for user-defined types (classes, structures and enums)
	/** @ingroup Reflection */
	class UserType : public Type
	{
	public:

		//////////////////////////////////
#		include "UserType_iterators.h"
		//////////////////////////////////

		UserType();

		void _init(detail::type_desc_base* desc);

		~UserType();

		size_t Name(char* buf, size_t size) const;

		size_t FullName(char* buf, size_t size) const;

		ETypeTag Tag() const { return mTypeDesc->tag; }

		EArchType ArchType() const { return RL_ARCH_USERDEFINED; }

		size_t Size() const { return mTypeDesc->size; }

		void Assign(void* to, void* val) const;

		bool ToString(void* value, char* buf, size_t size) const;

		bool TryParse(void * value, const char* str) const;

		bool Equal(const Type* other) const;

		void* CreateInstance() const;

		void DestroyInstance(void* v) const;

		/// Searches for the specified service descriptor
		TypeDescriptor* FindService(DescriptorType type) const;

		/// Returns number of base classes of this type
		size_t getBaseTypeNumber() const { return mFirstField; }

		/// Returns number of fields of this type (without inherited)
		size_t getFieldNumber() const { return mFirstMethod - mFirstField; }

		/// Returns number of methods of this type (without inherited)
		size_t getMethodNumber() const { return mFirstAccessor - mFirstMethod; }

		/// Returns number of accessors of this type (without inherited)
		size_t getAccessorNumber() const { return mFirstService - mFirstAccessor; }

		/// Returns the number of service descriptors
		size_t getServiceNumber() const { return mDescSize - mFirstService; }

		/// Returns the specified base type
		BaseType* getBaseTypeDescriptor(size_t index) const;

		/// Returns the specified field
		FieldDescriptor* getFieldDescriptor(size_t index) const;

		/// Returns the specified method
		MethodDescriptor* getMethodDescriptor(size_t index) const;

		/// Returns the specified accessor
		AccessorDescriptor* getAccessorDescriptor(size_t index) const;

		/// Returns the service descriptor at specified index
		TypeDescriptor* getServiceDescriptor(size_t index) const;

		/// Searches the base class by its name
		/** @param recursive specifies if indirect base classes should be considered */
		UserType* FindBaseType(const char* name, bool recursive = true) const;

		/// Searches construction descriptor with matching parameter set
		ConstructDescriptor* FindSuitableCtor(Type* args_t[], size_t argc) const;

		/// Searches the field by its name
		/** @param recursive specifies if inherited fields should be considered */
		Field FindField(const char* name, bool recursive = true, size_t offset = 0) const;

		/// Searches the method by its name
		/** @param recursive specifies if inherited methods should be considered */
		Method FindMethod(const char* name, bool recursive = true, size_t offset = 0) const;

		/// Searches the accessor by its name
		/** @param recursive specifies if inherited accessors should be considered */
		Accessor FindAccessor(const char* name, bool recursive = true, size_t offset = 0) const;

		/// Calculates the offset of 'this' pointer of base class
		/** @return (size_t)-1 on error */
		static size_t MeasureOffsetOfBase(UserType* tDerived, UserType* tParent);

	private:
		static size_t MeasureOffsetRecursive(UserType *tParent, BaseType* baseDesc, size_t offset);
		bool DescToString(void* value, char* buf, size_t size) const;
		bool EnumToString(void* value, char* buf, size_t size) const;
		bool DescTryParse(void * value, const char* str) const;
		bool EnumTryParse(void * value, const char* str) const;
		void sortDescs();

	private:
		detail::type_desc_base*		mTypeDesc;
		TypeDescriptor**			mDescriptors;
		size_t						mDescSize;
		size_t						mFirstField; // position of first field (end of base classes)
		size_t						mFirstMethod; // first method (and last field)
		size_t						mFirstAccessor; // first accessor (and last method)
		size_t						mFirstService; // first service descriptor (and last accessor)
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _USERTYPE_H__
