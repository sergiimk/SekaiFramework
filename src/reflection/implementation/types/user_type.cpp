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

		std::pair<attribute*, member*> get_attribute(size_t i) const
		{
			return m_attributes[i];
		}

	private:

		

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

	void user_type::_get_attribute(attribute*& attr, member*& mem, size_t i) const
	{
		std::pair<attribute*, member*> p = m_impl->get_attribute(i);
		attr = p.first;
		mem = p.second;
	}

	//////////////////////////////////////////////////////////////////////////

	user_type::member_iterator user_type::find_member(const char* name, bool search_base) const
	{
		size_t memcount = m_impl->member_count();
		size_t p = m_impl->find_member(name);
		if(p != memcount || !search_base)
			return member_iterator(*this, p); 

		for(attribute_iterator it = attributes_begin(), 
			end = attributes_end(); it != end; ++it)
		{
			if(it->get_type() == ATTR_BASE_TYPE)
			{
				base_type* bt = static_cast<base_type*>(&*it);
				member_iterator it = bt->get_base()->find_member(name, search_base);
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
				base_type* bt = static_cast<base_type*>(&*it);
				bt->get_base()->traverse_rec(tr, depth + 1);
			}
		}
		tr.LeaveType(*this, depth);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace


