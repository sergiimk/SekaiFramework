/*========================================================
* FunctionType.cpp
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "FunctionType.h"
#include "typetraits.h"
#include "platform/platform.h"

#include <string.h>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	FunctionType::FunctionType(GenericInvoker inv, bool isMethod, Type* rt, Type** arguments, int argc)
		: mIsMethod(isMethod), mInvoker(inv), mReturnType(rt)
	{
		ASSERT_STRICT(rt);

		memset(mArguments, 0, sizeof(void*) * (DELEG_MAX_INVOKE_PARAMS + 1));
		memcpy(mArguments, arguments, sizeof(void*) * argc);

		for(int i = 0; i < argc; ++i)
		{
			ASSERT_STRICT(arguments[i]);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	FunctionType::~FunctionType()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	size_t FunctionType::Name(char* buf, size_t size) const
	{
		// Return type
		size_t p = detail::type_get_name_safe(mReturnType, buf, size);

		// Class name
		if(mIsMethod)
		{
			buf[p-1] = ' ';
			p += detail::type_get_name_safe(*mArguments, &buf[p], size - p);
			buf[p-2]=':'; buf[p-1]=':'; buf[p++]='*'; buf[p++]='('; buf[p++]='\0';
		}
		else
		{
			buf[p-1]=' '; buf[p++]='('; buf[p++]='\0';
		}


		Type** pparg = (Type**)(mArguments);
		if(mIsMethod) ++pparg;

		// Arguments
		bool adjust = false;
		while(*pparg)
		{
			adjust = true;

			p += detail::type_get_name_safe(*pparg, &buf[p - 1], size - p) - 1;
			buf[p-1]=','; buf[p++]=' '; buf[p++]='\0';

			++pparg;
		}

		if(adjust) p -= 2;
		buf[p-1]=')'; buf[p++]='\0';

		return p;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t FunctionType::FullName(char* buf, size_t size) const
	{
		return Name(buf, size);
	}

	//////////////////////////////////////////////////////////////////////////

	bool FunctionType::ToString(void* value, char* buf, size_t size) const
	{
		Name(buf, size);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void FunctionType::Invoke(DelegateBase* deleg, void** args, void* result) const
	{
		mInvoker(deleg, args, result);
	}

	//////////////////////////////////////////////////////////////////////////

	bool FunctionType::Equal(const Type* other) const
	{
		if(	ArchType() != other->ArchType())
			return false;

		ASSERT_STRICT(false);
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t FunctionType::getArgumentNumber() const
	{
		size_t c = 0;
		Type** pparg = (Type**)mArguments;
		while(*pparg)
		{
			++c; ++pparg;
		}
		return c;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
