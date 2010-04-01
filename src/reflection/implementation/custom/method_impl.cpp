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

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	class method::method_impl : public member::member_impl
	{
	public:
		method_impl(const char* name, DelegateBase* deleg, function_type* type)
			: member_impl(MEMBER_METHOD, name)
			, m_type(type)
		{
			memcpy(m_delegBuf, deleg, sizeof(m_delegBuf));
		}

		virtual method_impl* clone() const
		{
			return new method_impl(get_name(), (DelegateBase*)m_delegBuf, m_type);
		}

	private:
		char m_delegBuf[member::_deleg_buf_size];
		function_type* m_type;
	};

	//////////////////////////////////////////////////////////////////////////
	// method
	//////////////////////////////////////////////////////////////////////////

	method::method(const char* name, DelegateBase* deleg, function_type* type)
		: member(new method_impl(name, deleg, type))
	{
		m_impl = static_cast<method_impl*>(member::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
