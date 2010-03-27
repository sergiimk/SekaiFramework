/*========================================================
* typedesc.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPEDESC_H__
#define _TYPEDESC_H__

// Pointer and offset magic
#include "module/guid.h"
#include "module/allocators.h"
#include "../reflection_fwd.h"
#include "platform/platform.h"

namespace Reflection
{

	class TypeDescriptor;

	//////////////////////////////////////////////////////////////////////////

	#include "../generated/construction.inc"

	template<class T> void type_assign(void* to, void* val) { *(T*)to = *(T*)val; }

	//////////////////////////////////////////////////////////////////////////
	namespace detail
	{
		struct type_desc_base
		{
			virtual TypeDescriptor** initialize(UserType* this_type, size_t& ndesc) = 0;
			const char*	name;
			ETypeTag	tag;
			size_t		size;
		};
		//////////////////////////////////////////////////////////////////////////

		template<class T>
		struct type_desc : public type_desc_base
		{
			TypeDescriptor** initialize(UserType* this_type, size_t& ndesc)
			{ name = 0; tag = RL_T_UNKNOWN; size = 0; ndesc = 0; return 0; }
		};

	} // detail

	//////////////////////////////////////////////////////////////////////////

	#define _reflect_type_empty(type, _tag)											\
	namespace Reflection {															\
		namespace detail {															\
			TypeDescriptor** type_desc<type>::initialize(UserType* this_type, size_t& ndesc)\
			{ name = #type; size = sizeof(type); tag = _tag; ndesc = 0; return 0; }	\
		}																			\
	}

	#define reflect_enum_empty(type) _reflect_type_empty(type, RL_T_ENUM)
	#define reflect_struct_empty(type) _reflect_type_empty(type, RL_T_STRUCT)
	#define reflect_class_empty(type) _reflect_type_empty(type, RL_T_CLASS)

	//////////////////////////////////////////////////////////////////////////

	#define _reflect_type(type, _tag)												\
	namespace Reflection {															\
		namespace detail {															\
			template<>																\
			struct type_desc<type> : public type_desc_base							\
			{																		\
				friend class UserType;												\
			private:																\
				TypeDescriptor** initialize(UserType* this_type, size_t& ndesc)		\
				{																	\
					name = #type; size = sizeof(type); tag = _tag;					\
					typedef type _Class; ndesc = 0;									\
					static TypeDescriptor* mems[] = {

	#define reflect_struct(type) _reflect_type(type, RL_T_STRUCT)
	#define reflect_class(type) _reflect_type(type, RL_T_CLASS)

	//////////////////////////////////////////////////////////////////////////

	#define end_reflection()														\
					};																\
					return mems;													\
				}																	\
			};																		\
		}																			\
	}

	//////////////////////////////////////////////////////////////////////////

	#define map_ctor_custom(create, destroy)											\
		new ConstructDescriptor((++ndesc, type_of(&create)), MakeGenericDelegate(&create), &destroy, this_type),

	#define map_ctor_alloc(alloc, ...)											\
		new ConstructDescriptor((++ndesc, type_of(&type_ctor<_Class, alloc, ## __VA_ARGS__>)), MakeGenericDelegate(&type_ctor<_Class, alloc, ## __VA_ARGS__>), &type_destructor<_Class, alloc>, this_type),

	#define map_ctor(...)																\
		map_ctor_alloc(Module::NewAllocator, ## __VA_ARGS__)

	#define map_create_inst(...)											\
		new ConstructDescriptor((++ndesc, type_of(&type_create_inst<_Class, ## __VA_ARGS__>)), MakeGenericDelegate(&type_create_inst<_Class, ## __VA_ARGS__>), &type_destroy_inst<_Class>, this_type),

	#define map_field_doc(name, field, doc)												\
		new FieldDescriptor((++ndesc, name), type_of(&_Class::field), this_type, offsetof(_Class, field), doc),

    // TODO: offsetof macro is unusable with virtual inheritance

	#define map_field(name, field) map_field_doc(name, field, 0)

	#define map_method_doc(name, method, doc)											\
		new MethodDescriptor((++ndesc, name), type_of(&_Class::method), this_type, MakeGenericDelegate(&_Class::method), doc),

	#define map_method(name, method) map_method_doc(name, method, 0)

	#define map_accessor_r_doc(name, gt, getter, st, setter, doc)						\
		new AccessorDescriptor((++ndesc, name), this_type, type_of((gt)&_Class::getter), type_of((st)&_Class::setter), MakeGenericDelegate((gt)&_Class::getter), MakeGenericDelegate((st)&_Class::setter), doc),

	#define map_accessor_r(name, gt, getter, st, setter) map_accessor_r_doc(name, gt, getter, st, setter, 0)

	#define map_accessor_doc(name, getter, setter, doc)									\
		new AccessorDescriptor((++ndesc, name), this_type, type_of(&_Class::getter), type_of(&_Class::setter), MakeGenericDelegate(&_Class::getter), MakeGenericDelegate(&_Class::setter), doc),

	#define map_accessor(name, getter, setter) map_accessor_doc(name, getter, setter, 0)

	#define map_base(type)																\
		new BaseType((++ndesc, #type), (UserType*)type_of<type>(), this_type, Module::classoffset<type, _Class>()),

	#define map_parsable()																\
		new ParsingDescriptorImpl<_Class>((++ndesc, this_type)),

	#define map_custom_assign2(as)														\
		new AssignmentDescriptor((++ndesc, as), this_type),

	#define map_custom_assign()															\
		map_custom_assign2(type_assign<_Class>)

	//////////////////////////////////////////////////////////////////////////
	// Enums
	//////////////////////////////////////////////////////////////////////////

	#define reflect_enum(type)															\
			_reflect_type(type, RL_T_ENUM)												\
			EnumerationDescriptor::Create((++ndesc, this_type),

	#define map_enum(value) SEnumEntry::make_entry(value, #value),

	#define map_enum2(value, name) SEnumEntry::make_entry(value, name),

	#define end_reflection_enum()														\
		SEnumEntry::make_entry(0, 0)),																\
		end_reflection()

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _TYPEDESC_H__
