
//////////////////////////////////////////////////////////////////////////

template<class C, class RT>
inline Type* type_of(RT (C::*)() CONST_METH) 
{ 
	typedef RT (FT)(); 
	GenericInvoker inv = &InvokeGenericM<FT, RT>;
	Type* rt = type_of<RT>();
	Type* args[1];
	args[0] = type_of<C*>();
	static FunctionType ft(inv, true, rt, args, 1); 
	return &ft;
}

template<class C, class RT>
inline Type* type_of(const RT& (C::*)() CONST_METH) 
{ 
	typedef const RT& (FT)(); 
	GenericInvoker inv = &InvokeGenericM<FT, RT>;
	Type* rt = type_of<RT>();
	Type* args[1];
	args[0] = type_of<C*>();
	static FunctionType ft(inv, true, rt, args, 1); 
	return &ft;
}

template<class C, class RT>
inline Type* type_of(RT& (C::*)() CONST_METH) 
{ 
	typedef RT& (FT)(); 
	GenericInvoker inv = &InvokeGenericMRef<FT, RT>;
	Type* rt = type_of<RT*>();
	Type* args[1];
	args[0] = type_of<C*>();
	static FunctionType ft(inv, true, rt, args, 1); 
	return &ft;
}

template<class C>
inline Type* type_of(void (C::*)() CONST_METH) 
{ 
	typedef void (FT)(); 
	GenericInvoker inv = &InvokeGenericMNoret<FT>;
	Type* rt = type_of<void>();
	Type* args[1];
	args[0] = type_of<C*>();
	static FunctionType ft(inv, true, rt, args, 1); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class RT>
inline Type* type_of(RT (C::*)(A1) CONST_METH) 
{ 
	typedef RT (FT)(A1); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[2];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	static FunctionType ft(inv, true, rt, args, 2); 
	return &ft;
}

template<class C, class A1, class RT>
inline Type* type_of(const RT& (C::*)(A1) CONST_METH) 
{ 
	typedef const RT& (FT)(A1); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[2];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	static FunctionType ft(inv, true, rt, args, 2); 
	return &ft;
}

template<class C, class A1, class RT>
inline Type* type_of(RT& (C::*)(A1) CONST_METH) 
{ 
	typedef RT& (FT)(A1); 
	GenericInvoker inv = &InvokeGenericMRef<FT, typename Utils::TStripType<A1>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[2];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	static FunctionType ft(inv, true, rt, args, 2); 
	return &ft;
}

template<class C, class A1>
inline Type* type_of(void (C::*)(A1) CONST_METH) 
{ 
	typedef void (FT)(A1); 
	GenericInvoker inv = &InvokeGenericMNoret<FT, typename Utils::TStripType<A1>::noref>;
	Type* rt = type_of<void>();
	Type* args[2];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	static FunctionType ft(inv, true, rt, args, 2); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class A2, class RT>
inline Type* type_of(RT (C::*)(A1, A2) CONST_METH) 
{ 
	typedef RT (FT)(A1, A2); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[3];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	static FunctionType ft(inv, true, rt, args, 3); 
	return &ft;
}

template<class C, class A1, class A2, class RT>
inline Type* type_of(const RT& (C::*)(A1, A2) CONST_METH) 
{ 
	typedef const RT& (FT)(A1, A2); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[3];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	static FunctionType ft(inv, true, rt, args, 3); 
	return &ft;
}

template<class C, class A1, class A2, class RT>
inline Type* type_of(RT& (C::*)(A1, A2) CONST_METH) 
{ 
	typedef RT& (FT)(A1, A2); 
	GenericInvoker inv = &InvokeGenericMRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[3];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	static FunctionType ft(inv, true, rt, args, 3); 
	return &ft;
}

template<class C, class A1, class A2>
inline Type* type_of(void (C::*)(A1, A2) CONST_METH) 
{ 
	typedef void (FT)(A1, A2); 
	GenericInvoker inv = &InvokeGenericMNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref>;
	Type* rt = type_of<void>();
	Type* args[3];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	static FunctionType ft(inv, true, rt, args, 3); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class A2, class A3, class RT>
inline Type* type_of(RT (C::*)(A1, A2, A3) CONST_METH) 
{ 
	typedef RT (FT)(A1, A2, A3); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[4];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	static FunctionType ft(inv, true, rt, args, 4); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class RT>
inline Type* type_of(const RT& (C::*)(A1, A2, A3) CONST_METH) 
{ 
	typedef const RT& (FT)(A1, A2, A3); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[4];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	static FunctionType ft(inv, true, rt, args, 4); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class RT>
inline Type* type_of(RT& (C::*)(A1, A2, A3) CONST_METH) 
{ 
	typedef RT& (FT)(A1, A2, A3); 
	GenericInvoker inv = &InvokeGenericMRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[4];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	static FunctionType ft(inv, true, rt, args, 4); 
	return &ft;
}

template<class C, class A1, class A2, class A3>
inline Type* type_of(void (C::*)(A1, A2, A3) CONST_METH) 
{ 
	typedef void (FT)(A1, A2, A3); 
	GenericInvoker inv = &InvokeGenericMNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref>;
	Type* rt = type_of<void>();
	Type* args[4];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	static FunctionType ft(inv, true, rt, args, 4); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class A2, class A3, class A4, class RT>
inline Type* type_of(RT (C::*)(A1, A2, A3, A4) CONST_METH) 
{ 
	typedef RT (FT)(A1, A2, A3, A4); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[5];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	static FunctionType ft(inv, true, rt, args, 5); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class RT>
inline Type* type_of(const RT& (C::*)(A1, A2, A3, A4) CONST_METH) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[5];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	static FunctionType ft(inv, true, rt, args, 5); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class RT>
inline Type* type_of(RT& (C::*)(A1, A2, A3, A4) CONST_METH) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4); 
	GenericInvoker inv = &InvokeGenericMRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[5];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	static FunctionType ft(inv, true, rt, args, 5); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4>
inline Type* type_of(void (C::*)(A1, A2, A3, A4) CONST_METH) 
{ 
	typedef void (FT)(A1, A2, A3, A4); 
	GenericInvoker inv = &InvokeGenericMNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref>;
	Type* rt = type_of<void>();
	Type* args[5];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	static FunctionType ft(inv, true, rt, args, 5); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class A2, class A3, class A4, class A5, class RT>
inline Type* type_of(RT (C::*)(A1, A2, A3, A4, A5) CONST_METH) 
{ 
	typedef RT (FT)(A1, A2, A3, A4, A5); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[6];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	static FunctionType ft(inv, true, rt, args, 6); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5, class RT>
inline Type* type_of(const RT& (C::*)(A1, A2, A3, A4, A5) CONST_METH) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4, A5); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[6];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	static FunctionType ft(inv, true, rt, args, 6); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5, class RT>
inline Type* type_of(RT& (C::*)(A1, A2, A3, A4, A5) CONST_METH) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4, A5); 
	GenericInvoker inv = &InvokeGenericMRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[6];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	static FunctionType ft(inv, true, rt, args, 6); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5>
inline Type* type_of(void (C::*)(A1, A2, A3, A4, A5) CONST_METH) 
{ 
	typedef void (FT)(A1, A2, A3, A4, A5); 
	GenericInvoker inv = &InvokeGenericMNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref>;
	Type* rt = type_of<void>();
	Type* args[6];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	static FunctionType ft(inv, true, rt, args, 6); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
inline Type* type_of(RT (C::*)(A1, A2, A3, A4, A5, A6) CONST_METH) 
{ 
	typedef RT (FT)(A1, A2, A3, A4, A5, A6); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[7];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	args[6] = type_of<A6>();
	static FunctionType ft(inv, true, rt, args, 7); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
inline Type* type_of(const RT& (C::*)(A1, A2, A3, A4, A5, A6) CONST_METH) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4, A5, A6); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[7];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	args[6] = type_of<A6>();
	static FunctionType ft(inv, true, rt, args, 7); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
inline Type* type_of(RT& (C::*)(A1, A2, A3, A4, A5, A6) CONST_METH) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4, A5, A6); 
	GenericInvoker inv = &InvokeGenericMRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[7];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	args[6] = type_of<A6>();
	static FunctionType ft(inv, true, rt, args, 7); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5, class A6>
inline Type* type_of(void (C::*)(A1, A2, A3, A4, A5, A6) CONST_METH) 
{ 
	typedef void (FT)(A1, A2, A3, A4, A5, A6); 
	GenericInvoker inv = &InvokeGenericMNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref>;
	Type* rt = type_of<void>();
	Type* args[7];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	args[6] = type_of<A6>();
	static FunctionType ft(inv, true, rt, args, 7); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
inline Type* type_of(RT (C::*)(A1, A2, A3, A4, A5, A6, A7) CONST_METH) 
{ 
	typedef RT (FT)(A1, A2, A3, A4, A5, A6, A7); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[8];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	args[6] = type_of<A6>();
	args[7] = type_of<A7>();
	static FunctionType ft(inv, true, rt, args, 8); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
inline Type* type_of(const RT& (C::*)(A1, A2, A3, A4, A5, A6, A7) CONST_METH) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4, A5, A6, A7); 
	GenericInvoker inv = &InvokeGenericM<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, RT>;
	Type* rt = type_of<RT>();
	Type* args[8];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	args[6] = type_of<A6>();
	args[7] = type_of<A7>();
	static FunctionType ft(inv, true, rt, args, 8); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
inline Type* type_of(RT& (C::*)(A1, A2, A3, A4, A5, A6, A7) CONST_METH) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4, A5, A6, A7); 
	GenericInvoker inv = &InvokeGenericMRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[8];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	args[6] = type_of<A6>();
	args[7] = type_of<A7>();
	static FunctionType ft(inv, true, rt, args, 8); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline Type* type_of(void (C::*)(A1, A2, A3, A4, A5, A6, A7) CONST_METH) 
{ 
	typedef void (FT)(A1, A2, A3, A4, A5, A6, A7); 
	GenericInvoker inv = &InvokeGenericMNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref>;
	Type* rt = type_of<void>();
	Type* args[8];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	args[4] = type_of<A4>();
	args[5] = type_of<A5>();
	args[6] = type_of<A6>();
	args[7] = type_of<A7>();
	static FunctionType ft(inv, true, rt, args, 8); 
	return &ft;
}

//////////////////////////////////////////////////////////////////////////
