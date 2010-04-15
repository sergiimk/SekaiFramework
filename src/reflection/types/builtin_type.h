/*========================================================
* builtin_type.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _BUILTINTYPE_H__
#define _BUILTINTYPE_H__

#include "types/type.h"
#include "custom/parsing_attribute.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////
	// suppress warning about not exported 
	// parsing attribute member
	#pragma warning( push )
	#pragma warning( disable:4251 )
	//////////////////////////////////////////////////////////////////////////

	/// Built-in type class
	/** @ingroup reflection */
	template<class T>
	class builtin_type : public type
	{
	public:
		builtin_type();

	private:

		virtual size_t _attribute_count() const;

		virtual const attribute* _get_attribute(size_t i) const;

		parsing_attribute_t<T> m_parse;
	};

	//////////////////////////////////////////////////////////////////////////
	#pragma warning( pop )
	//////////////////////////////////////////////////////////////////////////

	/// Built-in specialization for void type
	/** @ingroup reflection */
	template<>
	class REFLECTION_API builtin_type<void> : public type
	{
	public:
		builtin_type();
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif //_BUILTINTYPE_H__
