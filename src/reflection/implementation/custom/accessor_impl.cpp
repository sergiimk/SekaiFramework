/*========================================================
* accessor_impl.cpp
* @author Sergey Mikhtonyuk
* @date 30 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "member_impl.h"
#include "custom/accessor_member.h"
#include "types/function_type.h"

using namespace delegates;

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	class accessor_member::accessor_impl : public member::member_impl
	{
	public:
		accessor_impl(
			const char* name, 
			delegate_dynamic_base* delegGet, function_type* typeGet, 
			delegate_dynamic_base* delegSet, function_type* typeSet)
			: member_impl(MEMBER_ACCESSOR, name)
			, m_delegGet(delegGet)
			, m_delegSet(delegSet)
			, m_typeGet(typeGet)
			, m_typeSet(typeSet)
		{ }

		~accessor_impl()
		{
			delete m_delegGet;
			delete m_delegSet;
		}

		void get_value(void* inst, void* buffer) const
		{
			// Setup this pointer of delegate
			delegates::detail::function_data fd = m_delegGet->getFunctionData();
			fd.setThisPtr(reinterpret_cast<delegates::detail::GenericClass*>(inst));
			m_delegGet->setFunctionData(fd);

			m_delegGet->invoke(0, buffer);
		}

		void set_value(void* inst, void* buffer) const
		{
			if(m_typeSet)
			{
				// Setup this pointer of delegate
				delegates::detail::function_data fd = m_delegSet->getFunctionData();
				fd.setThisPtr(reinterpret_cast<delegates::detail::GenericClass*>(inst));
				m_delegSet->setFunctionData(fd);

				m_delegSet->invoke(&buffer, 0);
			}
		}

		bool is_read_only() const
		{
			return m_typeSet == 0;
		}

		type* value_type() const
		{
			return m_typeGet->return_type();
		}

	private:
		delegate_dynamic_base* m_delegGet;
		delegate_dynamic_base* m_delegSet;
		function_type* m_typeGet;
		function_type* m_typeSet;
	};

	//////////////////////////////////////////////////////////////////////////
	// accessor_member
	//////////////////////////////////////////////////////////////////////////

	accessor_member::accessor_member(
		const char* name, 
		delegate_dynamic_base* delegGet, 
		function_type* typeGet, 
		delegate_dynamic_base* delegSet /* = 0 */, 
		function_type* typeSet /* = 0 */)
		: member(new accessor_impl(name, delegGet, typeGet, delegSet, typeSet))
	{ }

	//////////////////////////////////////////////////////////////////////////

	void accessor_member::get_value(void* inst, void* buffer) const
	{
		static_cast<accessor_impl*>(m_impl)->get_value(inst, buffer);
	}

	//////////////////////////////////////////////////////////////////////////

	void accessor_member::set_value(void* inst, void* buffer) const
	{
		static_cast<accessor_impl*>(m_impl)->set_value(inst, buffer);
	}

	//////////////////////////////////////////////////////////////////////////

	bool accessor_member::is_read_only() const
	{
		return static_cast<accessor_impl*>(m_impl)->is_read_only();
	}

	//////////////////////////////////////////////////////////////////////////

	type* accessor_member::value_type() const
	{
		return static_cast<accessor_impl*>(m_impl)->value_type();
	}

	//////////////////////////////////////////////////////////////////////////

	void accessor_member::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
