/*========================================================
* ConstructDescriptor.h
* @author Sergey Mikhtonyuk
* @date 09 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CONSTRUCTDESCRIPTOR_H__
#define _CONSTRUCTDESCRIPTOR_H__

#include "TypeDescriptor.h"

namespace Reflection
{

	/// Describes that class supports CreateInstance() and DestroyInstance() operations
	/** @ingroup Reflection */
	class ConstructDescriptor : public TypeDescriptor
	{
	public:
		typedef void (*TDtor)(void*);

		ConstructDescriptor(Type* ctorType, DelegateBase* ctorDeleg, TDtor d, UserType* owner)
			: TypeDescriptor(RL_DESC_SERVICE_CONSTRUCT, owner, "<ctor desc>")
			, m_ctorType(static_cast<FunctionType*>(ctorType))
			, m_ctorDeleg(ctorDeleg)
			, m_dtor(d)
		{
		}

		~ConstructDescriptor()
		{
			delete m_ctorDeleg;
		}

		/// Creates type instance
		void* CreateInstance(void** args) const
		{
			void* ret = 0;
			m_ctorType->Invoke(m_ctorDeleg, args, &ret);
			return ret;
		}

		/// Creates type instance
		void DestroyInstance(void* v) const
		{
			m_dtor(v);
		}

		/// Returns reflected type of factory function
		FunctionType* GetCtorType() const
		{
			return m_ctorType;
		}

	private:
		FunctionType* m_ctorType;
		DelegateBase* m_ctorDeleg;
		TDtor m_dtor;
	};

} // namespace

#endif // _CONSTRUCTDESCRIPTOR_H__
