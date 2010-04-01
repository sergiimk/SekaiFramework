template<class C, class RT>
inline function_type* type_of(RT (C::*)() CONST_METH) 
{ 
	typedef RT (FT)(); 
	generic_invoker inv = &invoke_generic_m<FT, RT>;
	type* rt = type_of<RT>();
	type* args[1];
	args[0] = type_of<C*>();
	static function_type ft(inv, true, rt, args, 1); 
	return &ft;
}

template<class C, class RT>
inline function_type* type_of(const RT& (C::*)() CONST_METH) 
{ 
	typedef const RT& (FT)(); 
	generic_invoker inv = &invoke_generic_m<FT, RT>;
	type* rt = type_of<RT>();
	type* args[1];
	args[0] = type_of<C*>();
	static function_type ft(inv, true, rt, args, 1); 
	return &ft;
}

template<class C, class RT>
inline function_type* type_of(RT& (C::*)() CONST_METH) 
{ 
	typedef RT& (FT)(); 
	generic_invoker inv = &invoke_generic_m_ref<FT, RT>;
	type* rt = type_of<RT*>();
	type* args[1];
	args[0] = type_of<C*>();
	static function_type ft(inv, true, rt, args, 1); 
	return &ft;
}

template<class C>
inline function_type* type_of(void (C::*)() CONST_METH) 
{ 
	typedef void (FT)(); 
	generic_invoker inv = &invoke_generic_m_noret<FT>;
	type* rt = type_of<void>();
	type* args[1];
	args[0] = type_of<C*>();
	static function_type ft(inv, true, rt, args, 1); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class RT>
inline function_type* type_of(RT (C::*)(A1) CONST_METH) 
{ 
	typedef RT (FT)(A1); 
	generic_invoker inv = &invoke_generic_m<FT, t_strip<A1>::noref, RT>;
	type* rt = type_of<RT>();
	type* args[2];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	static function_type ft(inv, true, rt, args, 2); 
	return &ft;
}

template<class C, class A1, class RT>
inline function_type* type_of(const RT& (C::*)(A1) CONST_METH) 
{ 
	typedef const RT& (FT)(A1); 
	generic_invoker inv = &invoke_generic_m<FT, t_strip<A1>::noref, RT>;
	type* rt = type_of<RT>();
	type* args[2];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	static function_type ft(inv, true, rt, args, 2); 
	return &ft;
}

template<class C, class A1, class RT>
inline function_type* type_of(RT& (C::*)(A1) CONST_METH) 
{ 
	typedef RT& (FT)(A1); 
	generic_invoker inv = &invoke_generic_m_ref<FT, t_strip<A1>::noref, RT>;
	type* rt = type_of<RT*>();
	type* args[2];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	static function_type ft(inv, true, rt, args, 2); 
	return &ft;
}

template<class C, class A1>
inline function_type* type_of(void (C::*)(A1) CONST_METH) 
{ 
	typedef void (FT)(A1); 
	generic_invoker inv = &invoke_generic_m_noret<FT, t_strip<A1>::noref>;
	type* rt = type_of<void>();
	type* args[2];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	static function_type ft(inv, true, rt, args, 2); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class A2, class RT>
inline function_type* type_of(RT (C::*)(A1, A2) CONST_METH) 
{ 
	typedef RT (FT)(A1, A2); 
	generic_invoker inv = &invoke_generic_m<FT, t_strip<A1>::noref, t_strip<A2>::noref, RT>;
	type* rt = type_of<RT>();
	type* args[3];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	static function_type ft(inv, true, rt, args, 3); 
	return &ft;
}

template<class C, class A1, class A2, class RT>
inline function_type* type_of(const RT& (C::*)(A1, A2) CONST_METH) 
{ 
	typedef const RT& (FT)(A1, A2); 
	generic_invoker inv = &invoke_generic_m<FT, t_strip<A1>::noref, t_strip<A2>::noref, RT>;
	type* rt = type_of<RT>();
	type* args[3];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	static function_type ft(inv, true, rt, args, 3); 
	return &ft;
}

template<class C, class A1, class A2, class RT>
inline function_type* type_of(RT& (C::*)(A1, A2) CONST_METH) 
{ 
	typedef RT& (FT)(A1, A2); 
	generic_invoker inv = &invoke_generic_m_ref<FT, t_strip<A1>::noref, t_strip<A2>::noref, RT>;
	type* rt = type_of<RT*>();
	type* args[3];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	static function_type ft(inv, true, rt, args, 3); 
	return &ft;
}

template<class C, class A1, class A2>
inline function_type* type_of(void (C::*)(A1, A2) CONST_METH) 
{ 
	typedef void (FT)(A1, A2); 
	generic_invoker inv = &invoke_generic_m_noret<FT, t_strip<A1>::noref, t_strip<A2>::noref>;
	type* rt = type_of<void>();
	type* args[3];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	static function_type ft(inv, true, rt, args, 3); 
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class C, class A1, class A2, class A3, class RT>
inline function_type* type_of(RT (C::*)(A1, A2, A3) CONST_METH) 
{ 
	typedef RT (FT)(A1, A2, A3); 
	generic_invoker inv = &invoke_generic_m<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, RT>;
	type* rt = type_of<RT>();
	type* args[4];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	static function_type ft(inv, true, rt, args, 4); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class RT>
inline function_type* type_of(const RT& (C::*)(A1, A2, A3) CONST_METH) 
{ 
	typedef const RT& (FT)(A1, A2, A3); 
	generic_invoker inv = &invoke_generic_m<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, RT>;
	type* rt = type_of<RT>();
	type* args[4];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	static function_type ft(inv, true, rt, args, 4); 
	return &ft;
}

template<class C, class A1, class A2, class A3, class RT>
inline function_type* type_of(RT& (C::*)(A1, A2, A3) CONST_METH) 
{ 
	typedef RT& (FT)(A1, A2, A3); 
	generic_invoker inv = &invoke_generic_m_ref<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, RT>;
	type* rt = type_of<RT*>();
	type* args[4];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	static function_type ft(inv, true, rt, args, 4); 
	return &ft;
}

template<class C, class A1, class A2, class A3>
inline function_type* type_of(void (C::*)(A1, A2, A3) CONST_METH) 
{ 
	typedef void (FT)(A1, A2, A3); 
	generic_invoker inv = &invoke_generic_m_noret<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref>;
	type* rt = type_of<void>();
	type* args[4];
	args[0] = type_of<C*>();
	args[1] = type_of<A1>();
	args[2] = type_of<A2>();
	args[3] = type_of<A3>();
	static function_type ft(inv, true, rt, args, 4); 
	return &ft;
}
