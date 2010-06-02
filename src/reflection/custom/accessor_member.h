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
#include "dynamic_delegates/delegate_dynamic.h"
#include "common/typetraits.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Represents accessor functions
	/** @ingroup reflection */
	class REFLECTION_API accessor_member : public member
	{
	public:

		template<class Deleg1, class Deleg2>
		static accessor_member* create(
			const char* name, 
			const Deleg1& delegGet, 
			function_type* typeGet,
			const Deleg2& delegSet, 
			function_type* typeSet)
		{
			return new accessor_member(name, 
				new Deleg1(delegGet), typeGet, 
				new Deleg2(delegSet), typeSet);
		}

		template<class Deleg>
		static accessor_member* create(
			const char* name, 
			const Deleg& delegGet, 
			function_type* typeGet)
		{
			return new accessor_member(name, new Deleg(delegGet), typeGet);
		}

		accessor_member(const char* name, 
			delegates::delegate_dynamic_base* delegGet, 
			function_type* typeGet,
			delegates::delegate_dynamic_base* delegSet = 0,  
			function_type* typeSet = 0);

		void get_value(void* inst, void* buffer) const;

		void set_value(void* inst, void* buffer) const;

		bool is_read_only() const;

		type* value_type() const;

		virtual void release();

	private:
		class accessor_impl;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Wrapper around accessor_member that adjusts 'this' pointer before invoking
	/** @ingroup reflection */
	class accessor
	{
	public:

		typedef accessor_member member_type;
		static const EMemberType member_id = MEMBER_ACCESSOR;

		accessor() : m_accessor(0), m_offset(0) { }

		accessor(const accessor_member& acc, size_t offset) : m_accessor(&acc), m_offset(offset) { }

		const char* get_name() const { return m_accessor->get_name(); }

		void get_value(void* inst, void* buffer) const
		{
			m_accessor->get_value(adjustptr(inst, m_offset), buffer);
		}

		void set_value(void* inst, void* buffer) const
		{
			m_accessor->set_value(adjustptr(inst, m_offset), buffer);
		}

	private:
		const accessor_member* m_accessor;
		size_t m_offset;
	};

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_ACCESSOR_MEMBER_H__
