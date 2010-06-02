// Because of the weird rule about the class of derived member function pointers,
// implicit downcasts may need to be applied later to the 'this' pointer.
// That's why two classes (X and Y) appear in the definitions. Y must be implicitly
// castable to X.

//N=0
template <class X, class Y, class RetType>
DELEGATE(0)<RetType> MAKE_DELEGATE(Y* x, RetType (X::*func)() DELEG_CONST) { 
	return DELEGATE(0)<RetType>(x, func);
}

//N=1
template <class X, class Y, class P1, class RetType>
DELEGATE(1)<P1, RetType> MAKE_DELEGATE(Y* x, RetType (X::*func)(P1 p1) DELEG_CONST) { 
	return DELEGATE(1)<P1, RetType>(x, func);
}

//N=2
template <class X, class Y, class P1, class P2, class RetType>
DELEGATE(2)<P1, P2, RetType> MAKE_DELEGATE(Y* x, RetType (X::*func)(P1 p1, P2 p2) DELEG_CONST) { 
	return DELEGATE(2)<P1, P2, RetType>(x, func);
}

//N=3
template <class X, class Y, class P1, class P2, class P3, class RetType>
DELEGATE(3)<P1, P2, P3, RetType> MAKE_DELEGATE(Y* x, RetType (X::*func)(P1 p1, P2 p2, P3 p3) DELEG_CONST) { 
	return DELEGATE(3)<P1, P2, P3, RetType>(x, func);
}

//N=4
template <class X, class Y, class P1, class P2, class P3, class P4, class RetType>
DELEGATE(4)<P1, P2, P3, P4, RetType> MAKE_DELEGATE(Y* x, RetType (X::*func)(P1 p1, P2 p2, P3 p3, P4 p4) DELEG_CONST) { 
	return DELEGATE(4)<P1, P2, P3, P4, RetType>(x, func);
}

//N=5
template <class X, class Y, class P1, class P2, class P3, class P4, class P5, class RetType>
DELEGATE(5)<P1, P2, P3, P4, P5, RetType> MAKE_DELEGATE(Y* x, RetType (X::*func)(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) DELEG_CONST) { 
	return DELEGATE(5)<P1, P2, P3, P4, P5, RetType>(x, func);
}
