/*========================================================
* parsing_attribute.h
* @author Sergey Mikhtonyuk
* @date 04 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _PARSING_ATTRIBUTE_H__
#define _PARSING_ATTRIBUTE_H__

#include "attribute.h"
#include <sstream>
#include <string>

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	/// Attribute that allows to parse and convert type values to string
	/** @ingroup reflection */
	class REFLECTION_API parsing_attribute : public attribute
	{
	public:
		parsing_attribute() : attribute(ATTR_PARSING) { }

		/// Converts value to string using the iostream operators
		virtual bool to_string(void* value, char* buf, size_t size) const = 0;

		/// String to value using the iostream operators
		virtual bool try_parse(void* value, const char* str) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	class parsing_attribute_t : public parsing_attribute
	{
	public:
		/// Converts value to string using the iostream operators
		bool to_string(void* value, char* buf, size_t size) const
		{
			std::ostringstream ss;
			ss << *(T*)value;
			std::string t = ss.str();
			strncpy(buf, t.c_str(), std::min(t.size() + 1, size));
			return size > t.size() + 1;
		}

		/// String to value using the iostream operators
		bool try_parse(void* value, const char* str) const
		{
			std::istringstream ss(str);
			return !(!( ss >> *(T*)value));
		}

		virtual parsing_attribute_t<T>* clone() const
		{
			return new parsing_attribute_t<T>();
		}

		virtual void release()
		{
			delete this;
		}
	};

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_PARSING_ATTRIBUTE_H__
