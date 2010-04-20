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
#include "delegate/Delegate.h"
#include "common/typetraits.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Class member representation
	/** @ingroup reflection */
	class REFLECTION_API method_member : public member
	{
	public:

		template<class Deleg>
		static method_member create(const char* name, const Deleg& deleg, function_type* type)
		{
			static_assert(sizeof(Deleg) <= _deleg_buf_size, "Delegate buffer too small");
			return method_member(name, (void*)&deleg, type);
		}

		method_member(const char* name, void* deleg, function_type* type);

		/// Returns type of the method
		function_type* get_function_type() const;

		void invoke(void** args, void* result) const;

		virtual method_member* clone() const;

		virtual void release();

	private:
		class method_impl;
		method_impl* m_impl;

		method_member(method_impl* impl);
	};

	//////////////////////////////////////////////////////////////////////////

	/// Wrapper around method_member that adjusts 'this' pointer before invoking
	/** @ingroup reflection */
	class method
	{
	public:

		typedef method_member member_type;
		static const EMemberType member_id = MEMBER_METHOD;

		method() : m_method(0), m_offset(0) { }

		method(const method_member& mth, size_t offset) : m_method(&mth), m_offset(offset) { }

		const char* get_name() const { return m_method->get_name(); }

		function_type* get_function_type() const { return m_method->get_function_type(); }

		void invoke(void** args, void* result) const 
		{
			// Adjust pointer before the call
			void** oldInst = (void**)args[0];
			void* newInst = adjustptr(*oldInst, m_offset);
			args[0] = &newInst;

			m_method->invoke(args, result); 

			// Restore initial value
			args[0] = oldInst;
		}

	private:
		const method_member* m_method;
		size_t m_offset;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif //_METHOD_MEMBER_H__
