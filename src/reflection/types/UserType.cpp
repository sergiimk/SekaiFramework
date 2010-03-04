/*========================================================
* UserType.cpp
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "UserType.h"
#include "descriptors/BaseType.h"
#include "descriptors/FieldDescriptor.h"
#include "descriptors/AccessorDescriptor.h"
#include "descriptors/MethodDescriptor.h"
#include "descriptors/EnumerationDescriptor.h"
#include "descriptors/ParsingDescriptor.h"
#include "descriptors/ConstructDescriptor.h"
#include "descriptors/AssignmentDescriptor.h"
#include "platform/platform.h"

#include <algorithm>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	UserType::UserType()
		: mTypeDesc(0)
		, mDescriptors(0)
	{ }

	//////////////////////////////////////////////////////////////////////////

	void UserType::_init(detail::type_desc_base* desc)
	{
		if(mTypeDesc)
			return;

		mTypeDesc = desc;
		mDescriptors = desc->initialize(this, mDescSize);
		sortDescs();
	}

	//////////////////////////////////////////////////////////////////////////

	UserType::~UserType()
	{
		for(size_t i = 0; i != mDescSize; ++i)
		{
			delete mDescriptors[i];
			mDescriptors[i] = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	TypeDescriptor* UserType::FindService(DescriptorType type) const
	{
		for(size_t i = mFirstService; i != mDescSize; ++i)
			if(mDescriptors[i]->getDescriptorType() == type)
				return mDescriptors[i];
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	ConstructDescriptor* UserType::FindSuitableCtor(Type* args_t[], size_t argc) const
	{
		for(size_t i = mFirstService; i != mDescSize; ++i)
		{
			if(mDescriptors[i]->getDescriptorType() != RL_DESC_SERVICE_CONSTRUCT)
				continue;

			ConstructDescriptor* desc = static_cast<ConstructDescriptor*>(mDescriptors[i]);
			FunctionType* tctor = desc->GetCtorType();

			size_t tnargs = tctor->getArgumentNumber();
			Type** argTypes = tctor->getArgumentTypes();

			if(tnargs != argc)
				continue;

			for(size_t t = 0; t != tnargs; ++t)
				if(!argTypes[t]->Equal(args_t[t]))
					continue;

			return desc;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void* UserType::CreateInstance() const
	{
		ConstructDescriptor* ctor = FindSuitableCtor(0, 0);
		if(!ctor) return 0;

		return ctor->CreateInstance(0);
	}

	//////////////////////////////////////////////////////////////////////////

	void UserType::DestroyInstance(void* v) const
	{
		ConstructDescriptor* ctor = static_cast<ConstructDescriptor*>(FindService(RL_DESC_SERVICE_CONSTRUCT));
		if(ctor) ctor->DestroyInstance(v);
	}

	//////////////////////////////////////////////////////////////////////////

	size_t UserType::Name(char *buf, size_t size) const
	{
		int pos = 0;
		for(int i = 0; mTypeDesc->name[i] != '\0'; ++i)
			if(mTypeDesc->name[i] == ':')
				pos = i + 1;

		strncpy(buf, &mTypeDesc->name[pos], size);
		return strlen(buf) + 1;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t UserType::FullName(char *buf, size_t size) const
	{
		strncpy(buf, mTypeDesc->name, size);
		return strlen(buf);
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::Equal(const Type* other) const
	{
		if(this == other)
			return true;

		if(ArchType() != other->ArchType())
			return false;

		char buf1[255];
		char buf2[255];

		size_t p1 = FullName(buf1, 255);
		size_t p2 = other->FullName(buf2, 255);

		if(p1 != p2)
			return false;

		return strcmp(buf1, buf2) == 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void UserType::Assign(void *to, void *val) const
	{
		AssignmentDescriptor* asng = static_cast<AssignmentDescriptor*>(FindService(RL_DESC_SERVICE_ASSIGN));
		if(asng)
			asng->Assign(to, val);
		else
			memcpy(to, val, Size());
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::ToString(void* value, char* buf, size_t size) const
	{
		return mTypeDesc->tag == RL_T_ENUM
			? EnumToString(value, buf, size)
			: DescToString(value, buf, size);
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::DescToString(void* value, char* buf, size_t size) const
	{
		ParsingDescriptor* parse = static_cast<ParsingDescriptor*>(FindService(RL_DESC_SERVICE_PARSING));
		return parse ? parse->ToString(value, buf, size) : false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::EnumToString(void* value, char* buf, size_t size) const
	{
		EnumerationDescriptor* en = static_cast<EnumerationDescriptor*>(FindService(RL_DESC_SERVICE_ENUMERATION));
		if(en)
		{
			const char* name = en->getNameByValue(*(unsigned int*)value);
			if(name)
			{
				size_t len = strlen(name);
				strncpy(buf, name, std::min(len + 1, size));
				return size > len;
			}
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::TryParse(void * value, const char* str) const
	{
		return mTypeDesc->tag == RL_T_ENUM
			? EnumTryParse(value, str)
			: DescTryParse(value, str);
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::DescTryParse(void * value, const char* str) const
	{
		ParsingDescriptor* parse = static_cast<ParsingDescriptor*>(FindService(RL_DESC_SERVICE_PARSING));
		return parse ? parse->TryParse(value, str) : false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::EnumTryParse(void * value, const char* str) const
	{
		EnumerationDescriptor* en = static_cast<EnumerationDescriptor*>(FindService(RL_DESC_SERVICE_ENUMERATION));
		if(en)
		{
			unsigned int v;
			if(en->getValueByName(str, v))
			{
				*(unsigned int*)value = v;
				return true;
			}
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	static bool cmp_tag(TypeDescriptor* lhs, TypeDescriptor* rhs)
	{
		return lhs->getDescriptorType() < rhs->getDescriptorType();
	}

	//////////////////////////////////////////////////////////////////////////

	void UserType::sortDescs()
	{
		if(!mDescriptors) return;

		std::sort(&mDescriptors[0], &mDescriptors[mDescSize], cmp_tag);

		DescriptorType lt = RL_DESC_BASE;
		mFirstField = mFirstMethod = mFirstAccessor = mFirstService = mDescSize;
		for(size_t i = 0; i != mDescSize; ++i)
		{
			if(lt != RL_DESC_FIELD && mDescriptors[i]->getDescriptorType() == RL_DESC_FIELD)
			{
				mFirstField = i;
				lt = RL_DESC_FIELD;
			}
			else if(lt != RL_DESC_METHOD && mDescriptors[i]->getDescriptorType() == RL_DESC_METHOD)
			{
				mFirstMethod = i;
				lt = RL_DESC_METHOD;
			}
			else if(lt != RL_DESC_ACCESSOR && mDescriptors[i]->getDescriptorType() == RL_DESC_ACCESSOR)
			{
				mFirstAccessor = i;
				lt = RL_DESC_ACCESSOR;
			}
			else if(lt < RL_DESC_SERVICE_PARSING && mDescriptors[i]->getDescriptorType() > RL_DESC_ACCESSOR)
			{
				mFirstService = i;
				lt = RL_DESC_SERVICE_PARSING;
			}
		}

		if(mFirstAccessor == mDescSize) mFirstAccessor = mFirstService;
		if(mFirstMethod == mDescSize) mFirstMethod = mFirstAccessor;
		if(mFirstField == mDescSize) mFirstField = mFirstMethod;
	}

	//////////////////////////////////////////////////////////////////////////

	BaseType* UserType::getBaseTypeDescriptor(size_t index) const
	{
		ASSERT_STRICT(index < mFirstField && mDescriptors[index]->getDescriptorType() == RL_DESC_BASE);
		if(index >= mFirstField) return 0;
		return static_cast<BaseType*>(mDescriptors[index]);
	}

	//////////////////////////////////////////////////////////////////////////

	FieldDescriptor* UserType::getFieldDescriptor(size_t index) const
	{
		index += mFirstField;
		assert(index < mFirstMethod && mDescriptors[index]->getDescriptorType() == RL_DESC_FIELD);
		return static_cast<FieldDescriptor*>(mDescriptors[index]);
	}

	//////////////////////////////////////////////////////////////////////////

	MethodDescriptor* UserType::getMethodDescriptor(size_t index) const
	{
		index += mFirstMethod;
		assert(index < mDescSize && mDescriptors[index]->getDescriptorType() == RL_DESC_METHOD);
		return static_cast<MethodDescriptor*>(mDescriptors[index]);
	}

	//////////////////////////////////////////////////////////////////////////

	AccessorDescriptor* UserType::getAccessorDescriptor(size_t index) const
	{
		index += mFirstAccessor;
		assert(index < mDescSize && mDescriptors[index]->getDescriptorType() == RL_DESC_ACCESSOR);
		return static_cast<AccessorDescriptor*>(mDescriptors[index]);
	}

	//////////////////////////////////////////////////////////////////////////

	TypeDescriptor* UserType::getServiceDescriptor(size_t index) const
	{
		index += mFirstService;
		assert(index < mDescSize);
		return mDescriptors[index];
	}

	//////////////////////////////////////////////////////////////////////////

	UserType* UserType::FindBaseType(const char* name, bool recursive) const
	{
		for(size_t i = 0; i != mFirstField; ++i)
		{
			if(strcmp(name, mDescriptors[i]->getName()) == 0)
				return getBaseTypeDescriptor(i)->getBaseType();
		}

		if(!recursive) return 0;

		for(size_t i = 0; i != mFirstField; ++i)
		{
			UserType* base = getBaseTypeDescriptor(i)->getBaseType();
			UserType* ret = base->FindBaseType(name, recursive);
			if(ret) return ret;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	Field UserType::FindField(const char* name, bool recursive, size_t offset) const
	{
		for(size_t i = mFirstField; i != mFirstMethod; ++i)
		{
			if(strcmp(name, mDescriptors[i]->getName()) == 0)
			{
				assert(mDescriptors[i]->getDescriptorType() == RL_DESC_FIELD);
				FieldDescriptor* desc = static_cast<FieldDescriptor*>(mDescriptors[i]);
				return Field(desc, offset);
			}
		}

		if(!recursive) return Field();

		for(size_t i = 0; i != mFirstField; ++i)
		{
			BaseType* baseDesc = getBaseTypeDescriptor(i);
			UserType* base = baseDesc->getBaseType();
			Field ret = base->FindField(name, true, offset + baseDesc->getThisOffset());
			if(ret.isValid()) return ret;
		}

		return Field();
	}

	//////////////////////////////////////////////////////////////////////////

	Method UserType::FindMethod(const char* name, bool recursive, size_t offset) const
	{
		for(size_t i = mFirstMethod; i != mFirstAccessor; ++i)
		{
			if(strcmp(name, mDescriptors[i]->getName()) == 0)
			{
				assert(mDescriptors[i]->getDescriptorType() == RL_DESC_METHOD);
				MethodDescriptor* desc = static_cast<MethodDescriptor*>(mDescriptors[i]);
				return Method(desc, offset);
			}
		}

		if(!recursive) return Method();

		for(size_t i = 0; i != mFirstField; ++i)
		{
			BaseType* baseDesc = getBaseTypeDescriptor(i);
			UserType* base = baseDesc->getBaseType();
			Method ret = base->FindMethod(name, recursive, offset + baseDesc->getThisOffset());
			if(ret.isValid()) return ret;
		}

		return Method();
	}

	//////////////////////////////////////////////////////////////////////////

	Accessor UserType::FindAccessor(const char* name, bool recursive, size_t offset) const
	{
		for(size_t i = mFirstAccessor; i != mDescSize; ++i)
		{
			if(strcmp(name, mDescriptors[i]->getName()) == 0)
			{
				assert(mDescriptors[i]->getDescriptorType() == RL_DESC_ACCESSOR);
				AccessorDescriptor* desc = static_cast<AccessorDescriptor*>(mDescriptors[i]);
				return Accessor(desc, offset);
			}
		}

		if(!recursive) return Accessor();

		for(size_t i = 0; i != mFirstField; ++i)
		{
			BaseType* baseDesc = getBaseTypeDescriptor(i);
			UserType* base = baseDesc->getBaseType();
			Accessor ret = base->FindAccessor(name, recursive, offset + baseDesc->getThisOffset());
			if(ret.isValid()) return ret;
		}

		return Accessor();
	}

	//////////////////////////////////////////////////////////////////////////

	size_t UserType::MeasureOffsetOfBase(UserType *tDerived, UserType *tParent)
	{
		if(tDerived->Equal(tParent))
			return 0;

		size_t nBase = tDerived->getBaseTypeNumber();

		for(size_t i = 0; i != nBase; ++i)
		{
			size_t offset = MeasureOffsetRecursive(tParent, tDerived->getBaseTypeDescriptor(i), 0);
			if(offset != (size_t)-1)
				return offset;
		}

		return (size_t)-1;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t UserType::MeasureOffsetRecursive(UserType *tParent, BaseType* baseDesc, size_t offset)
	{
		UserType* tBase = baseDesc->getBaseType();

		offset += baseDesc->getThisOffset();

		if(tParent->Equal(tBase))
			return offset;

		size_t nBase = tBase->getBaseTypeNumber();
		for(size_t i = 0; i != nBase; ++i)
		{
			size_t res = MeasureOffsetRecursive(tParent, tBase->getBaseTypeDescriptor(i), offset);
			if(res != (size_t)-1)
				return res;
		}

		return (size_t)-1;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
