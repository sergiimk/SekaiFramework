/*========================================================
* directory_iterator.cpp
* @author Sergey Mikhtonyuk
* @date 21 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "directory_iterator.h"
#include "path.h"
#include "module/exception.h"
#include "common/stack_string.h"
#include <string>

#if defined OS_WINDOWS
#	include <windows.h>
#endif

namespace filesystem
{

	//////////////////////////////////////////////////////////////////////////
	
	struct directory_iterator::directory_iterator_impl
	{
		
		//////////////////////////////////////////////////////////////////////////

		directory_iterator_impl(const path& _p) 
			: p(_p)
			, h(INVALID_HANDLE_VALUE)
			, steps(0)
		{
			if(!_p.is_directory())
				throw Module::InvalidArgumentException("Path does not specify a directory");

			stack_string<> path(p.c_str());
			*path += "\\*";

			WIN32_FIND_DATAA data;
			h = ::FindFirstFileA(path->c_str(), &data);

			if(h != INVALID_HANDLE_VALUE)
				entry = data.cFileName;
		}

		//////////////////////////////////////////////////////////////////////////

		directory_iterator_impl(const directory_iterator_impl& other) 
			: p(other.p)
		{
			clone_handle(other);
		}

		//////////////////////////////////////////////////////////////////////////

		~directory_iterator_impl()
		{
			cleanup();
		}

		//////////////////////////////////////////////////////////////////////////

		directory_iterator_impl& operator=(const directory_iterator_impl& rhs) 
		{
			if(this == &rhs)
				return *this;

			cleanup();
			p = rhs.p;

			clone_handle(rhs);
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////

		operator bool() const
		{
			return h != INVALID_HANDLE_VALUE;
		}

		//////////////////////////////////////////////////////////////////////////

		directory_iterator_impl& operator++()
		{
			assert(h != INVALID_HANDLE_VALUE);
			++steps;

			WIN32_FIND_DATAA data;
			if( ! FindNextFileA(h, &data) )
				cleanup();

			if(h != INVALID_HANDLE_VALUE)
				entry = data.cFileName;

			return *this;
		}

		//////////////////////////////////////////////////////////////////////////

		directory_iterator_impl operator++(int)
		{
			directory_iterator_impl ret(*this);
			++*this;
			return ret;
		}

		//////////////////////////////////////////////////////////////////////////

		path current() const
		{
			assert(h != INVALID_HANDLE_VALUE);
			return path(entry.c_str());
		}

		//////////////////////////////////////////////////////////////////////////

		bool clone_handle(const directory_iterator_impl& other)
		{
			h = INVALID_HANDLE_VALUE;

			if(other.h == INVALID_HANDLE_VALUE)
				return true;

			// Here we can't just copy handle
			// we need to do deep copy, so
			// just repeat the same number of steps
			// made to 'other' handle

			stack_string<> path(other.p.c_str());
			*path += "\\*";

			WIN32_FIND_DATAA data;
			h = ::FindFirstFileA(path->c_str(), &data);

			if(h == INVALID_HANDLE_VALUE)
				return false;

			steps = 0;
			while(steps != other.steps && FindNextFileA(h, &data))
				++steps;

			if(steps != other.steps)
			{
				cleanup();
				return false;
			}

			entry = data.cFileName;
			return true;
		}

		//////////////////////////////////////////////////////////////////////////

		void cleanup()
		{
			if(h != INVALID_HANDLE_VALUE)
			{
				FindClose(h);
				h = INVALID_HANDLE_VALUE;
				entry.clear();
			}
		}

		//////////////////////////////////////////////////////////////////////////

		std::string entry;
		HANDLE h;
		path p;
		size_t steps; // used in deep copying of handle

		//////////////////////////////////////////////////////////////////////////

	};

	//////////////////////////////////////////////////////////////////////////

	directory_iterator::directory_iterator(const path& p)
		: m_impl(new directory_iterator_impl(p))
	{
	}

	//////////////////////////////////////////////////////////////////////////

	directory_iterator::directory_iterator(const directory_iterator& other)
		: m_impl(new directory_iterator_impl(*other.m_impl))
	{
	}

	//////////////////////////////////////////////////////////////////////////

	directory_iterator::~directory_iterator()
	{
		delete m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	directory_iterator& directory_iterator::operator=(const directory_iterator& rhs)
	{
		if(this == &rhs)
			return *this;

		*m_impl = *rhs.m_impl;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	directory_iterator::operator bool() const
	{
		return *m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	directory_iterator& directory_iterator::operator++()
	{
		++*m_impl;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	directory_iterator directory_iterator::operator++(int)
	{
		directory_iterator ret(*this);
		++*this;
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	path directory_iterator::current() const
	{
		return m_impl->current();
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
