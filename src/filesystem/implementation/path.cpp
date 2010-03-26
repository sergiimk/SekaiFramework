/*========================================================
* path.cpp
* @author Sergey Mikhtonyuk
* @date 20 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "path.h"
#include "directory_iterator.h"
#include "module/exception.h"
#include "common/stack_string.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#if defined OS_WINDOWS
#	include <windows.h>
#endif

namespace filesystem
{
	//////////////////////////////////////////////////////////////////////////

	static bool is_sep(char c)
	{
		const char* seps = path::separators();
		while(*seps)
		{
			if(c == *seps) return true;
			++seps;
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool pathcmp(const char* s1, const char* s2)
	{
		for(; *s1 && *s2; ++s1, ++s2)
		{
			if(*s1 != *s2
				&& !(is_sep(*s1) && is_sep(*s2))
#if defined OS_WINDOWS
				&& (tolower(*s1) != tolower(*s2))
#endif
				)
				return false;
		}
		return *s1 == '\0' && *s2 == '\0';
	}

	//////////////////////////////////////////////////////////////////////////
	// path impl
	//////////////////////////////////////////////////////////////////////////

	struct path::path_impl
	{
		//////////////////////////////////////////////////////////////////////////

		path_impl() 
		{ }

		//////////////////////////////////////////////////////////////////////////

		path_impl(const char* p)
		{
			for(const char* pp = p; *pp; ++pp)
				if(is_bad_path_symbol(*pp))
					throw Module::InvalidArgumentException("Invalid symbols in the path");

			size_t l = strlen(p);
			while(l-- > 1 && is_sep(p[l]))
				;

			str.assign(p, l + 1);
		}

		//////////////////////////////////////////////////////////////////////////

		path_impl(const path_impl& other)
			: str(other.str)
		{ }

		//////////////////////////////////////////////////////////////////////////

		path_impl& operator=(const path_impl& rhs)
		{
			if(this == &rhs)
				return *this;

			str = rhs.str;
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////

		path_impl& operator+=(const path_impl& rhs)
		{
			if(!rhs.str.empty())
			{
				size_t size = str.size();

				const char* as = rhs.str.c_str();
				
				if(size) // skip as a trick for unix root paths
					while(*as && is_sep(*as))
						++as;

				if(size && *as && !is_sep(str[size - 1]))
					str += *path::separators();

				str.append(as);
			}
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////

		bool operator==(const path_impl& rhs) const
		{
			return pathcmp(str.c_str(), rhs.str.c_str());
		}

		//////////////////////////////////////////////////////////////////////////

		bool operator!=(const path_impl& rhs) const
		{
			return ! (*this == rhs );
		}

		//////////////////////////////////////////////////////////////////////////

		std::string str;
	};

	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// path
	//////////////////////////////////////////////////////////////////////////

	path::path() : m_impl(new path_impl()) { }

	//////////////////////////////////////////////////////////////////////////

	path::path(const char* p) : m_impl(new path_impl(p)) { }

	//////////////////////////////////////////////////////////////////////////

	path::path(const path& other) : m_impl(new path_impl(*other.m_impl)) { }

	//////////////////////////////////////////////////////////////////////////

	path::path(const iterator& begin, const iterator& end)
		: m_impl(new path_impl())
	{
		stack_string<> tmp = "";
		bool first = true;
		for(iterator it = begin; it != end; ++it)
		{
			if(!first && !is_sep((*tmp)[tmp->size()-1]))
				*tmp += *separators();
			*tmp += it.element();
			first = false;
		}
		m_impl->str = tmp->c_str();
	}

	//////////////////////////////////////////////////////////////////////////

	path::~path() { delete m_impl; }

	//////////////////////////////////////////////////////////////////////////

	path& path::operator=(const filesystem::path &rhs)
	{
		if(this == &rhs)
			return *this;

		*m_impl = *rhs.m_impl;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::empty() const
	{
		return m_impl->str.empty();
	}

	//////////////////////////////////////////////////////////////////////////

	size_t path::size() const
	{
		return m_impl->str.size();
	}

	//////////////////////////////////////////////////////////////////////////

	const char* path::c_str() const
	{
		return m_impl->str.c_str();
	}

	//////////////////////////////////////////////////////////////////////////

	path::iterator path::begin() const
	{
		return iterator(*this, 0);
	}

	//////////////////////////////////////////////////////////////////////////

	path::iterator path::end() const
	{
		return iterator(*this, m_impl->str.length());
	}

	//////////////////////////////////////////////////////////////////////////

	path& path::operator +=(const path &rhs)
	{
		*m_impl += *rhs.m_impl;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	path path::operator +(const path &rhs) const
	{
		path ret(*this);
		return ret += rhs;
	}

	//////////////////////////////////////////////////////////////////////////

	path& path::operator--()
	{
		iterator it = end();
		slice(begin(), --it);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	path path::operator--(int)
	{
		path ret(*this);
		--*this;
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::operator ==(const path& rhs) const
	{
		return *m_impl == *rhs.m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::operator !=(const path& rhs) const
	{
		return !( *this == rhs );
	}

	//////////////////////////////////////////////////////////////////////////

	const char* path::extension() const
	{
		stack_string<10> sep(separators());
		*sep += '.';
		size_t i = m_impl->str.find_last_of(sep->c_str());
		
		if(i == std::string::npos || m_impl->str[i] != '.')
			return "";

		return &m_impl->str.c_str()[i];
	}

	//////////////////////////////////////////////////////////////////////////

	void path::absolute()
	{
		char buf[512];

		DWORD len = ::GetFullPathNameA(m_impl->str.c_str(), sizeof(buf), buf, 0);
		if(len < sizeof(buf))
		{
			*this = path(len ? buf : "");
			return;
		}

		std::vector<char> vec;
		vec.resize(len + 1);
		::GetFullPathNameA(m_impl->str.c_str(), len + 1, &vec[0], 0);

		*this = path(&vec[0]);
	}

	//////////////////////////////////////////////////////////////////////////

	void path::relative()
	{
		relative(current_dir());
	}

	//////////////////////////////////////////////////////////////////////////

	void path::relative(const path& dir)
	{
		if(!is_absolute() || !dir.is_absolute() || size() <= dir.size())
			return;

		path tmp;

		path prefix = common_prefix(*this, dir);

		if(prefix.size() == dir.size())
		{
			slice(iterator(*this, prefix.size() + 1), end());
			return;
		}

		for(iterator it(dir, prefix.size() + 1), e = dir.end(); it != e; ++it)
			tmp += "..";

		for(iterator it(*this, prefix.size() + 1), e = end(); it != e; ++it)
			tmp += it.element();

		std::swap(m_impl->str, tmp.m_impl->str);
	}

	//////////////////////////////////////////////////////////////////////////

	void path::normcase()
	{
		std::transform(m_impl->str.begin(), m_impl->str.end(), m_impl->str.begin(), tolower);
	}

	//////////////////////////////////////////////////////////////////////////

	void path::normpath()
	{
		path tmp;
		const char sep[2] = { *separators(), '\0' };

		for(iterator it = begin(), e = end(); it != e; ++it)
		{
			if(strcmp(it.element(), "..") != 0 || tmp.empty())
			{
				tmp += it.element();
				tmp += sep;
			}	
			else
				--tmp;
		}
		std::swap(this->m_impl->str, tmp.m_impl->str);
	}

	//////////////////////////////////////////////////////////////////////////

	path path::basename() const
	{
		iterator it = end();
		return path(--it, end());
	}

	//////////////////////////////////////////////////////////////////////////

	path path::dirname() const
	{
		iterator it = end();
		return path(begin(), --it);
	}

	//////////////////////////////////////////////////////////////////////////

	void path::slice(const iterator& begin, const iterator& end)
	{
		stack_string<> tmp = "";
		bool first = true;
		for(iterator it = begin; it != end; ++it)
		{
			if(!first && !is_sep((*tmp)[tmp->size()-1]))
				*tmp += *separators();
			*tmp += it.element();
			first = false;
		}
		m_impl->str = tmp->c_str();
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::exists() const
	{
		return !(get_attributes() & fa_not_found);
	}

	//////////////////////////////////////////////////////////////////////////
	
	bool path::is_absolute() const
	{
#if defined OS_WINDOWS
		return m_impl->str.length() > 1 && m_impl->str[1] == ':';
#elif defined OS_LINUX
		return !m_impl->str.empty() && m_impl->str[0] == '/';
#endif
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::is_file() const
	{
		return (get_attributes() & fa_file) ? true : false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::is_directory() const
	{
		return get_attributes() & fa_directory;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::is_link() const
	{
		throw Module::NotImplementedException(__FUNCTION__);
	}

	//////////////////////////////////////////////////////////////////////////

	int path::get_attributes() const
	{
		DWORD attrs = ::GetFileAttributesA(m_impl->str.c_str());
		if(attrs == 0xffffffff)
		{
			DWORD ec = ::GetLastError();
			if(ec == ERROR_FILE_NOT_FOUND
				|| ec == ERROR_PATH_NOT_FOUND
				|| ec == ERROR_INVALID_NAME
				|| ec == ERROR_INVALID_DRIVE
				|| ec == ERROR_INVALID_PARAMETER
				|| ec == ERROR_BAD_PATHNAME
				|| ec == ERROR_BAD_NETPATH)
			{
				return fa_not_found;
			}
			return fa_unknown;
		}
		int ret = (attrs & FILE_ATTRIBUTE_DIRECTORY) ? fa_directory : fa_file;
		if(attrs & FILE_ATTRIBUTE_HIDDEN) ret |= fa_hidden;
		if(attrs & FILE_ATTRIBUTE_READONLY) ret |= fa_readonly;
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	directory_iterator path::list_dir() const
	{
		return directory_iterator(*this);
	}

	//////////////////////////////////////////////////////////////////////////

	const char* path::separators() 
	{ 
		return "\\/";
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::is_bad_filename_symbol(char c)
	{
		unsigned char code = (unsigned char)c;
		return code < 32 || c == '"' || c == '<' || c == '>' || c == '|' 
			 || c == ':' || c == '*' || c == '?' || c == '\\' || c == '/' ;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::is_bad_path_symbol(char c)
	{
		unsigned char code = (unsigned char)c;
		return code < 32 || c == '"' || c == '<' || c == '>' || c == '|';
	}

	//////////////////////////////////////////////////////////////////////////

	path path::common_prefix(const path& p1, const path& p2)
	{
		iterator it1 = p1.begin(), e1 = p1.end();
		iterator it2 = p2.begin(), e2 = p2.end();

		for(; it1 != e1 
			&& it2 != e2 
			&& pathcmp(it1.element(), it2.element());
		++it1, ++it2)
			;
		return path(p1.begin(), it1);
	}

	//////////////////////////////////////////////////////////////////////////

	path path::current_dir()
	{
		char buf[512];
		DWORD len = ::GetCurrentDirectoryA(sizeof(buf), buf);
		if(len < sizeof(buf))
			return path(len ? buf : "");

		std::vector<char> vec;
		vec.resize(len + 1);
		::GetCurrentDirectoryA(len + 1, &vec[0]);

		return path(&vec[0]);
	}

	//////////////////////////////////////////////////////////////////////////

	path path::temp_dir()
	{
		char buf[_MAX_PATH];
		::GetTempPathA(_MAX_PATH, buf);
		return path(buf);
	}

	//////////////////////////////////////////////////////////////////////////

	path path::temp_file_name(const path& p, const char* prefix)
	{
		char buf[_MAX_PATH];
		::GetTempFileNameA(p.c_str(), prefix, 0, buf);
		return path(buf);
	}
	
	//////////////////////////////////////////////////////////////////////////

	std::ostream& operator<<(std::ostream& os, const path& p)
	{
		os << p.c_str();
		return os;
	}

	//////////////////////////////////////////////////////////////////////////

	std::istream& operator>>(std::istream& is, path& p)
	{
		std::string s;
		is >> s;
		p = path(s.c_str());
		return is;
	}

	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// path iterator impl
	//////////////////////////////////////////////////////////////////////////

	struct path::iterator::iterator_impl
	{

		//////////////////////////////////////////////////////////////////////////

		iterator_impl(const path& parent, size_t position)
			: p(&parent)
			, pos(position)
			, pstr(&parent.m_impl->str)
		{
			set_element(pos);
		}

		//////////////////////////////////////////////////////////////////////////

		iterator_impl(const iterator_impl& other)
			: p(other.p)
			, pos(other.pos)
			, pstr(other.pstr)
			, element(other.element)
		{ }

		//////////////////////////////////////////////////////////////////////////

		iterator_impl& operator=(const iterator_impl& rhs)
		{
			if(this == &rhs)
				return *this;

			p = rhs.p;
			pos = rhs.pos;
			pstr = rhs.pstr;
			element = rhs.element;
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////

		iterator_impl& operator++()
		{
			assert(pstr->c_str()[pos]);
			pos += element.size();
			pos = skip_seps(pos);
			set_element(pos);
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////

		iterator_impl operator++(int)
		{
			iterator_impl ret(*this);
			++*this;
			return ret;
		}

		//////////////////////////////////////////////////////////////////////////

		iterator_impl& operator--()
		{
			size_t np = rskip_seps(pos);
			np = rnext_sep(np);
			assert(np != pos);
			pos = np;
			set_element(np);
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////

		iterator_impl operator--(int)
		{
			iterator_impl ret(*this);
			--*this;
			return ret;
		}

		//////////////////////////////////////////////////////////////////////////

		operator bool() const
		{
			return pos != pstr->size();
		}

		//////////////////////////////////////////////////////////////////////////

		bool operator==(const iterator_impl& rhs) const
		{
			assert(rhs.p == p);
			return pos == rhs.pos;
		}

		//////////////////////////////////////////////////////////////////////////

		bool operator!=(const iterator_impl& rhs) const
		{
			return !(*this == rhs);
		}

		//////////////////////////////////////////////////////////////////////////

		bool operator<(const iterator_impl& rhs) const
		{
			assert(rhs.p == p);
			return pos < rhs.pos;
		}

		//////////////////////////////////////////////////////////////////////////

		bool operator<=(const iterator_impl& rhs) const
		{
			assert(rhs.p == p);
			return pos <= rhs.pos;
		}

		//////////////////////////////////////////////////////////////////////////

		bool operator>(const iterator_impl& rhs) const
		{
			assert(rhs.p == p);
			return pos > rhs.pos;
		}

		//////////////////////////////////////////////////////////////////////////

		bool operator>=(const iterator_impl& rhs) const
		{
			assert(rhs.p == p);
			return pos >= rhs.pos;
		}

		//////////////////////////////////////////////////////////////////////////

		void set_element(size_t start)
		{
			element.clear();
			size_t end = next_sep(start);
			if(start != end)
				element.assign(&(*pstr)[start], end - start);
			else if(!start && !pstr->empty())
				element += *path::separators();
		}

		//////////////////////////////////////////////////////////////////////////

		size_t skip_seps(size_t _p) const
		{
			const char* s = pstr->c_str();
			while( s[_p] && is_sep(s[_p]) )
				++_p;
			return _p;
		}

		size_t rskip_seps(size_t _p) const
		{
			const char* s = pstr->c_str();
			while (_p-- && is_sep(s[_p]))
				;
			return _p + 1;
		}

		//////////////////////////////////////////////////////////////////////////

		size_t next_sep(size_t _p) const
		{
			const char* s = pstr->c_str();
			while( s[_p] && !is_sep(s[_p]) )
				++_p;
			return _p;
		}

		size_t rnext_sep(size_t _p) const
		{
			const char* s = pstr->c_str();
			while (_p-- && !is_sep(s[_p]))
				;
			return _p + 1;
		}

		//////////////////////////////////////////////////////////////////////////

		std::string element;
		const path* p;
		std::string* pstr;
		size_t pos;
	};

	//////////////////////////////////////////////////////////////////////////





	//////////////////////////////////////////////////////////////////////////
	// path iterator
	//////////////////////////////////////////////////////////////////////////

	path::iterator::iterator(const path& parent, size_t position) 
		: m_impl(new iterator_impl(parent, position))
	{ }

	//////////////////////////////////////////////////////////////////////////

	path::iterator::iterator(const path::iterator &other)
		: m_impl(new iterator_impl(*other.m_impl))
	{ }

	//////////////////////////////////////////////////////////////////////////

	path::iterator::~iterator()
	{
		delete m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	path::iterator& path::iterator::operator=(const path::iterator& rhs)
	{
		if(this == &rhs)
			return *this;

		*m_impl = *rhs.m_impl;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	path::iterator& path::iterator::operator++()
	{
		++*m_impl;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	path::iterator path::iterator::operator++(int)
	{
		iterator ret(*this);
		++*this;
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	path::iterator& path::iterator::operator--()
	{
		--*m_impl;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	path::iterator path::iterator::operator--(int)
	{
		iterator ret(*this);
		--*this;
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	path::iterator::operator bool() const
	{
		return *m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::iterator::operator ==(const path::iterator &rhs) const
	{
		return *m_impl == *rhs.m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::iterator::operator !=(const path::iterator &rhs) const
	{
		return !(*m_impl == *rhs.m_impl);
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::iterator::operator<(const iterator& rhs) const
	{
		return *m_impl < *rhs.m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::iterator::operator<=(const iterator& rhs) const
	{
		return *m_impl <= *rhs.m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::iterator::operator>(const iterator& rhs) const
	{
		return *m_impl > *rhs.m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	bool path::iterator::operator>=(const iterator& rhs) const
	{
		return *m_impl >= *rhs.m_impl;
	}

	//////////////////////////////////////////////////////////////////////////

	const char* path::iterator::element() const
	{
		return m_impl->element.c_str();
	}

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
