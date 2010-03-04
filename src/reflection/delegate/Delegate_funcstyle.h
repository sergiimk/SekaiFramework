#ifdef FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX

// Declare Delegate as a class template.  It will be specialized
// later for all number of arguments.
template <typename Signature>
class Delegate;

//N=0
// Specialization to allow use of
// Delegate< R (  ) >
// instead of 
// Delegate0 < R >
template<typename R>
class Delegate< R (  ) >
	// Inherit from Delegate0 so that it can be treated just like a Delegate0
	: public Delegate0 < R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate0 < R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)(  ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)(  ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)(  ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};

//N=1
// Specialization to allow use of
// Delegate< R ( Param1 ) >
// instead of 
// Delegate1 < Param1, R >
template<typename R, class Param1>
class Delegate< R ( Param1 ) >
	// Inherit from Delegate1 so that it can be treated just like a Delegate1
	: public Delegate1 < Param1, R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate1 < Param1, R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)( Param1 p1 ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)( Param1 p1 ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)( Param1 p1 ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};

//N=2
// Specialization to allow use of
// Delegate< R ( Param1, Param2 ) >
// instead of 
// Delegate2 < Param1, Param2, R >
template<typename R, class Param1, class Param2>
class Delegate< R ( Param1, Param2 ) >
	// Inherit from Delegate2 so that it can be treated just like a Delegate2
	: public Delegate2 < Param1, Param2, R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate2 < Param1, Param2, R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)( Param1 p1, Param2 p2 ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)( Param1 p1, Param2 p2 ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)( Param1 p1, Param2 p2 ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};

//N=3
// Specialization to allow use of
// Delegate< R ( Param1, Param2, Param3 ) >
// instead of 
// Delegate3 < Param1, Param2, Param3, R >
template<typename R, class Param1, class Param2, class Param3>
class Delegate< R ( Param1, Param2, Param3 ) >
	// Inherit from Delegate3 so that it can be treated just like a Delegate3
	: public Delegate3 < Param1, Param2, Param3, R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate3 < Param1, Param2, Param3, R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3 ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3 ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)( Param1 p1, Param2 p2, Param3 p3 ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};

//N=4
// Specialization to allow use of
// Delegate< R ( Param1, Param2, Param3, Param4 ) >
// instead of 
// Delegate4 < Param1, Param2, Param3, Param4, R >
template<typename R, class Param1, class Param2, class Param3, class Param4>
class Delegate< R ( Param1, Param2, Param3, Param4 ) >
	// Inherit from Delegate4 so that it can be treated just like a Delegate4
	: public Delegate4 < Param1, Param2, Param3, Param4, R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate4 < Param1, Param2, Param3, Param4, R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};

//N=5
// Specialization to allow use of
// Delegate< R ( Param1, Param2, Param3, Param4, Param5 ) >
// instead of 
// Delegate5 < Param1, Param2, Param3, Param4, Param5, R >
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5>
class Delegate< R ( Param1, Param2, Param3, Param4, Param5 ) >
	// Inherit from Delegate5 so that it can be treated just like a Delegate5
	: public Delegate5 < Param1, Param2, Param3, Param4, Param5, R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate5 < Param1, Param2, Param3, Param4, Param5, R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};

//N=6
// Specialization to allow use of
// Delegate< R ( Param1, Param2, Param3, Param4, Param5, Param6 ) >
// instead of 
// Delegate6 < Param1, Param2, Param3, Param4, Param5, Param6, R >
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
class Delegate< R ( Param1, Param2, Param3, Param4, Param5, Param6 ) >
	// Inherit from Delegate6 so that it can be treated just like a Delegate6
	: public Delegate6 < Param1, Param2, Param3, Param4, Param5, Param6, R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate6 < Param1, Param2, Param3, Param4, Param5, Param6, R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};

//N=7
// Specialization to allow use of
// Delegate< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) >
// instead of 
// Delegate7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R >
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7>
class Delegate< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) >
	// Inherit from Delegate7 so that it can be treated just like a Delegate7
	: public Delegate7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};

//N=8
// Specialization to allow use of
// Delegate< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) >
// instead of 
// Delegate8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R >
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8>
class Delegate< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) >
	// Inherit from Delegate8 so that it can be treated just like a Delegate8
	: public Delegate8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R >
{
public:
	// Make using the base type a bit easier via typedef.
	typedef Delegate8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R > BaseType;

	// Allow users access to the specific type of this delegate.
	typedef Delegate SelfType;

	// Mimic the base class constructors.
	Delegate() : BaseType() { }

	template < class X, class Y >
	Delegate(Y * pthis, 
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
		: BaseType(pthis, function_to_bind)  { }

	template < class X, class Y >
	Delegate(const Y *pthis,
		R (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ) const)
		: BaseType(pthis, function_to_bind)
	{  }

	Delegate(R (*function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
		: BaseType(function_to_bind)  { }
	void operator = (const BaseType &x)  {	  
		*static_cast<BaseType*>(this) = x; }
};


#endif //FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX
