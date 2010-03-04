/*========================================================
* BaseType.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _BASETYPE_H__
#define _BASETYPE_H__

#include "TypeDescriptor.h"
#include "platform/platform.h"

namespace Reflection
{
	/// Describes base class of the type
	/** @ingroup Reflection */
	class BaseType : public TypeDescriptor
	{
	public:
		/// Ctor
		BaseType(const char* name, UserType* base, UserType* owner, unsigned long offset)
			: TypeDescriptor(RL_DESC_BASE, owner, name)
			, m_baseType(base)
			, m_offset(offset)
		{
			ASSERT_STRICT(base);
		}

		/// Returns the base type
		UserType* getBaseType() const
		{
			return m_baseType;
		}

		/// Returns offset of the base from 'this' of derived
		unsigned long getThisOffset() const
		{
			return m_offset;
		}

	private:
		UserType* m_baseType;
		unsigned long m_offset;
	};

} // namespace

#endif // _BASETYPE_H__
