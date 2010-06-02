#ifndef _DELEGATE_CLOSURE_H__
#define _DELEGATE_CLOSURE_H__

////////////////////////////////////////////////////////////////////////////////
//						Fast Delegates, part 2:
//
//	Define the DELEGATE storage, and cope with static functions
//
////////////////////////////////////////////////////////////////////////////////

// function_data -- an opaque structure which can hold an arbitary DELEGATE.
// It knows nothing about the calling convention or number of arguments used by
// the function pointed to.
// It supplies comparison operators so that it can be stored in STL collections.
// It cannot be set to anything other than null, nor invoked directly.
//
// Implementation:
// There are two possible implementations: the Safe method and the Evil method.
//				function_data - Safe version
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
// When stored stored inside a specific DELEGATE, the 'dontcare' entries are replaced
// with a reference to the DELEGATE itself. This complicates the = and == operators
// for the DELEGATE class.
//
//				function_data - Evil version
//
// For compilers where data pointers are at least as big as code pointers, it is 
// possible to store the function pointer in the this pointer, using another 
// horrible_cast. In this case the function_data implementation is simple:
// +--pThis --+-- pMemFunc-+-- Meaning---------------------+
// |    0     |  0         | Empty                         |
// |  !=0     |  !=0*      | Static function or method call|
// +----------+------------+-------------------------------+
//  * For Metrowerks, this can be 0. (first virtual function in a 
//       single_inheritance class).
// Note that the Sun C++ and MSVC documentation explicitly state that they 
// support static_cast between void * and function pointers.

namespace detail {

	class function_data 
	{
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
		function_data() : m_pthis(0), m_pFunction(0), m_pStaticFunction(0) {};

		void clear() 
		{
			m_pthis=0; m_pFunction=0; m_pStaticFunction=0;
		}
#else
		function_data() : m_pthis(0), m_pFunction(0) {};
		void clear() {	m_pthis=0; m_pFunction=0; }
#endif

	public:
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		inline bool IsEqual (const function_data &x) const
		{
			// We have to cope with the static function pointers as a special case
			if (m_pFunction!=x.m_pFunction) return false;
			// the static function ptrs must either both be equal, or both be 0.
			if (m_pStaticFunction!=x.m_pStaticFunction) return false;
			if (m_pStaticFunction!=0) return m_pthis==x.m_pthis;
			else return true;
		}
#else // Evil Method
		inline bool IsEqual (const function_data &x) const
		{
			return m_pthis==x.m_pthis && m_pFunction==x.m_pFunction;
		}
#endif
		// Provide a strict weak ordering for function_datas.
		inline bool IsLess(const function_data &right) const 
		{
			// deal with static function pointers first
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
			if (m_pStaticFunction !=0 || right.m_pStaticFunction!=0) 
				return m_pStaticFunction < right.m_pStaticFunction;
#endif
			if (m_pthis !=right.m_pthis) 
				return m_pthis < right.m_pthis;

			// There are no ordering operators for member function pointers, 
			// but we can fake one by comparing each byte. The resulting ordering is
			// arbitrary (and compiler-dependent), but it permits storage in ordered STL containers.
			return memcmp(&m_pFunction, &right.m_pFunction, sizeof(m_pFunction)) < 0;

		}

		inline bool operator ! () const { return m_pthis==0 && m_pFunction==0; }
		inline bool empty() const { return m_pthis==0 && m_pFunction==0; }

	public:
		function_data & operator=(const function_data &right)  
		{
			SetMementoFrom(right); 
			return *this;
		}
		inline bool operator <(const function_data &right) { return IsLess(right); }
		inline bool operator >(const function_data &right) { return right.IsLess(*this); }

		function_data (const function_data &right)  
			: m_pFunction(right.m_pFunction)
			, m_pthis(right.m_pthis)
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
			, m_pStaticFunction (right.m_pStaticFunction)
#endif
		{ }


