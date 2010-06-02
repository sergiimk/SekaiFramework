
//////////////////////////////////////////////////////////////////////////

template<class RT>
inline function_type* type_of(RT (*)()) 
{ 
	typedef RT (FT)(); 
	type* rt = type_of<RT>();
	static function_type ft(false, rt, 0, 0);
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class A1, class RT>
inline function_type* type_of(RT (*)(A1)) 
{ 
	typedef RT (FT)(A1); 
	type* rt = type_of<RT>();
	type* args[1];
	args[0] = type_of<A1>();
	static function_type ft(false, rt, args, 1);
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class RT>
inline function_type* type_of(RT (*)(A1, A2)) 
{ 
	typedef RT (FT)(A1, A2); 
	type* rt = type_of<RT>();
	type* args[2];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	static function_type ft(false, rt, args, 2);
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class RT>
inline function_type* type_of(RT (*)(A1, A2, A3)) 
{ 
	typedef RT (FT)(A1, A2, A3); 
	type* rt = type_of<RT>();
	type* args[3];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	static function_type ft(false, rt, args, 3);
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class A4, class RT>
inline function_type* type_of(RT (*)(A1, A2, A3, A4)) 
{ 
	typedef RT (FT)(A1, A2, A3, A4); 
	type* rt = type_of<RT>();
	type* args[4];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	static function_type ft(false, rt, args, 4);
	return &ft;
}


//////////////////////////////////////////////////////////////////////////

template<class A1, class A2, class A3, class A4, class A5, class RT>
inline function_type* type_of(RT (*)(A1, A2, A3, A4, A5)) 
{ 
	typedef RT (FT)(A1, A2, A3, A4, A5); 
	type* rt = type_of<RT>();
	type* args[5];
	args[0] = type_of<A1>();
	args[1] = type_of<A2>();
	args[2] = type_of<A3>();
	args[3] = type_of<A4>();
	args[4] = type_of<A5>();
	static function_type ft(false, rt, args, 5);
	return &ft;
}



