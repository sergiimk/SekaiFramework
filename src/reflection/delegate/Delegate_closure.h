//						ClosurePtr<>
//
// A private wrapper class that adds function signatures to FunctionData.
// It's the class that does most of the actual work.
// The signatures are specified by:
// GenericMemFunc: must be a type of GenericClass member function pointer. 
// StaticFuncPtr:  must be a type of function pointer with the same signature 
//                 as GenericMemFunc.
// UnvoidStaticFuncPtr: is the same as StaticFuncPtr, except on VC6
//                 where it never returns void (returns DefaultVoid instead).

// An outer class, DelegateN<>, handles the invoking and creates the
// necessary typedefs.
// This class does everything else.

namespace detail {

	template < class GenericMemFunc, class StaticFuncPtr, class UnvoidStaticFuncPtr>
	class ClosurePtr : public FunctionData 
	{
	public:
		// These functions are for setting the delegate to a member function.

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
		// VC6 has problems if we just overload 'bindmemfunc', so we give it a different name.
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
		inline GenericMemFunc GetClosureMemPtr() const { return reinterpret_cast<GenericMemFunc>(m_pFunction); }

		// There are a few ways of dealing with static function pointers.
		// There's a standard-compliant, but tricky method.
		// There's also a straightforward hack, that won't work on DOS compilers using the
		// medium memory model. It's so evil that I can't recommend it, but I've
		// implemented it anyway because it produces very nice asm code.

#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)

		//				ClosurePtr<> - Safe version
		//
		// This implementation is standard-compliant, but a bit tricky.
		// I store the function pointer inside the class, and the delegate then
		// points to itself. Whenever the delegate is copied, these self-references
		// must be transformed, and this complicates the = and == operators.
	public:
		// The next two functions are for operator ==, =, and the copy constructor.
		// We may need to convert the m_pthis pointers, so that
		// they remain as self-references.
		template< class DerivedClass >
		inline void CopyFrom (DerivedClass *pParent, const FunctionData &x) 
		{
			SetFunctionDataFrom(x);
			if (m_pStaticFunction!=0) 
			{
				// transform self references...
				m_pthis=reinterpret_cast<GenericClass *>(pParent);
			}
		}
		// For static functions, the 'static_function_invoker' class in the parent 
		// will be called. The parent then needs to call GetStaticFunction() to find out 
		// the actual function to invoke.
		template < class DerivedClass, class ParentInvokerSig >
		inline void bindstaticfunc(DerivedClass *pParent, ParentInvokerSig static_function_invoker, StaticFuncPtr function_to_bind ) 
		{
			if (function_to_bind==0) { // cope with assignment to 0
				m_pFunction=0;
			} else { 
				bindmemfunc(pParent, static_function_invoker);
			}
			m_pStaticFunction=reinterpret_cast<GenericFuncPtr>(function_to_bind);
		}

		inline UnvoidStaticFuncPtr GetStaticFunction() const 
		{ 
			return reinterpret_cast<UnvoidStaticFuncPtr>(m_pStaticFunction); 
		}
#else

		//				ClosurePtr<> - Evil version
		//
		// For compilers where data pointers are at least as big as code pointers, it is 
		// possible to store the function pointer in the this pointer, using another 
		// horrible_cast. Invocation isn't any faster, but it saves 4 bytes, and
		// speeds up comparison and assignment. If C++ provided direct language support
		// for delegates, they would produce asm code that was almost identical to this.
		// Note that the Sun C++ and MSVC documentation explicitly state that they 
		// support static_cast between void * and function pointers.

		template< class DerivedClass >
		inline void CopyFrom (DerivedClass *pParent, const FunctionData &right) 
		{
			SetFunctionDataFrom(right);
		}
		// For static functions, the 'static_function_invoker' class in the parent 
		// will be called. The parent then needs to call GetStaticFunction() to find out 
		// the actual function to invoke.
		// ******** EVIL, EVIL CODE! *******
		template < 	class DerivedClass, class ParentInvokerSig>
		inline void bindstaticfunc(DerivedClass *pParent, ParentInvokerSig static_function_invoker, StaticFuncPtr function_to_bind) 
		{
			if (function_to_bind==0) { // cope with assignment to 0
				m_pFunction=0;
			} else { 
				// We'll be ignoring the 'this' pointer, but we need to make sure we pass
				// a valid value to bindmemfunc().
				bindmemfunc(pParent, static_function_invoker);
			}

			// WARNING! Evil hack. We store the function in the 'this' pointer!
			// Ensure that there's a compilation failure if function pointers 
			// and data pointers have different sizes.
			// If you get this error, you need to #undef FASTDELEGATE_USESTATICFUNCTIONHACK.
			typedef int ERROR_CantUseEvilMethod[sizeof(GenericClass *)==sizeof(function_to_bind) ? 1 : -1];
			m_pthis = horrible_cast<GenericClass *>(function_to_bind);
		}

		// ******** EVIL, EVIL CODE! *******
		// This function will be called with an invalid 'this' pointer!!
		// We're just returning the 'this' pointer, converted into
		// a function pointer!
		inline UnvoidStaticFuncPtr GetStaticFunction() const 
		{
			// Ensure that there's a compilation failure if function pointers 
			// and data pointers have different sizes.
			// If you get this error, you need to #undef FASTDELEGATE_USESTATICFUNCTIONHACK.
			typedef int ERROR_CantUseEvilMethod[sizeof(UnvoidStaticFuncPtr)==sizeof(this) ? 1 : -1];
			return horrible_cast<UnvoidStaticFuncPtr>(this);
		}
#endif // !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)

		// Does the closure contain this static function?
		inline bool IsEqualToStaticFuncPtr(StaticFuncPtr funcptr)
		{
			if (funcptr==0) return empty(); 
			// For the Evil method, if it doesn't actually contain a static function, this will return an arbitrary
			// value that is not equal to any valid function pointer.
			else return funcptr==reinterpret_cast<StaticFuncPtr>(GetStaticFunction());
		}
	};


} // namespace detail