		// Hacky methods for reflection library
		GenericClass* getThisPtr() const { return m_pthis; }
		void setThisPtr(GenericClass* pThis) { m_pthis = pThis; }

	protected:
		void SetMementoFrom(const function_data &right)  
		{
			m_pFunction = right.m_pFunction;
			m_pthis = right.m_pthis;
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
			m_pStaticFunction = right.m_pStaticFunction;
#endif
		}
	};


	//						closure_ptr<>
	//
	// A private wrapper class that adds function signatures to function_data.
	// It's the class that does most of the actual work.
	// The signatures are specified by:
	// GenericMemFunc: must be a type of GenericClass member function pointer. 
	// StaticFuncPtr:  must be a type of function pointer with the same signature 
	//                 as GenericMemFunc.
	// An outer class, DELEGATE_n<>, handles the invoking and creates the
	// necessary typedefs.
	// This class does everything else.

	template < class GenericMemFunc, class StaticFuncPtr>
	class closure_ptr : public function_data 
	{
	public:
		// These functions are for setting the DELEGATE to a member function.

		// Here's the clever bit: we convert an arbitrary member function into a 
		// standard form. XMemFunc should be a member function of class X, but I can't 
		// enforce that here. It needs to be enforced by the wrapper class.
		template < class X, class XMemFunc >
		inline void bindmemfunc(X *pthis, XMemFunc function_to_bind ) 
		{
			m_pthis = SimplifyMemFunc< sizeof(function_to_bind) >::Convert(pthis, function_to_bind, m_pFunction);
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
			m_pStaticFunction = 0;
#endif
		}

		// For const member functions, we only need a const class pointer.
		// Since we know that the member function is const, it's safe to 
		// remove the const qualifier from the 'this' pointer with a const_cast.
		template < class X, class XMemFunc>
		inline void bindconstmemfunc(const X *pthis, XMemFunc function_to_bind) 
		{
			m_pthis= SimplifyMemFunc< sizeof(function_to_bind) >::Convert(const_cast<X*>(pthis), function_to_bind, m_pFunction);
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
			m_pStaticFunction = 0;
#endif
		}

#ifdef FASTDELEGATE_GCC_BUG_8271	// At present, GCC doesn't recognize constness of MFPs in templates
		template < class X, class XMemFunc>
		inline void bindmemfunc(const X *pthis, XMemFunc function_to_bind) 
		{
			bindconstmemfunc(pthis, function_to_bind);
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
			m_pStaticFunction = 0;
#endif
		}
#endif

		// These functions are required for invoking the stored function
		inline GenericClass *GetClosureThis() const { return m_pthis; }
		inline GenericMemFunc GetClosureMemPtr() const { return reinterpret_cast<GenericMemFunc>(m_pFunction); }

		// There are a few ways of dealing with static function pointers.
		// There's a standard-compliant, but tricky method.
		// There's also a straightforward hack, that won't work on DOS compilers using the
		// medium memory model. It's so evil that I can't recommend it, but I've
		// implemented it anyway because it produces very nice asm code.

#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)

		//				closure_ptr<> - Safe version
		//
		// This implementation is standard-compliant, but a bit tricky.
		// I store the function pointer inside the class, and the DELEGATE then
		// points to itself. Whenever the DELEGATE is copied, these self-references
		// must be transformed, and this complicates the = and == operators.
	public:
		// The next two functions are for operator ==, =, and the copy constructor.
		// We may need to convert the m_pthis pointers, so that
		// they remain as self-references.
		template< class DerivedClass >
		inline void CopyFrom (DerivedClass *pParent, const function_data &x) 
		{
			SetMementoFrom(x);
			if (m_pStaticFunction!=0) 
				m_pthis=reinterpret_cast<GenericClass *>(pParent);
		}

