
//////////////////////////////////////////////////////////////////////////

template<class RT>
inline Type* type_of(RT (*)()) 
{ 
	typedef RT (FT)(); 
	GenericInvoker inv = &InvokeGeneric<FT, RT>; 
	Type* rt = type_of<RT>();
	static FunctionType ft(inv, false, rt, 0, 0);
	return &ft;
}

template<class RT>
inline Type* type_of(const RT& (*)()) 
{ 
	typedef const RT& (FT)(); 
	GenericInvoker inv = &InvokeGeneric<FT, RT>; 
	Type* rt = type_of<RT>();
	static FunctionType ft(inv, false, rt, 0, 0);
	return &ft;
}

template<class RT>
inline Type* type_of(RT& (*)()) 
{ 
	typedef RT& (FT)(); 
	GenericInvoker inv = &InvokeGenericRef<FT, RT>;
	Type* rt = type_of<RT*>();
	static FunctionType ft(inv, false, rt, 0, 0);
	return &ft;
}

template<>
inline Type* type_of(void (*)()) 
{ 
	typedef void (FT)(); 
	GenericInvoker inv = &InvokeGenericNoret<FT>;
	Type* rt = type_of<void>();
	static FunctionType ft(inv, false, rt, 0, 0);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class RT>
inline Type* type_of(RT (*)(A1)) 
{ 
	typedef RT (FT)(A1); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[1];
	args[0] = type_of<A1>();
	static FunctionType ft(inv, false, rt, args, 1);
	return &ft;
}

template<class A1, class RT>
inline Type* type_of(const RT& (*)(A1)) 
{ 
	typedef const RT& (FT)(A1); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[1];
	args[0] = type_of<A1>();
	static FunctionType ft(inv, false, rt, args, 1);
	return &ft;
}

template<class A1, class RT>
inline Type* type_of(RT& (*)(A1)) 
{ 
	typedef RT& (FT)(A1); 
	GenericInvoker inv = &InvokeGenericRef<FT, typename Utils::TStripType<A1>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[1];
	args[0] = type_of<A1>();
	static FunctionType ft(inv, false, rt, args, 1);
	return &ft;
}

template<class A1>
inline Type* type_of(void (*)(A1)) 
{ 
	typedef void (FT)(A1); 
	GenericInvoker inv = &InvokeGenericNoret<FT, typename Utils::TStripType<A1>::noref>;
	Type* rt = type_of<void>();
	Type* args[1];
	args[0] = type_of<A1>();
	static FunctionType ft(inv, false, rt, args, 1);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class RT>
inline Type* type_of(RT (*)(A1, A2)) 
{ 
	typedef RT (FT)(A1, A2); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static FunctionType ft(inv, false, rt, args, 2);
	return &ft;
}

template<class A1, class A2, class RT>
inline Type* type_of(const RT& (*)(A1, A2)) 
{ 
	typedef const RT& (FT)(A1, A2); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static FunctionType ft(inv, false, rt, args, 2);
	return &ft;
}

template<class A1, class A2, class RT>
inline Type* type_of(RT& (*)(A1, A2)) 
{ 
	typedef RT& (FT)(A1, A2); 
	GenericInvoker inv = &InvokeGenericRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static FunctionType ft(inv, false, rt, args, 2);
	return &ft;
}

template<class A1, class A2>
inline Type* type_of(void (*)(A1, A2)) 
{ 
	typedef void (FT)(A1, A2); 
	GenericInvoker inv = &InvokeGenericNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref>;
	Type* rt = type_of<void>();
	Type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static FunctionType ft(inv, false, rt, args, 2);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class RT>
inline Type* type_of(RT (*)(A1, A2, A3)) 
{ 
	typedef RT (FT)(A1, A2, A3); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static FunctionType ft(inv, false, rt, args, 3);
	return &ft;
}

template<class A1, class A2, class A3, class RT>
inline Type* type_of(const RT& (*)(A1, A2, A3)) 
{ 
	typedef const RT& (FT)(A1, A2, A3); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static FunctionType ft(inv, false, rt, args, 3);
	return &ft;
}

template<class A1, class A2, class A3, class RT>
inline Type* type_of(RT& (*)(A1, A2, A3)) 
{ 
	typedef RT& (FT)(A1, A2, A3); 
	GenericInvoker inv = &InvokeGenericRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static FunctionType ft(inv, false, rt, args, 3);
	return &ft;
}

template<class A1, class A2, class A3>
inline Type* type_of(void (*)(A1, A2, A3)) 
{ 
	typedef void (FT)(A1, A2, A3); 
	GenericInvoker inv = &InvokeGenericNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref>;
	Type* rt = type_of<void>();
	Type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static FunctionType ft(inv, false, rt, args, 3);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class A4, class RT>
inline Type* type_of(RT (*)(A1, A2, A3, A4)) 
{ 
	typedef RT (FT)(A1, A2, A3, A4); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static FunctionType ft(inv, false, rt, args, 4);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class RT>
inline Type* type_of(const RT& (*)(A1, A2, A3, A4)) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static FunctionType ft(inv, false, rt, args, 4);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class RT>
inline Type* type_of(RT& (*)(A1, A2, A3, A4)) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4); 
	GenericInvoker inv = &InvokeGenericRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static FunctionType ft(inv, false, rt, args, 4);
	return &ft;
}

template<class A1, class A2, class A3, class A4>
inline Type* type_of(void (*)(A1, A2, A3, A4)) 
{ 
	typedef void (FT)(A1, A2, A3, A4); 
	GenericInvoker inv = &InvokeGenericNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref>;
	Type* rt = type_of<void>();
	Type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static FunctionType ft(inv, false, rt, args, 4);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class A4, class A5, class RT>
inline Type* type_of(RT (*)(A1, A2, A3, A4, A5)) 
{ 
	typedef RT (FT)(A1, A2, A3, A4, A5); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[5];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	static FunctionType ft(inv, false, rt, args, 5);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class RT>
inline Type* type_of(const RT& (*)(A1, A2, A3, A4, A5)) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4, A5); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[5];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	static FunctionType ft(inv, false, rt, args, 5);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class RT>
inline Type* type_of(RT& (*)(A1, A2, A3, A4, A5)) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4, A5); 
	GenericInvoker inv = &InvokeGenericRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[5];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	static FunctionType ft(inv, false, rt, args, 5);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5>
inline Type* type_of(void (*)(A1, A2, A3, A4, A5)) 
{ 
	typedef void (FT)(A1, A2, A3, A4, A5); 
	GenericInvoker inv = &InvokeGenericNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref>;
	Type* rt = type_of<void>();
	Type* args[5];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	static FunctionType ft(inv, false, rt, args, 5);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class A4, class A5, class A6, class RT>
inline Type* type_of(RT (*)(A1, A2, A3, A4, A5, A6)) 
{ 
	typedef RT (FT)(A1, A2, A3, A4, A5, A6); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[6];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	static FunctionType ft(inv, false, rt, args, 6);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6, class RT>
inline Type* type_of(const RT& (*)(A1, A2, A3, A4, A5, A6)) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4, A5, A6); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[6];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	static FunctionType ft(inv, false, rt, args, 6);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6, class RT>
inline Type* type_of(RT& (*)(A1, A2, A3, A4, A5, A6)) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4, A5, A6); 
	GenericInvoker inv = &InvokeGenericRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[6];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	static FunctionType ft(inv, false, rt, args, 6);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6>
inline Type* type_of(void (*)(A1, A2, A3, A4, A5, A6)) 
{ 
	typedef void (FT)(A1, A2, A3, A4, A5, A6); 
	GenericInvoker inv = &InvokeGenericNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref>;
	Type* rt = type_of<void>();
	Type* args[6];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	static FunctionType ft(inv, false, rt, args, 6);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
inline Type* type_of(RT (*)(A1, A2, A3, A4, A5, A6, A7)) 
{ 
	typedef RT (FT)(A1, A2, A3, A4, A5, A6, A7); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[7];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	args[6] = type_of<A7>();
	static FunctionType ft(inv, false, rt, args, 7);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
inline Type* type_of(const RT& (*)(A1, A2, A3, A4, A5, A6, A7)) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4, A5, A6, A7); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[7];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	args[6] = type_of<A7>();
	static FunctionType ft(inv, false, rt, args, 7);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
inline Type* type_of(RT& (*)(A1, A2, A3, A4, A5, A6, A7)) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4, A5, A6, A7); 
	GenericInvoker inv = &InvokeGenericRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[7];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	args[6] = type_of<A7>();
	static FunctionType ft(inv, false, rt, args, 7);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline Type* type_of(void (*)(A1, A2, A3, A4, A5, A6, A7)) 
{ 
	typedef void (FT)(A1, A2, A3, A4, A5, A6, A7); 
	GenericInvoker inv = &InvokeGenericNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref>;
	Type* rt = type_of<void>();
	Type* args[7];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	args[6] = type_of<A7>();
	static FunctionType ft(inv, false, rt, args, 7);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
inline Type* type_of(RT (*)(A1, A2, A3, A4, A5, A6, A7, A8)) 
{ 
	typedef RT (FT)(A1, A2, A3, A4, A5, A6, A7, A8); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, typename Utils::TStripType<A8>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[8];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	args[6] = type_of<A7>();
	args[7] = type_of<A8>();
	static FunctionType ft(inv, false, rt, args, 8);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
inline Type* type_of(const RT& (*)(A1, A2, A3, A4, A5, A6, A7, A8)) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4, A5, A6, A7, A8); 
	GenericInvoker inv = &InvokeGeneric<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, typename Utils::TStripType<A8>::noref, RT>; 
	Type* rt = type_of<RT>();
	Type* args[8];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	args[6] = type_of<A7>();
	args[7] = type_of<A8>();
	static FunctionType ft(inv, false, rt, args, 8);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
inline Type* type_of(RT& (*)(A1, A2, A3, A4, A5, A6, A7, A8)) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4, A5, A6, A7, A8); 
	GenericInvoker inv = &InvokeGenericRef<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, typename Utils::TStripType<A8>::noref, RT>;
	Type* rt = type_of<RT*>();
	Type* args[8];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	args[6] = type_of<A7>();
	args[7] = type_of<A8>();
	static FunctionType ft(inv, false, rt, args, 8);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline Type* type_of(void (*)(A1, A2, A3, A4, A5, A6, A7, A8)) 
{ 
	typedef void (FT)(A1, A2, A3, A4, A5, A6, A7, A8); 
	GenericInvoker inv = &InvokeGenericNoret<FT, typename Utils::TStripType<A1>::noref, typename Utils::TStripType<A2>::noref, typename Utils::TStripType<A3>::noref, typename Utils::TStripType<A4>::noref, typename Utils::TStripType<A5>::noref, typename Utils::TStripType<A6>::noref, typename Utils::TStripType<A7>::noref, typename Utils::TStripType<A8>::noref>;
	Type* rt = type_of<void>();
	Type* args[8];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	args[5] = type_of<A6>();
	args[6] = type_of<A7>();
	args[7] = type_of<A8>();
	static FunctionType ft(inv, false, rt, args, 8);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////
