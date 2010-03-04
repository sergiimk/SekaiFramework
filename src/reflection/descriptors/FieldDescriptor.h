/*========================================================
* FieldDescriptor.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _FIELD_DESCRIPTOR_H__
#define _FIELD_DESCRIPTOR_H__

#include "DataDescriptor.h"

namespace Reflection
{
	/// Class field Descriptor
	/** Not intended to be used directly, use Field instead, that does 'this' fix-up
	 *  when accessing the field of base class.
	 *  @ingroup Reflection */
	class FieldDescriptor : public DataDescriptor
	{
	public:

		/// Ctor
		FieldDescriptor(const char* name, Type* type, UserType* owner, size_t offset, const char* docString = 0)
			: DataDescriptor(RL_DESC_FIELD, name, owner, type, docString)
			, mOffset(offset)
		{
		}

		bool isReadOnly() const
		{
			return false;
		}

		void getValue(void* inst, void* buffer) const
		{
			void* pobj = (char*)inst + mOffset;
			getType()->Assign(buffer, pobj);
		}

		void setValue(void* inst, void* buffer) const
		{
			void* pobj = (char*)inst + mOffset;
			getType()->Assign(pobj, buffer);
		}

		/// Converts value to string
		bool ToString(void* inst, char* buf, size_t size) const
		{
			void* pobj = (char*)inst + mOffset;
			return getType()->ToString(pobj, buf, size);
		}

		/// Restores value from string
		bool TryParse(void * inst, const char* str) const
		{
			void* pobj = (char*)inst + mOffset;
			return getType()->TryParse(pobj, str);
		}

	private:
		size_t mOffset;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Field is a wrapper for FieldDescriptor that adjusts 'this' pointer before accessing data
	/** @ingroup Reflection */
	class Field : public Data
	{
	public:

		Field()
		{ }

		Field(FieldDescriptor* desc, size_t offset)
			: Data(desc, offset)
		{ }

		/// Converts value to string
		bool ToString(void* inst, char* buf, size_t size) const
		{
			return static_cast<FieldDescriptor*>(m_descriptor)->ToString(Module::adjustptr(inst, m_offset), buf, size);
		}

		/// Restores value from string
		bool TryParse(void * inst, const char* str) const
		{
			return static_cast<FieldDescriptor*>(m_descriptor)->TryParse(Module::adjustptr(inst, m_offset), str);
		}
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _FIELD_DESCRIPTOR_H__
