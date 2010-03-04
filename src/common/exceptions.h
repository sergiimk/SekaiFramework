/*========================================================
* exceptions.h
* @author Sergey Mikhtonyuk
* @date 23 February 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _FWK_EXCEPTIONS_H__
#define _FWK_EXCEPTIONS_H__

#include <exception>
#include <string>

class framework_exception : public std::exception
{
public:
    framework_exception() { }
    framework_exception(const char* msg) : m_message(msg) { }
	virtual ~framework_exception() throw() { }
    virtual const char* what() { return m_message.c_str(); }

private:
    std::string m_message;
};

#endif //_FWK_EXCEPTIONS_H__
