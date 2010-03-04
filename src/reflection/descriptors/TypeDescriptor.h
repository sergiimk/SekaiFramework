/*========================================================
* TypeDescriptor.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPEDESCRIPTOR_H__
#define _TYPEDESCRIPTOR_H__

#include "../types/Type.h"
#include "../reflection_fwd.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Types of descriptors, the order is important
	/** @ingroup Reflection */
	enum DescriptorType
	{
		RL_DESC_BASE,
		RL_DESC_FIELD,
		RL_DESC_METHOD,
		RL_DESC_ACCESSOR,
		RL_DESC_SERVICE_PARSING,
		RL_DESC_SERVICE_CONSTRUCT,
		RL_DESC_SERVICE_ASSIGN,
		RL_DESC_SERVICE_ENUMERATION,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Base class for type descriptors
	/** @ingroup Reflection */
	class TypeDescriptor
	{
	public:
		/// Ctor
		TypeDescriptor(DescriptorType dt, UserType* owner, const char* name, const char* docString = 0)
			: mDescType(dt)
			, mOwner(owner)
			, mName(name)
			, mDocString(docString)
		{
		}

		virtual ~TypeDescriptor() {}

		/// Returns the name of the descriptor
		const char* getName() const { return mName; }

		/// Return the documentation string of the descriptor
		const char* getDocString() const { return mDocString; }

		/// Returns the type of the owner of the descriptor
		UserType* getOwnerClass() const { return mOwner; }

		/// Returns type of the descriptor
		DescriptorType getDescriptorType() const { return mDescType; }

	private:
		DescriptorType	mDescType;
		UserType*		mOwner;
		const char*		mName;
		const char*		mDocString;
	};

} // namespace

#endif // _TYPEDESCRIPTOR_H__
