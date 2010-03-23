/*========================================================
* exception.cpp
* @author Sergey Mikhtonyuk
* @date 21 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "exception.h"
#include <string.h>

namespace Module
{
	//////////////////////////////////////////////////////////////////////////

	Exception::Exception(const char* msg, int code)
		: m_code(code)
		, m_nested(0)
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}

	//////////////////////////////////////////////////////////////////////////

	Exception::Exception(const char* msg, const char* arg, int code)
		: m_code(code)
		, m_nested(0)
	{
		size_t ms = strlen(msg);
		size_t s = ms + strlen(arg) + 2;

		m_msg = new char[s];

		strcpy(m_msg, msg);
		m_msg[ms] = ' ';

		strcpy(m_msg + ms + 1, arg);
	}

	//////////////////////////////////////////////////////////////////////////

	Exception::Exception(const char* msg, const Exception& nested, int code)
		: m_code(code)
		, m_nested(nested.clone())
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}

	//////////////////////////////////////////////////////////////////////////

	Exception::Exception(const Exception& other)
		: m_code(other.m_code)
		, m_nested(other.m_nested ? other.m_nested->clone() : 0)
	{
		m_msg = new char[strlen(other.m_msg) + 1];
		strcpy(m_msg, other.m_msg);
	}

	//////////////////////////////////////////////////////////////////////////

	Exception::~Exception() throw()
	{
		if(m_nested)
			m_nested->release();
		delete[] m_msg;
	}

	//////////////////////////////////////////////////////////////////////////

	Exception& Exception::operator = (const Exception& exc)
	{
		if(&exc == this)
			return *this;

		if(m_nested)
		{
			m_nested->release();
			m_nested = 0;
		}
		delete[] m_msg;

		size_t s = strlen(exc.m_msg);
		m_msg = new char[s + 1];
		strcpy(m_msg, exc.m_msg);

		if(exc.m_nested)
			m_nested = exc.m_nested->clone();
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	const char* Exception::className() const throw()
	{
		return "Exception";
	}

	//////////////////////////////////////////////////////////////////////////

	const char* Exception::what() const throw()
	{
		return m_msg;
	}

	//////////////////////////////////////////////////////////////////////////

	Exception* Exception::clone() const
	{
		return new Exception(*this);
	}

	//////////////////////////////////////////////////////////////////////////

	void Exception::release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////

	void Exception::rethrow() const
	{
		throw *this;
	}

	//////////////////////////////////////////////////////////////////////////

	SF_IMPLEMENT_EXCEPTION(LogicException, Exception)
	SF_IMPLEMENT_EXCEPTION(InvalidArgumentException, LogicException)
	SF_IMPLEMENT_EXCEPTION(NotImplementedException, LogicException)
	SF_IMPLEMENT_EXCEPTION(RangeException, LogicException)

	//////////////////////////////////////////////////////////////////////////

	SF_IMPLEMENT_EXCEPTION(RuntimeException, Exception)
	SF_IMPLEMENT_EXCEPTION(NotFoundException, RuntimeException)
	SF_IMPLEMENT_EXCEPTION(ExistsException, RuntimeException)
	SF_IMPLEMENT_EXCEPTION(TimeoutException, RuntimeException)
	SF_IMPLEMENT_EXCEPTION(NoPermissionException, RuntimeException)
	SF_IMPLEMENT_EXCEPTION(IOException, RuntimeException)	

	//////////////////////////////////////////////////////////////////////////
	
} // namespace
