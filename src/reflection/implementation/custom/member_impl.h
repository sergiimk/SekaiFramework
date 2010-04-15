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

		const user_type* get_owner() const;

		void set_owner(const user_type* own);

	private:
		std::string m_name;
		const user_type* m_owner;
		EMemberType m_type;
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

	inline const user_type* member::member_impl::get_owner() const
	{
		return m_owner;
	}

	inline void member::member_impl::set_owner(const user_type* own)
	{
		m_owner = own;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_MEMBER_IMPL_H__
