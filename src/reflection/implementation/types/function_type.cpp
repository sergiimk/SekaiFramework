/*========================================================
* function_type.cpp
* @author Sergey Mikhtonyuk
* @date 29 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "types/function_type.h"
#include "type_impl.h"
#include "common/stack_string.h"

namespace reflection
{
	//////////////////////////////////////////////////////////////////////////

	class function_type::function_type_impl : public type::type_impl
	{
	public:
		function_type_impl(generic_invoker inv, bool isMethod, type* rt, type** arguments, int argc)
			: type_impl(isMethod ? T_METHOD : T_FUNCTION, ARCH_FUNCTION, 0)
			, m_invoker(inv)
			, m_retType(rt)
			, m_argc(argc)
		{
			ASSERT_STRICT(rt);
			for(int i = 0; i < argc; ++i)
			{
				ASSERT_STRICT(arguments[i]);
			}

			memcpy(m_argTypes, arguments, sizeof(void*) * argc);
		}

		virtual void print_name() const
		{
			stack_string<> buf;

			*buf += m_retType->name();
			*buf += ' ';

			if(tag() == T_METHOD)
			{
				*buf += m_argTypes[0]->name();
				*buf += "::*";
			}
			
			*buf += '(';

			for(size_t i = tag() == T_METHOD ? 1 : 0; i != m_argc; ++i) 
			{
				*buf += m_argTypes[i]->name();
				if(i != m_argc - 1)
					*buf += ", ";
			}

			*buf += ')';
			
			set_name(buf->c_str());
		}

		type* return_type() const
		{
			return m_retType;
		}

		size_t argument_count() const
		{
			return m_argc;
		}

		type** argument_types() const
		{
			return (type**)m_argTypes;
		}

		void invoke(DelegateBase* deleg, void** args, void* result) const
		{
			m_invoker(deleg, args, result);
		}

	private:
		generic_invoker	m_invoker;
		type*			m_retType;
		type*			m_argTypes[DELEG_MAX_INVOKE_PARAMS];
		size_t			m_argc;
	};

	//////////////////////////////////////////////////////////////////////////
	// function_type
	//////////////////////////////////////////////////////////////////////////

	function_type::function_type(generic_invoker inv, bool isMethod, type* rt, type** arguments, int argc)
		: type(new function_type_impl(inv, isMethod, rt, arguments, argc))
	{
		m_impl = static_cast<function_type_impl*>(type::m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	type* function_type::return_type() const
	{
		return m_impl->return_type();
	}

	//////////////////////////////////////////////////////////////////////////

	size_t function_type::argument_count() const
	{
		return m_impl->argument_count();
	}

	//////////////////////////////////////////////////////////////////////////

	type** function_type::argument_types() const
	{
		return m_impl->argument_types();
	}

	//////////////////////////////////////////////////////////////////////////

	void function_type::invoke(DelegateBase *deleg, void **args, void *result) const
	{
		m_impl->invoke(deleg, args, result);
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
