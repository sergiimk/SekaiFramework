// FunctionData -- an opaque structure which can hold an arbitrary delegate.
// It knows nothing about the calling convention or number of arguments used by
// the function pointed to.
// It supplies comparison operators so that it can be stored in STL collections.
// It cannot be set to anything other than null, nor invoked directly: 
//   it must be converted to a specific delegate.

// Implementation:
// There are two possible implementations: the Safe method and the Evil method.
//				FunctionData - Safe version
//
// This implementation is standard-compliant, but a bit tricky.
// A static function pointer is stored inside the class. 
// Here are the valid values:
// +-- Static pointer --+--pThis --+-- pMemFunc-+-- Meaning------+
// |   0				|  0       |   0        | Empty          |
// |   !=0              |(dontcare)|  Invoker   | Static function|
// |   0                |  !=0     |  !=0*      | Method call    |
// +--------------------+----------+------------+----------------+
//  * For Metrowerks, this can be 0. (first virtual function in a 
//       single_inheritance class).
// When stored stored inside a specific delegate, the 'dontcare' entries are replaced
// with a reference to the delegate itself. This complicates the = and == operators
// for the delegate class.

//				FunctionData - Evil version
//
// For compilers where data pointers are at least as big as code pointers, it is 
// possible to store the function pointer in the this pointer, using another 
// horrible_cast. In this case the FunctionData implementation is simple:
// +--pThis --+-- pMemFunc-+-- Meaning---------------------+
// |    0     |  0         | Empty                         |
// |  !=0     |  !=0*      | Static function or method call|
// +----------+------------+-------------------------------+
//  * For Metrowerks, this can be 0. (first virtual function in a 
//       single_inheritance class).
// Note that the Sun C++ and MSVC documentation explicitly state that they 
// support static_cast between void * and function pointers.

class FunctionData {
protected: 
	// the data is protected, not private, because many
	// compilers have problems with template friends.
	typedef void (detail::GenericClass::*GenericMemFuncType)(); // arbitrary MFP.
	detail::GenericClass *m_pthis;
	GenericMemFuncType m_pFunction;

#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
	typedef void (*GenericFuncPtr)(); // arbitrary code pointer
	GenericFuncPtr m_pStaticFunction;
#endif

public:
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
	FunctionData() : m_pthis(0), m_pFunction(0), m_pStaticFunction(0) {};
	void clear() {
		m_pthis=0; m_pFunction=0; m_pStaticFunction=0;
	}
#else
	FunctionData() : m_pthis(0), m_pFunction(0) {};
	void clear() {	m_pthis=0; m_pFunction=0;	}
#endif
public:
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
	inline bool IsEqual (const FunctionData &x) const{
		// We have to cope with the static function pointers as a special case
		if (m_pFunction!=x.m_pFunction) return false;
		// the static function ptrs must either both be equal, or both be 0.
		if (m_pStaticFunction!=x.m_pStaticFunction) return false;
		if (m_pStaticFunction!=0) return m_pthis==x.m_pthis;
		else return true;
	}
#else // Evil Method
	inline bool IsEqual (const FunctionData &x) const{
		return m_pthis==x.m_pthis && m_pFunction==x.m_pFunction;
	}
#endif
	// Provide a strict weak ordering for FunctionDatas.
	inline bool IsLess(const FunctionData &right) const {
		// deal with static function pointers first
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		if (m_pStaticFunction !=0 || right.m_pStaticFunction!=0) 
			return m_pStaticFunction < right.m_pStaticFunction;
#endif
		if (m_pthis !=right.m_pthis) return m_pthis < right.m_pthis;
		// There are no ordering operators for member function pointers, 
		// but we can fake one by comparing each byte. The resulting ordering is
		// arbitrary (and compiler-dependent), but it permits storage in ordered STL containers.
		return memcmp(&m_pFunction, &right.m_pFunction, sizeof(m_pFunction)) < 0;

	}
	// BUGFIX (Mar 2005):
	// We can't just compare m_pFunction because on Metrowerks,
	// m_pFunction can be zero even if the delegate is not empty!
	inline bool operator ! () const		// Is it bound to anything?
	{ return m_pthis==0 && m_pFunction==0; }
	inline bool empty() const		// Is it bound to anything?
	{ return m_pthis==0 && m_pFunction==0; }
public:
	FunctionData & operator = (const FunctionData &right)  {
		SetFunctionDataFrom(right); 
		return *this;
	}
	inline bool operator <(const FunctionData &right) {
		return IsLess(right);
	}
	inline bool operator >(const FunctionData &right) {
		return right.IsLess(*this);
	}
	FunctionData (const FunctionData &right)  : 
		m_pthis(right.m_pthis), m_pFunction(right.m_pFunction)
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		, m_pStaticFunction (right.m_pStaticFunction)
#endif
	{}
	inline detail::GenericClass *GetThisPtr() const { return m_pthis; }
	inline void	SetThisPtr(detail::GenericClass* nthis) { m_pthis = nthis; }
protected:
	void SetFunctionDataFrom(const FunctionData &right)  {
		m_pFunction = right.m_pFunction;
		m_pthis = right.m_pthis;
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		m_pStaticFunction = right.m_pStaticFunction;
#endif
	}
};
