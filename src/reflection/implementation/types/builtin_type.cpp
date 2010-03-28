/*========================================================
* builtin_type.cpp
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "types/builtin_type.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	const char* get_type_name(ETypeTag tag)
	{
		switch (tag) { 
			  case T_VOID:
				  return "void";
			  case T_CHAR:
				  return "char";
			  case T_UCHAR:
				  return "unsigned char";
			  case T_SHORT:
				  return "short";
			  case T_USHORT:
				  return "unsigned short";
			  case T_BOOL:
				  return "bool";
			  case T_INT:
				  return "int";
			  case T_UINT:
				  return "unsigned int";
			  case T_LONG:
				  return "long";
			  case T_ULONG:
				  return "unsigned long";
			  case T_LONGLONG:
				  return "long long";
			  case T_ULONGLONG:
				  return "unsigned long long";
			  case T_FLOAT:
				  return "float";
			  case T_DOUBLE:
				  return "double";
			  default:
				  return "unknown";
		}
	}

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	builtin_type<T>::builtin_type()
		: type(detail::type_tag<T>::tag, ARCH_BUILTIN, sizeof(T))
	{
		type::set_name(get_type_name(tag()));
	}

	//////////////////////////////////////////////////////////////////////////

	builtin_type<void>::builtin_type()
		: type(T_VOID, ARCH_BUILTIN, 0)
	{
		type::set_name(get_type_name(tag()));
	}

	//////////////////////////////////////////////////////////////////////////

	template class REFLECTION_API builtin_type<char>;
	template class REFLECTION_API builtin_type<unsigned char>;

	template class REFLECTION_API builtin_type<short>;
	template class REFLECTION_API builtin_type<unsigned short>;

	template class REFLECTION_API builtin_type<int>;
	template class REFLECTION_API builtin_type<unsigned int>;

	template class REFLECTION_API builtin_type<long>;
	template class REFLECTION_API builtin_type<unsigned long>;

	template class REFLECTION_API builtin_type<long long>;
	template class REFLECTION_API builtin_type<unsigned long long>;

	template class REFLECTION_API builtin_type<bool>;
	template class REFLECTION_API builtin_type<float>;
	template class REFLECTION_API builtin_type<double>;

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
