// Also declare overloads of a MakeDelegate() global function to 
// reduce the need for typedefs.
// We need seperate overloads for const and non-const member functions.
// Also, because of the weird rule about the class of derived member function pointers,
// implicit downcasts may need to be applied later to the 'this' pointer.
// That's why two classes (X and Y) appear in the definitions. Y must be implicitly
// castable to X.

// Workaround for VC6. VC6 needs void return types converted into DefaultVoid.
// GCC 3.2 and later won't compile this unless it's preceded by 'typename',
// but VC6 doesn't allow 'typename' in this context.
// So, I have to use a macro.

#ifdef FASTDLGT_VC6
#define FASTDLGT_RETTYPE detail::VoidToDefaultVoid<RetType>::type
#else 
#define FASTDLGT_RETTYPE RetType
#endif


//N=0
template <class X, class Y, class RetType>
Delegate0<FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)() DELEG_CONST) { 
	return Delegate0<FASTDLGT_RETTYPE>(x, func);
}

//N=1
template <class X, class Y, class Param1, class RetType>
Delegate1<Param1, FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)(Param1 p1) DELEG_CONST) { 
	return Delegate1<Param1, FASTDLGT_RETTYPE>(x, func);
}

//N=2
template <class X, class Y, class Param1, class Param2, class RetType>
Delegate2<Param1, Param2, FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)(Param1 p1, Param2 p2) DELEG_CONST) { 
	return Delegate2<Param1, Param2, FASTDLGT_RETTYPE>(x, func);
}

//N=3
template <class X, class Y, class Param1, class Param2, class Param3, class RetType>
Delegate3<Param1, Param2, Param3, FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3) DELEG_CONST) { 
	return Delegate3<Param1, Param2, Param3, FASTDLGT_RETTYPE>(x, func);
}

//N=4
template <class X, class Y, class Param1, class Param2, class Param3, class Param4, class RetType>
Delegate4<Param1, Param2, Param3, Param4, FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) DELEG_CONST) { 
	return Delegate4<Param1, Param2, Param3, Param4, FASTDLGT_RETTYPE>(x, func);
}

//N=5
template <class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
Delegate5<Param1, Param2, Param3, Param4, Param5, FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) DELEG_CONST) { 
	return Delegate5<Param1, Param2, Param3, Param4, Param5, FASTDLGT_RETTYPE>(x, func);
}

//N=6
template <class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
Delegate6<Param1, Param2, Param3, Param4, Param5, Param6, FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) DELEG_CONST) { 
	return Delegate6<Param1, Param2, Param3, Param4, Param5, Param6, FASTDLGT_RETTYPE>(x, func);
}

//N=7
template <class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType>
Delegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) DELEG_CONST) { 
	return Delegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, FASTDLGT_RETTYPE>(x, func);
}

//N=8
template <class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType>
Delegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, FASTDLGT_RETTYPE> MakeDelegate(Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) DELEG_CONST) { 
	return Delegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, FASTDLGT_RETTYPE>(x, func);
}


// clean up after ourselves...
#undef FASTDLGT_RETTYPE
