/*========================================================
* activator.cpp
* @author Sergey Mikhtonyuk
* @date 11 Apr 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "utils/activator.h"
#include "types/function_type.h"
#include "custom/construction_attribute.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	const construct_attribute* activator::find_ctor(const type &t, const type* argv[], size_t argc)
	{
		for(type::attribute_iterator it = t.attributes_begin(),
			end = t.attributes_end();
			it != end; ++it)
		{
			if(it->get_type() != ATTR_CONSTRUCTION)
				continue;
			
			const construct_attribute* ca = static_cast<const construct_attribute*>(&*it);
			if(suitable_params(ca->ctor_type(), argv, argc))
				return ca;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void* activator::create_instance(const type& t, value_type_pair argv[], size_t argc)
	{
		const type* argv_t[delegates::MAX_INVOKE_ARGS];
		void* argv_i[delegates::MAX_INVOKE_ARGS];

		for(size_t i = 0; i != argc; ++i)
		{
			argv_t[i] = argv[i].Type;
			argv_i[i] = argv[i].Value;
		}

		const construct_attribute* ctor = find_ctor(t, argv_t, argc);
		if(!ctor)
			return 0;
		return ctor->create_instance(argv_i);
	}

	//////////////////////////////////////////////////////////////////////////

	void activator::destroy_instance(const type& t, void* inst)
	{
		for(type::attribute_iterator it = t.attributes_begin(),
			end = t.attributes_end();
			it != end; ++it)
		{
			if(it->get_type() != ATTR_CONSTRUCTION)
				continue;

			const construct_attribute* ca = static_cast<const construct_attribute*>(&*it);
			ca->destroy_instance(inst);
			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	bool activator::suitable_params(const function_type &ft, const type* argv[], size_t argc)
	{
		size_t fargc = ft.argument_count();
		if(fargc != argc)
			return false;

		type** fargv = ft.argument_types();

		for(size_t i = 0; i != argc; ++i)
			if(!fargv[i]->equal(argv[i]))
				return false;

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
