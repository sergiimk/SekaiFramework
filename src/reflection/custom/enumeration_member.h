/*========================================================
* enumeration_member.h
* @author Sergey Mikhtonyuk
* @date 04 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ENUMERATION_MEMBER_H__
#define _ENUMERATION_MEMBER_H__

#include "member.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Reflects enumeration entry
	/** @ingroup reflection */
	class REFLECTION_API enumeration_member : public member
	{
	public:

		static enumeration_member* create(const char* name, unsigned int value)
		{
			return new enumeration_member(name, value);
		}

		enumeration_member(const char* name, unsigned int value);

		unsigned int get_value() const;

		virtual void release();

	private:
		struct enumeration_impl;
	};

	//////////////////////////////////////////////////////////////////////////

	class enumeration
	{
	public:

		typedef enumeration_member member_type;
		static const EMemberType member_id = MEMBER_ENUMERATION;

		enumeration() : m_enum(0) { }

		enumeration(const enumeration_member& en, size_t) : m_enum(&en) { }

		const char* get_name() const { return m_enum->get_name(); }

		unsigned int get_value() const { return m_enum->get_value(); }

	private:
		const enumeration_member* m_enum;
	};

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_ENUMERATION_MEMBER_H__
