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

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	class accessor::accessor_impl : public member::member_impl
	{
	public:
		accessor_impl(
			const char* name, 
			DelegateBase* delegGet, function_type* typeGet, 
			DelegateBase* delegSet, function_type* typeSet)
			: member_impl(MEMBER_ACCESSOR, name)
			, m_typeGet(typeGet)
			, m_typeSet(typeSet)
		{
			memcpy(m_delegGetBuf, delegGet, sizeof(m_delegGetBuf));
			if(typeSet)
				memcpy(m_delegSetBuf, delegSet, sizeof(m_delegSetBuf));
		}

		virtual accessor_impl* clone() const
		{
			return new accessor_impl(
				get_name(), 
				(DelegateBase*)m_delegGetBuf, m_typeGet,
				(DelegateBase*)m_delegSetBuf, m_typeSet);
		}

	private:
		char m_delegGetBuf[member::_deleg_buf_size];
		char m_delegSetBuf[member::_deleg_buf_size];
		function_type* m_typeGet;
		function_type* m_typeSet;
	};

	//////////////////////////////////////////////////////////////////////////
	// accessor
	//////////////////////////////////////////////////////////////////////////

	accessor::accessor(
		const char* name, 
		DelegateBase* delegGet, 
		function_type* typeGet, 
		DelegateBase* delegSet /* = 0 */, 
		function_type* typeSet /* = 0 */)
		: member(new accessor_impl(name, delegGet, typeGet, delegSet, typeSet))
	{
		m_impl = static_cast<accessor_impl*>(member::m_impl);
	}
	
} // namespace