		// For static functions, the 'static_function_invoker' class in the parent 
		// will be called. The parent then needs to call GetStaticFunction() to find out 
		// the actual function to invoke.
		template < class DerivedClass, class ParentInvokerSig >
		inline void bindstaticfunc(DerivedClass *pParent, ParentInvokerSig static_function_invoker, StaticFuncPtr function_to_bind ) 
		{
			if (0 == function_to_bind)
				m_pFunction = 0;
			else
				bindmemfunc(pParent, static_function_invoker);

			m_pStaticFunction=reinterpret_cast<GenericFuncPtr>(function_to_bind);
		}

		inline StaticFuncPtr GetStaticFunction() const 
		{ 
			return reinterpret_cast<StaticFuncPtr>(m_pStaticFunction); 
		}


#else

		//				closure_ptr<> - Evil version
		//
		// For compilers where data pointers are at least as big as code pointers, it is 
		// possible to store the function pointer in the this pointer, using another 
		// horrible_cast. Invocation isn't any faster, but it saves 4 bytes, and
		// speeds up comparison and assignment. If C++ provided direct language support
		// for DELEGATEs, they would produce asm code that was almost identical to this.
		// Note that the Sun C++ and MSVC documentation explicitly state that they 
		// support static_cast between void * and function pointers.

		template< class DerivedClass >
		inline void CopyFrom (DerivedClass *pParent, const function_data &right) 
		{
			SetMementoFrom(right);
		}

		// For static functions, the 'static_function_invoker' class in the parent 
		// will be called. The parent then needs to call GetStaticFunction() to find out 
		// the actual function to invoke.
		// ******** EVIL, EVIL CODE! *******
		template <class DerivedClass, class ParentInvokerSig>
		inline void bindstaticfunc(DerivedClass *pParent, ParentInvokerSig static_function_invoker, StaticFuncPtr function_to_bind) 
		{
			if (0 == function_to_bind)
				m_pFunction=0;
			else
				// We'll be ignoring the 'this' pointer, but we need to make sure we pass
				// a valid value to bindmemfunc().
				bindmemfunc(pParent, static_function_invoker);

			// WARNING! Evil hack. We store the function in the 'this' pointer!
			// Ensure that there's a compilation failure if function pointers 
			// and data pointers have different sizes.
			// If you get this error, you need to #undef FASTDELEGATE_USESTATICFUNCTIONHACK.
			static_assert(sizeof(GenericClass *) == sizeof(function_to_bind), "Can't use this optimization method");
			m_pthis = horrible_cast<GenericClass *>(function_to_bind);
			// MSVC, SunC++ and DMC accept the following (non-standard) code:
			//		m_pthis = static_cast<GenericClass *>(static_cast<void *>(function_to_bind));
			// BCC32, Comeau and DMC accept this method. MSVC7.1 needs __int64 instead of long
			//		m_pthis = reinterpret_cast<GenericClass *>(reinterpret_cast<long>(function_to_bind));
		}
		// ******** EVIL, EVIL CODE! *******
		// This function will be called with an invalid 'this' pointer!!
		// We're just returning the 'this' pointer, converted into
		// a function pointer!
		inline StaticFuncPtr GetStaticFunction() const 
		{
			// Ensure that there's a compilation failure if function pointers 
			// and data pointers have different sizes.
			// If you get this error, you need to #undef FASTDELEGATE_USESTATICFUNCTIONHACK.
			static_assert(sizeof(StaticFuncPtr) == sizeof(this), "Can't use this optimization method");
			return horrible_cast<StaticFuncPtr>(this);
		}
#endif // !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)

		// Does the closure contain this static function?
		inline bool IsEqualToStaticFuncPtr(StaticFuncPtr funcptr)
		{
			if (funcptr==0)
				return empty(); 
			// For the Evil method, if it doesn't actually contain a static function, this will return an arbitrary
			// value that is not equal to any valid function pointer.
			else 
				return funcptr == reinterpret_cast<StaticFuncPtr>(GetStaticFunction());
		}
	};


} // namespace detail

#endif //_DELEGATE_CLOSURE_H__
