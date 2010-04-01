/*========================================================
* method_member.h
* @author Sergey Mikhtonyuk
* @date 30 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _METHOD_MEMBER_H__
#define _METHOD_MEMBER_H__

#include "member.h"
#include "delegate/DelegateBase.h"
#include "delegate/Delegate.h"
#include "common/static_assert.h"

namespace reflection
{

	/// Class member representation
	/** @ingroup reflection */
	class REFLECTION_API method : public member
	{
	public:

		template<class Deleg>
		static method create(const char* name, const Deleg& deleg, function_type* type)
		{
			static_assert(sizeof(Deleg) <= _deleg_buf_size, "Delegate buffer too small");
			return method(name, (DelegateBase*)&deleg, type);
		}

		method(const char* name, DelegateBase* deleg, function_type* type);

	private:
		class method_impl;
		method_impl* m_impl;
	};

} // namespace

#endif //_METHOD_MEMBER_H__
