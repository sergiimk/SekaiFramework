/*========================================================
* BuiltInType.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _BUILTINTYPE_H__
#define _BUILTINTYPE_H__

#include "Type.h"
#include "typetraits.h"
#include <string.h>
#include <algorithm>
#include <sstream>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Type implementation for built-in types
	/** @ingroup Reflection */
	template<class T>
	class BuiltInType : public Type
	{
	public:
		size_t Name(char* buf, size_t size) const 
		{ 
			strncpy(buf, detail::get_type_name(Tag()), size);
			return strlen(buf) + 1;
		}

		size_t FullName(char* buf, size_t size) const 
		{
			return Name(buf, size);
		}

		ETypeTag Tag() const { return detail::r_type_traits<T>::type_tag; }

		EArchType ArchType() const { return RL_ARCH_BUILTIN; }

		size_t Size() const { return sizeof(T); }

		void Assign(void* to, void* val) const 
		{ 
			memcpy(to, val, sizeof(T));
		}

		bool ToString(void* value, char* buf, size_t size) const
		{
			std::ostringstream ss;
			ss << *(T*)value;
			std::string t = ss.str();
			strncpy(buf, t.c_str(), std::min(t.size() + 1, size));
			return size > t.size();
		}

		bool TryParse(void * value, const char* str) const
		{
			std::istringstream ss(str); 
			return !(!( ss >> *(T*)value));
		}

		bool Equal(const Type* other) const
		{
			if(	ArchType() != other->ArchType())
				return false;

			return Tag() == other->Tag();
		}

		void* CreateInstance() const { return new T(); }

		void DestroyInstance(void* v) const { delete ((T*)v); }
	};

	//////////////////////////////////////////////////////////////////////////

	template<>
	class BuiltInType<void> : public Type
	{
	public:
		size_t Name(char* buf, size_t size) const 
		{ 
			strncpy(buf, detail::get_type_name(Tag()), size);
			return strlen(buf);
		}
		size_t FullName(char* buf, size_t size) const { return Name(buf, size); }
		ETypeTag Tag() const { return RL_T_VOID; }
		size_t Size() const { return 0; }
		void Assign(void* to, void* val) const { }
		bool ToString(void* value, char* buf, size_t size) const
		{
			strncpy(buf, "void", std::min((size_t)5, size));
			return size > 4;
		}
		bool TryParse(void * value, const char* str) const { return false; }
		EArchType ArchType() const { return RL_ARCH_BUILTIN; }
		bool Equal(const Type* other) const
		{
			if(	ArchType() != other->ArchType())
				return false;

			return Tag() == other->Tag();
		}
		void* CreateInstance() const { NOT_IMPLEMENTED(); }
		void DestroyInstance(void* v) const { }
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _BUILTINTYPE_H__

