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

		#include "user_type_iters.inc"

		user_type(ETypeTag tag, const char* name, size_t size);

		virtual bool equal(const type* other) const;

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

		/// Calculates the offset of 'this' pointer of base class
		/** @return (size_t)-1 on error */
		static size_t calculate_offset(const user_type& derived, const user_type& base);

	private:

		virtual size_t _attribute_count() const;
		virtual const attribute* _get_attribute(size_t i) const;

		size_t _member_count() const;
		member* _get_member(size_t i) const;
		size_t _find_member(const char* name) const;

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
		typedef clas Class;														\
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

#define def_ctor_custom(_create, _destroy)										\
	def(construct_attribute::create(											\
	type_of(_create),															\
	MakeDelegate(_create),														\
	_destroy))

#define def_ctor_alloc(alloc, ...)												\
	def(construct_attribute::create(											\
	type_of(&type_ctor<Class, alloc, ## __VA_ARGS__>),							\
	MakeDelegate(&type_ctor<Class, alloc, ## __VA_ARGS__>),						\
	&type_destructor<Class, alloc>))

#define def_create_inst(...)													\
	def(construct_attribute::create(											\
	type_of(&type_create_inst<Class, ## __VA_ARGS__>),							\
	MakeDelegate(&type_create_inst<Class, ## __VA_ARGS__>),						\
	&type_destroy_inst<Class>))

#define def_ctor(...)															\
	def_ctor_alloc(Module::NewAllocator, ## __VA_ARGS__)


#define def_method(name, func)													\
	def(method_member::create(name, MakeDelegate(static_cast<Class*>(0), &Class::func), type_of(&Class::func)))

#define def_accessor(name, fget, fset)											\
	def(accessor_member::create(name,											\
	MakeDelegate(static_cast<Class*>(0), &Class::fget), type_of(&Class::fget),	\
	MakeDelegate(static_cast<Class*>(0), &Class::fset), type_of(&Class::fset)))

#define def_accessor_ro(name, fget)												\
	def(accessor_member::create(name,											\
	MakeDelegate(static_cast<Class*>(0), &Class::fget), type_of(&Class::fget)))

#define def_enum(name, value) def(enumeration_member(name, value))

#define def_base(base) def(base_type(type_of<base>(), classoffset<base, Class>()))

#define def_parsable() def(parsing_attribute_t<Class>())

//////////////////////////////////////////////////////////////////////////

#define end_reflection() ;}return &t;}};}}

//////////////////////////////////////////////////////////////////////////

#endif //_USERTYPE_H__
