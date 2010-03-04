/*========================================================
* DataDescriptor.h
* @author Sergey Mikhtonyuk
* @date 25 June 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _DATADESCRIPTOR_H__
#define _DATADESCRIPTOR_H__

#include "TypeDescriptor.h"

namespace Reflection
{
	/// Abstraction above field and accessor for uniform use
	/** @ingroup Reflection */
	class DataDescriptor : public TypeDescriptor
	{
	protected:
		DataDescriptor(DescriptorType dt, const char* name, UserType* owner, Type* type, const char* docString)
			: TypeDescriptor(dt, owner, name, docString)
			, m_dataType(type)
		{
			ASSERT_STRICT(type);
		}

	public:

		/// Returns data type
		Type* getType() const { return m_dataType; }

		/// Checks if data is read-only
		virtual bool isReadOnly() const = 0;

		/// Copies the field value to buffer
		virtual void getValue(void* inst, void* buffer) const = 0;

		/// Sets the value from one in the buffer
		virtual void setValue(void* inst, void* buffer) const = 0;

	private:
		Type* m_dataType;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Data is a wrapper for DataDescriptor that adjusts 'this' pointer before accessing data
	/** @ingroup Reflection */
	class Data
	{
	public:

		Data() : m_descriptor(0)
		{ }

		Data(DataDescriptor* desc, size_t offset)
			: m_descriptor(desc)
			, m_offset(offset)
		{ }

		bool isValid() const
		{
			return m_descriptor != 0;
		}

		/// Returns data type
		Type* getType() const 
		{ 
			return m_descriptor->getType(); 
		}

		/// Checks if data is read-only
		bool isReadOnly() const 
		{ 
			return m_descriptor->isReadOnly(); 
		}

		/// Copies the field value to buffer
		void getValue(void* inst, void* buffer) const
		{
			m_descriptor->getValue(Module::adjustptr(inst, m_offset), buffer);
		}

		/// Sets the value from one in the buffer
		void setValue(void* inst, void* buffer) const
		{
			m_descriptor->setValue(Module::adjustptr(inst, m_offset), buffer);
		}

	protected:
		DataDescriptor* m_descriptor;
		size_t m_offset;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _DATADESCRIPTOR_H__
