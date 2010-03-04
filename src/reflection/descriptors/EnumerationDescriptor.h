/*========================================================
* EnumerationDescriptor.h
* @author Sergey Mikhtonyuk
* @date 25 October 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ENUMERATIONDESCRIPTOR_H__
#define _ENUMERATIONDESCRIPTOR_H__

#include "TypeDescriptor.h"
#include "platform/platform.h"
#include <stdarg.h>
#include <string.h>

namespace Reflection
{
	static const size_t MAX_ENUM_ENTRIES = 50;

	namespace detail
	{
		struct SEnumEntry
		{
			unsigned int value;
			const char* name;
			static SEnumEntry make_entry(unsigned int v, const char* n)
			{
				SEnumEntry e = { v, n };
				return e;
			}
		};
	} // detail

	/// Descriptor for enumeration members
	/** @ingroup Reflection */
	class EnumerationDescriptor : public TypeDescriptor
	{
	public:

		/// Ctor
		EnumerationDescriptor(UserType* owner)
			: TypeDescriptor(RL_DESC_SERVICE_ENUMERATION, owner, "<enumeration desc>")
		{
		}

		/// Returns the number of enum entries
		size_t NumEntries() const { return m_numEntries; }

		/// Returns the value of entry
		unsigned int getValue(size_t entry) const 
		{
			ASSERT_STRICT(entry < m_numEntries);
			return m_entries[entry].value;
		}

		/// Returns the name of entry
		const char* getName(size_t entry) const
		{
			ASSERT_STRICT(entry < m_numEntries);
			return m_entries[entry].name;
		}

		/// Returns the name by enum value
		const char* getNameByValue(unsigned int val) const
		{
			if(val < m_numEntries && m_entries[val].value == val)
				return m_entries[val].name;

			for(size_t i = 0; i != m_numEntries; ++i)
				if(m_entries[i].value == val)
					return m_entries[i].name;

			return 0;
		}

		/// Searches the value by its name
		bool getValueByName(const char* name, unsigned int& outVal) const
		{
			for(size_t i = 0; i != m_numEntries; ++i)
			{
				if(strcmp(name, m_entries[i].name) == 0)
				{
					outVal = m_entries[i].value;
					return true;
				}
			}
			return false;
		}

		/// Factory method
		static EnumerationDescriptor* Create(UserType* owner, ...)
		{
			EnumerationDescriptor* desc = new EnumerationDescriptor(owner);

			size_t pos = 0;
			va_list vals;
			va_start(vals, owner);

			detail::SEnumEntry entry;
			while(true)
			{
				entry = va_arg(vals, detail::SEnumEntry);
				if(!entry.name)
					break;

				ASSERT_STRICT(pos != MAX_ENUM_ENTRIES);
				if(pos == MAX_ENUM_ENTRIES)
					break;

				desc->m_entries[pos] = entry;
				++pos;
			}

			desc->m_numEntries = pos;

			va_end(vals);
			return desc;
		}

	private:

		detail::SEnumEntry m_entries[MAX_ENUM_ENTRIES];
		size_t m_numEntries;
	};

} // namespace

#endif // _ENUMERATIONDESCRIPTOR_H__
