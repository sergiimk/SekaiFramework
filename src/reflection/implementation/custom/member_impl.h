/*========================================================
* member_impl.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _MEMBER_IMPL_H__
#define _MEMBER_IMPL_H__

#include "custom/member.h"
#include <string>

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Implementation of base member
	/** @ingroup reflection */
	class member::member_impl
	{
	public:

		member_impl(EMemberType type, const char* name);

		virtual ~member_impl();

		EMemberType get_type() const;

		const char* get_name() const;

		virtual member_impl* clone() const = 0;

	private:
		EMemberType m_type;
		std::string m_name;
	};

	//////////////////////////////////////////////////////////////////////////

	inline EMemberType member::member_impl::get_type() const
	{
		return m_type;
	}

	//////////////////////////////////////////////////////////////////////////

	inline const char* member::member_impl::get_name() const
	{
		return m_name.c_str();
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_MEMBER_IMPL_H__
