/*========================================================
* user_type.cpp
* @author Sergey Mikhtonyuk
* @date 29 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "types/user_type.h"
#include "type_impl.h"
#include "custom/member.h"
#include "custom/attribute.h"
#include <vector>

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	class user_type::user_type_impl : public type::type_impl
	{
	public:

		user_type_impl(ETypeTag tag, const char* name, size_t size)
			: type_impl(tag, ARCH_USERDEFINED, size)
		{
			type_impl::set_name(name);
		}

		~user_type_impl()
		{
			for(size_t i = 0, size = m_attributes.size(); i != size; ++i)
				m_attributes[i].first->release();

			for(size_t i = 0, size = m_members.size(); i != size; ++i)
				m_members[i]->release();
		}

		void add_member(const member& mem)
		{
			m_members.push_back(mem.clone());
		}

		void add_attribute(const attribute& attr)
		{
			m_attributes.push_back(std::make_pair<attribute*, member*>(attr.clone(), 0));
		}

	private:
		typedef std::vector<member*> TMemberContainer;
		typedef std::vector<std::pair<attribute*, member*> > TAttributeContainer;

		TMemberContainer m_members;
		TAttributeContainer m_attributes;
	};

	//////////////////////////////////////////////////////////////////////////
	// user_type
	//////////////////////////////////////////////////////////////////////////

	user_type::user_type(ETypeTag tag, const char* name, size_t size)
		: type(new user_type_impl(tag, name, size))
	{
		m_impl = static_cast<user_type_impl*>(type::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	void user_type::add_member(const member& mem)
	{
		m_impl->add_member(mem);
	}

	//////////////////////////////////////////////////////////////////////////

	void user_type::add_attribute(const attribute& attr)
	{
		m_impl->add_attribute(attr);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace


