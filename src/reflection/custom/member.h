/*========================================================
* member.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SF_MEMBER_H__
#define _SF_MEMBER_H__

#include "reflection_fwd.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Defines types of member
	/** @ingroup reflection */
	enum EMemberType
	{
		MEMBER_METHOD,
		MEMBER_ACCESSOR,
		MEMBER_ENUMERATION,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Base type of user-defined class members
	/** @ingroup reflection */
	class REFLECTION_API member
	{
	public:

		~member();

		/// Returns type of this member
		EMemberType get_type() const;

		/// Returns name of this member
		const char* get_name() const;

		/// Clones the member
		member* clone() const;

		/// Releases the cloned member
		void release();

	private:
		member(const member& other);
		member& operator=(const member& rhs);

	protected:
		class member_impl;

		member(member_impl* impl);

		member_impl* m_impl;

		static const int _deleg_buf_size = 10;
	};

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_SF_MEMBER_H__
