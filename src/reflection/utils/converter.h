/*========================================================
* converter.h
* @author Sergey Mikhtonyuk
* @date 06 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CONVERTER_H__
#define _CONVERTER_H__

#include "reflection_fwd.h"

namespace reflection
{
	
	/// Encapsulates type conversion logic
	/** @ingroup reflection */
	class REFLECTION_API converter
	{
	public:

		/// Converts value to string
		static bool to_string(const value_type_pair& vt, char* buf, size_t size);

		/// Parses string into a value
		static bool try_parse(const value_type_pair& vt, const char* str);
	};

} // namespace

#endif //_CONVERTER_H__
