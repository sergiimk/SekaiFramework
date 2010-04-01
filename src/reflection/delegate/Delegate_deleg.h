// Once we have the member function conversion templates, it's easy to make the
// wrapper classes. So that they will work with as many compilers as possible, 
// the classes are of the form
//   Delegate3<int, char *, double>
// They can cope with any combination of parameters. The max number of parameters
// allowed is 8, but it is trivial to increase this limit.
// Note that we need to treat const member functions seperately.
// All this class does is to enforce type safety, and invoke the delegate with
// the correct list of parameters.

// Because of the weird rule about the class of derived member function pointers,
// you sometimes need to apply a downcast to the 'this' pointer.
// This is the reason for the use of "implicit_cast<X*>(pthis)" in the code below. 
// If CDerivedClass is derived from CBaseClass, but doesn't override SimpleVirtualFunction,
// without this trick you'd need to write:
//		MyDelegate(static_cast<CBaseClass *>(&d), &CDerivedClass::SimpleVirtualFunction);
// but with the trick you can write
//		MyDelegate(&d, &CDerivedClass::SimpleVirtualFunction);

// RetType is the type the compiler uses in compiling the template. For VC6,
// it cannot be void. DesiredRetType is the real type which is returned from
// all of the functions. It can be void.

// Implicit conversion to "bool" is achieved using the safe_bool idiom,
// using member data pointers (MDP). This allows "if (dg)..." syntax
// Because some compilers (eg codeplay) don't have a unique value for a zero
// MDP, an extra padding member is added to the SafeBool struct.
// Some compilers (eg VC6) won't implicitly convert from 0 to an MDP, so
// in that case the static function constructor is not made explicit; this
// allows "if (dg==0) ..." to compile.

//N=0
template<class RetType=detail::DefaultVoid>
class Delegate0 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)();
	typedef RetType (*UnvoidStaticFunctionPtr)();
	typedef RetType (detail::GenericClass::*GenericMemFn)();
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate0 type;

	// Construction and comparison functions
	Delegate0() { clear(); }
	Delegate0(const Delegate0 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate0 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate0 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate0 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate0 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate0 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate0(Y *pthis, DesiredRetType (X::* function_to_bind)() ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)()) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate0(const Y *pthis, DesiredRetType (X::* function_to_bind)() const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)() const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate0(DesiredRetType (*function_to_bind)() ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)() ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)()) {
		m_Closure.bindstaticfunc(this, &Delegate0::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() () const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction() const {
		return (*(m_Closure.GetStaticFunction()))(); }
};

//N=1
template<class Param1, class RetType=detail::DefaultVoid>
class Delegate1 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1);
	typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1);
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate1 type;

	// Construction and comparison functions
	Delegate1() { clear(); }
	Delegate1(const Delegate1 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate1 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate1 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate1 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate1 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate1 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate1(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1) ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1)) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate1(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate1(DesiredRetType (*function_to_bind)(Param1 p1) ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1) ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)(Param1 p1)) {
		m_Closure.bindstaticfunc(this, &Delegate1::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1) const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(p1); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1) const {
		return (*(m_Closure.GetStaticFunction()))(p1); }
};

//N=2
template<class Param1, class Param2, class RetType=detail::DefaultVoid>
class Delegate2 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2);
	typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2);
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate2 type;

	// Construction and comparison functions
	Delegate2() { clear(); }
	Delegate2(const Delegate2 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate2 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate2 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate2 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate2 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate2 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate2(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2) ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2)) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate2(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate2(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2) ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2) ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2)) {
		m_Closure.bindstaticfunc(this, &Delegate2::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2) const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(p1, p2); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2) const {
		return (*(m_Closure.GetStaticFunction()))(p1, p2); }
};

//N=3
template<class Param1, class Param2, class Param3, class RetType=detail::DefaultVoid>
class Delegate3 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3);
	typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3);
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate3 type;

	// Construction and comparison functions
	Delegate3() { clear(); }
	Delegate3(const Delegate3 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate3 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate3 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate3 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate3 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate3 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate3(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3) ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3)) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate3(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate3(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3) ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3) ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3)) {
		m_Closure.bindstaticfunc(this, &Delegate3::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3) const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3) const {
		return (*(m_Closure.GetStaticFunction()))(p1, p2, p3); }
};

//N=4
template<class Param1, class Param2, class Param3, class Param4, class RetType=detail::DefaultVoid>
class Delegate4 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4);
	typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4);
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate4 type;

	// Construction and comparison functions
	Delegate4() { clear(); }
	Delegate4(const Delegate4 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate4 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate4 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate4 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate4 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate4 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate4(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate4(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate4(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
		m_Closure.bindstaticfunc(this, &Delegate4::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4) const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const {
		return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4); }
};

//N=5
template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=detail::DefaultVoid>
class Delegate5 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5);
	typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5);
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate5 type;

	// Construction and comparison functions
	Delegate5() { clear(); }
	Delegate5(const Delegate5 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate5 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate5 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate5 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate5 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate5 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate5(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate5(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate5(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) {
		m_Closure.bindstaticfunc(this, &Delegate5::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const {
		return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4, p5); }
};

//N=6
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=detail::DefaultVoid>
class Delegate6 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6);
	typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6);
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate6 type;

	// Construction and comparison functions
	Delegate6() { clear(); }
	Delegate6(const Delegate6 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate6 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate6 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate6 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate6 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate6 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate6(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate6(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate6(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) {
		m_Closure.bindstaticfunc(this, &Delegate6::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const {
		return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4, p5, p6); }
};

//N=7
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType=detail::DefaultVoid>
class Delegate7 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7);
	typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7);
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate7 type;

	// Construction and comparison functions
	Delegate7() { clear(); }
	Delegate7(const Delegate7 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate7 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate7 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate7 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate7 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate7 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate7(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate7(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate7(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) {
		m_Closure.bindstaticfunc(this, &Delegate7::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6, p7); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const {
		return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4, p5, p6, p7); }
};

//N=8
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType=detail::DefaultVoid>
class Delegate8 : public DelegateBase {
private:
	typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8);
	typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8);
	typedef detail::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef Delegate8 type;

	// Construction and comparison functions
	Delegate8() { clear(); }
	Delegate8(const Delegate8 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const Delegate8 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const Delegate8 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const Delegate8 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const Delegate8 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const Delegate8 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	Delegate8(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) ) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8)) {
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	Delegate8(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const) {
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	Delegate8(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) ) {
		bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) ) {
		bind(function_to_bind);	}
	inline void bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8)) {
		m_Closure.bindstaticfunc(this, &Delegate8::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const {
		return (m_Closure.GetThisPtr()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6, p7, p8); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
		return empty()? 0: &SafeBoolStruct::m_nonzero;
	}
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
		return !m_Closure; }
	inline bool empty() const	{
		return !m_Closure; }
	void clear() { m_Closure.clear();}
	// Conversion to and from the FunctionData storage class
	const FunctionData & GetFunctionData() { return m_Closure; }
	void SetFunctionData(const FunctionData &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const {
		return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4, p5, p6, p7, p8); }
};
