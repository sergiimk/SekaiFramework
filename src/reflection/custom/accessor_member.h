/*========================================================
* accessor_member.h
* @author Sergey Mikhtonyuk
* @date 30 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ACCESSOR_MEMBER_H__
#define _ACCESSOR_MEMBER_H__

#include "member.h"
#include "delegate/DelegateBase.h"
#include "delegate/Delegate.h"
#include "common/static_assert.h"

namespace reflection
{

	/// Represents accessor functions
	/** @ingroup reflection */
	class REFLECTION_API accessor : public member
	{
	public:

		template<class Deleg1, class Deleg2>
		static accessor create(
			const char* name, 
			const Deleg1& delegGet, 
			function_type* typeGet,
			const Deleg2& delegSet, 
			function_type* typeSet)
		{
			static_assert(sizeof(Deleg1) <= _deleg_buf_size, "Delegate buffer too small");
			static_assert(sizeof(Deleg2) <= _deleg_buf_size, "Delegate buffer too small");
			return accessor(name, (DelegateBase*)&delegGet, typeGet, (DelegateBase*)&delegSet, typeSet);
		}

		template<class Deleg>
		static accessor create(
			const char* name, 
			const Deleg& delegGet, 
			function_type* typeGet)
		{
			static_assert(sizeof(Deleg) <= _deleg_buf_size, "Delegate buffer too small");
			return accessor(name, (DelegateBase*)&delegGet, typeGet);
		}

		accessor(const char* name, 
			DelegateBase* delegGet, 
			function_type* typeGet,
			DelegateBase* delegSet = 0,  
			function_type* typeSet = 0);

	private:
		class accessor_impl;
		accessor_impl* m_impl;
	};
	
} // namespace

#endif //_ACCESSOR_MEMBER_H__
