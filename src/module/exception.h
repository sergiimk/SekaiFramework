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

namespace Module
{

	/// Base exception class
	/** @ingroup Common */
	class Exception: public std::exception
	{
	public:

		Exception(const char* msg, int code = 0);

		Exception(const char* msg, const char* arg, int code = 0);

		/// clones the nested exception
		Exception(const char* msg, const Exception& nested, int code = 0);

		Exception(const Exception& other);

		~Exception() throw();

		Exception& operator = (const Exception& exc);

		/// Returns the name of the exception class
		virtual const char* className() const throw();

		/// Returns a static string describing the exception
		const char* message() const;

		/// Same as message(), for compatibility with std::exception
		virtual const char* what() const throw();
		
		/// Returns a pointer to the nested exception
		const Exception* nested() const;

		/// Returns the exception code if defined
		int code() const;

		/// Creates an exact copy of the exception.
		/** The copy can later be thrown again by
		  * invoking rethrow() on it */
		virtual Exception* clone() const;

		/// Releases exception, use only on cloned ones
		virtual void release();

		/// (Re)Throws the exception.
		/** This is useful for temporarily storing a
		  * copy of an exception, then throwing it again
		  * @see clone */
		virtual void rethrow() const;

	private:
		char*		m_msg;
		Exception*  m_nested;
		int			m_code;
	};

	//////////////////////////////////////////////////////////////////////////

	inline const Exception* Exception::nested() const
	{
		return m_nested;
	}

	//////////////////////////////////////////////////////////////////////////

	inline const char* Exception::message() const
	{
		return m_msg;
	}

	//////////////////////////////////////////////////////////////////////////

	inline int Exception::code() const
	{
		return m_code;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

#define SF_DECLARE_EXCEPTION(Name, Base)									\
	class Name: public Base													\
	{																		\
	public:																	\
		Name(const char* msg, int code = 0);								\
		Name(const char* msg, const char* arg, int code = 0);				\
		Name(const char* msg, const Exception& nested, int code = 0);		\
		Name(const Name& other);										\
		~Name() throw();													\
		Name& operator = (const Name& exc);									\
		const char* className() const throw();								\
		Name* clone() const;												\
		void release();														\
		void rethrow() const;												\
	};

	//////////////////////////////////////////////////////////////////////////

#define SF_IMPLEMENT_EXCEPTION(Name, Base)														\
	Name::Name(const char* msg, int code) : Base(msg, code) { }									\
	Name::Name(const char* msg, const char* arg, int code) : Base(msg, arg, code) { }			\
	Name::Name(const char* msg, const Exception& nested, int code) : Base(msg, nested, code) { }\
	Name::Name(const Name& other) : Base(other) { }												\
	Name::~Name() throw() { }																	\
	Name& Name::operator = (const Name& exc) { Base::operator = (exc); return *this; }			\
	const char* Name::className() const throw() { return #Name; }								\
	Name* Name::clone() const { return new Name(*this); }										\
	void Name::release() { delete this; }														\
	void Name::rethrow() const { throw *this; }

	//////////////////////////////////////////////////////////////////////////

	SF_DECLARE_EXCEPTION(LogicException, Exception)
	SF_DECLARE_EXCEPTION(InvalidArgumentException, LogicException)
	SF_DECLARE_EXCEPTION(NotImplementedException, LogicException)
	SF_DECLARE_EXCEPTION(RangeException, LogicException)

	//////////////////////////////////////////////////////////////////////////

	SF_DECLARE_EXCEPTION(RuntimeException, Exception)
	SF_DECLARE_EXCEPTION(NotFoundException, RuntimeException)
	SF_DECLARE_EXCEPTION(ExistsException, RuntimeException)
	SF_DECLARE_EXCEPTION(TimeoutException, RuntimeException)
	SF_DECLARE_EXCEPTION(NoPermissionException, RuntimeException)
	SF_DECLARE_EXCEPTION(IOException, RuntimeException)	

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif //_FWK_EXCEPTIONS_H__
