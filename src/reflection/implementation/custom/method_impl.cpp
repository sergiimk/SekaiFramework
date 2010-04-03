/*========================================================
* method_impl.cpp
* @author Sergey Mikhtonyuk
* @date 30 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "custom/method_member.h"
#include "member_impl.h"
#include "types/function_type.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	class method_member::method_impl : public member::member_impl
	{
	public:
		method_impl(const char* name, void* deleg, function_type* type)
			: member_impl(MEMBER_METHOD, name)
			, m_type(type)
		{
			memcpy(m_delegBuf, deleg, sizeof(m_delegBuf));
		}

		method_impl(const method_impl& other)
			: member_impl(MEMBER_METHOD, other.get_name())
			, m_type(other.m_type)
		{
			memcpy(m_delegBuf, other.m_delegBuf, sizeof(m_delegBuf));
		}

		function_type* get_function_type() const
		{
			return m_type;
		}

		void invoke(void** args, void* result) const
		{
			m_type->invoke((DelegateBase*)m_delegBuf, args, result);
		}

	private:
		char m_delegBuf[member::_deleg_buf_size];
		function_type* m_type;
	};

	//////////////////////////////////////////////////////////////////////////
	// method_member
	//////////////////////////////////////////////////////////////////////////

	method_member::method_member(const char* name, void* deleg, function_type* type)
		: member(new method_impl(name, deleg, type))
	{
		m_impl = static_cast<method_impl*>(member::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	method_member::method_member(method_impl* impl)
		: member(impl)
	{
		m_impl = impl;
	}

	//////////////////////////////////////////////////////////////////////////

	function_type* method_member::get_function_type() const
	{
		return m_impl->get_function_type();
	}

	//////////////////////////////////////////////////////////////////////////

	void method_member::invoke(void** args, void* result) const
	{
		m_impl->invoke(args, result);
	}

	//////////////////////////////////////////////////////////////////////////

	method_member* method_member::clone() const
	{
		return new method_member(new method_impl(*m_impl));
	}

	//////////////////////////////////////////////////////////////////////////

	void method_member::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
