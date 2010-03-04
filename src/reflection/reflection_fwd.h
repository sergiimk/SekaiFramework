/*========================================================
* Reflection_fwd.h
* @author Sergey Mikhtonyuk
* @date 23 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _REFLECTION_FWD_H__
#define _REFLECTION_FWD_H__

#include "types/TypeTag.h"

namespace Reflection
{
	struct ValueTypePair;

	class Type;
	class ArrayType;
	class PointerType;
	class FunctionType;
	class UserType;

	class TypeDescriptor;
	class DataDescriptor;
	class BaseType;
	class Field;
	class FieldDescriptor;
	class Method;
	class MethodDescriptor;
	class Accessor;
	class AccessorDescriptor;
	class EnumerationDescriptor;
	class ConstructDescriptor;
	class ParsingDescriptor;
	class AssignmentDescriptor;

	template<class T> Type* type_of();
	template<class T> Type* type_of(const T&);
	template<class T, int S> Type* type_of(T (&)[S]);
	template<class T, class C> Type* type_of(T C::*);

} // namespace

#endif // _REFLECTION_FWD_H__
