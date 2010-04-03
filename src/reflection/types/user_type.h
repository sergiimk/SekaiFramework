/*========================================================
* user_type.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _USERTYPE_H__
#define _USERTYPE_H__

#include "types/type.h"

namespace reflection
{
	/// User-defined type class
	/** @ingroup reflection */
	class REFLECTION_API user_type : public type
	{
	public:

		#include "user_type_iters.h"

		user_type(ETypeTag tag, const char* name, size_t size);

		/// Adds type member
		void add_member(const member& mem);

		/// Adds attribute to the type itself
		void add_attribute(const attribute& attr);

		/// Declare member
		user_type& def(const member& mem) 
		{ 
			add_member(mem); 
			return *this; 
		}

		/// Declare class attribute
		user_type& def(const attribute& a) 
		{ 
			add_attribute(a); 
			return *this; 
		}

		/// Declare method
		template<class C, class MemFun>
		user_type& def(const char* name, MemFun meth)
		{
			add_member(method_member::create(name, MakeDelegate(static_cast<C*>(0), meth), type_of(meth)));
			return *this;
		}

		/// Declare accessor
		template<class C, class TGet, class TSet>
		user_type& def(const char* name, TGet getter, TSet setter)
		{
			add_member(accessor_member::create(name, 
				MakeDelegate(static_cast<C*>(0), getter), type_of(getter), 
				MakeDelegate(static_cast<C*>(0), setter), type_of(setter)));
			return *this;
		}

	private:
		size_t _member_count() const;
		member* _get_member(size_t i) const;
		size_t _find_member(const char* name) const;

		size_t _attribute_count() const;
		void _get_attribute(attribute*& attr, member*& mem, size_t i) const;

		void traverse_rec(hierarchy_traverser& tr, size_t depth) const;

	private:
		class user_type_impl;
		user_type_impl* m_impl;
	};

} // namespace

//////////////////////////////////////////////////////////////////////////

#define reflect_user(clas, name, tag)											\
namespace reflection { namespace detail {										\
template<> struct type_desc<clas> {												\
	user_type* get_type() {														\
		static bool is_init = false;											\
		static user_type t(tag, name, sizeof(clas));							\
		if(!is_init) {															\
			is_init = true;														\
			t

//////////////////////////////////////////////////////////////////////////

#define reflect_class(clas, name) reflect_user(clas, name, T_CLASS)
#define reflect_struct(clas, name) reflect_user(clas, name, T_STRUCT)
#define reflect_enum(clas, name) reflect_user(clas, name, T_ENUM)

//////////////////////////////////////////////////////////////////////////

#define end_reflection() ;}return &t;}};}}

//////////////////////////////////////////////////////////////////////////

#endif //_USERTYPE_H__
