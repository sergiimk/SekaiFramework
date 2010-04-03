/*========================================================
* accessor_impl.cpp
* @author Sergey Mikhtonyuk
* @date 30 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "custom/accessor_member.h"
#include "member_impl.h"
#include "types/function_type.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	class accessor_member::accessor_impl : public member::member_impl
	{
	public:
		accessor_impl(
			const char* name, 
			void* delegGet, function_type* typeGet, 
			void* delegSet, function_type* typeSet)
			: member_impl(MEMBER_ACCESSOR, name)
			, m_typeGet(typeGet)
			, m_typeSet(typeSet)
		{
			memcpy(m_delegGetBuf, delegGet, sizeof(m_delegGetBuf));
			if(m_typeSet)
				memcpy(m_delegSetBuf, delegSet, sizeof(m_delegSetBuf));
		}

		accessor_impl(const accessor_impl& other)
			: member_impl(MEMBER_ACCESSOR, other.get_name())
			, m_typeGet(other.m_typeGet)
			, m_typeSet(other.m_typeSet)
		{
			memcpy(m_delegGetBuf, other.m_delegGetBuf, sizeof(m_delegGetBuf));
			if(m_typeSet)
				memcpy(m_delegSetBuf, other.m_delegSetBuf, sizeof(m_delegSetBuf));
		}

		void get_value(void* inst, void* buffer) const
		{
			void* args[] = { &inst };
			m_typeGet->invoke((DelegateBase*)m_delegGetBuf, args, buffer);
		}

		void set_value(void* inst, void* buffer) const
		{
			if(m_typeSet)
			{
				void* args[] = { &inst, buffer };
				m_typeSet->invoke((DelegateBase*)m_delegSetBuf, args, 0);
			}
		}

	private:
		char m_delegGetBuf[member::_deleg_buf_size];
		char m_delegSetBuf[member::_deleg_buf_size];
		function_type* m_typeGet;
		function_type* m_typeSet;
	};

	//////////////////////////////////////////////////////////////////////////
	// accessor_member
	//////////////////////////////////////////////////////////////////////////

	accessor_member::accessor_member(
		const char* name, 
		void* delegGet, 
		function_type* typeGet, 
		void* delegSet /* = 0 */, 
		function_type* typeSet /* = 0 */)
		: member(new accessor_impl(name, delegGet, typeGet, delegSet, typeSet))
	{
		m_impl = static_cast<accessor_impl*>(member::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	accessor_member::accessor_member(accessor_impl* impl)
		: member(impl)
	{
		m_impl = impl;
	}

	//////////////////////////////////////////////////////////////////////////

	void accessor_member::get_value(void* inst, void* buffer) const
	{
		m_impl->get_value(inst, buffer);
	}

	//////////////////////////////////////////////////////////////////////////

	void accessor_member::set_value(void* inst, void* buffer) const
	{
		m_impl->set_value(inst, buffer);
	}


	//////////////////////////////////////////////////////////////////////////

	accessor_member* accessor_member::clone() const
	{
		return new accessor_member(new accessor_impl(*m_impl));
	}

	//////////////////////////////////////////////////////////////////////////

	void accessor_member::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
