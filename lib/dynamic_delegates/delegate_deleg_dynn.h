#ifndef _DELEGATE_DELEG_DYNN_H__
#define _DELEGATE_DELEG_DYNN_H__

#include "delegate_delegn.h"
#include "typetraits.h"

//////////////////////////////////////////////////////////////////////////
// Dynamic delegates
//////////////////////////////////////////////////////////////////////////

// Declares pure virtual function for dynamic invocation of function
class delegate_dynamic_base
{
public:
	virtual ~delegate_dynamic_base() { }
	virtual const detail::function_data& getFunctionData() = 0;
	virtual void setFunctionData(const detail::function_data &any) = 0;
	virtual void invoke(void ** args, void * ret) const = 0;
};

//////////////////////////////////////////////////////////////////////////

#define UP_ARG(T, N)		(*(t_strip<T>::noref*)args[N])
#define UP_RET()			(*(t_strip<R>::norefp*)rt)

template<class Deleg, class R>
struct rt_invoker0 {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { if(rt) UP_RET() = dlg(); else dlg(); }
};
template<class Deleg>
struct rt_invoker0<Deleg, void> {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { dlg(); }
};

template<class Deleg, class P1, class R>
struct rt_invoker1 {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { if(rt) UP_RET() = dlg(UP_ARG(P1, 0)); else dlg(UP_ARG(P1, 0)); }
};
template<class Deleg, class P1>
struct rt_invoker1<Deleg, P1, void> {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { dlg(UP_ARG(P1, 0)); }
};

template<class Deleg, class P1, class P2, class R>
struct rt_invoker2 {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { if(rt) UP_RET() = dlg(UP_ARG(P1, 0), UP_ARG(P2, 1)); else dlg(UP_ARG(P1, 0), UP_ARG(P2, 1)); }
};
template<class Deleg, class P1, class P2>
struct rt_invoker2<Deleg, P1, P2, void> {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { dlg(UP_ARG(P1, 0), UP_ARG(P2, 1)); }
};

template<class Deleg, class P1, class P2, class P3, class R>
struct rt_invoker3 {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { if(rt) UP_RET() = dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2)); else dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2)); }
};
template<class Deleg, class P1, class P2, class P3>
struct rt_invoker3<Deleg, P1, P2, P3, void> {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2)); }
};

template<class Deleg, class P1, class P2, class P3, class P4, class R>
struct rt_invoker4 {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { if(rt) UP_RET() = dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2), UP_ARG(P4, 3)); else dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2), UP_ARG(P4, 3)); }
};
template<class Deleg, class P1, class P2, class P3, class P4>
struct rt_invoker4<Deleg, P1, P2, P3, P4, void> {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2), UP_ARG(P4, 3)); }
};

template<class Deleg, class P1, class P2, class P3, class P4, class P5, class R>
struct rt_invoker5 {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { if(rt) UP_RET() = dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2), UP_ARG(P4, 3), UP_ARG(P5, 4)); else dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2), UP_ARG(P4, 3), UP_ARG(P5, 4)); }
};
template<class Deleg, class P1, class P2, class P3, class P4, class P5>
struct rt_invoker5<Deleg, P1, P2, P3, P4, P5, void> {
	inline static void invoke(void ** args, void * rt, const Deleg& dlg) { dlg(UP_ARG(P1, 0), UP_ARG(P2, 1), UP_ARG(P3, 2), UP_ARG(P4, 3), UP_ARG(P5, 4)); }
};

#undef UP_ARG
#undef UP_RET

//////////////////////////////////////////////////////////////////////////

//N=0
template<typename R = void>
class delegate_dynamic0 : public delegate0 < R >, public delegate_dynamic_base
{
public:
	typedef delegate0 < R > base_type;
	typedef delegate_dynamic0 this_type;

	delegate_dynamic0() : base_type() { }

	template < class X, class Y >
	delegate_dynamic0(Y * pthis, R (X::* function_to_bind)(  ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	delegate_dynamic0(const Y *pthis, R (X::* function_to_bind)(  ) const)
		: base_type(pthis, function_to_bind)
	{ }

	delegate_dynamic0(R (*function_to_bind)(  ))
		: base_type(function_to_bind) 
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }

	virtual void invoke(void ** args, void * ret) const
	{
		rt_invoker0<this_type, R>::invoke(args, ret, *this);
	}

	virtual const detail::function_data& getFunctionData() { return base_type::getFunctionData(); }

	virtual void setFunctionData(const detail::function_data &any) { base_type::setFunctionData(any); }
};

//N=1
template<class P1, typename R = void>
class delegate_dynamic1 : public delegate1 < P1, R >, public delegate_dynamic_base
{
public:
	typedef delegate1 < P1, R > base_type;
	typedef delegate_dynamic1 this_type;

	delegate_dynamic1() : base_type() { }

