/*========================================================
* attribute.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SF_ATTRIBUTE_H__
#define _SF_ATTRIBUTE_H__

#include "reflection_fwd.h"

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	/// Defines possible attribute types
	/** @ingroup reflection */
	enum EAttributeType
	{
		ATTR_BASE_TYPE,
		ATTR_PARSING,
		ATTR_CONSTRUCTION,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Attribute base class
	/** @ingroup reflection */
	class REFLECTION_API attribute
	{
	public:

		attribute(EAttributeType type);

		// Non-virtual because release is called
		~attribute();

		/// Returns type of the attribute
		EAttributeType get_type() const;

		/// Destroys the attribute
		virtual void release() = 0;

	private:
		attribute(const attribute& other);
		attribute& operator=(const attribute& rhs);

	protected:
		class attribute_impl;

		attribute(attribute_impl* impl);

		attribute_impl* m_impl;
	};

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_SF_ATTRIBUTE_H__
