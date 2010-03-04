/*========================================================
* typetraits.cpp
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "TypeTag.h"
#include "Type.h"
#include <string.h>

namespace Reflection
{
	namespace detail
	{
	
		const char* get_type_name(ETypeTag tag)
		{
			switch (tag) { 
			  case RL_T_VOID:
				  return "void";
			  case RL_T_CHAR:
				  return "char";
			  case RL_T_UCHAR:
				  return "unsigned char";
			  case RL_T_SHORT:
				  return "short";
			  case RL_T_USHORT:
				  return "unsigned short";
			  case RL_T_BOOL:
				  return "bool";
			  case RL_T_INT:
				  return "int";
			  case RL_T_UINT:
				  return "unsigned int";
			  case RL_T_LONG:
				  return "long";
			  case RL_T_ULONG:
				  return "unsigned long";
			  case RL_T_LONGLONG:
				  return "long long";
			  case RL_T_ULONGLONG:
				  return "unsigned long long";
			  case RL_T_FLOAT:
				  return "float";
			  case RL_T_DOUBLE:
				  return "double";
			  default:
				  return "unknown";
			}
		}


		size_t type_get_name_safe(Type* t, char* buffer, size_t size)
		{
			size_t p = 0;

			if(t)
			{
				p = t->Name(buffer, size);
			}
			else
			{
				strncpy(buffer, detail::get_type_name(RL_T_UNKNOWN), size);
				p = strlen(buffer) + 1;
			}
			return p;
		}


	} // detail

} // namespace