	template < class X, class Y >
	delegate_dynamic1(Y * pthis, R (X::* function_to_bind)( P1 p1 ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	delegate_dynamic1(const Y *pthis, R (X::* function_to_bind)( P1 p1 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	delegate_dynamic1(R (*function_to_bind)( P1 p1 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }

	virtual void invoke(void ** args, void * ret) const
	{
		rt_invoker1<this_type, P1, R>::invoke(args, ret, *this);
	}

	virtual const detail::function_data& getFunctionData() { return base_type::getFunctionData(); }

	virtual void setFunctionData(const detail::function_data &any) { base_type::setFunctionData(any); }
};

//N=2
template<class P1, class P2, typename R = void>
class delegate_dynamic2 : public delegate2 < P1, P2, R >, public delegate_dynamic_base
{
public:
	typedef delegate2 < P1, P2, R > base_type;
	typedef delegate_dynamic2 this_type;

	delegate_dynamic2() : base_type() { }

	template < class X, class Y >
	delegate_dynamic2(Y * pthis, R (X::* function_to_bind)( P1 p1, P2 p2 ))
		: base_type(pthis, function_to_bind) 
	{ }

	template < class X, class Y >
	delegate_dynamic2(const Y *pthis, R (X::* function_to_bind)( P1 p1, P2 p2 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	delegate_dynamic2(R (*function_to_bind)( P1 p1, P2 p2 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }

	virtual void invoke(void ** args, void * ret) const
	{
		rt_invoker2<this_type, P1, P2, R>::invoke(args, ret, *this);
	}

	virtual const detail::function_data& getFunctionData() { return base_type::getFunctionData(); }

	virtual void setFunctionData(const detail::function_data &any) { base_type::setFunctionData(any); }
};

//N=3
template<class P1, class P2, class P3, typename R = void>
class delegate_dynamic3 : public delegate3 < P1, P2, P3, R >, public delegate_dynamic_base
{
public:
	typedef delegate3 < P1, P2, P3, R > base_type;
	typedef delegate_dynamic3 this_type;

	delegate_dynamic3() : base_type() { }

	template < class X, class Y >
	delegate_dynamic3(Y * pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3 ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	delegate_dynamic3(const Y *pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	delegate_dynamic3(R (*function_to_bind)( P1 p1, P2 p2, P3 p3 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }

	virtual void invoke(void ** args, void * ret) const
	{
		rt_invoker3<this_type, P1, P2, P3, R>::invoke(args, ret, *this);
	}

	virtual const detail::function_data& getFunctionData() { return base_type::getFunctionData(); }

	virtual void setFunctionData(const detail::function_data &any) { base_type::setFunctionData(any); }
};

//N=4
template<class P1, class P2, class P3, class P4, typename R = void>
class delegate_dynamic4 : public delegate4 < P1, P2, P3, P4, R >, public delegate_dynamic_base
{
public:
	typedef delegate4 < P1, P2, P3, P4, R > base_type;
	typedef delegate_dynamic4 this_type;

	delegate_dynamic4() : base_type() { }

	template < class X, class Y >
	delegate_dynamic4(Y * pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4 ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	delegate_dynamic4(const Y *pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	delegate_dynamic4(R (*function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }

	virtual void invoke(void ** args, void * ret) const
	{
		rt_invoker4<this_type, P1, P2, P3, P4, R>::invoke(args, ret, *this);
	}

	virtual const detail::function_data& getFunctionData() { return base_type::getFunctionData(); }

	virtual void setFunctionData(const detail::function_data &any) { base_type::setFunctionData(any); }
};

//N=5
template<class P1, class P2, class P3, class P4, class P5, typename R = void>
class delegate_dynamic5 : public delegate5 < P1, P2, P3, P4, P5, R >, public delegate_dynamic_base
{
public:
	typedef delegate5 < P1, P2, P3, P4, P5, R > base_type;
	typedef delegate_dynamic5 this_type;

	delegate_dynamic5() : base_type() { }

	template < class X, class Y >
	delegate_dynamic5(Y * pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ))
		: base_type(pthis, function_to_bind)  
	{ }

	template < class X, class Y >
	delegate_dynamic5(const Y *pthis, R (X::* function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) const)
		: base_type(pthis, function_to_bind)
	{ }

	delegate_dynamic5(R (*function_to_bind)( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ))
		: base_type(function_to_bind)  
	{ }

	void operator = (const base_type &x)  { *static_cast<base_type*>(this) = x; }

	virtual void invoke(void ** args, void * ret) const
	{
		rt_invoker5<this_type, P1, P2, P3, P4, P5, R>::invoke(args, ret, *this);
	}

	virtual const detail::function_data& getFunctionData() { return base_type::getFunctionData(); }

	virtual void setFunctionData(const detail::function_data &any) { base_type::setFunctionData(any); }
};

//////////////////////////////////////////////////////////////////////////

#endif //_DELEGATE_DELEG_DYNN_H__
