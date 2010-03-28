/*========================================================
* type_impl.h
* @author Sergey Mikhtonyuk
* @date 28 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPEIMPL_H__
#define _TYPEIMPL_H__

#include "types/type.h"
#include <string>
#include <vector>

namespace reflection
{

	//////////////////////////////////////////////////////////////////////////

	/// Implementation of Type
	/** @ingroup reflection */
	class type::type_impl
	{
	public:

		type_impl(ETypeTag tag, EArchType arch, size_t size);

		virtual ~type_impl();

		ETypeTag tag() const;

		EArchType arch_type() const;

		size_t size() const;

		void set_name(const char* name) const;

		const char* get_name() const;

		void add_member(const member& mem);

		void add_attribute(const attribute& attr);

	protected:

		virtual void print_name() const;

	private:
		typedef std::vector<member*> TMemberContainer;
		typedef std::vector<std::pair<attribute*, member*> > TAttributeContainer;

		TMemberContainer m_members;
		TAttributeContainer m_attributes;
		mutable std::string m_name;
		size_t m_size;
		ETypeTag m_tag;
		EArchType m_archt;
	};

	//////////////////////////////////////////////////////////////////////////

	inline ETypeTag type::type_impl::tag() const
	{
		return m_tag;
	}

	//////////////////////////////////////////////////////////////////////////

	inline EArchType type::type_impl::arch_type() const
	{
		return m_archt;
	}

	//////////////////////////////////////////////////////////////////////////

	inline size_t type::type_impl::size() const
	{
		return m_size;
	}

	//////////////////////////////////////////////////////////////////////////

	inline void type::type_impl::set_name(const char* name) const
	{
		m_name = name;
	}

	//////////////////////////////////////////////////////////////////////////

	inline const char* type::type_impl::get_name() const
	{
		if(m_name.empty())
			print_name();
		return m_name.c_str();
	}

	//////////////////////////////////////////////////////////////////////////

	inline void type::type_impl::print_name() const
	{
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_TYPEIMPL_H__
