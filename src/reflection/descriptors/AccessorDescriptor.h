/*========================================================
* AccessorDescriptor.h
* @author Sergey Mikhtonyuk
* @date 23 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ACCESSOR_DESCRIPTOR_H__
#define _ACCESSOR_DESCRIPTOR_H__

#include "DataDescriptor.h"
#include "../types/FunctionType.h"
#include "platform/platform.h"

namespace Reflection
{

	/// Descriptor of data hidden behind get/set methods
	/** Use Accessor to access data that may be provided by base class (does 'this' fix-up).
	 *  @ingroup Reflection */
	class AccessorDescriptor : public DataDescriptor
	{
	public:

		/// Ctor
		AccessorDescriptor(const char* name, UserType* owner, Type* getter, Type* setter,
				 DelegateBase* dgetter, DelegateBase* dsetter, const char* docString = 0)
			: DataDescriptor(RL_DESC_ACCESSOR, name, owner, static_cast<FunctionType*>(getter)->getReturnType(), docString)
			, mGetter(static_cast<FunctionType*>(getter))
			, mSetter(static_cast<FunctionType*>(setter))
			, mDelegGetter(dgetter)
			, mDelegSetter(dsetter)
		{
		}

		/// Destructor
		~AccessorDescriptor()
		{
			delete mDelegGetter;
			delete mDelegSetter;
		}

		bool isReadOnly() const
		{
			return mSetter == 0;
		}

		void getValue(void* inst, void* buffer) const
		{
			void* args[] = { &inst };
			mGetter->Invoke(mDelegGetter, args, buffer);
		}

		void setValue(void* inst, void* buffer) const
		{
			ASSERT_SOFT(!isReadOnly());
			if(isReadOnly()) return;

			void* args[] = { &inst, buffer };
			mSetter->Invoke(mDelegSetter, args, 0);
		}

		/// Returns type of getter function
		FunctionType* getGetterType() const { return mGetter; }

		/// Returns type of setter function
		FunctionType* getSetterType() const { return mSetter; }

	private:
		FunctionType* mGetter;
		FunctionType* mSetter;
		DelegateBase* mDelegGetter;
		DelegateBase* mDelegSetter;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Accessor is a wrapper for AccessorDescriptor that adjusts 'this' pointer before calls
	/** @ingroup Reflection */
	class Accessor : public Data
	{
	public:
		Accessor()
		{ }

		Accessor(AccessorDescriptor* desc, size_t offset)
			: Data(desc, offset)
		{ }

		/// Returns type of getter function
		FunctionType* getGetterType() const
		{
			return static_cast<AccessorDescriptor*>(m_descriptor)->getGetterType();
		}

		/// Returns type of setter function
		FunctionType* getSetterType() const
		{
			return static_cast<AccessorDescriptor*>(m_descriptor)->getSetterType();
		}
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ACCESSOR_DESCRIPTOR_H__
