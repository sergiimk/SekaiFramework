/*========================================================
* stack_container.h
* @author Davydov Max
* @date 24 February 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _STACK_STRING_H___
#define _STACK_STRING_H___

#include <string>
#include "stack_container.h"
#include "noncopyable.h"

//////////////////////////////////////////////////////////////////////////

/// Stack string implementation
/** Internal buffer located on stack. Growing the string beyond the stack capacity
  * will transparently overflow onto the heap.
  * @ingroup Common */
template<size_t stack_capacity = 512, class TChar = char>
class stack_string : public stack_string_container<
	std::basic_string<TChar, std::char_traits<TChar>, stack_allocator<TChar, stack_capacity> >,
	stack_capacity, stack_capacity - 1>
{
public:
	typedef stack_allocator<TChar, stack_capacity> Allocator;
	typedef std::char_traits<TChar> CharTraits;
	typedef std::basic_string<TChar, CharTraits, Allocator> CharString;
	typedef stack_string_container<CharString, stack_capacity, stack_capacity - 1> StackStringContainer;

	/// Empty ctor
	stack_string()
		: StackStringContainer()
	{ }

	/// String ctor
	stack_string(const TChar* s)
		: StackStringContainer()
	{
		this->container().assign(s);
	}

	/// std::string ctor
	stack_string(const std::basic_string<TChar>& s)
		: StackStringContainer()
	{
		this->container().assign(s.c_str());
	}

private:
	/// disallow copy ctor and operator=
	stack_string(const stack_string&);
	const stack_string& operator=(const stack_string&);
};

//////////////////////////////////////////////////////////////////////////


#endif // _STACK_STRING_H___

