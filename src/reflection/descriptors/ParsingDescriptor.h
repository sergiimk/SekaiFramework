/*========================================================
* ParsingDescriptor.h
* @author Sergey Mikhtonyuk
* @date 09 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _PARSINGDESCRIPTOR_H__
#define _PARSINGDESCRIPTOR_H__

#include "TypeDescriptor.h"

#include <sstream>
#include <string>

namespace Reflection
{

	/// Describes that type supports conversion to string and parsing
	/** @ingroup Reflection */
	class ParsingDescriptor : public TypeDescriptor
	{
	public:

		/// Ctor
		ParsingDescriptor(UserType* owner)
			: TypeDescriptor(RL_DESC_SERVICE_PARSING, owner, "<parsing desc>")
		{
		}

		/// Converts value to string using the iostream operators
		virtual bool ToString(void* value, char* buf, size_t size) const = 0;

		/// String to value using the iostream operators
		virtual bool TryParse(void* value, const char* str) const = 0;

	};

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	class ParsingDescriptorImpl : public ParsingDescriptor
	{
	public:
		/// Ctor
		ParsingDescriptorImpl(UserType* owner)
			: ParsingDescriptor(owner)
		{
		}

		/// Converts value to string using the iostream operators
		bool ToString(void* value, char* buf, size_t size) const
		{
			std::ostringstream ss;
			ss << *(T*)value;
			std::string t = ss.str();
			strncpy(buf, t.c_str(), std::min(t.size(), size));
			return size > t.size();
		}

		/// String to value using the iostream operators
		bool TryParse(void* value, const char* str) const
		{
			std::istringstream ss(str);
			return !(!( ss >> *(T*)value));
		}
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _PARSINGDESCRIPTOR_H__
