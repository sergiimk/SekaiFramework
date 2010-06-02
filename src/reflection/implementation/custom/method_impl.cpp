/*========================================================
* method_impl.cpp
* @author Sergey Mikhtonyuk
* @date 30 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "member_impl.h"
#include "custom/method_member.h"

using namespace delegates;

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	class method_member::method_impl : public member::member_impl
	{
	public:
		method_impl(const char* name, delegate_dynamic_base* deleg, function_type* type)
			: member_impl(MEMBER_METHOD, name)
			, m_delegate(deleg)
			, m_type(type)
		{ }

		~method_impl()
		{
			delete m_delegate;
		}

		function_type* get_function_type() const
		{
			return m_type;
		}

		void invoke(void** args, void* result) const
		{			
			// Setup this pointer of delegate
			detail::function_data fd = m_delegate->getFunctionData();
			fd.setThisPtr(reinterpret_cast<detail::GenericClass*>(*(void**)args[0]));
			m_delegate->setFunctionData(fd);

			m_delegate->invoke(&args[1], result);
		}

	private:
		delegate_dynamic_base* m_delegate;
		function_type* m_type;
	};

	//////////////////////////////////////////////////////////////////////////
	// method_member
	//////////////////////////////////////////////////////////////////////////

	method_member::method_member(const char* name, delegate_dynamic_base* deleg, function_type* type)
		: member(new method_impl(name, deleg, type))
	{ }

	//////////////////////////////////////////////////////////////////////////

	function_type* method_member::get_function_type() const
	{
		return static_cast<method_impl*>(m_impl)->get_function_type();
	}

	//////////////////////////////////////////////////////////////////////////

	void method_member::invoke(void** args, void* result) const
	{
		static_cast<method_impl*>(m_impl)->invoke(args, result);
	}

	//////////////////////////////////////////////////////////////////////////

	void method_member::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
