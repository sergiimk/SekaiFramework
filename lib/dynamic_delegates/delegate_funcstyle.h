////////////////////////////////////////////////////////////////////////////////
//						Fast Delegates, part 4:
// 
//				delegate<> class (Original author: Jody Hagins)
//	Allows boost::function style syntax like:
//			delegate< double (int, long) >
// instead of:
//			delegate2< int, long, double >
//
////////////////////////////////////////////////////////////////////////////////

#ifdef FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX

// Declare delegate as a class template.  It will be specialized
// later for all number of arguments.
template <typename Signature> class FS_DELEGATE;

//N=0
template<typename R>
class FS_DELEGATE< R (  ) > : public DELEGATE(0) < R >
{
public:
	typedef DELEGATE(0) < R > base_type;
	typedef FS_DELEGATE this_type;

	FS_DELEGATE() : base_type() { }
	template < class X, class Y >
	FS_DELEGATE(Y * pthis, R (X::* function_to_bind)(  ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	FS_DELEGATE(const Y *pthis, R (X::* function_to_bind)(  ) const)
		: base_type(pthis, function_to_bind)
	{ }

	FS_DELEGATE(R (*function_to_bind)(  ))
		: base_type(function_to_bind) 
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }
};

//N=1
template<typename R, class P1>
class FS_DELEGATE< R ( P1 ) > : public DELEGATE(1) < P1, R >
{
public:
	typedef DELEGATE(1) < P1, R > base_type;
	typedef FS_DELEGATE this_type;

	FS_DELEGATE() : base_type() { }

	template < class X, class Y >
	FS_DELEGATE(Y * pthis, R (X::* function_to_bind)( P1 p1 ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	FS_DELEGATE(const Y *pthis, R (X::* function_to_bind)( P1 p1 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	FS_DELEGATE(R (*function_to_bind)( P1 p1 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }
};

//N=2
template<typename R, class P1, class P2>
class FS_DELEGATE< R ( P1, P2 ) > : public DELEGATE(2) < P1, P2, R >
{
public:
	typedef DELEGATE(2) < P1, P2, R > base_type;
	typedef FS_DELEGATE this_type;

	FS_DELEGATE() : base_type() { }

	template < class X, class Y >
	FS_DELEGATE(Y * pthis, R (X::* function_to_bind)( P1 p1, P2 p2 ))
		: base_type(pthis, function_to_bind) 
	{ }

	template < class X, class Y >
	FS_DELEGATE(const Y *pthis, R (X::* function_to_bind)( P1 p1, P2 p2 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	FS_DELEGATE(R (*function_to_bind)( P1 p1, P2 p2 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }
};

//N=3
template<typename R, class P1, class P2, class P3>
class FS_DELEGATE< R ( P1, P2, P3 ) > : public DELEGATE(3) < P1, P2, P3, R >
{
public:
	typedef DELEGATE(3) < P1, P2, P3, R > base_type;
	typedef FS_DELEGATE this_type;

	FS_DELEGATE() : base_type() { }

	template < class X, class Y >
	FS_DELEGATE(Y * pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3 ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	FS_DELEGATE(const Y *pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	FS_DELEGATE(R (*function_to_bind)( P1 p1, P2 p2, P3 p3 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }
};

//N=4
template<typename R, class P1, class P2, class P3, class P4>
class FS_DELEGATE< R ( P1, P2, P3, P4 ) > : public DELEGATE(4) < P1, P2, P3, P4, R >
{
public:
	typedef DELEGATE(4) < P1, P2, P3, P4, R > base_type;
	typedef FS_DELEGATE this_type;

	FS_DELEGATE() : base_type() { }

	template < class X, class Y >
	FS_DELEGATE(Y * pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4 ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	FS_DELEGATE(const Y *pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	FS_DELEGATE(R (*function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }
};

//N=5
template<typename R, class P1, class P2, class P3, class P4, class P5>
class FS_DELEGATE< R ( P1, P2, P3, P4, P5 ) > : public DELEGATE(5) < P1, P2, P3, P4, P5, R >
{
public:
	typedef DELEGATE(5) < P1, P2, P3, P4, P5, R > base_type;
	typedef FS_DELEGATE this_type;

	FS_DELEGATE() : base_type() { }

	template < class X, class Y >
	FS_DELEGATE(Y * pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	FS_DELEGATE(const Y *pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	FS_DELEGATE(R (*function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }
};

#endif //FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX
