
//////////////////////////////////////////////////////////////////////////

template<class RT>
inline function_type* type_of(RT (*)()) 
{ 
	typedef RT (FT)(); 
	deleg_generic_invoke inv = &invoke_generic<FT, RT>; 
	type* rt = type_of<RT>();
	static function_type ft(inv, false, rt, 0, 0);
	return &ft;
}

template<class RT>
inline function_type* type_of(const RT& (*)()) 
{ 
	typedef const RT& (FT)(); 
	deleg_generic_invoke inv = &invoke_generic<FT, RT>; 
	type* rt = type_of<RT>();
	type* args[0];
	static function_type ft(inv, false, rt, args, 0);
	return &ft;
}

template<class RT>
inline function_type* type_of(RT& (*)()) 
{ 
	typedef RT& (FT)(); 
	deleg_generic_invoke inv = &invoke_generic_ref<FT, RT>;
	type* rt = type_of<RT*>();
	type* args[0];
	static function_type ft(inv, false, rt, args, 0);
	return &ft;
}

template<>
inline function_type* type_of(void (*)()) 
{ 
	typedef void (FT)(); 
	deleg_generic_invoke inv = &invoke_generic_noret<FT>;
	type* rt = type_of<void>();
	static function_type ft(inv, false, rt, 0, 0);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class RT>
inline function_type* type_of(RT (*)(A1)) 
{ 
	typedef RT (FT)(A1); 
	deleg_generic_invoke inv = &invoke_generic<FT, t_strip<A1>::noref, RT>; 
	type* rt = type_of<RT>();
	type* args[1];
	args[0] = type_of<A1>();
	static function_type ft(inv, false, rt, args, 1);
	return &ft;
}

template<class A1, class RT>
inline function_type* type_of(const RT& (*)(A1)) 
{ 
	typedef const RT& (FT)(A1); 
	deleg_generic_invoke inv = &invoke_generic<FT, t_strip<A1>::noref, RT>; 
	type* rt = type_of<RT>();
	type* args[1];
	args[0] = type_of<A1>();
	static function_type ft(inv, false, rt, args, 1);
	return &ft;
}

template<class A1, class RT>
inline function_type* type_of(RT& (*)(A1)) 
{ 
	typedef RT& (FT)(A1); 
	deleg_generic_invoke inv = &invoke_generic_ref<FT, t_strip<A1>::noref, RT>;
	type* rt = type_of<RT*>();
	type* args[1];
	args[0] = type_of<A1>();
	static function_type ft(inv, false, rt, args, 1);
	return &ft;
}

template<class A1>
inline function_type* type_of(void (*)(A1)) 
{ 
	typedef void (FT)(A1); 
	deleg_generic_invoke inv = &invoke_generic_noret<FT, t_strip<A1>::noref>;
	type* rt = type_of<void>();
	type* args[1];
	args[0] = type_of<A1>();
	static function_type ft(inv, false, rt, args, 1);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class RT>
inline function_type* type_of(RT (*)(A1, A2)) 
{ 
	typedef RT (FT)(A1, A2); 
	deleg_generic_invoke inv = &invoke_generic<FT, t_strip<A1>::noref, t_strip<A2>::noref, RT>; 
	type* rt = type_of<RT>();
	type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static function_type ft(inv, false, rt, args, 2);
	return &ft;
}

template<class A1, class A2, class RT>
inline function_type* type_of(const RT& (*)(A1, A2)) 
{ 
	typedef const RT& (FT)(A1, A2); 
	deleg_generic_invoke inv = &invoke_generic<FT, t_strip<A1>::noref, t_strip<A2>::noref, RT>; 
	type* rt = type_of<RT>();
	type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static function_type ft(inv, false, rt, args, 2);
	return &ft;
}

template<class A1, class A2, class RT>
inline function_type* type_of(RT& (*)(A1, A2)) 
{ 
	typedef RT& (FT)(A1, A2); 
	deleg_generic_invoke inv = &invoke_generic_ref<FT, t_strip<A1>::noref, t_strip<A2>::noref, RT>;
	type* rt = type_of<RT*>();
	type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static function_type ft(inv, false, rt, args, 2);
	return &ft;
}

template<class A1, class A2>
inline function_type* type_of(void (*)(A1, A2)) 
{ 
	typedef void (FT)(A1, A2); 
	deleg_generic_invoke inv = &invoke_generic_noret<FT, t_strip<A1>::noref, t_strip<A2>::noref>;
	type* rt = type_of<void>();
	type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static function_type ft(inv, false, rt, args, 2);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class RT>
inline function_type* type_of(RT (*)(A1, A2, A3)) 
{ 
	typedef RT (FT)(A1, A2, A3); 
	deleg_generic_invoke inv = &invoke_generic<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, RT>; 
	type* rt = type_of<RT>();
	type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static function_type ft(inv, false, rt, args, 3);
	return &ft;
}

template<class A1, class A2, class A3, class RT>
inline function_type* type_of(const RT& (*)(A1, A2, A3)) 
{ 
	typedef const RT& (FT)(A1, A2, A3); 
	deleg_generic_invoke inv = &invoke_generic<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, RT>; 
	type* rt = type_of<RT>();
	type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static function_type ft(inv, false, rt, args, 3);
	return &ft;
}

template<class A1, class A2, class A3, class RT>
inline function_type* type_of(RT& (*)(A1, A2, A3)) 
{ 
	typedef RT& (FT)(A1, A2, A3); 
	deleg_generic_invoke inv = &invoke_generic_ref<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, RT>;
	type* rt = type_of<RT*>();
	type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static function_type ft(inv, false, rt, args, 3);
	return &ft;
}

template<class A1, class A2, class A3>
inline function_type* type_of(void (*)(A1, A2, A3)) 
{ 
	typedef void (FT)(A1, A2, A3); 
	deleg_generic_invoke inv = &invoke_generic_noret<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref>;
	type* rt = type_of<void>();
	type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static function_type ft(inv, false, rt, args, 3);
	return &ft;
}

//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class A4, class RT>
inline function_type* type_of(RT (*)(A1, A2, A3, A4)) 
{ 
	typedef RT (FT)(A1, A2, A3, A4); 
	deleg_generic_invoke inv = &invoke_generic<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, t_strip<A4>::noref, RT>; 
	type* rt = type_of<RT>();
	type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static function_type ft(inv, false, rt, args, 4);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class RT>
inline function_type* type_of(const RT& (*)(A1, A2, A3, A4)) 
{ 
	typedef const RT& (FT)(A1, A2, A3, A4); 
	deleg_generic_invoke inv = &invoke_generic<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, t_strip<A4>::noref, RT>; 
	type* rt = type_of<RT>();
	type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static function_type ft(inv, false, rt, args, 4);
	return &ft;
}

template<class A1, class A2, class A3, class A4, class RT>
inline function_type* type_of(RT& (*)(A1, A2, A3, A4)) 
{ 
	typedef RT& (FT)(A1, A2, A3, A4); 
	deleg_generic_invoke inv = &invoke_generic_ref<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, t_strip<A4>::noref, RT>;
	type* rt = type_of<RT*>();
	type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static function_type ft(inv, false, rt, args, 4);
	return &ft;
}

template<class A1, class A2, class A3, class A4>
inline function_type* type_of(void (*)(A1, A2, A3, A4)) 
{ 
	typedef void (FT)(A1, A2, A3, A4); 
	deleg_generic_invoke inv = &invoke_generic_noret<FT, t_strip<A1>::noref, t_strip<A2>::noref, t_strip<A3>::noref, t_strip<A4>::noref>;
	type* rt = type_of<void>();
	type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static function_type ft(inv, false, rt, args, 4);
	return &ft;
}
