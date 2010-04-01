import sys
import io

MAX_PARAMS = int(sys.argv[1])

#=======================================================================================

function_creators = '''
//////////////////////////////////////////////////////////////////////////

template<%targs%, class RT>
inline function_type* type_of(RT (*)(%args%)) 
{ 
	typedef RT (FT)(%args%); 
	generic_invoker inv = &invoke_generic<FT, %sargs%, RT>; 
	Type* rt = type_of<RT>();
	Type* args[%nargs%];%fill_args%
	static function_type ft(inv, false, rt, args, %nargs%);
	return &ft;
}

template<%targs%, class RT>
inline function_type* type_of(const RT& (*)(%args%)) 
{ 
	typedef const RT& (FT)(%args%); 
	generic_invoker inv = &invoke_generic<FT, %sargs%, RT>; 
	Type* rt = type_of<RT>();
	Type* args[%nargs%];%fill_args%
	static function_type ft(inv, false, rt, args, %nargs%);
	return &ft;
}

template<%targs%, class RT>
inline function_type* type_of(RT& (*)(%args%)) 
{ 
	typedef RT& (FT)(%args%); 
	generic_invoker inv = &invoke_generic_ref<FT, %sargs%, RT>;
	Type* rt = type_of<RT*>();
	Type* args[%nargs%];%fill_args%
	static function_type ft(inv, false, rt, args, %nargs%);
	return &ft;
}

template<%targs%>
inline function_type* type_of(void (*)(%args%)) 
{ 
	typedef void (FT)(%args%); 
	generic_invoker inv = &invoke_generic_noret<FT, %sargs%>;
	Type* rt = type_of<void>();
	Type* args[%nargs%];%fill_args%
	static function_type ft(inv, false, rt, args, %nargs%);
	return &ft;
}
'''

method_creators = '''
//////////////////////////////////////////////////////////////////////////

template<class C, %targs%, class RT>
inline function_type* type_of(RT (C::*)(%args%) CONST_METH) 
{ 
	typedef RT (FT)(%args%); 
	generic_invoker inv = &invoke_generic_m<FT, %sargs%, RT>;
	type* rt = type_of<RT>();
	type* args[%nargs%];
	args[0] = type_of<C*>();%fill_args%
	static function_type ft(inv, true, rt, args, %nargs%); 
	return &ft;
}

template<class C, %targs%, class RT>
inline function_type* type_of(const RT& (C::*)(%args%) CONST_METH) 
{ 
	typedef const RT& (FT)(%args%); 
	generic_invoker inv = &invoke_generic_m<FT, %sargs%, RT>;
	type* rt = type_of<RT>();
	type* args[%nargs%];
	args[0] = type_of<C*>();%fill_args%
	static function_type ft(inv, true, rt, args, %nargs%); 
	return &ft;
}

template<class C, %targs%, class RT>
inline function_type* type_of(RT& (C::*)(%args%) CONST_METH) 
{ 
	typedef RT& (FT)(%args%); 
	generic_invoker inv = &invoke_generic_m_ref<FT, %sargs%, RT>;
	type* rt = type_of<RT*>();
	type* args[%nargs%];
	args[0] = type_of<C*>();%fill_args%
	static function_type ft(inv, true, rt, args, %nargs%); 
	return &ft;
}

template<class C, %targs%>
inline function_type* type_of(void (C::*)(%args%) CONST_METH) 
{ 
	typedef void (FT)(%args%); 
	generic_invoker inv = &invoke_generic_m_noret<FT, %sargs%>;
	type* rt = type_of<void>();
	type* args[%nargs%];
	args[0] = type_of<C*>();%fill_args%
	static function_type ft(inv, true, rt, args, %nargs%); 
	return &ft;
}

'''


#=======================================================================================

with open('function_typeof.inc', 'w') as file:

	for i in range(0, MAX_PARAMS + 1):
		
		block = function_creators		

		args = ""
		for j in range(1, i+1):
			args += "A" + str(j) + ", "

		sargs = ""
		for j in range(1, i+1):
			sargs += "t_strip<A" + str(j) + ">::noref, "


		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "
			
		fill_args = "\n\t"
		for j in range(0, i):
			fill_args += "args[" + str(j) + "] = type_of<A" + str(j+1) + ">();\n\t"

		block = block.replace("%args%", args[:-2])
		block = block.replace("%sargs%", sargs[:-2])
		block = block.replace("%targs%", targs[:-2])
		block = block.replace("%fill_args%", fill_args[:-2])
		block = block.replace("%nargs%", str(i))

		file.write(block)




	for i in range(0, MAX_PARAMS):
		
		block = method_creators		

		args = ""
		for j in range(1, i+1):
			args += "A" + str(j) + ", "

		sargs = ""
		for j in range(1, i+1):
			sargs += "t_strip<A" + str(j) + ">::noref, "


		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "
			
		fill_args = "\n\t"
		for j in range(1, i+1):
			fill_args += "args[" + str(j) + "] = type_of<A" + str(j) + ">();\n\t"

		block = block.replace("%args%", args[:-2])
		block = block.replace("%sargs%", sargs[:-2])
		block = block.replace("%targs%", targs[:-2])
		block = block.replace("%fill_args%", fill_args[:-2])
		block = block.replace("%nargs%", str(i+1))

		file.write(block)

