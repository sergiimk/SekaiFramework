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
#include "custom/basetype_attribute.h"
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
				m_attributes[i]->release();

			for(size_t i = 0, size = m_members.size(); i != size; ++i)
				m_members[i]->release();
		}

		void add_member(const member& mem)
		{
			m_members.push_back(mem.clone());
		}

		void add_attribute(const attribute& attr)
		{
			m_attributes.push_back(attr.clone());
		}

		size_t member_count() const
		{
			return m_members.size();
		}

		member* get_member(size_t i) const
		{
			return m_members[i];
		}

		size_t find_member(const char* name) const
		{
			for(size_t i = 0, size = m_members.size(); i != size; ++i)
				if(strcmp(m_members[i]->get_name(), name) == 0)
					return i;
			return m_members.size();
		}

		size_t attribute_count() const
		{
			return m_attributes.size();
		}

		attribute* get_attribute(size_t i) const
		{
			return m_attributes[i];
		}

	private:
		typedef std::vector<member*> TMemberContainer;
		typedef std::vector<attribute*> TAttributeContainer;

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

	bool user_type::equal(const type* other) const
	{
		return type::equal(other) && strcmp(name(), other->name()) == 0;
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

	size_t user_type::_member_count() const
	{
		return m_impl->member_count();
	}

	//////////////////////////////////////////////////////////////////////////

	member* user_type::_get_member(size_t i) const
	{
		return m_impl->get_member(i);
	}

	//////////////////////////////////////////////////////////////////////////

	size_t user_type::_find_member(const char* name) const
	{
		return m_impl->find_member(name);
	}

	//////////////////////////////////////////////////////////////////////////

	size_t user_type::_attribute_count() const
	{
		return m_impl->attribute_count();
	}

	//////////////////////////////////////////////////////////////////////////

	const attribute* user_type::_get_attribute(size_t i) const
	{
		return m_impl->get_attribute(i);
	}

	//////////////////////////////////////////////////////////////////////////

	user_type::member_iterator user_type::find_member(const char* name, bool search_base, size_t offset) const
	{
		size_t memcount = m_impl->member_count();
		size_t p = m_impl->find_member(name);
		if(p != memcount || !search_base)
			return member_iterator(*this, p, offset); 

		for(attribute_iterator it = attributes_begin(), 
			end = attributes_end(); it != end; ++it)
		{
			if(it->get_type() == ATTR_BASE_TYPE)
			{
				const base_type* bt = static_cast<const base_type*>(&*it);
				member_iterator it = bt->get_base()->find_member(name, search_base, offset + bt->get_offset());
				if(it != bt->get_base()->members_end())
					return it;
			}
		}
		return member_iterator(*this, memcount);
	}

	//////////////////////////////////////////////////////////////////////////

	void user_type::traverse_hierarchy(hierarchy_traverser& tr) const
	{
		traverse_rec(tr, 0);
	}

	//////////////////////////////////////////////////////////////////////////

	void user_type::traverse_rec(hierarchy_traverser& tr, size_t depth) const
	{
		tr.EnterType(*this, depth);

		for(attribute_iterator it = attributes_begin(), 
			end = attributes_end(); it != end; ++it)
		{
			if(it->get_type() == ATTR_BASE_TYPE)
			{
				const base_type* bt = static_cast<const base_type*>(&*it);
				bt->get_base()->traverse_rec(tr, depth + 1);
			}
		}
		tr.LeaveType(*this, depth);
	}

	//////////////////////////////////////////////////////////////////////////

	/*bool user_type::to_string(void* value, char* buf, size_t size) const
	{
		if(tag() != T_ENUM)
		{
			attribute_iterator it = std::find_if(
				attributes_begin(), attributes_end(),
				find_attribute(ATTR_PARSING));

			if(it != attributes_end())
				return static_cast<const parsing_attribute*>(&*it)->to_string(value, buf, size);
		}
		else
		{
			member_iterator it = std::find_if(
				members_begin(), members_end(), 
				find_enum(*(unsigned int*)value));

			if(it != members_end())
			{
				const char* name = it->get_name();
				strncpy(buf, name, size - 1);
				return strlen(name) < size;
			}
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool user_type::try_parse(void* value, const char* str) const
	{
		if(tag() != T_ENUM)
		{
			attribute_iterator it = std::find_if(
				attributes_begin(), attributes_end(),
				find_attribute(ATTR_PARSING));

			if(it != attributes_end())
				return static_cast<const parsing_attribute*>(&*it)->try_parse(value, str);
		}
		else
		{
			member_iterator it = find_member(str);

			if(it.is<enumeration>())
			{
				unsigned int* pui = (unsigned int*)value;
				*pui = it.get<enumeration>().get_value();
				return true;
			}
		}
		return false;
	}*/

	//////////////////////////////////////////////////////////////////////////

} // namespace


