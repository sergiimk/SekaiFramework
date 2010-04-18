/*========================================================
* converter.cpp
* @author Sergey Mikhtonyuk
* @date 06 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "utils/converter.h"
#include "types/user_type.h"
#include "custom/parsing_attribute.h"
#include "custom/enumeration_member.h"
#include <algorithm>

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	struct find_enum {
		unsigned int val;
		find_enum(unsigned int v) : val(v) { }
		bool operator()(const member& mem) {
			return mem.get_type() == MEMBER_ENUMERATION 
				&& ((const enumeration_member&)mem).get_value() == val; 
		}
	};

	struct find_attribute
	{
		EAttributeType attr_t;
		find_attribute(EAttributeType t) : attr_t(t) { }
		bool operator()(const attribute& attr) { return attr.get_type() == attr_t; }
	};

	//////////////////////////////////////////////////////////////////////////

	bool converter::to_string(const value_type_pair &vt, char *buf, size_t size)
	{
		if(vt.Type->tag() != T_ENUM)
		{
			type::attribute_iterator it = std::find_if(
				vt.Type->attributes_begin(), vt.Type->attributes_end(),
				find_attribute(ATTR_PARSING));

			if(it != vt.Type->attributes_end())
				return static_cast<const parsing_attribute*>(&*it)->to_string(vt.Value, buf, size);
		}
		else
		{
			const user_type& ut = static_cast<const user_type&>(*vt.Type);
			user_type::member_iterator it = std::find_if(
				ut.members_begin(), ut.members_end(),
				find_enum(*(unsigned int*)vt.Value));

			if(it != ut.members_end())
			{
				const char* name = it->get_name();
				strncpy(buf, name, size - 1);
				return strlen(name) < size;
			}
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool converter::try_parse(const reflection::value_type_pair &vt, const char *str)
	{
		if(vt.Type->tag() != T_ENUM)
		{
			type::attribute_iterator it = std::find_if(
				vt.Type->attributes_begin(), vt.Type->attributes_end(),
				find_attribute(ATTR_PARSING));

			if(it != vt.Type->attributes_end())
				return static_cast<const parsing_attribute*>(&*it)->try_parse(vt.Value, str);
		}
		else
		{
			const user_type& ut = static_cast<const user_type&>(*vt.Type);
			user_type::member_iterator it = ut.find_member(str);

			if(it.is<enumeration>())
			{
				unsigned int* pui = (unsigned int*)vt.Value;
				*pui = it.get<enumeration>().get_value();
				return true;
			}
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
