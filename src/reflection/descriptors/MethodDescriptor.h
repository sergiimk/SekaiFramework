/*========================================================
* MethodDescriptor.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _METHOD_DESCRIPTOR_H__
#define _METHOD_DESCRIPTOR_H__

#include "TypeDescriptor.h"
#include "../types/FunctionType.h"


namespace Reflection
{

	/// Class method descriptor
	/** Shouldn't be invoked directly, use Method instead, that does the 'this' pointer
	 *  fix-up before actual call to the method of base class.
	 *  @ingroup Reflection */
	class MethodDescriptor : public TypeDescriptor
	{
	public:

		/// Ctor
		MethodDescriptor(const char* name, Type* type, UserType* owner, DelegateBase* deleg, const char* docString = 0)
			: TypeDescriptor(RL_DESC_METHOD, owner, name, docString)
			, m_type(static_cast<FunctionType*>(type))
			, mDelegate(deleg)
		{
		}

		/// Destructor
		~MethodDescriptor()
		{
			delete mDelegate;
		}

		/// Returns method type
		FunctionType* getType() const
		{
			return m_type;
		}

		/// Invokes the method, first argument should be class instance
		void Invoke(void** args, void* result) const
		{
			m_type->Invoke(mDelegate, args, result);
		}

	private:
		FunctionType* m_type;
		DelegateBase* mDelegate;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Method is a wrapper for MethodDescriptor that adjusts 'this' pointer before call
	/** @ingroup Reflection */
	class Method
	{
	public:

		Method() : m_descriptor(0)
		{ }

		Method(MethodDescriptor* desc, size_t offset)
			: m_descriptor(desc)
			, m_offset(offset)
		{
		}

		bool isValid() const
		{
			return m_descriptor != 0;
		}

		/// Returns method type
		FunctionType* getType() const
		{
			return m_descriptor->getType();
		}

		/// Invokes the method, first argument should be class instance
		void Invoke(void** args, void* result) const
		{
			// Adjust pointer before the call
			void** oldInst = (void**)args[0];
			void* newInst = Module::adjustptr(*oldInst, m_offset);
			args[0] = &newInst;

			m_descriptor->Invoke(args, result);

			// Restore initial value
			args[0] = oldInst;
		}

	private:
		MethodDescriptor* m_descriptor;
		size_t m_offset;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _METHOD_DESCRIPTOR_H__
